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
	m_sRect.x = x;
	m_sRect.y = y;
	m_sRect.width = width;
	m_sRect.height = height;
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
void CDrawUnit::SetRect(const SRect &rect)
{
	m_sRect = rect;
}

/******************************************************************************
*
*   功能：  获取控件区域
*
******************************************************************************/
SRect CDrawUnit::GetRect() const
{
	return m_sRect;
}

bool CDrawUnit::IsInClientArea(int x, int y)
{
	if ( !((m_sRect.x > x)||((m_sRect.x + m_sRect.width) < x )) 
		&& !((m_sRect.y > y)||((m_sRect.y + m_sRect.height) < y ))  ) 
	{
		return true;
	}
	else
	{
		return false;
	}
	//	return true;
}

void CDrawUnit::AddItem(CDrawUnit *item)
{
	children.push_back(item);
}

void CDrawUnit::DeleteItem(CDrawUnit *item)
{
	std::list<CDrawUnit *>::iterator it = children.begin();
	while( it != children.end() )
	{
		if( *it == item)
			children.erase(it);
		it++;
	}
}