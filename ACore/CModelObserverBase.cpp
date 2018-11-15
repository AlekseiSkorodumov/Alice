#include <CModelObserverBase.h>


// std includes
#include <cassert>


// public methods

CModelObserverBase::CModelObserverBase()
{

}


void CModelObserverBase::OnUpdate(std::weak_ptr<IModel> modelPtr)
{
}


// reimplemented (IObserver)

bool CModelObserverBase::OnModelAttached(std::weak_ptr<IModel> modelPtr)
{
	std::shared_ptr<IModel> modelInputPtr = modelPtr.lock();
	if (modelInputPtr.get() == NULL){
		return false;
	}

	for (ModelList::const_iterator modelIter = m_modelList.cbegin(); modelIter != m_modelList.cend(); ++modelIter){
		std::shared_ptr<IModel> modelLockedPtr = (*modelIter).lock();
		if (modelLockedPtr.get() == modelInputPtr.get()){
			assert(false);

			return false;
		}
	}

	BeforeUpdate(modelPtr);

	m_modelList.push_back(modelPtr);

	AfterUpdate(modelPtr);

	return true;
}


bool CModelObserverBase::OnModelDetached(std::weak_ptr<IModel> modelPtr)
{
	std::shared_ptr<IModel> modelInputPtr = modelPtr.lock();
	if (modelInputPtr.get() == NULL){
		return false;
	}

	for (ModelList::const_iterator modelIter = m_modelList.cbegin(); modelIter != m_modelList.cend(); ++modelIter){
		std::shared_ptr<IModel> modelLockedPtr = (*modelIter).lock();
		if (modelLockedPtr.get() == modelInputPtr.get()){
			m_modelList.erase(modelIter);
		}
	}

	return false;
}


void CModelObserverBase::BeforeUpdate(std::weak_ptr<IModel> /*modelPtr*/)
{
}


void CModelObserverBase::AfterUpdate(std::weak_ptr<IModel> modelPtr)
{
	OnUpdate(modelPtr);
}


bool CModelObserverBase::IsModelAttached(const std::weak_ptr<IModel> modelPtr) const
{
	std::shared_ptr<IModel> modelInputPtr = modelPtr.lock();
	if (modelInputPtr.get() == NULL){
		return false;
	}

	for (ModelList::const_iterator modelIter = m_modelList.cbegin(); modelIter != m_modelList.cend(); ++modelIter){
		std::shared_ptr<IModel> modelLockedPtr = (*modelIter).lock();
		if (modelLockedPtr.get() == modelInputPtr.get()){
			return true;
		}
	}

	return false;
}
