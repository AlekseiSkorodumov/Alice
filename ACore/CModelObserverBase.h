#pragma once


// std includes
#include <list>
#include <memory>

// local includes
#include <IChangeable.h>
#include <IObserver.h>


class CModelObserverBase : virtual public IObserver,
		public std::enable_shared_from_this<IObserver>
{
public:
	CModelObserverBase();

	// to be reimplemented
	virtual void OnUpdate(std::weak_ptr<IModel> modelPtr);

	// reimplemented (IObserver)
	virtual bool OnModelAttached(std::weak_ptr<IModel> modelPtr) override;
	virtual bool OnModelDetached(std::weak_ptr<IModel> modelPtr) override;
	virtual void BeforeUpdate(std::weak_ptr<IModel> modelPtr) override;
	virtual void AfterUpdate(std::weak_ptr<IModel> modelPtr) override;
	virtual bool IsModelAttached(const std::weak_ptr<IModel> modelPtr) const override;

private:
	typedef std::list<std::weak_ptr<IModel>> ModelList;
	ModelList m_modelList;
};
