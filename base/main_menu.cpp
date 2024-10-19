#include "common.hpp"
#include "main_menu.hpp"
#include "ui/interface.hpp"
using namespace MainMenuVars;
using namespace VX;
namespace MainMenuVars {

}

void MainMenu::Init() {
	//setName("Home", true, true);


}

void MainMenu::UpdateOnce() {

}

void MainMenu::Update() {
}

void MainMenu::FeatureUpdate() {}

/*Singleton*/
MainMenu* _instance;
MainMenu* MainMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MainMenu();
		_instance->Init();
	}
	return _instance;
}
MainMenu::~MainMenu() { delete _instance; }