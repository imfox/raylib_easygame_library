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
			if (node->hitTest(pos.x, pos.y))
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
			auto child = container->childs[i];
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
	if (!this->stage)return;
	auto mousePos = GetMousePosition();
	bool mouseMoved = mousePos.x != mousePositionLast.x && mousePos.y != mousePositionLast.y;

	if (mouseMoved) {
		std::cout << "mouseMoved test" << std::endl;

	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		std::cout << "IsMouseButtonPressed test" << std::endl;
		auto hit = hitTest(stage, MOUSE_BUTTON_LEFT, mousePos);
		if (hit) {
			std::cout << typeid(*hit).name() << std::endl;
			std::to_string(1);
		}
	} else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		std::cout << "IsMouseButtonReleased test" << std::endl;
	}


	mousePositionLast = mousePos;
}