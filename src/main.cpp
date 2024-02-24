#include <Geode/Geode.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>

using namespace geode::prelude;

#include <Geode/modify/PlayLayer.hpp>

int randomNum = rand() % 100;
float randomPercent = rand() % 90;
float currentPercent;

/* 
	Keep in mind these notes are for my idiot self 
	so don't expect anything too intelligent 
*/
class $modify(PlayLayer){
	void updateProgressbar()
	{
		// CALL THE ORIGINAL :PAIN:
		PlayLayer::updateProgressbar();

		// Gets the chance percentage setting
		auto hac = Mod::get()->getSettingValue<int64_t>("hac");

		// I think this stops it working in certain modes or something 
		if (this == nullptr) return;
		if (this->m_isPracticeMode) return;
		if (this->m_isTestMode) return;

		// Sets the currentpercent float to the game's current percent
		currentPercent = this->getCurrentPercent();

		// This is essentially just "IF player != null"
		if (m_player1)
		{
			/* 
				IF hac value is less or equal to randomnum 
				&& percent is greater or equal THEN kill
			*/
			if (hac >= randomNum &&  currentPercent >= randomPercent)
			{
				// Randomizes the numbers for the next attempt
				randomNum = rand() % 100;
				randomPercent = rand() % 90;

				// violence
				this->PlayLayer::destroyPlayer(this->m_player1, nullptr);
			}
		}
	}
};
