#include <Geode/Geode.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>
#include <Geode/binding/GJGameLevel.hpp>

using namespace geode::prelude;

#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>
int randomNum = rand() % 3;
int randomPercent = rand() % 99;
float currentPercent;
class $modify(ShuffleTheStuff, PlayerObject) {
	void playerDestroyed(bool p0)
	{
		PlayerObject::playerDestroyed(p0);
		randomNum = rand() % 100;
		randomPercent = rand() % 100;
	}
};
class $modify(PlayLayer){
	void updateProgressbar()
	{
		PlayLayer::updateProgressbar();
		/* i think this stops it working in certain modes or smth */
		if (this == nullptr) return;
		if (this->m_isPracticeMode) return;
		if (this->m_isTestMode) return;

		auto hac = Mod::get()->getSettingValue<int64_t>("hac");

		currentPercent = this->getCurrentPercent();
		if (m_player1)
		{
			if (randomNum <= hac &&  currentPercent >= randomPercent)
			{
				this->PlayLayer::destroyPlayer(this->m_player1, nullptr);
			}
		}
	}
};