#pragma once


// local includes
#include <IChangeable.h>
#include <TCustomModelBase.h>


template <class Base, class NotificationTypeBase>
class TMakeCustomModelWrap:  public TCustomModelBase<Base, NotificationTypeBase>
{
public:
	typedef TCustomModelBase<Base, NotificationTypeBase> BaseClass;
	typedef NotificationTypeBase NotificationDataType;

    TMakeCustomModelWrap();
	TMakeCustomModelWrap(const TMakeCustomModelWrap<Base, NotificationTypeBase>&) = delete;

    // pseudo-reimplemented (TICustomChangeable)
    virtual void BeginChanges(NotificationDataType notificationData);
    virtual void EndChanges(NotificationDataType notificationData);
};


// public methods

template <class Base, class NotificationTypeBase>
TMakeCustomModelWrap<Base, NotificationTypeBase>::TMakeCustomModelWrap()
{
}


// pseudo-reimplemented (istd::TICustomChangeable)

template <class Base, class NotificationTypeBase>
void TMakeCustomModelWrap<Base, NotificationTypeBase>::BeginChanges(NotificationDataType notificationData)
{
	BaseClass::NotifyBeforeChange(notificationData);
}


template <class Base, class NotificationTypeBase>
void TMakeCustomModelWrap<Base, NotificationTypeBase>::EndChanges(NotificationDataType notificationData)
{
	BaseClass::NotifyAfterChange(notificationData);
}
