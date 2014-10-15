#include "DrawUnit.h"


CDrawUnit::CDrawUnit(void *parent, unsigned int nID)
	: m_pParent(parent)
	, m_nID(nID)
	, m_pHandler(NULL)
{
	SetType("CDrawUnit");
}

CDrawUnit::CDrawUnit(void *parent, int x, int y, int width, int height)
    : m_nID(0)
    , m_pHandler(NULL)
{
	SetType("CDrawUnit");
	m_pParent = parent;
	m_sPosition.x = x;
	m_sPosition.y = y;
	m_sPosition.width = width;
	m_sPosition.height = height;
}

CDrawUnit::~CDrawUnit(void)
{
}

void CDrawUnit::SetType(const string &type)
{
	m_strType = type;
}

bool CDrawUnit::IsKindOf(const string &kind)
{
	return (0==strcmp(kind.c_str(),m_strType.c_str()));
}

/******************************************************************************
*
*   功能：  设置控件区域
*
******************************************************************************/
void CDrawUnit::SetRect(const SRect &pos)
{
	m_sPosition = pos;
}

/******************************************************************************
*
*   功能：  获取控件区域
*
******************************************************************************/
SRect CDrawUnit::GetRect() const
{
	return m_sPosition;
}

bool CDrawUnit::IsInClientArea(int x, int y)
{
	if ( !((m_sPosition.x > x)||((m_sPosition.x + m_sPosition.width) < x )) 
		&& !((m_sPosition.y > y)||((m_sPosition.y + m_sPosition.height) < y ))  ) 
	{
		return true;
	}
	else
	{
		return false;
	}
	//	return true;
}
