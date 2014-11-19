
#ifndef DRAWUNIT_H
#define DRAWUNIT_H

#include <string>
#include <list>

using namespace std;

struct SRect
{
	int x;
	int y;
	int width;
	int height;
	SRect()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}
	SRect(int _x,int _y ,int _width,int _height)
	{
		x = _x;
		y  = _y;
		width = _width;
		height = _height;
	}
	void operator=(const SRect &pos)
	{
		x = pos.x;
		y   = pos.y;
		width =pos.width;
		height=pos.height;
	}
};

class CDrawUnit
{
public:
	CDrawUnit(void *parent = NULL, unsigned int nID = 0);
	CDrawUnit(void* parent,int x,int y,int width, int height);
	virtual ~CDrawUnit(void);

	virtual void Draw(void * handler) = 0;
	//virtual void ReDraw() = 0;
	virtual void ReadDatas(void) = 0;
	virtual void WriteDatas(void) = 0;
	void SetType(const string &type);
	bool IsKindOf(const string &kind);
	//设置控件区域
	virtual void SetRect(const SRect &rect);
	//获取控件区域
	SRect GetRect() const;
	//void move(const Struct_position &pos);

	void AddItem(CDrawUnit *item);
	void DeleteItem(CDrawUnit *item);
	
protected:
	bool IsInClientArea(int x, int y);
	SRect m_sRect;
	string			m_strType;
	void*			m_pParent;
	void*			m_pHandler;
	unsigned int	m_nID;
	std::list<CDrawUnit *> children;
};

#endif