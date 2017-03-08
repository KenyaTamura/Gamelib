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
		class Impl {	// ���ۂ̒l�������Ă���N���X
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
			HWND mHwnd;		// ���̃n���h�����g��������
			RECT mRect;
		};

		Impl* gWindow = 0;	// �O�ł�Window�N���X�̂悤�ɐU�镑��
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

	// �R���t�B�O
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
	// �ȉ�Window�v���O���~���O

#define MAX_LOADSTRING 100

	// �O���[�o���ϐ�:
	HINSTANCE hInst;								// ���݂̃C���^�[�t�F�C�X
	TCHAR szTitle[MAX_LOADSTRING];					// �^�C�g�� �o�[�̃e�L�X�g
	TCHAR szWindowClass[MAX_LOADSTRING];			// ���C�� �E�B���h�E �N���X��
													// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
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

		// �E�B���h�E��ԕێ��N���X����
		gWindow = new Impl;
		Window win = Window::instance();
		// �R���t�B�O�֐��Ăяo��
		Window::Configuration config;
		win.configure(&config);

		memcpy(szTitle, win.get_title(), win.get_title_length());
		memcpy(szWindowClass, "My_lib Window makeing", sizeof("My_lib Window makeing"));

		MyRegisterClass(hInstance);

		// �A�v���P�[�V�����̏����������s���܂�:
		if (!InitInstance(hInstance, nCmdShow)) {
			return FALSE;
		}

		timeBeginPeriod(1);
		HWND window_handle = gWindow->mHwnd;
		// ��O������������A���b�Z�[�W�{�b�N�X���o���ďI��点��
		try {
			win.start(window_handle);
		}
		catch (...) { 
			MessageBoxA(
				window_handle,
				"�v���I�Ȗ�肪����A�N���ł��܂���B�\���󂠂�܂��񂪏I���������܂�",
				"�v���I�G���[",
				MB_OK | MB_ICONERROR);
			// �I������
			win.request_end(); 
			win.update();	// ���ŏI������
			delete gWindow;
			gWindow = 0;
			timeEndPeriod(1);
			return 0;
		}
		gWindow->mStarted = true; // ���[�v�J�n
		while (true) {
			// ���b�Z�[�W������Ȃ珈��
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
				if (GetMessage(&msg, NULL, 0, 0)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else {
					break; // WM_QUIT�����烋�[�v�𔲂���
				}
			}
			// �I����Ă��window�j��
			if (gWindow->mEnded) { // �I����ĂȂ���΍X�V���[�v
				if (window_handle) { // �����������2�񗈂邩������Ȃ��̂ŔO�̂���
					DestroyWindow(window_handle);
					window_handle = 0;
				}
			}
			else {	// ���s�{��
				try {
					win.update();	// �����ŏ���������
				}
				catch (...) {	// ��O�������������肠�����I��
					MessageBoxA(
						window_handle,
						"�v���I�Ȗ�肪����A�p���ł��܂���B�\���󂠂�܂��񂪏I���������܂�",
						"�v���I�G���[",
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

	// �����ݒ�
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
	{
		HWND hWnd;

		hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B
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
		rect.bottom -= rect.top; //�����v�Z
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

	// ���̕ӂ͂��܂��Ȃ�
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


	//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
	//
	//  �ړI:  ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
	//
	//  WM_COMMAND	- �A�v���P�[�V���� ���j���[�̏���
	//  WM_PAINT	- ���C�� �E�B���h�E�̕`��
	//  WM_DESTROY	- ���~���b�Z�[�W��\�����Ė߂�
	//
	//
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			break;
		case WM_CLOSE: // �I���v��
			gWindow->mEnd_requested = true;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATE:
			if (wParam & 0xffff0000) { // �ŏ�������Ă����false
				gWindow->mActive = false;
			}
			else {
				gWindow->mActive = ((wParam & 0xffff) != 0);
			}
			break;
		case WM_SYSCOMMAND:
			if (wParam == SC_MAXIMIZE) {
				// �ő剻�͖�������
			}
			else if (wParam == SC_MINIMIZE) {
				// �ŏ���
				gWindow->mMinimized = true;
				gWindow->mActive = false;
				DefWindowProc(hWnd, message, wParam, lParam);
			}
			else if (wParam == SC_RESTORE) {
				// �ĕ\��
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
