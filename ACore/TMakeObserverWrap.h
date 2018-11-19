#pragma once


// std includes
#include <cassert>

// local includes
#include <IChangeable.h>
#include <IObserver.h>


template <class Base>
class TMakeObserverWrap: public Base
{
public:
	TMakeObserverWrap();

	// to be reimplemented
	virtual void OnUpdate(std::weak_ptr<IModel> modelPtr);

	// pseudo-reimplemented (IObserver)
	virtual bool OnModelAttached(std::weak_ptr<IModel> modelPtr) override;
	virtual bool OnModelDetached(std::weak_ptr<IModel> modelPtr) override;
	virtual void BeforeUpdate(std::weak_ptr<IModel> modelPtr) override;
	virtual void AfterUpdate(std::weak_ptr<IModel> modelPtr) override;
	virtual bool IsModelAttached(const std::weak_ptr<IModel> modelPtr) const override;

	std::shared_ptr<TMakeObserverWrap<Base>> shared_from_this()
	{
	   return std::dynamic_pointer_cast<TMakeObserverWrap<Base>>(VirtualEnableSharedFromThisBase::shared_from_this());
	}

protected:
	typedef std::list<std::weak_ptr<IModel>> ModelList;
	ModelList m_modelList;
};


// public methods

template <class Base>
TMakeObserverWrap<Base>::TMakeObserverWrap()
{
}


template <class Base>
void TMakeObserverWrap<Base>::OnUpdate(std::weak_ptr<IModel> /*modelPtr*/)
{
}


// pseudo-reimplemented (IObserver)

template <class Base>
bool TMakeObserverWrap<Base>::OnModelAttached(std::weak_ptr<IModel> modelPtr)
{
	std::shared_ptr<IModel> modelInputPtr = modelPtr.lock();
	if (modelInputPtr.get() == NULL){
		return false;
	}

	for (ModelList::const_iterator modelIter = m_modelList.cbegin(); modelIter != m_modelList.cend(); ++modelIter){
		std::shared_ptr<IModel> modelLockedPtr = (*modelIter).lock();
		if (modelLockedPtr.get() == modelInputPtr.get()){
			assert(false);

			return false;
		}
	}

	BeforeUpdate(modelPtr);

	m_modelList.push_back(modelPtr);

	AfterUpdate(modelPtr);

	return true;
}


template <class Base>
bool TMakeObserverWrap<Base>::OnModelDetached(std::weak_ptr<IModel> modelPtr)
{
	std::shared_ptr<IModel> modelInputPtr = modelPtr.lock();
	if (modelInputPtr.get() == NULL){
		return false;
	}

	for (ModelList::const_iterator modelIter = m_modelList.cbegin(); modelIter != m_modelList.cend(); ++modelIter){
		std::shared_ptr<IModel> modelLockedPtr = (*modelIter).lock();
		if (modelLockedPtr.get() == modelInputPtr.get()){
			m_modelList.erase(modelIter);
		}
	}

	return false;
}


template <class Base>
void TMakeObserverWrap<Base>::BeforeUpdate(std::weak_ptr<IModel> /*modelPtr*/)
{
}


template <class Base>
void TMakeObserverWrap<Base>::AfterUpdate(std::weak_ptr<IModel> modelPtr)
{
	OnUpdate(modelPtr);
}


template <class Base>
bool TMakeObserverWrap<Base>::IsModelAttached(const std::weak_ptr<IModel> modelPtr) const
{
	std::shared_ptr<IModel> modelInputPtr = modelPtr.lock();
	if (modelInputPtr.get() == NULL){
		return false;
	}

	for (ModelList::const_iterator modelIter = m_modelList.cbegin(); modelIter != m_modelList.cend(); ++modelIter){
		std::shared_ptr<IModel> modelLockedPtr = (*modelIter).lock();
		if (modelLockedPtr.get() == modelInputPtr.get()){
			return true;
		}
	}

	return false;
}



typedef TMakeObserverWrap<IObserver> CModelObserverBase;
