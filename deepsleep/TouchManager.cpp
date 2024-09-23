#include "TouchManager.h"
#include "Stage.h"
#include "Utils.h"
#include <iostream>>
#include <raylib.h>

ds::TouchManager::TouchManager(Stage* stage) {
	this->stage = stage;
}

ds::DisplayObject* ds::TouchManager::hitNodeTest(DisplayObject* node, Vector2 pos, bool touchThrough)
{
	if (node->getWidth() > 0 && node->getHeight() > 0 || touchThrough) {
		if (!touchThrough) {
			auto tx = (pos.x + node->getPivotX() * node->getScaleX()) / node->getScaleX();
			auto ty = (pos.y + node->getPivotY() * node->getScaleY()) / node->getScaleY();
			if (node->hitTest(tx, ty))
				return node;
		}
	}

	return nullptr;
}

ds::DisplayObject* ds::TouchManager::hitTest(DisplayObject* node, TouchID id, Vector2 pos) {
	if (!node || disabled) return nullptr;

	Vector2 posTemp = pos;
	if (fmodf(node->getAngle(), 360.f) != 0.f)
		Utils::rotatePointByZero(posTemp, -node->getAngle());

	if (node->scrollEnabled)
		//TODO:
		;
	node->mousePosition = posTemp;
	if (!node->touchThrough) {
		if (!hitNodeTest(node, posTemp, node->touchThrough))
			return nullptr;
	} else
		if (!hitNodeTest(node, posTemp, false))
			return nullptr;

	if (node->isDisplayObjectContainer) {
		auto container = (DisplayObjectContainer*)node;
		for (int i = container->numChildren() - 1; i >= 0; i--)
		{
			auto child = container->children[i];
			if (child->visible && child->touchEnabled) {
				posTemp.x += node->getPivotX() * node->getScaleX();
				posTemp.y += node->getPivotY() * node->getScaleY();
				auto hit = hitTest(child, id, posTemp);
				if (hit) {
					return hit;
				}
			}
		}
	}

	DisplayObject* hit = nullptr;

	if (!node->touchThrough)
		hit = node;
	else
		hit = hitTest(node, id, posTemp);

	return hit;
}


void ds::TouchManager::onTouchBegin(DisplayObject* node, TouchID id, const Vector2 pos) {
	if (!node) return;

}

void ds::TouchManager::onTouchMove(DisplayObject* node, TouchID id, const Vector2 pos) {
	if (!node) return;

}

void ds::TouchManager::onTouchEnd(DisplayObject* node, TouchID id, const Vector2 pos) {
	if (!node) return;

}

void ds::TouchManager::update() {
	if (!stage || disabled) return;

	TouchID id = INT_MIN;
	TouchEvent type = TouchEvent::MOVE;

	auto mousePos = GetMousePosition();
	bool mouseMoved = mousePos.x != mousePositionLast.x && mousePos.y != mousePositionLast.y;
	mousePositionLast = mousePos;

	if (mode == TouchMode::Mouse) {
		for (TouchID touchID = MOUSE_BUTTON_LEFT; touchID <= MOUSE_BUTTON_BACK; touchID++) {
			if (IsMouseButtonPressed(touchID)) {
				id = touchID;
				type = TouchEvent::TOUCH_BEGIN;
			} else if (IsMouseButtonReleased(touchID)) {
				id = touchID;
				type = TouchEvent::TOUCH_END;
			}
		}
		if (mouseMoved && id == INT_MIN) {
			id = MOUSE_BUTTON_LEFT;
			type = TouchEvent::MOVE;
		}
	} else if (mode == TouchMode::Touch) {
		auto touchCount = GetTouchPointCount();
		Vector2 touchPos;
		for (int i = 0, touchId; i < touchCount; i++) {
			touchId = GetTouchPointId(i);
			touchPos = GetTouchPosition(i);
		}

#ifdef _DEBUG //DEBUG on Windows
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			id = MOUSE_BUTTON_LEFT;
			type = TouchEvent::TOUCH_BEGIN;
		} else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			id = MOUSE_BUTTON_LEFT;
			type = TouchEvent::TOUCH_END;
		}
		if (mouseMoved && id == INT_MIN) {
			id = MOUSE_BUTTON_LEFT;
			type = TouchEvent::MOVE;
		}
#endif
	}



	if (id != INT_MIN) {
		auto hit = hitTest(stage, id, mousePos);
		if (hit) {
			switch (type) {
			case TouchEvent::TOUCH_BEGIN: onTouchBegin(hit, id, mousePos); break;
			case TouchEvent::TOUCH_END: onTouchEnd(hit, id, mousePos); break;
			case TouchEvent::MOVE: onTouchMove(hit, id, mousePos); break;
			}
			if (type != TouchEvent::MOVE) {
				std::cout << typeid(*hit).name() << std::endl;
			}
		} else {

		}
	}

}