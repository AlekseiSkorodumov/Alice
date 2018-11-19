#pragma once


// local includes
#include <CChangeNotification.h>
#include <IChangeable.h>
//std::weak_ptr<TICustomChangeable<NotificationDataType>>

template <class NotificationTypeBase>
class TCustomChangeNotification : public CChangeNotification
{
public:
	typedef NotificationTypeBase NotificationDataType;
	typedef TICustomChangeable<NotificationTypeBase> SourceChangeableType;

	TCustomChangeNotification(std::weak_ptr<SourceChangeableType> sourcePtr, NotificationTypeBase notificationData);
	~TCustomChangeNotification();
	TCustomChangeNotification(const TCustomChangeNotification&) = delete;

private:
	NotificationDataType m_notificationData;
};


template <class NotificationTypeBase>
TCustomChangeNotification<NotificationTypeBase>::TCustomChangeNotification(std::weak_ptr<SourceChangeableType> sourcePtr, NotificationTypeBase notificationData)
	:CChangeNotification(sourcePtr)
{
	m_notificationData = std::move(notificationData);

	std::shared_ptr<SourceChangeableType> sourceSharedPtr = sourcePtr.lock();
	if (sourceSharedPtr.get() != NULL){
		m_sourcePtr = sourcePtr;
		sourceSharedPtr->BeginChanges(m_notificationData);
	}
}


template <class NotificationTypeBase>
TCustomChangeNotification<NotificationTypeBase>::~TCustomChangeNotification()
{
	std::shared_ptr<IChangeable> sourceSharedPtr = m_sourcePtr.lock();
	if (sourceSharedPtr.get() != NULL){
		// \todo ugly or ok?..
		SourceChangeableType* customChangeablePtr = dynamic_cast<SourceChangeableType*>(sourceSharedPtr.get());
		if (customChangeablePtr != NULL){
			customChangeablePtr->EndChanges(m_notificationData);
		}
	}
}


// template class definition

typedef TCustomChangeNotification<std::shared_ptr<IPolymorphic<VirtualEnableSharedFromThisBase>>> CCustomChangeSharedPolymorphic;


