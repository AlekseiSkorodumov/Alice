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
