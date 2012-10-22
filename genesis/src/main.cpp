#include <allegro5/allegro.h>
#include <iostream>
#include "Application/ApplicationTest.h"
#include "Memory/MemoryTest.h"
#include "Settings/SettingsTest.h"
 
int main(int argc, char **argv)
{
	al_init();

	SettingsTest st; st.run();
	MemoryTest mt; mt.run();
	ApplicationTest at; at.run();

	std::cout << "Press Enter to Continue..." << std::endl;
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	//al_rest(5.0);

	return 0;
}