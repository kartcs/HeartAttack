#include <Geode/binding/PlayLayer.hpp>
#include <Geode/binding/MenuLayer.hpp>
#include <Geode/Geode.hpp>
#include <Geode/modify/Addresses.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

int randomNum = rand() % 100;
float randomPercent = rand() % 90;
float currentPercent;

/* 
	Keep in mind these notes are for my idiot self 
	so don't expect anything too intelligent 
*/

bool warned = false;
class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}
		if (!warned)
		{
			if (Mod::get()->getSettingValue<bool>("enabled") == true)
			{
				warned = true;
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
class $modify(PlayLayer){
	void updateProgressbar()
	{
		PlayLayer::updateProgressbar();
		auto HAC = Mod::get()->getSettingValue<int64_t>("hac");
		if (this == nullptr) return;
		if (this->m_isPracticeMode) return;
		if (this->m_isTestMode) return;
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
						reset = true;
						this->PlayLayer::destroyPlayer(this->m_player1, nullptr);
					}
				}
			}
		}
	}
	void resetLevel()
	{
		PlayLayer::resetLevel();
		reset = false;
		randomNum = rand() % 100;
		randomPercent = rand() % 90;
	}
};
