#pragma once


// std includes
#include <memory>

// local includes
#include <IPolymorphic.h>


class IObserver;


class IModel: virtual public IPolymorphic<IModel>
{
public:
    virtual bool AttachObserver(std::weak_ptr<IObserver> observerPtr) = 0;
    virtual void DetachObserver(std::weak_ptr<IObserver> observerPtr) = 0;
    virtual void DetachAllObservers() = 0; //?
    virtual bool IsAttached(const std::weak_ptr<IObserver> observerPtr) const = 0;
};

