//#include "NetworkCommon.h"
//
//void NetworkCommon::loop(float fElapsedTime)
//{
//	for (Object* o : instances)
//	{
//		o->loop(fElapsedTime);
//	}
//
//	drawList.remove_if([&](const Drawable* d)
//		{
//			return d->removeFlag;
//		});
//
//	instances.remove_if([&](const Object* o)
//		{
//			if (o->removeFlag)
//			{
//				delete o;
//				return true;
//			}
//			else
//			{
//				return false;
//			}
//		});
//}
//
//void NetworkCommon::draw(float fElapsedTime)
//{
//	drawList.sort([&](const Drawable* d1, const Drawable* d2) { return d1->depth > d2->depth; });
//
//	for (Drawable* d : drawList)
//	{
//		d->draw(this);
//	}
//}
//
//bool NetworkCommon::OnUserCreate()
//{
//	return true;
//}
//
//bool NetworkCommon::OnUserUpdate(float fElapsedTime)
//{
//	loop();
//	draw(fElapsedTime);
//
//	return true;
//}
