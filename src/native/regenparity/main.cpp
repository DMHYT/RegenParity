#include <hook.h>
#include <symbol.h>

#include "main.hpp"


void RegenParityModule::initialize() {

	DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

	// TODO hook

}


MAIN {
	Module* main_module = new RegenParityModule();
}