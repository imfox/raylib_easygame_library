#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include <rlgl.h>
#include <raymath.h>

bool ds::DisplayObject::defaultTouchEnabled = true;

void ds::DisplayObject::$setX(float x)
{
	this->$values.x = x;
}

float ds::DisplayObject::$getX() {
	if (this->$values.explicitX) {
		return this->$values.explicitX;
	}
	return this->$values.x;
}

void ds::DisplayObject::$setY(float y) {
	this->$values.y = y;
}

float ds::DisplayObject::$getY() {
	if (this->$values.explicitY) {
		return this->$values.explicitY;
	}
	return this->$values.y;
}

void ds::DisplayObject::$setPivotX(float x)
{
	this->$values.pivotX = x;
}

void ds::DisplayObject::$setPivotY(float y)
{
	this->$values.pivotY = y;
}

void ds::DisplayObject::$setAngle(float a)
{
	this->$values.angle = a;
}

float ds::DisplayObject::$getPivotX()
{
	return this->$values.pivotX;
}

float ds::DisplayObject::$getPivotY()
{
	return this->$values.pivotY;
}

float ds::DisplayObject::$getAngle()
{
	return this->$values.angle;
}

void ds::DisplayObject::$setWidth(float w) {
	this->$values.width = w;
}

float ds::DisplayObject::$getWidth() {
	if (!isnan(this->$values.explicitWidth)) {
		return this->$values.explicitWidth;
	} else if (!isnan(this->$values.width)) {
		return this->$values.width;
	} else if (!isnan(this->$values.measureWidth)) {
		return this->$values.measureWidth;
	}
	return 0;
}

void ds::DisplayObject::$setHeight(float h) {
	this->$values.height = h;
}

float ds::DisplayObject::$getHeight() {
	if (!isnan(this->$values.explicitHeight)) {
		return this->$values.explicitHeight;
	} else if (!isnan(this->$values.height)) {
		return this->$values.height;
	} else if (!isnan(this->$values.measureHeight)) {
		return this->$values.measureHeight;
	}
	return 0;
}

void ds::DisplayObject::$setScaleX(float x) {
	this->$values.scaleX = x;
}

void ds::DisplayObject::$setScaleY(float y)
{
	this->$values.scaleY = y;
}

float ds::DisplayObject::$getScaleX()
{
	return this->$values.scaleX;
}

float ds::DisplayObject::$getScaleY()
{
	return this->$values.scaleY;
}

void ds::DisplayObject::$render()
{
	rlPushMatrix();
	//ds::Math::setTransform(&this->$matrix, this->$values.x, this->$values.y, this->$values.angle, this->$values.scaleX, this->$values.scaleY);

	if (this->$values.x != 0.f || this->$values.y != 0.f)
		rlTranslatef(this->$values.x, this->$values.y, 0.f);
	if (this->$values.scaleX != 1.f || this->$values.scaleY != 1.f)
		rlScalef(this->$values.scaleX, this->$values.scaleY, 1);
	if (fmod(this->$values.angle, 360.f))
		rlRotatef(this->$values.angle, 0.0f, 0.0f, 1.0f);
	if (this->$values.pivotX != 0.f || this->$values.pivotY != 0.f)
		rlTranslatef(-this->$values.pivotX, -this->$values.pivotY, 0.f);

	this->$draw();

	rlPopMatrix();
}



void ds::DisplayObject::$draw()
{
}

ds::DisplayObject::~DisplayObject()
{
	this->parent = nullptr;
}

ds::DisplayObject* ds::DisplayObject::removeSelf()
{
	if (this->parent)
		this->parent->removeChild(this);
	return this;
}

ds::DisplayObject* ds::DisplayObject::addTo(DisplayObjectContainer* parent)
{
	parent->addChild(this);
	return this;
}

bool ds::DisplayObject::operator==(const DisplayObject* b) const
{
	return this == b;
}

ds::DisplayObject* ds::DisplayObject::setAngle(float x)
{
	this->$setAngle(x);
	return this;
}
float ds::DisplayObject::getAngle()
{
	return this->$getAngle();
}

ds::DisplayObject* ds::DisplayObject::setPivotX(float x)
{
	this->$setPivotX(x);
	return this;
}

float ds::DisplayObject::getPivotX()
{
	return this->$getPivotX();
}

ds::DisplayObject* ds::DisplayObject::setPivotY(float y)
{
	this->$setPivotX(y);
	return this;
}

float ds::DisplayObject::getPivotY()
{
	return this->$getPivotY();
}

ds::DisplayObject* ds::DisplayObject::setScaleX(float x)
{
	this->$setScaleX(x);
	return this;
}

float ds::DisplayObject::getScaleX()
{
	return this->$getScaleX();
}

ds::DisplayObject* ds::DisplayObject::setScaleY(float y)
{
	this->$setScaleY(y);
	return this;
}

float ds::DisplayObject::getScaleY()
{
	return this->$getScaleY();
}

float ds::DisplayObject::getWidth()
{
	return this->$getWidth();
}

float ds::DisplayObject::getHeight()
{
	return this->$getHeight();
}

ds::DisplayObject* ds::DisplayObject::size(float w, float h) {
	this->$setWidth(w);
	this->$setHeight(h);
	return this;
}

bool ds::DisplayObject::hitTest(int x, int y)
{
	return x > 0 && y > 0 and x <= this->$getWidth() and y <= this->$getHeight();
}

Vector2 ds::DisplayObject::localToParent(float x, float y)
{
	//scale
	x = x * this->$values.scaleX;
	y = y * this->$values.scaleY;
	//rotate
	auto r = this->$values.angle * PI / 180;
	auto c = cos(r);
	auto s = sin(r);
	auto rx = c * x - s * y;
	auto ry = s * x + c * y;
	x = rx;
	y = ry;
	//translate
	x = x + this->$values.x;
	y = y + this->$values.y;
	return { x, y };
}

Vector2 ds::DisplayObject::localToParent(Vector2 pos)
{
	return localToParent(pos.x, pos.y);
}

Vector2 ds::DisplayObject::parentToLocal(float x, float y)
{
	//translate
	x = x - this->$values.x;
	y = y - this->$values.y;
	//rotate
	auto r = -this->$values.angle * PI / 180;
	auto c = cos(r);
	auto s = sin(r);
	auto rx = c * x - s * y;
	auto ry = s * x + c * y;
	x = rx;
	y = ry;
	//scale
	x = x / this->$values.scaleX;
	y = y / this->$values.scaleY;
	return { x, y };
}

Vector2 ds::DisplayObject::parentToLocal(Vector2 pos)
{
	return parentToLocal(pos.x, pos.y);
}

Vector2 ds::DisplayObject::localToGlobal(float x, float y)
{
	Vector2 r = this->localToParent(x, y);
	auto p = this->parent;
	if (p)
		r = p->localToParent(r);
	return r;
}

Vector2 ds::DisplayObject::localToGlobal(Vector2 pos)
{
	return localToGlobal(pos.x, pos.y);
}

Vector2 ds::DisplayObject::globalToLocal(float x, float y)
{
	auto p = this->parent;
	Vector2	r = { x,y };
	if (p)
		r = p->globalToLocal(r);
	return r;
}

Vector2 ds::DisplayObject::globalToLocal(Vector2 pos)
{
	return globalToLocal(pos.x, pos.y);
}

void ds::DisplayObject::setZIndex(int z) {
	if (parent) {
		parent->sortableChildren = true;
		parent->sortDirty = true;
	}
	this->$values.zIndex = z;
}

int ds::DisplayObject::getZIndex() {
	return this->$values.zIndex;
}
ds::DisplayObject* ds::DisplayObject::setX(float x)
{
	this->$setX(x);
	return this;
}

float ds::DisplayObject::getX()
{
	return this->$getX();
}

ds::DisplayObject* ds::DisplayObject::setY(float y)
{
	this->$setY(y);
	return this;
}

float ds::DisplayObject::getY()
{
	return this->$getY();
}

