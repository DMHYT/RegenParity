#include <hook.h>
#include <symbol.h>

#include <innercore/vtable.h>

#include "main.hpp"


void RegenParityModule::tickHungerAttributeDelegate(HungerAttributeDelegate* delegate) {
	Player* player = delegate->player;
	VTABLE_FIND_OFFSET(Actor_isCreative, _ZTV5Actor, _ZNK5Actor10isCreativeEv);
	if(!VTABLE_CALL<bool>(Actor_isCreative, player)) {
		Level* level = player->getLevel();
		int difficulty = level->getDifficulty();
		if(difficulty == 0) {
			AttributeInstance* mutableInstance = delegate->_getMutableInstance();
			if(mutableInstance != nullptr) {
				mutableInstance->addBuff(InstantaneousAttributeBuff(1.0f, (AttributeBuffType) 10));
			}
		}
		float currentHunger = delegate->_getInstance()->getCurrentValue();
		delegate->prevFoodLevel = currentHunger;
		bool naturalRegenEnabled = level->getGameRules()->getBool(GameRuleId(15));
		float currentSaturation = player->getSaturation();
		if(naturalRegenEnabled && currentSaturation > 0.0f && player->isHurt() && currentHunger >= 20.0f) {
			++delegate->foodTimer;
			if(delegate->foodTimer >= 10) healForExhaustion(delegate, player);
		} else if(naturalRegenEnabled && currentHunger >= 18 && player->isHurt()) {
			++delegate->foodTimer;
			if(delegate->foodTimer >= 80) healForExhaustion(delegate, player);
		} else if(currentHunger <= 0) {
			++delegate->foodTimer;
			if(delegate->foodTimer >= 80) {
				int currentHealth = player->getHealth();
				if(currentHealth > 10 || difficulty == 3 || (currentHealth > 1 && difficulty == 2)) {
					player->hurt(ActorDamageSource((ActorDamageCause) 16), 1, true, false);
				}
				delegate->foodTimer = 0;
			}
		} else delegate->foodTimer = 0;
	}
}

void RegenParityModule::healForExhaustion(HungerAttributeDelegate* delegate, Player* player) {
	VTABLE_FIND_OFFSET(AttributeInstanceDelegate_tick, _ZTV25AttributeInstanceDelegate, _ZN25AttributeInstanceDelegate4tickEv);
	player->heal(1);
	AttributeInstance* instance = player->getMutableAttribute(Player::SATURATION);
	if(instance != nullptr && instance->getCurrentValue() > 0.0f) {
		instance->addBuff(InstantaneousAttributeBuff(-1.0f, (AttributeBuffType) 10));
	} else {
		instance = player->getMutableAttribute(Player::HUNGER);
		if(instance != nullptr) {
			instance->addBuff(InstantaneousAttributeBuff(-1.0f, (AttributeBuffType) 10));
		}
	}
	player->causeFoodExhaustion(2.0f);
	delegate->foodTimer = 0;
}


void RegenParityModule::initialize() {

	DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

	HookManager::addCallback(
		SYMBOL("mcpe", "_ZN23HungerAttributeDelegate4tickEv"),
		LAMBDA((HookManager::CallbackController* controller, HungerAttributeDelegate* delegate), {
			controller->prevent();
			tickHungerAttributeDelegate(delegate);
		}, ),
		HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER
	);

}


MAIN {
	Module* main_module = new RegenParityModule();
}