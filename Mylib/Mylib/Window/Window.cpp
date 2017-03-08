#include"Mylib\Window\Window.h"

#include<string>
#include<tchar.h>
#include<Windows.h>
#include<mmsystem.h>

using namespace std;
using namespace Mylib;

#define IDI_WINDOWCREATOR			101
#define IDI_SMALL				102
#define IDC_WINDOWCREATOR			103

namespace Mylib {
	namespace {
		class Impl {	// 実際の値を持っているクラス
		public:
			Impl() :
				mWidth{ 640 },
				mHeight{ 480 },
				mTitle{ "My_lib default" },
				mCommandline{ 0 },
				mEnd_requested{ false },
				mEnded{ false },
				mStarted{ false },
				mActive{ false },
				mMinimized{ false },
				mMousewheel{ 0 }
			{
			}

			~Impl() {
			}

			int mWidth;
			int mHeight;
			string mTitle;
			string mCommandline;
			bool mEnd_requested;
			bool mEnded;
			bool mStarted;
			bool mActive;
			bool mMinimized;
			int mMousewheel;
			HWND mHwnd;		// このハンドルを使い続ける
			RECT mRect;
		};

		Impl* gWindow = 0;	// 外ではWindowクラスのように振る舞う
	}

	Window::Window() {
	}

	Window::~Window() {
	}

	Window Window::instance() {
		return Window();
	}

	const char* Window::get_title() const {
		return gWindow->mTitle.c_str();
	}

	const char* Window::get_commandline_string() const {
		return gWindow->mCommandline.c_str();
	}

	int Window::get_title_length() const {
		return static_cast<int>(gWindow->mTitle.size());
	}

	int Window::get_height() const {
		return gWindow->mHeight;
	}

	int Window::get_width() const {
		return gWindow->mWidth;
	}

	bool Window::is_end_requested() const {
		return gWindow->mEnd_requested;
	}

	void Window::request_end() {
		gWindow->mEnd_requested = true;
	}

	void Window::end() {
		gWindow->mEnded = true;
	}

	bool Window::is_active() const {
		return gWindow->mActive;
	}

	bool Window::is_minimized() const {
		return gWindow->mMinimized;
	}

	unsigned Window::get_time() const {
		return timeGetTime();
	}

	void Window::sleep(int ms) const {
		Sleep(ms);
	}

	int Window::get_and_reset_mousewheel() {
		int t = gWindow->mMousewheel;
		gWindow->mMousewheel = 0;
		return t;
	}

	// コンフィグ
	void Window::Configuration::set_width(int w) {
		gWindow->mWidth = w;
	}

	void Window::Configuration::set_height(int h) {
		gWindow->mHeight = h;
	}

	void Window::Configuration::set_title(const char* title) {
		gWindow->mTitle = title;
	}
}
	// 以下Windowプログラミング

#define MAX_LOADSTRING 100

	// グローバル変数:
	HINSTANCE hInst;								// 現在のインターフェイス
	TCHAR szTitle[MAX_LOADSTRING];					// タイトル バーのテキスト
	TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名
													// このコード モジュールに含まれる関数の宣言を転送します:
	BOOL				InitInstance(HINSTANCE, int);
	ATOM				MyRegisterClass(HINSTANCE hInstance);
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


	int APIENTRY _tWinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPTSTR    lpCmdLine,
		int       nCmdShow)
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		UNREFERENCED_PARAMETER(hPrevInstance);
		UNREFERENCED_PARAMETER(lpCmdLine);

		MSG msg;

		// ウィンドウ状態保持クラス生成
		gWindow = new Impl;
		Window win = Window::instance();
		// コンフィグ関数呼び出し
		Window::Configuration config;
		win.configure(&config);

		memcpy(szTitle, win.get_title(), win.get_title_length());
		memcpy(szWindowClass, "My_lib Window makeing", sizeof("My_lib Window makeing"));

		MyRegisterClass(hInstance);

		// アプリケーションの初期化を実行します:
		if (!InitInstance(hInstance, nCmdShow)) {
			return FALSE;
		}

		timeBeginPeriod(1);
		HWND window_handle = gWindow->mHwnd;
		// 例外が発生したら、メッセージボックスを出して終わらせる
		try {
			win.start(window_handle);
		}
		catch (...) { 
			MessageBoxA(
				window_handle,
				"致命的な問題があり、起動できません。申し訳ありませんが終了いたします",
				"致命的エラー",
				MB_OK | MB_ICONERROR);
			// 終了処理
			win.request_end(); 
			win.update();	// 中で終了処理
			delete gWindow;
			gWindow = 0;
			timeEndPeriod(1);
			return 0;
		}
		gWindow->mStarted = true; // ループ開始
		while (true) {
			// メッセージがあるなら処理
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
				if (GetMessage(&msg, NULL, 0, 0)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else {
					break; // WM_QUITきたらループを抜ける
				}
			}
			// 終わってればwindow破棄
			if (gWindow->mEnded) { // 終わってなければ更新ループ
				if (window_handle) { // もしかすると2回来るかもしれないので念のため
					DestroyWindow(window_handle);
					window_handle = 0;
				}
			}
			else {	// 実行本体
				try {
					win.update();	// ここで処理をする
				}
				catch (...) {	// 例外が発生したら取りあえず終了
					MessageBoxA(
						window_handle,
						"致命的な問題があり、継続できません。申し訳ありませんが終了いたします",
						"致命的エラー",
						MB_OK | MB_ICONERROR);
				}
			}
		}
		delete gWindow;
		gWindow = 0;
		timeEndPeriod(1);

		CoUninitialize();
		return (int)msg.wParam;
	}

	// 初期設定
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
	{
		HWND hWnd;

		hInst = hInstance; // グローバル変数にインスタンス処理を格納します。
						   //----
		DWORD style = 0;
		style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX; // | WS_MAXIMIZEBOX

		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = gWindow->mWidth;
		rect.bottom = gWindow->mHeight;
		AdjustWindowRect(&rect, style, FALSE);
		rect.right -= rect.left;
		rect.bottom -= rect.top; //差分計算
		rect.left = 0;
		rect.top = 0;
		//----

		hWnd = CreateWindow(szWindowClass, szTitle,
			style,
			CW_USEDEFAULT, CW_USEDEFAULT,
			rect.right, rect.bottom, NULL, NULL, hInstance, NULL);

		if (!hWnd)
		{
			return FALSE;
		}
		ShowWindow(hWnd, SW_RESTORE);
		UpdateWindow(hWnd);

		gWindow->mHwnd = hWnd;

		return TRUE;
	}

	// この辺はおまじない
	ATOM MyRegisterClass(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWCREATOR));
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WINDOWCREATOR);
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
		return RegisterClassEx(&wcex);
	}


	//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
	//
	//  目的:  メイン ウィンドウのメッセージを処理します。
	//
	//  WM_COMMAND	- アプリケーション メニューの処理
	//  WM_PAINT	- メイン ウィンドウの描画
	//  WM_DESTROY	- 中止メッセージを表示して戻る
	//
	//
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			break;
		case WM_CLOSE: // 終了要請
			gWindow->mEnd_requested = true;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATE:
			if (wParam & 0xffff0000) { // 最小化されていればfalse
				gWindow->mActive = false;
			}
			else {
				gWindow->mActive = ((wParam & 0xffff) != 0);
			}
			break;
		case WM_SYSCOMMAND:
			if (wParam == SC_MAXIMIZE) {
				// 最大化は無視する
			}
			else if (wParam == SC_MINIMIZE) {
				// 最小化
				gWindow->mMinimized = true;
				gWindow->mActive = false;
				DefWindowProc(hWnd, message, wParam, lParam);
			}
			else if (wParam == SC_RESTORE) {
				// 再表示
				gWindow->mMinimized = false;
				gWindow->mActive = true;
				DefWindowProc(hWnd, message, wParam, lParam);
			}
			else {
				DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_MOUSEWHEEL:
			gWindow->mMousewheel = (static_cast< short >(HIWORD(wParam)) > 0) ? 1 : -1;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}
