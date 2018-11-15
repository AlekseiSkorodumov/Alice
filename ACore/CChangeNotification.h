#pragma once


// std includes
#include <memory>

// local includes
#include <IChangeable.h>


class CChangeNotification
{
public:
	CChangeNotification(std::weak_ptr<IChangeable> sourcePtr);
	~CChangeNotification();
	CChangeNotification(const CChangeNotification&) = delete;


protected:
	std::weak_ptr<IChangeable> m_sourcePtr;
};

