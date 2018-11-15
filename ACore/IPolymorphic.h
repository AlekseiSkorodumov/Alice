#pragma once

#include <memory>


struct VirtualEnableSharedFromThisBase : std::enable_shared_from_this<VirtualEnableSharedFromThisBase>
{
	virtual ~VirtualEnableSharedFromThisBase()
	{
	}
};


template<typename T>
struct IPolymorphic : virtual VirtualEnableSharedFromThisBase
{
	std::shared_ptr<T> shared_from_this()
	{
	   return std::dynamic_pointer_cast<T>(VirtualEnableSharedFromThisBase::shared_from_this());
	}
};

//struct A: VirtualEnableSharedFromThis<A> {};
//struct B: VirtualEnableSharedFromThis<B> {};
//struct Z: A, B { };
//int main() {
//   std::shared_ptr<Z> z = std::make_shared<Z>();
//   std::shared_ptr<B> b = z->B::shared_from_this();
//}


/**
	Base interface for all other interfaces
*/
//class IPolymorphic// : public std::enable_shared_from_this<IPolymorphic>
//{
//public:
//	virtual ~IPolymorphic()
//	{
//	}
//};
