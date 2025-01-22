#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

#include <Geode/modify/LevelSettingsLayer.hpp>

class $modify(IDKLEVELSETTINGSLAYER, LevelSettingsLayer) {

	void updateSprite(ColorChannelSprite* sprite) {
		auto channel = static_cast<int>(sprite->getTag());
		auto action = LevelEditorLayer::get()->m_levelSettings->m_effectManager->getColorAction(channel);

		sprite->updateValues(action);
	}

	void onShowPicker(CCObject* sender) {
		LevelSettingsLayer::onShowPicker(sender);
	}

	void onLiveEdit(CCObject* sender) {
		LevelSettingsLayer::onLiveEdit(sender);
	}

	void colorSelectClosed(CCNode* p0) {
		if (this->m_buttonMenu) {
			for (auto child : CCArrayExt<CCMenuItemSpriteExtra*>(this->m_buttonMenu->getChildren())) {
				if (auto spr = static_cast<ColorChannelSprite*>(child->getChildByID("objChannel_colorSpr"_spr))) {
					this->updateSprite(spr);
				}
				if (auto spr = static_cast<ColorChannelSprite*>(child->getChildByID("dlChannel_colorSpr"_spr))) {
					this->updateSprite(spr);
				}
			}
		}
		LevelSettingsLayer::colorSelectClosed(p0);
	}

	bool init(LevelSettingsObject* settingsObject, LevelEditorLayer* editorLayer) {
		if (!LevelSettingsLayer::init(settingsObject, editorLayer)) return false;

		auto* director = CCDirector::sharedDirector();
		auto winSize = director->getWinSize();

		CCMenu* menu = this->m_buttonMenu;
		CCLayer* mainLayer = this->m_mainLayer;

		auto objLabel = CCLabelBMFont::create("OBJ:", "bigFont.fnt");
		objLabel->setScale(0.35f);
		objLabel->setPosition({winSize.width / 2.f + 92.f, winSize.height / 2.f + 142.f});
		mainLayer->addChild(objLabel);

		auto dlLabel = CCLabelBMFont::create("3DL:", "bigFont.fnt");
		dlLabel->setScale(0.35f);
		dlLabel->setPosition({winSize.width / 2.f + 138.f, winSize.height / 2.f + 142.f});
		mainLayer->addChild(dlLabel);
		
		auto plusSpr = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
		plusSpr->setScale(0.3f);
		plusSpr->setColor({0,0,0});
		plusSpr->setOpacity(100);
		auto plusLabel = CCLabelBMFont::create("+", "bigFont.fnt");
		plusLabel->setOpacity(100);
		plusLabel->setScale(1.4f);
		plusLabel->setPosition(plusSpr->getContentWidth() / 2.f + 2.f, plusSpr->getContentHeight() / 2.f + 2.f);
		plusSpr->addChild(plusLabel);

		auto objSprite = ColorChannelSprite::create();
		objSprite->setID("objChannel_colorSpr"_spr);
		objSprite->setScale(0.45f);
		auto objButton = CCMenuItemSpriteExtra::create(objSprite, this, menu_selector(IDKLEVELSETTINGSLAYER::onShowPicker));
		objButton->setTag(1004);
		objSprite->setTag(1004);
		objButton->setPosition({92.f, 128.f});
		menu->addChild(objButton);
		auto objLiveButton = CCMenuItemSpriteExtra::create(plusSpr, this, menu_selector(IDKLEVELSETTINGSLAYER::onLiveEdit));
		objLiveButton->setPosition({110.f, 142.f});
		objLiveButton->setTag(1004);
		menu->addChild(objLiveButton);

		auto dlSprite = ColorChannelSprite::create();
		dlSprite->setID("dlChannel_colorSpr"_spr);
		dlSprite->setScale(0.45f);
		auto dlButton = CCMenuItemSpriteExtra::create(dlSprite, this, menu_selector(IDKLEVELSETTINGSLAYER::onShowPicker));
		dlButton->setTag(1003);
		dlButton->setTag(1003);
		dlButton->setPosition({138.f, 128.f});
		menu->addChild(dlButton);
		auto dlLiveButton = CCMenuItemSpriteExtra::create(plusSpr, this, menu_selector(IDKLEVELSETTINGSLAYER::onLiveEdit));
		dlLiveButton->setPosition({158.f, 142.f});
		dlLiveButton->setTag(1003);
		menu->addChild(dlLiveButton);

		updateSprite(objSprite);
		updateSprite(dlSprite);

		return true;
	}
};