#include <CModelBase.h>


// std includes
#include <algorithm>
#include <cassert>

// public methods

CModelBase::CModelBase()
{

}


// reimplemented (IModel)

bool CModelBase::AttachObserver(std::weak_ptr<IObserver> observerPtr)
{
	std::shared_ptr<IObserver> observerInputPtr = observerPtr.lock();
	if (observerInputPtr.get() == NULL){
		return false;
	}

	for (ObserverList::iterator observerIter = m_observerList.begin(); observerIter != m_observerList.end(); ++observerIter){
		std::shared_ptr<IObserver> observerLockedPtr = (*observerIter).lock();
		if (observerLockedPtr.get() == observerInputPtr.get()){
			assert(false);
			return true;
		}
	}

	m_observerList.push_back(observerPtr);

	observerInputPtr->OnModelAttached(shared_from_this());

	return true;
}


void CModelBase::DetachObserver(std::weak_ptr<IObserver> observerPtr)
{
	std::shared_ptr<IObserver> observerInputPtr = observerPtr.lock();
	if (observerInputPtr.get() == NULL){
		return;
	}

	for (ObserverList::const_iterator observerIter = m_observerList.cbegin(); observerIter != m_observerList.cend(); ++observerIter){
		std::shared_ptr<IObserver> observerLockedPtr = (*observerIter).lock();
		if (observerLockedPtr.get() == observerInputPtr.get()){
			m_observerList.erase(observerIter);

			observerInputPtr->OnModelDetached(shared_from_this());

			return;
		}
	}
}


void CModelBase::DetachAllObservers()
{
	m_observerList.clear();
}


bool CModelBase::IsAttached(const std::weak_ptr<IObserver> observerPtr) const
{
	std::shared_ptr<IObserver> observerInputPtr = observerPtr.lock();
	if (observerInputPtr.get() == NULL){
		return false;
	}

	for (ObserverList::const_iterator observerIter = m_observerList.cbegin(); observerIter != m_observerList.cend(); ++observerIter){
		std::shared_ptr<IObserver> observerLockedPtr = (*observerIter).lock();
		if (observerLockedPtr.get() == observerInputPtr.get()){
			return true;
		}
	}

	return false;
}


// protected methods

void CModelBase::NotifyBeforeChange()
{
	for (ObserverList::const_iterator observerIter = m_observerList.cbegin(); observerIter != m_observerList.cend(); ++observerIter){
		std::shared_ptr<IObserver> observerLockedPtr = (*observerIter).lock();
		if (observerLockedPtr.get() != NULL){
			observerLockedPtr->BeforeUpdate(shared_from_this());
		}
	}
}


void CModelBase::NotifyAfterChange()
{
	for (ObserverList::const_iterator observerIter = m_observerList.cbegin(); observerIter != m_observerList.cend(); ++observerIter){
		std::shared_ptr<IObserver> observerLockedPtr = (*observerIter).lock();
		if (observerLockedPtr.get() != NULL){
			observerLockedPtr->AfterUpdate(shared_from_this());
		}
	}
}
