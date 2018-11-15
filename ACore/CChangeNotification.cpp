#include <CChangeNotification.h>


CChangeNotification::CChangeNotification(std::weak_ptr<IChangeable> sourcePtr)
{
	std::shared_ptr<IChangeable> sourceSharedPtr = sourcePtr.lock();
	if (sourceSharedPtr.get() != NULL){
		m_sourcePtr = sourcePtr;
		sourceSharedPtr->BeginChanges();
	}
}

CChangeNotification::~CChangeNotification()
{
	std::shared_ptr<IChangeable> sourceSharedPtr = m_sourcePtr.lock();
	if (sourceSharedPtr.get() != NULL){
		sourceSharedPtr->EndChanges();
	}
}
