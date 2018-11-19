#pragma once


// std includes
#include <memory>

// local includes
#include <IPolymorphic.h>


class IChangeable : virtual public IPolymorphic<IChangeable>
{
public:
	virtual void BeginChanges()
	{
	}
	virtual void EndChanges()
	{
	}
};


template<class Base>
class TICustomChangeable : virtual public IChangeable
{
public:
	typedef Base NotificationDataType;

	using IChangeable::BeginChanges;
	using IChangeable::EndChanges;

    virtual void BeginChanges(NotificationDataType /*notificationData*/)
	{
	}

    virtual void EndChanges(NotificationDataType /*notificationData*/)
	{
	}
};
