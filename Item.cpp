#include "Item.h"


Item::Item(ITEM_TYPE t,ITEM_COLOR c,QPoint pt)
{
	m_type = t;
	m_color = c;
	m_pt = pt;
	m_bShow = true;
}


Item::~Item(void)
{
}

void Item::Draw( QPainter& painter )
{

}

void Item::SetPoint( QPoint pt )
{
	m_pt = pt;
}

void Item::SetSelectedStatus()
{
	
}
