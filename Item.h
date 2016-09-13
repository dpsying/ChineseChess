#pragma once
#include "qpainter.h"


enum ITEM_TYPE{
	ITEM_SHUAI = 0,
	ITEM_SHI,
	ITEM_XIANG,
	ITEM_JU,
	ITEM_MA,
	ITEM_PAO,
	ITEM_BING,
	ITEM_MAX,
};

enum ITEM_COLOR{
	COLOR_RED = 0,
	COLOR_BLACK,
	COLOR_MAX,
};

class Item
{
public:
	Item(){}
	Item(ITEM_TYPE t,ITEM_COLOR c,QPoint pt);	
	~Item(void);

	void SetPoint(QPoint pt);
	void Draw(QPainter& painter);

	void SetSelectedStatus();

//private:
public:
	ITEM_TYPE m_type;
	ITEM_COLOR m_color;

	QPoint m_pt;	//Œª÷√
	bool m_bShow;
};

