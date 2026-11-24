#include <Geode/binding/PlayLayer.hpp>
#include <Geode/binding/MenuLayer.hpp>

#include <Geode/Geode.hpp>
#include <Geode/loader/Log.hpp>

#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

bool enabled = Mod::get()->getSettingValue<bool>("enabled");
int randomNum;
float randomPercent;
float currentPercent;
float chance;
float low;
float high;

void getNewValues() {
	enabled = Mod::get()->getSettingValue<bool>("enabled");
	randomNum = rand() % 100;
	low = Mod::get()->getSettingValue<float>("lowrange");
	high = Mod::get()->getSettingValue<float>("highrange");
	chance = Mod::get()->getSettingValue<int64_t>("hac");

	if (high < low)
	{
		// flip in case the player is a MORONNNN
		float t = high;
		high = low;
		low = t;
	}

	randomPercent = rand() * (high - low) + low;
	geode::log::info("REFRESHED VALUES: chance, low, high, rp");
	geode::log::info(chance);
	geode::log::info(low);
	geode::log::info(high);
	geode::log::info(randomPercent);
}

bool warned = false;
class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}
		getNewValues();
		if (!warned)
		{
			if (enabled)
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
		if (this == nullptr) return;
		if (this->m_isPracticeMode) return;
		if (this->m_isTestMode) return;
		currentPercent = this->getCurrentPercent();

		if (enabled)
		{
			if (!reset)
			{
				if (m_player1)
				{
					if (chance >= randomNum && currentPercent >= randomPercent && currentPercent >= low && currentPercent <= high)
					{
						geode::log::info("w speed");
						reset = true;
						this->PlayLayer::destroyPlayer(this->m_player1, nullptr);
						// ignore this i just HAVE to know what this does lmfao
						PlayLayer::spawnFirework();
					}
				}
			}
		}
	}
	void resetLevel()
	{
		PlayLayer::resetLevel();
		reset = false;
		getNewValues();
	}
	void fullReset()
	{
		PlayLayer::fullReset();
		reset = false;
		getNewValues();
	}
};
