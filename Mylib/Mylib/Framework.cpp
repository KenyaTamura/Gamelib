#include"Mylib\Framework.h"
#include"Mylib\FileIO\FileIO_impl.h"
#include"Mylib\Graphics\Graphics_impl.h"
#include"Mylib\Input\Input_impl.h"
#include"Mylib\Sound\Sound_impl.h"
#include"Mylib\Window\Window.h"

#include<fstream>
using namespace std;

namespace Mylib {
	Framework* Framework::mInstance = 0;

	Framework::Framework() :
		mWidth{ 640 },
		mHeight{ 480 },
		mTitle{ "A Mylib Framework Application" },
		mFramerate{ 0 },
		mIdeal_frame_interval{ 33 },
		mPrev_frame_interval{ 0 },
		mPrev_frametime{ 0 },
		mFirst_loading{ true },
		mEnd_requested{ false },
		mStarted{ false }
	{
	}

	Framework::~Framework() {
		Graphics::Graphics_impl::destroy();
		FileIO::FileIO_impl::destroy();
		Input::Input_impl::destroy();
		Sound::Sound_impl::destroy();
	}

	Framework* Framework::instance() {
		return mInstance;
	}

	void Framework::create() {
		if (!mInstance) {
			mInstance = new Framework();
		}
	}

	void Framework::destroy() {
		if (mInstance) {
			delete mInstance;
			mInstance = nullptr;
		}
	}

	int Framework::get_width() const {
		return mInstance->mWidth;
	}

	int Framework::get_height() const {
		return mInstance->mHeight;
	}

	string Framework::get_title() const {
		return mInstance->mTitle;
	}

	void Framework::request_end() {
		mInstance->mEnd_requested = true;
	}

	bool Framework::is_end_requested() const {
		return mInstance->mEnd_requested;
	}

	void Framework::sleep(int ms) const {
		Window::instance().sleep(ms);
	}

	int Framework::get_framerate() const {
		return mInstance->mFramerate;
	}

	void Framework::set_framerate(int framerate) {
		mIdeal_frame_interval = 1000 / framerate;
	}
	
	void Framework::start(void* window_handle) {
		// ファイルIO
		FileIO::FileIO_impl::create();
		//入力初期化
		Input::Input_impl::create(window_handle);
		//描画初期化
		Graphics::Graphics_impl::create(window_handle);
		// 音声初期化
		Sound::Sound_impl::create(window_handle);
		mStarted = true;
	}

	void Framework::pre_update() {
		Window win= Window::instance();
		unsigned current_time = win.get_time();
		// フレームレート調整
		while ((current_time - mPrev_frametime) < mIdeal_frame_interval) {
			win.sleep(1);
			current_time = win.get_time();
		}
		mPrev_frame_interval = current_time - mPrev_frametime;
		mPrev_frametime = current_time;

		//フレーム時間更新
		if (mPrev_frame_interval) {
			mFramerate = 1000 / mPrev_frame_interval;
		}
		Graphics::Graphics_impl::instance()->begin_draw();
		Input::Input_impl::instance()->update();
		FileIO::FileIO_impl::instance()->update();
	}

	void Framework::post_update() {
		Graphics::Graphics_impl::instance()->end_draw();
	}

	// WindowProcedureの初期設定
	void Window::configure(Configuration* config) {
		Framework::create();
		//ユーザ設定
		Framework* f = Framework::instance();
		Framework::Configuration fwConfig;
		f->configure(&fwConfig);
		config->set_width(f->get_width());
		config->set_height(f->get_height());
		config->set_title(f->get_title().c_str());
	}

	// 本体の処理
	void Window::update() {
		Window win;
		Framework* f = Framework::instance();
		// Windowの状態次第でいろいろする
		bool sleepFlag = false;
		// 最小化していれば寝る
		if (win.is_minimized()) {
			sleepFlag = true;
		}

		if (!sleepFlag) {
			f->pre_update();
		}
		// 上流(×ボタンとか)から終了命令が来ているかチェック
		if (win.is_end_requested()) { // 来ていればFrameworkに終了命令を伝達
			f->request_end();
		}
		if (sleepFlag) {
			sleep(50); // 適当に休憩
		}
		else {
			f->update();
			f->post_update();
		}
		// 終了判定
		if (f->is_end_requested()) {
			Framework::destroy();
			end();	 //上流にも知らせを
		}
	}

	void Window::start(void* windowHandle) {
		Framework::instance()->start(windowHandle);
	}

	// Configureationクラス、初期設定ウィンドウ幅
	void Framework::Configuration::set_width(int w) {
		mInstance->mWidth = w;
	}
	// Configureationクラス、初期設定ウィンドウ高さ
	void Framework::Configuration::set_height(int h) {
		mInstance->mHeight = h;
	}
	// Configureationクラス、初期設定ウィンドウ名
	void Framework::Configuration::set_title(const char* title) {
		mInstance->mTitle = title;
	}

	// 初期設定読み込み
	void Framework::Configuration::load_file(const char* filename, string* out) const {
		// まだFileIOが使えないから仕方なく
		// 一回しか使わせない
		if (mInstance->mFirst_loading) {
			mInstance->mFirst_loading = false;
			ifstream in(filename, ifstream::binary);
			in.seekg(0, ifstream::end);
			streamsize size = in.tellg();
			in.seekg(0, ifstream::beg);
			char* s = new char[static_cast<unsigned>(size) + 1];
			in.read(s, size);
			s[size] = '\0';
			*out = s;
		}
	}

}