#pragma once


// local includes
#include <IChangeable.h>
#include <CModelBase.h>


template <class Base>
class TMakeModelWrap :
        public CModelBase,
        public Base
{
public:
	typedef CModelBase BaseClass;

	TMakeModelWrap();
	TMakeModelWrap(const TMakeModelWrap<Base>&) = delete;

	// pseudo-reimplemented (IChangeable)
	virtual void BeginChanges();
	virtual void EndChanges();

	std::shared_ptr<TMakeModelWrap<Base>> shared_from_this()
	{
	   return std::dynamic_pointer_cast<TMakeModelWrap<Base>>(VirtualEnableSharedFromThisBase::shared_from_this());
	}
};


// public methods

template <class Base>
TMakeModelWrap<Base>::TMakeModelWrap()
{
}


// pseudo-reimplemented (istd::IChangeable)

template <class Base>
void TMakeModelWrap<Base>::BeginChanges()
{
	BaseClass::NotifyBeforeChange();
}


template <class Base>
void TMakeModelWrap<Base>::EndChanges()
{
	BaseClass::NotifyAfterChange();
}

