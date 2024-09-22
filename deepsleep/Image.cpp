#include "Image.h"
#include "Enum.h"
#include "Runtime.h"

void ds::Image::$setSkin(const std::string& url)
{
	this->$skin = url;
	if (!this->$skin.empty()) {
		auto tex = loader->get<Texture>(this->$skin);
		if (tex) {
			this->$values.measureWidth = tex->sourceWidth;
			this->$values.measureHeight = tex->sourceHeight;
		}
	}
}

std::string& ds::Image::$getSkin()
{
	return this->$skin;
}

void ds::Image::$draw()
{
	if (this->imageData) {
		DrawTexture(this->imageData->data, 0, 0, WHITE);
	} else if (!this->$skin.empty()) {
		auto res = loader->get<Texture>(this->$skin);
		if (res) {
			if (res->type == ds::LoaderResType::Texture) {
				DrawTexture(res->data, 0, 0, WHITE);
			}
		}
	}
}

ds::Image* ds::Image::setSkin(const std::string& url)
{
	this->$setSkin(url);
	return this;
}

std::string& ds::Image::getSkin()
{
	return this->$getSkin();
}
