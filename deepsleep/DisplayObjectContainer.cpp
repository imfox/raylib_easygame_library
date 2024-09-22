#include "DisplayObjectContainer.h"
#include "Enum.h"

ds::DisplayObjectContainer::DisplayObjectContainer() {
	isDisplayObjectContainer = true;
}

ds::DisplayObjectContainer::~DisplayObjectContainer()
{
	this->childs.clear();
}

void ds::DisplayObjectContainer::replaceChild(ds::DisplayObject* object, ds::DisplayObject* newObject)
{
	if (!object->parent || !newObject->parent)
		return;
	auto index = object->parent->getChildIndex(object);
	auto newIndex = newObject->parent->getChildIndex(newObject);
	auto parent = object->parent;
	newObject->parent->addChild(object, newIndex);
	parent->addChild(newObject);
}

ds::DisplayObject* ds::DisplayObjectContainer::addChild(ds::DisplayObject* object, int index)
{
	if (object->parent) {
		if (object->parent == this)
			if (this->getChildIndex(object) < index)
				index--;
		object->removeSelf();
	}
	int pos = index < 0 ? (int)this->childs.size() : index;
	if (pos <= this->childs.size()) {
		this->childs.insert(this->childs.begin() + pos, object);
		object->parent = this;
		//object->event((int)ds::Event::ADD);
	}
	return object;
}

ds::DisplayObject* ds::DisplayObjectContainer::removeChild(ds::DisplayObject* object)
{
	auto index = this->getChildIndex(object);
	if (index >= 0)
	{
		this->childs.erase(this->childs.begin() + index);
		object->parent = nullptr;
		//object->event((int)ds::Event::REMOVE);
		return object;
	}
	return nullptr;
}

std::vector<ds::DisplayObject*> ds::DisplayObjectContainer::removeChild(int index, int end)
{
	std::vector<ds::DisplayObject*> result;
	int size = this->childs.size();
	if (index >= size)
		return result;
	auto end_ = std::min(size - 1, std::max(index, end));
	for (int i = 0; i < (end_ - index) + 1; i++)
	{
		auto object = this->childs[index];
		this->removeChild(object);
		result.push_back(object);
	}
	return result;
}

ds::DisplayObject* ds::DisplayObjectContainer::setChildIndex(ds::DisplayObject* object, int index)
{
	if (this == object->parent)
		return this->addChild(object, index);
	return nullptr;
}

int ds::DisplayObjectContainer::getChildIndex(DisplayObject* object)
{
	auto iter = std::find(this->childs.begin(), this->childs.end(), object);
	if (iter == this->childs.end())
		return -1;
	return iter - this->childs.begin();
}

ds::DisplayObject* ds::DisplayObjectContainer::getChildByName(std::string name)
{
	auto begin = this->childs.begin();
	auto iter = this->childs.begin();
	while (iter != this->childs.end())
	{
		auto obj = this->childs.at(iter - begin);
		if (obj->name == name)
			return obj;
		iter++;
	}
	return nullptr;
}

bool ds::DisplayObjectContainer::contains(ds::DisplayObject* object)
{
	auto parent = object->parent;
	while (parent)
	{
		if (parent == this)
			return true;
		parent = parent->parent;
	}
	return false;
}

unsigned int ds::DisplayObjectContainer::numChildren()
{
	return this->childs.size();
}

void ds::DisplayObjectContainer::$render()
{
	rlPushMatrix();
	//ds::Math::setTransform(&this->$matrix, this->$values.x, this->$values.y, this->$values.angle, this->$values.scaleX, this->$values.scaleY);
	//rlMultMatrixf(MatrixToFloat(this->$matrix));

	if (this->$values.x != 0.f && this->$values.y != 0.f)
		rlTranslatef(this->$values.x, this->$values.y, 0.f);
	if (this->$values.scaleX != 0.f && this->$values.scaleY != 0.f)
		rlScalef(this->$values.scaleX, this->$values.scaleY, 1);
	if (fmod(this->$values.angle, 360.f))
		rlRotatef(this->$values.angle, 0.0f, 0.0f, 1.0f);
	if (this->$values.pivotX != 0.f && this->$values.pivotY != 0.f)
		rlTranslatef(-this->$values.pivotX, -this->$values.pivotY, 0.f);


	this->$draw();
	this->$drawChildren();

	rlPopMatrix();
}

void ds::DisplayObjectContainer::$drawChildren()
{
	if (!this->childs.empty())
	{
		for (auto child : this->childs) {
			if (child->visible /* || child.alpha <= 0.f */) {
				child->$render();
			}
		}
	}
}

