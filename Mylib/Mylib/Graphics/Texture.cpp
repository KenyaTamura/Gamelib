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
		// ����������
		bool Texture::is_ready() {
			return mInstance->is_ready();
		}
		// �摜�̕�
		int Texture::get_width() const {
			return mInstance->get_width();
		}
		// �摜�̍���
		int Texture::get_height() const {
			return mInstance->get_height();
		}
		// �摜�f�[�^
		const unsigned* Texture::get_data() {
			return mInstance->get_data();
		}

	}
}