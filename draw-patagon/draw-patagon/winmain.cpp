#include <windows.h>

long WINAPI WndProc(HWND hWnd, UINT iMessage, UINT wParam, LONG lParam);			//消息处理函数声明

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG Message;										//定义消息变量
	HWND hWnd;										//定义窗口句柄
	WNDCLASS WndClass;									//定义窗口类
	WndClass.cbClsExtra = 0;								//无窗口类扩展
	WndClass.cbWndExtra = 0;								//无窗口实例扩展
	WndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));	//背景为白色
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);			//窗口采用箭头光标
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			//采用缺省图标
	WndClass.hInstance = hInstance;						//当前应用程序句柄
	WndClass.lpfnWndProc = WndProc;						//窗口处理函数
	WndClass.lpszClassName = L"SIN";						//窗口类名称
	WndClass.lpszMenuName = NULL;							//无窗口菜单
	WndClass.style = 0;									//窗口类型为缺省类型

	if (!RegisterClass(&WndClass))						//注册窗口
	{
		MessageBeep(0);
		return FALSE;
	}

	hWnd = CreateWindow(L"PATAGON",							//窗口类名
		L"等边五边形",			//标题名
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,						//窗口左上角坐标
		0,
		CW_USEDEFAULT,						//采用缺省的宽度和高度
		0,
		NULL,							//无父窗口
		NULL,							//无主菜单
		hInstance,						//当前实例句柄
		NULL);							//不要此参数
	ShowWindow(hWnd, nCmdShow);							//显示窗口
	UpdateWindow(hWnd);								//更新并绘制用户区

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);						//消息循环
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

long WINAPI WndProc(HWND hWnd, UINT iMessage, UINT wParam, LONG lParam)			//消息处理函数
{
	HDC hDC;											//定义设备环境句柄
	HBRUSH hBrush;										//定义画刷句柄
	HPEN hPen;											//定义画笔句柄
	PAINTSTRUCT PtStr;									//定义包含绘图信息的结构体变量
	switch (iMessage)
	{
	case WM_PAINT:										//处理绘图消息
		hDC = BeginPaint(hWnd, &PtStr);						//获得设备环境指针
		
		EndPaint(hWnd, &PtStr);							//删除设备环境句柄
		break;
	case WM_DESTROY:									//关闭窗口
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	}
	return 0;
}