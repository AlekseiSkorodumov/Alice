#pragma once


// std includes
#include <memory>

// local includes
#include <IPolymorphic.h>


class IModel;

class IObserver: virtual public IPolymorphic<IObserver>
{
public:
    virtual bool OnModelAttached(std::weak_ptr<IModel> modelPtr) = 0;
    virtual bool OnModelDetached(std::weak_ptr<IModel> modelPtr) = 0;
    virtual void BeforeUpdate(std::weak_ptr<IModel> modelPtr) = 0;
    virtual void AfterUpdate(std::weak_ptr<IModel> modelPtr) = 0;
	virtual bool IsModelAttached(const std::weak_ptr<IModel> modelPtr) const = 0;
};


template<class Base>
class TICustomObserver : virtual public IObserver
{
public:
	typedef Base NotificationDataType;

	using IObserver::BeforeUpdate;
	using IObserver::AfterUpdate;

	virtual void BeforeUpdate(std::weak_ptr<IModel> modelPtr, NotificationDataType notificationData) = 0;
	virtual void AfterUpdate(std::weak_ptr<IModel> modelPtr, NotificationDataType notificationData) = 0;
};
