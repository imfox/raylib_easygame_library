#include "DisplayObjectContainer.h"
#include "Enum.h"

ds::DisplayObjectContainer::DisplayObjectContainer() {
	isDisplayObjectContainer = true;
}

ds::DisplayObjectContainer::~DisplayObjectContainer()
{
	this->children.clear();
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

ds::DisplayObject* ds::DisplayObjectContainer::addChild(ds::DisplayObject* object, int index) {
	if (object->parent) {
		if (object->parent == this)
			if (this->getChildIndex(object) < index)
				index--;
		object->removeSelf();
	}
	int pos = index < 0 ? (int)this->children.size() : index;
	if (pos <= this->children.size()) {
		this->children.insert(this->children.begin() + pos, object);
		object->parent = this;
		//object->event((int)ds::Event::ADD);
	}
	if (object->$values.zIndex != 0) {
		sortableChildren = true;
		sortDirty = true;
	}
	return object;
}

ds::DisplayObject* ds::DisplayObjectContainer::removeChild(ds::DisplayObject* object) {
	auto index = this->getChildIndex(object);
	if (index >= 0) {
		this->children.erase(this->children.begin() + index);
		object->parent = nullptr;
		sortDirty = true;
		//object->event((int)ds::Event::REMOVE);
		return object;
	}
	return nullptr;
}

std::vector<ds::DisplayObject*> ds::DisplayObjectContainer::removeChild(int index, int end)
{
	std::vector<ds::DisplayObject*> result;
	int size = this->children.size();
	if (index >= size)
		return result;
	auto end_ = std::min(size - 1, std::max(index, end));
	for (int i = 0; i < (end_ - index) + 1; i++)
	{
		auto object = this->children[index];
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
	auto iter = std::find(this->children.begin(), this->children.end(), object);
	if (iter == this->children.end())
		return -1;
	return iter - this->children.begin();
}

ds::DisplayObject* ds::DisplayObjectContainer::getChildByName(std::string name)
{
	auto begin = this->children.begin();
	auto iter = this->children.begin();
	while (iter != this->children.end())
	{
		auto obj = this->children.at(iter - begin);
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
	return this->children.size();
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

	if (!filters.empty() || mask) {
		//TODO
	}

	this->$draw();
	this->$drawChildren();

	rlPopMatrix();
}

void ds::DisplayObjectContainer::$drawChildren() {
	if (!this->children.empty()) {
		if (this->sortableChildren && this->sortDirty)
			this->sortChildren();
		auto& childred = this->sortableChildren ? this->zOrderChilds : this->children;
		for (auto child : childred)
			if (child->visible /* || child.alpha <= 0.f */)
				child->$render();
	}
}

void ds::DisplayObjectContainer::sortChildren() {
	sortDirty = false;
	bool sortRequired = false;
	for (int i = children.size() - 1; i >= 0; i--) {
		auto& child = children[i];
		if (!sortRequired && child->$values.zIndex != 0) {
			sortRequired = true;
			break;
		}
	}
	zOrderChilds = children;
	if (sortRequired) {
		int count = this->numChildren();
		DisplayObject* temp;
		for (int a = 0; a < count - 1; a++)
			for (int b = a + 1; b < count; b++)
				if (zOrderChilds[a]->$values.zIndex > zOrderChilds[b]->$values.zIndex) {
					temp = zOrderChilds[b];
					zOrderChilds[b] = zOrderChilds[a];
					zOrderChilds[a] = temp;
				}
	}
}


