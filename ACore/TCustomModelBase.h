#pragma once


// std includes
#include <list>
#include <memory>

// local includes
#include <IChangeable.h>
#include <IModel.h>
#include <IObserver.h>
#include <CModelBase.h>
#include <TMakeModelWrap.h>


template <class Base, class NotificationTypeBase>
class TCustomModelBase :
		public TMakeModelWrap<Base>
{
public:
	typedef TMakeModelWrap<Base> BaseClass;
	typedef NotificationTypeBase NotificationDataType;

	TCustomModelBase();
	TCustomModelBase(const TCustomModelBase&) = delete;

protected:
	void NotifyBeforeChange(NotificationDataType notificationData);
	void NotifyAfterChange(NotificationDataType notificationData);

protected:
	std::list<NotificationDataType> m_notificationDataDelayedList;
	int m_notificationDelayedCounter;
};


template <class Base, class NotificationTypeBase>
TCustomModelBase<Base, NotificationTypeBase>::TCustomModelBase()
	:m_notificationDelayedCounter(0)
{
}


template <class Base, class NotificationTypeBase>
void TCustomModelBase<Base, NotificationTypeBase>::NotifyBeforeChange(NotificationDataType notificationData)
{
	++m_notificationDelayedCounter;
    for (CModelBase::ObserverList::const_iterator observerIter = BaseClass::m_observerList.cbegin(); observerIter != BaseClass::m_observerList.cend(); ++observerIter){
		std::shared_ptr<IObserver> observerLockedPtr = (*observerIter).lock();
		if (observerLockedPtr.get() != NULL){
			TICustomObserver<NotificationDataType>* customObserverLockedPtr = dynamic_cast<TICustomObserver<NotificationDataType>*>(observerLockedPtr.get());
			if (customObserverLockedPtr != NULL){
                customObserverLockedPtr->BeforeUpdate(BaseClass::shared_from_this(), notificationData);
			}
		}
	}
}


template <class Base, class NotificationTypeBase>
void TCustomModelBase<Base, NotificationTypeBase>::NotifyAfterChange(NotificationDataType notificationData)
{
	m_notificationDataDelayedList.push_back(std::move(notificationData));
	--m_notificationDelayedCounter;
	if (m_notificationDelayedCounter > 0){
		return;
	}

// \todo (or not?) customize notification approach possibility (add each receive current, instead of each receive all)
    for (CModelBase::ObserverList::const_iterator observerIter = BaseClass::m_observerList.cbegin(); observerIter != BaseClass::m_observerList.cend(); ++observerIter){
		std::shared_ptr<IObserver> observerLockedPtr = (*observerIter).lock();
		if (observerLockedPtr.get() != NULL){
			TICustomObserver<NotificationDataType>* customObserverLockedPtr = dynamic_cast<TICustomObserver<NotificationDataType>*>(observerLockedPtr.get());
			if (customObserverLockedPtr != NULL){
				for (NotificationDataType& notificationDataItem : m_notificationDataDelayedList){
                    customObserverLockedPtr->AfterUpdate(BaseClass::shared_from_this(), notificationDataItem);
				}
			}
		}
	}

	m_notificationDataDelayedList.clear();
}
