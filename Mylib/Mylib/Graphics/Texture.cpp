#include"Mylib\Graphics\Texture.h"
#include"Mylib\Graphics\Texture_impl.h"

namespace Mylib {
	namespace Graphics {
		Texture::Texture(const std::string& filename) :
			mInstance{ nullptr }
		{
			mInstance = new Texture_impl(filename);
		}

		Texture::Texture(const unsigned* data, int width, int height) :
			mInstance{ nullptr }
		{
			mInstance = new Texture_impl(data, width, height);
		}

		Texture::~Texture() {
			delete mInstance;
			mInstance = nullptr;
		}
		// €”õŠ®—¹‚©
		bool Texture::is_ready() {
			return mInstance->is_ready();
		}
		// ‰æ‘œ‚Ì•
		int Texture::get_width() const {
			return mInstance->get_width();
		}
		// ‰æ‘œ‚Ì‚‚³
		int Texture::get_height() const {
			return mInstance->get_height();
		}
		// ‰æ‘œƒf[ƒ^
		const unsigned* Texture::get_data() {
			return mInstance->get_data();
		}

	}
}