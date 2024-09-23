#include "Label.h"
#include "Runtime.h"

void ds::Label::$draw() {
	if (!this->$text.empty()) {
		Font font = this->$extra.fontName.empty() ? GetFontDefault() : ds::loader->getFont(this->$extra.fontName);
		DrawTextEx(font, this->$text.c_str(), Vector2{ 0, 0 }, this->$extra.fontSize, 0, WHITE);
	}
}

void ds::Label::$setText(std::string text) {
	this->$text = text;
}

std::string ds::Label::$getText() {
	return "";
}

ds::Label ds::Label::setText(std::string text) {
	this->$setText(text);
	return *this;
}

ds::Label ds::Label::setText() {
	this->$setText("");
	return *this;
}

std::string ds::Label::getText() {
	return this->$getText();
}