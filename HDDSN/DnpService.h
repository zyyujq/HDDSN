
#pragma once

#include <winsvc.h>
#include "atlstr.h"

class	CDnpService
{
	//
	//	启动/停止服务线程类
	//
	class CServiceThread
	{
	public:
		CServiceThread()
		{
			_bCancel = false;
		}

	private:

		bool					_bCancel;			//服务启动/停止处理中断用变量，如果为真则中断开始
		CComAutoCriticalSection	_secbCancel;		//启动/停止服务中断的关键部分

	public:

		//
		//	服务启动/停止处理中断用函数
		//
		//	如果要暂停，请调用IsCancel（true，true）
		//
		bool	IsCancel(bool bSave = false, bool bNewValue = false)
		{
			bool	ret;

			_secbCancel.Lock();
			if (bSave)
			{
				_bCancel = bNewValue;
				ret = true;
			}
			else
				ret = _bCancel;
			_secbCancel.Unlock();

			return	ret;
		}



		//
        //简化服务控制
        //
        //如果直接调用，则在无限循环中等待服务启动/停止。
        //在线程中调用，通过使用IsCancel（）不陷入无限循环
        //可控制。
		//
		bool EasyStartStop(LPCTSTR pszName, bool b)
		{
			//bool			ret = false;
			BOOL			bRet = FALSE;
			SC_HANDLE		hManager = NULL;
			SC_HANDLE		hService = NULL;
			SERVICE_STATUS	sStatus;

			hManager = ::OpenSCManager(NULL, NULL, GENERIC_EXECUTE);
			if (hManager == NULL)
			{
				return false;
			}

			hService = ::OpenService(hManager, pszName, SERVICE_START | SERVICE_QUERY_STATUS);
			if (hService == NULL)
			{
				if (hManager) { ::CloseServiceHandle(hManager); }
				return false;
			}

			::ZeroMemory(&sStatus, sizeof(SERVICE_STATUS));
			bRet = ::QueryServiceStatus(hService, &sStatus);
			if (bRet == FALSE)
			{
				if (hService) { ::CloseServiceHandle(hService); }
				if (hManager) { ::CloseServiceHandle(hManager); }
				return false;
			}

			if (sStatus.dwCurrentState == SERVICE_RUNNING)
			{
				if (hService) { ::CloseServiceHandle(hService); }
				if (hManager) { ::CloseServiceHandle(hManager); }
				return true;
			}

			CString cstr;
			cstr.Format(_T("sStatus.dwCurrentState:%08X"), sStatus.dwCurrentState);
			DebugPrint(cstr);

			//服务启动请求
			DebugPrint(_T("StartService - 1"));
			bRet = ::StartService(hService, NULL, NULL);

			//在无限循环中等待开始
			DebugPrint(_T("QueryServiceStatus - 1"));
			int count = 0;
			while (::QueryServiceStatus(hService, &sStatus))
			{
				// 避免无限循环（最多等待WMI初始化1秒）
				if (count >= 4)
				{
					break;
				}

				if (sStatus.dwCurrentState == SERVICE_RUNNING)
				{
					DebugPrint(_T("StartService Completed : SERVICE_RUNNING"));
					if (hService) { ::CloseServiceHandle(hService); }
					if (hManager) { ::CloseServiceHandle(hManager); }
					return true;
				}

				::Sleep(100 * count);
				DebugPrint(_T("Sleep"));
				count++;
			}

			// 将服务启动模式强制更改为auto
			ShellExecute(NULL, NULL, _T("sc"), _T("config Winmgmt start= auto"), NULL, SW_HIDE);
			count = 0;
			DebugPrint(_T("QueryServiceStatus - 2"));
			while (::QueryServiceStatus(hService, &sStatus))
			{
				//服务启动请求
				DebugPrint(_T("StartService - 2"));
				::StartService(hService, NULL, NULL);

				// 避免无限循环（最多等待5秒钟WMI初始化）
				if (count >= 10)
				{
					break;
				}

				if (sStatus.dwCurrentState == SERVICE_RUNNING)
				{
					DebugPrint(_T("StartService Completed : SERVICE_RUNNING"));
					if (hService) { ::CloseServiceHandle(hService); }
					if (hManager) { ::CloseServiceHandle(hManager); }
					return true;
				}

				::Sleep(500);
				DebugPrint(_T("Sleep"));
				count++;
			}

			if (hService) { ::CloseServiceHandle(hService); }
			if (hManager) { ::CloseServiceHandle(hManager); }
			return false;
		}
	};


public:


	//
    //简化服务控制
    //
    //在无限循环中等待服务启动/停止。
	//
	bool	EasyStartStop(LPCTSTR pszName, bool bStart)
	{
		CServiceThread	cThread;

		return	cThread.EasyStartStop(pszName, bStart);
	}


	//
    //快速启动服务
    //
    //在无限循环中等待服务启动。
	//
	bool	EasyStart(LPCTSTR pszName)
	{
		return	EasyStartStop(pszName, true);
	}

	//
    //快速停止服务
    //
    //在无限循环中等待服务停止。
	//
	bool	EasyStop(LPCTSTR pszName)
	{
		return	EasyStartStop(pszName, false);
	}


	//
    //快速重新启动服务
    //
    //在无限循环中等待服务重新启动。
	//
	bool	EasyRestart(LPCTSTR pszName)
	{
		bool			ret;
		CServiceThread	cThread;

		ret = cThread.EasyStartStop(pszName, false);
		if (ret)
			ret = cThread.EasyStartStop(pszName, true);

		return	ret;
	}



	//
    //检查指定的服务是否在运行
    //
    //在false的情况下不一定是“停止”。服务不存在的情况等也成为假。
	//
	bool	IsServiceRunning(LPCTSTR pszName)
	{
		bool			ret;
		BOOL			bRet;
		SC_HANDLE		hManager;
		SC_HANDLE		hService;
		SERVICE_STATUS	sStatus;

		ret = false;
		hManager = NULL;
		hService = NULL;
		while (1)			//不是无限循环！
		{
			hManager = ::OpenSCManager(NULL, NULL, GENERIC_EXECUTE);
			ATLASSERT(hManager);
			if (hManager == NULL)
				break;

			hService = ::OpenService(hManager, pszName, SERVICE_QUERY_STATUS);
			ATLASSERT(hService);
			if (hService == NULL)
				break;

			::ZeroMemory(&sStatus, sizeof(SERVICE_STATUS));
			bRet = ::QueryServiceStatus(hService, &sStatus);
			ATLASSERT(bRet);
			if (bRet == FALSE)
				break;

			if (sStatus.dwCurrentState == SERVICE_RUNNING)
				ret = true;

			break;		//必须
		}

		if (hService)
			::CloseServiceHandle(hService);
		if (hManager)
			::CloseServiceHandle(hManager);

		return	ret;
	}
};
