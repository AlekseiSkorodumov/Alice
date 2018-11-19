#pragma once


// local includes
#include <IObserver.h>
#include <TMakeObserverWrap.h>


template <class NotificationTypeBase>
class TCustomModelObserver :
		public TMakeObserverWrap<
				TICustomObserver<NotificationTypeBase> >
{
public:
	typedef NotificationTypeBase NotificationDataType;

	TCustomModelObserver();

	// to be reimplemented
	virtual void OnUpdate(std::weak_ptr<IModel> modelPtr, NotificationDataType notificationData);

	// reimplemented (TICustomObserver)
	virtual void BeforeUpdate(std::weak_ptr<IModel> modelPtr, NotificationDataType notificationData) override;
	virtual void AfterUpdate(std::weak_ptr<IModel> modelPtr, NotificationDataType notificationData) override;
};


// public methods

template <class NotificationTypeBase>
TCustomModelObserver<NotificationTypeBase>::TCustomModelObserver()
{
}


template <class NotificationTypeBase>
void TCustomModelObserver<NotificationTypeBase>::OnUpdate(std::weak_ptr<IModel> /*modelPtr*/, NotificationDataType /*notificationData*/)
{
}


// reimplemented (TICustomObserver)

template <class NotificationTypeBase>
void TCustomModelObserver<NotificationTypeBase>::BeforeUpdate(std::weak_ptr<IModel> /*modelPtr*/, NotificationDataType /*notificationData*/)
{
}


template <class NotificationTypeBase>
void TCustomModelObserver<NotificationTypeBase>::AfterUpdate(std::weak_ptr<IModel> modelPtr, NotificationDataType notificationData)
{
	OnUpdate(modelPtr, notificationData);
}



// pseudo-reimplemented (IObserver)
