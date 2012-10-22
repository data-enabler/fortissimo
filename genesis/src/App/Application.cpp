#include "Application.h"
#include "Logging/Log.h"
#include "Settings/SettingsManager.h"
#include "Tasks/Kernel.h"
#include "Timing/ProfileSample.h"
#include "Timing/ProfilerLogHandler.h"

Application::Application(void) {}

Application::~Application(void) {}

void Application::defaultInit(void) {
	Log::get().init();
	SettingsManager::getInstance();
	Kernel::getInstance();
	ProfileSample::outputHandler = std::make_shared<ProfilerLogHandler>();
}

void Application::run(void) {
	Kernel::getInstance()->execute();
	delete Kernel::getInstance();
	delete SettingsManager::getInstance();
}