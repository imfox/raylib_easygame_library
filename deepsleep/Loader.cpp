#include "Loader.h"

void ds::Loader::load(const char* url, ds::LoaderResType type) {
	if (FileExists(url))
	{
		switch (type)
		{
		case ds::LoaderResType::Texture: {
			auto tex = ::LoadTexture(url);
			auto data = setTexture(tex);
			this->cache(std::string(url), data);
			break;
		}
		case ds::LoaderResType::None:
		default:
			TraceLog(LOG_WARNING, TextFormat("none file type, url: %s .", url));
		}
	} else {
		TraceLog(LOG_WARNING, TextFormat("file not exist: %s .", url));
	}

}

void ds::Loader::load(const char* url) {
	auto ext = GetFileExtension(url);
	ds::LoaderResType type = ds::LoaderResType::None;
	if (std::strcmp(ext, ".png") == 0
		|| std::strcmp(ext, ".jpg") == 0
		|| std::strcmp(ext, ".jpeg") == 0
		|| std::strcmp(ext, ".bmp") == 0
		) {
		type = ds::LoaderResType::Texture;
	}
	load(url, type);
}

void ds::Loader::load(std::string& url) {
	auto ext = GetFileExtension(url.c_str());
	ds::LoaderResType type = ds::LoaderResType::None;
	if (std::strcmp(ext, ".png") == 0
		|| std::strcmp(ext, ".jpg") == 0
		|| std::strcmp(ext, ".jpeg") == 0
		|| std::strcmp(ext, ".bmp") == 0
		) {
		type = ds::LoaderResType::Texture;
	}
	load(url.c_str(), type);
}


std::shared_ptr<ds::Texture> ds::Loader::setTexture(RLTexture& tex, int x, int y, int width, int height, int offsetX, int offsetY, int sourceWidth, int sourceHeight)
{
	return std::make_shared<Texture>(tex, x, y, width, height, offsetX, offsetY, sourceWidth, sourceHeight);
}

std::shared_ptr<ds::Texture> ds::Loader::setTexture(RLTexture& tex)
{
	return std::make_shared<Texture>(tex);
}
