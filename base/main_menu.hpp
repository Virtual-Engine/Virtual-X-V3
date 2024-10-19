#pragma once
#include "common.hpp"

class MainMenu
{
public:
	static MainMenu* GetInstance();

	void Init();
	void UpdateOnce();
	void Update();
	void FeatureUpdate();

	MainMenu() { }
	~MainMenu();
};

namespace MainMenuVars
{

}