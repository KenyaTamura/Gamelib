#include"Mylib\Framework.h"
#include"Mylib\Manager.h"
#include"Mylib\XML\Document.h"

// �����ݒ�
void Mylib::Framework::configure(Framework::Configuration* config){
	std::string s;
	config->load_file("config.xml", &s);
	XML::Document d;
	d.create(s);
	XML::Element* e = d.get_root()->get_element(0);
	for (int i = 0; i < e->get_attribute_num(); ++i) {
		s = e->get_attribute(i)->get_name().c_str();
		if (s == "width") {
			config->set_width(e->get_attribute(i)->get_val_int());
		}
		else if (s == "height") {
			config->set_height(e->get_attribute(i)->get_val_int());
		}
		else if (s == "title") {
			config->set_title(e->get_attribute(i)->get_val().c_str());
		}
	}
}

bool gStart = true;

void Mylib::Framework::update() {
	// �J�n
	if (gStart) {
		Mylib::Manager::instance().set_framerate(30);
		gStart = false;
	}
	// �I���v��
	if (Mylib::Manager::instance().is_end_requested()) {
		
	}
	// ���C�����[�v
	else {
		Mylib::Manager::instance().sleep(5);
	}
}