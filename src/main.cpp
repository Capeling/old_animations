#include <Geode/Geode.hpp>
#include <Geode/modify/AchievementBar.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(AchievementBar) {
	bool init(char const* title, char const* desc, char const* icon, bool quest) {
		if (!AchievementBar::init(title, desc, icon, quest))
			return false;

		m_bg->setContentSize({ 300.f, 70.f });
		m_layerColor->setPositionY(35.f);

		return true;
	}
	void show() {
		auto scene = CCScene::get();
		auto director = CCDirector::get();

		int highestZ = scene->getHighestChildZ();
		highestZ++;

		scene->addChild(this, highestZ);
		
		this->setPositionY(director->getScreenTop() + 2.f);
		m_achievementGlowSprite->setVisible(false);

		auto moveDown = CCEaseInOut::create(CCMoveBy::create(1.f, ccp(.0f, -74)), 2.f);
		auto delay1P5 = CCDelayTime::create(1.5f);

		auto moveUp = CCEaseInOut::create(CCMoveBy::create(1.f, ccp(.0f, 74)), 2.f);
		auto callFunc = CCCallFunc::create(AchievementNotifier::sharedState(), callfunc_selector(AchievementNotifier::achievementDisplayFinished));

		auto sequence = CCSequence::create(
			moveDown,
			delay1P5,
			moveUp,
			callFunc,
			0
		);
		this->runAction(sequence);
	}
};

#ifdef DEBUG_BUILD
class $modify(MenuLayer) {
	void keyDown(enumKeyCodes key) {
		if (key == enumKeyCodes::KEY_G) {
			AchievementNotifier::sharedState()->notifyAchievement("long title lada dada dada dada", "ach", "color2_11", false);
		}
		MenuLayer::keyDown(key);
	}
};
#endif