#pragma once
#include "DisplayObject.h"

namespace ds {
	class DisplayObjectContainer : public DisplayObject
	{
	public:
		int layout;
		std::vector<DisplayObject*> childs;
	public:
		DisplayObjectContainer();
		virtual ~DisplayObjectContainer();
		void replaceChild(DisplayObject* a, DisplayObject* newObject);
		DisplayObject* addChild(DisplayObject* object, int index = -1);
		DisplayObject* removeChild(DisplayObject* object);
		std::vector<DisplayObject*> removeChild(int index, int end = -1);
		DisplayObject* setChildIndex(DisplayObject* object, int index);
		int getChildIndex(DisplayObject* object);
		DisplayObject* getChildByName(std::string name);
		bool contains(DisplayObject* object);
		unsigned int numChildren();
		virtual void $render();
		void $drawChildren();
	};
}

