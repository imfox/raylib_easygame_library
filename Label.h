#pragma once
#include "DisplayObject.h"

namespace ds {
	class Label : public ds::DisplayObject {
	protected:
		std::string $text;
		std::string $textFlow;
		struct Value {
			std::string fontName;
			std::uint8_t fontSize = 14;
			int charSpacing = 0;
			int lineSpacing = 0;
			bool bold = false;//����
			bool underline = false;//�»���
			bool italic = false;//б��
		};
		Value $extra;
		void $setText(std::string text);
		std::string $getText();

	public:
		virtual void $draw();
		Label setText(std::string text);
		Label setText();
		std::string getText();
	};
}

