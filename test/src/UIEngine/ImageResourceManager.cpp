

#include "ImageResourceManager.h"
#include "../Common/setdebugnew.h"
#include "../Common/xFile/xmemfile.h"

using namespace UIEngine;

CImageResourceManager *CImageResourceManager::m_singelton = NULL;

CImageResourceManager::CImageResourceManager()
{

}

CImageResourceManager::~CImageResourceManager()
{

}


CImageResourceManager *CImageResourceManager::GetInstance()
{
	CImageResourceManager *result = NULL;

	if(m_singelton == NULL)
	{
		m_singelton = new CImageResourceManager();
	}
	result = m_singelton;

	return result;
}