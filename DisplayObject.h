#pragma once
#include "Object.h"
#include "Enum.h"
#include <raylib.h>
#include <rlgl.h>
#include <vector>
#include <string>

namespace ds {
	class DisplayObjectContainer;

	class DisplayObject : public Object
	{
	protected:
		friend DisplayObjectContainer;
		struct Value
		{
			float x = 0.f;
			float y = 0.f;
			int zIndex = 0;
			float width = NAN;
			float height = NAN;
			float left = NAN;
			float right = NAN;
			float top = NAN;
			float bottom = NAN;
			float explicitX = NAN; //��Relative(left)����Layout���ú��X
			float explicitY = NAN; //��Relative(top)����Layout���ú��Y
			float explicitWidth = NAN; //��Relative(left, right)����Layout���ú�Ŀ��
			float explicitHeight = NAN;//��Relative(top, bottom)����Layout���ú�Ŀ��
			float measureWidth = NAN;
			float measureHeight = NAN;
			float scaleX = 1.f;
			float scaleY = 1.f;
			float pivotX = 0.f;
			float pivotY = 0.f;
			float angle = 0.f;
			float alpha = 1.f;
			Color tint = { 0 };
		};
		Value $values;
		Matrix $matrix;

	private:
		Matrix transform;

	protected:
		void $setX(float x);
		void $setY(float y);
		void $setPivotX(float x);
		void $setPivotY(float y);
		void $setAngle(float a);
		void $setWidth(float w);
		void $setHeight(float h);
		void $setScaleX(float x);
		void $setScaleY(float y);


		float $getX();
		float $getY();
		float $getPivotX();
		float $getPivotY();
		float $getAngle();
		float $getWidth();
		float $getHeight();
		float $getScaleX();
		float $getScaleY();

		//void $setCacheAsBitmap(bool state);
		//void $getCacheAsBitmap();
	public:
		static bool defaultTouchEnabled;
		DisplayObjectContainer* parent;
		std::string name = "";
		bool isDisplayObjectContainer = false; //only read ��Ҫ���ⲿ�޸� ���ڵ���ж�ʱ, ����Ļ�֪������

		int tint = 0;
		int zIndex = 0;
		// ���ģʽ
		BlendMode blendMode = BlendMode::NONE;
		// 
		FillMode fillMode = FillMode::SCALE;
		// �ɷ�����Ԫ�� (��ȫ���ܵ����Ҫ��touchChildrenҲ����Ϊfalse)
		bool touchEnabled = defaultTouchEnabled;
		bool touchThrough = false;
		// �ɷ�����Ԫ��
		bool touchChildren = true;
		// ������Ƿ񱻲���Ӱ��
		bool includeInLayout = true;
		bool scrollEnabled = false;
		// ����	
		bool visible = true;
		// �Ƿ񻺴���Ⱦ���ݣ����뱣֤��Ԫ����ȫ���������������Ⱦ(��Դ�������)���Ų��ᵼ����Ⱦ�����쳣
		bool cacheAsBitmap = false;
		// ����
		DisplayObject* mask;
		// �˾�
		std::vector<void*> filters;
		Vector2 mousePosition;

		////Canvas* renderObject;
		void* renderObject;

	public:
		virtual void $render();
		virtual void $draw();
		virtual ~DisplayObject();
		DisplayObject* removeSelf();
		DisplayObject* addTo(DisplayObjectContainer* parent);
		virtual bool operator== (const DisplayObject* b) const;

		DisplayObject* setX(float x);
		float getX();
		DisplayObject* setY(float y);
		float getY();
		DisplayObject* setAngle(float angle);
		float getAngle();
		DisplayObject* setPivotX(float x);
		float getPivotX();
		DisplayObject* setPivotY(float y);
		float getPivotY();
		DisplayObject* setScaleX(float x);
		float getScaleX();
		DisplayObject* setScaleY(float y);
		float getScaleY();
		float getWidth();
		float getHeight();
		void setZIndex(int z);
		int getZIndex();
		DisplayObject* size(float w, float h);

		Vector2 localToParent(float x, float y);
		Vector2 localToParent(Vector2 pos);
		Vector2 parentToLocal(float x, float y);
		Vector2 parentToLocal(Vector2 pos);
		Vector2 localToGlobal(float x, float y);
		Vector2 localToGlobal(Vector2 pos);
		Vector2 globalToLocal(float x, float y);
		Vector2 globalToLocal(Vector2 pos);
		bool hitTest(int x, int y);
	};
}