#pragma once


// std includes
#include <list>
#include <memory>

// local includes
#include <IChangeable.h>
#include <IModel.h>
#include <IObserver.h>


class CModelBase : virtual public IModel
{
public:
	CModelBase();
	CModelBase(const CModelBase&) = delete;

	// reimplemented (IModel)
	virtual bool AttachObserver(std::weak_ptr<IObserver> observerPtr) override;
	virtual void DetachObserver(std::weak_ptr<IObserver> observerPtr) override;
	virtual void DetachAllObservers() override;
	virtual bool IsAttached(const std::weak_ptr<IObserver> observerPtr) const override;

protected:
	void NotifyBeforeChange();
	void NotifyAfterChange();

private:
	typedef std::list<std::weak_ptr<IObserver>> ObserverList;
	ObserverList m_observerList;
};
