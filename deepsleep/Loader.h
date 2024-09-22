#pragma once

#include "Enum.h"
#include <raylib.h>
#include <unordered_map>
#include <memory>

namespace ds {
	using RLTexture = ::Texture;

	class LoaderRes {
	public:
		LoaderResType type = LoaderResType::None;
	};

	class Texture : public LoaderRes
	{
	public:
		RLTexture data = { 0 };
		unsigned short x = 0;
		unsigned short y = 0;
		unsigned short width = 0;
		unsigned short height = 0;
		unsigned short offsetX = 0;
		unsigned short offsetY = 0;
		unsigned short sourceWidth = 0;
		unsigned short sourceHeight = 0;
		Texture() {
			type = LoaderResType::Texture;
		};
		Texture(RLTexture tex) {
			type = LoaderResType::Texture;
			width = tex.width;
			height = tex.height;
			sourceWidth = tex.width;
			sourceHeight = tex.height;
			this->data = tex;
		}
		Texture(RLTexture tex, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int offsetX, unsigned int offsetY, unsigned int sourceWidth, unsigned int sourceHeight) {
			type = LoaderResType::Texture;
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->offsetX = offsetX;
			this->offsetY = offsetY;
			this->sourceWidth = sourceWidth;
			this->sourceHeight = sourceHeight;
			this->data = tex;
		}
	};

	class Loader /* : public EventDispatcher */ {
		std::unordered_map<std::string, std::shared_ptr<LoaderRes>> res;
	public:

		template <typename T = LoaderRes>
		void cache(const std::string& url, T res) {
			this->res.emplace(url, res);
		}

		template <typename T = LoaderRes>
		T* get(const std::string& url) {
			return get<T>(url.c_str());
		};

		template <typename T = LoaderRes>
		T* get(const char* url) {
			return (T*)this->res[url].get();
		};

		void load(const char* url);
		void load(const char* url, LoaderResType type);
		void load(std::string& url);
		static std::shared_ptr<Texture> setTexture(RLTexture& tex, int x, int y, int width, int height, int offsetX, int offsetY, int sourceWidth, int sourceHeight);
		static std::shared_ptr<Texture> setTexture(RLTexture& tex);
		static std::shared_ptr<LoaderRes> texture(std::string& url);
	};

}

