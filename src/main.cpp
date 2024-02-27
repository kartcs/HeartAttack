#include <Geode/Geode.hpp>

#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Variables and stuff :yeah:
int randomNum = rand() % 100;
float randomPercent = rand() % 90;
float currentPercent;

/* 
	Keep in mind these notes are for my idiot self 
	so don't expect anything too intelligent 
*/

// Warning bool so it only does it once
bool warned = false;

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			log::info("wuh oheieoeoe");
			return false;
		}

		// If mod enabled, warn user
		if (!warned)
		{
			if (Mod::get()->getSettingValue<bool>("enabled") == true)
			{
				warned = true;
				// WUH OH!!
				auto warning = FLAlertLayer::create(
					"WARNING",
					"Heart attacks are <cr>enabled</c>, proceed at your own risk.",
					"OK"
				);
				warning->m_scene = this;
				warning->show();
			}
		}
		return true;
	}
};

bool reset = false;
// The actual functionality
class $modify(PlayLayer){
	void updateProgressbar()
	{
		// CALL THE ORIGINAL :PAIN:
		PlayLayer::updateProgressbar();

		// Gets the chance percentage setting
		auto HAC = Mod::get()->getSettingValue<int64_t>("hac");

		// I think this stops it working in certain modes or something 
		if (this == nullptr) return;
		if (this->m_isPracticeMode) return;
		if (this->m_isTestMode) return;

		// Sets the currentpercent float to the game's current percent
		currentPercent = this->getCurrentPercent();

		if (Mod::get()->getSettingValue<bool>("enabled") == true)
		{
			if (!reset)
			{
				if (m_player1)
				{
					/* 
						IF hac value is less or equal to randomnum 
						&& percent is greater or equal THEN kill
					*/
					if (HAC >= randomNum && currentPercent >= randomPercent)
					{
						// Locks the part so it run a billion times
						reset = true;

						// violence
						this->PlayLayer::destroyPlayer(this->m_player1, nullptr);
					}
				}
			}
		}
	}
	void resetLevel()
	{
		// CALL THE ORIGINAL :PAIN:
		PlayLayer::resetLevel();

		// Undoes the lock on the killing part
		reset = false;

		// Randomizes the numbers for the next attempt
		randomNum = rand() % 100;
		randomPercent = rand() % 90;
	}
};
