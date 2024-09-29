#pragma once
#include "DisplayObject.h"
#include "Loader.h"
#include <memory>

namespace ds {
	class Image : public DisplayObject {
	protected:
		std::string $skin;
		void $setSkin(const std::string& url);
		std::string& $getSkin();
	public:
		std::shared_ptr<ds::Texture> imageData;
	public:
		virtual ~Image() override {};
		virtual void $draw();
		ds::Image* setSkin(const std::string& url);
		std::string& getSkin();
	};
}

