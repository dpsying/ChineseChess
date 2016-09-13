#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Item.h"
#include "qmap.h"

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void InitItems();
	void NewGame();

	bool FindItemAtPoint(QPoint pt,Item& item);
	bool DeleteItemAtPoint(QPoint pt,bool& bDeleteSHUAI);		//是否打掉的是“帅”或“将”
	void ChangeItemPoint(QPoint ptItem,QPoint pt);
	void SetItemShow(Item item,bool bShow);
	
	bool MoveItem(Item item,QPoint ptMoveTo);

	void DrawItem(QPainter& painter,Item item);

	//获取棋子能移动的区域
	void GetItemCanMoveArea(Item item,QVector<QPoint>& area);
	void GetMoveArea_JU(Item item,QVector<QPoint>& area);
	void GetMoveArea_MA(Item item,QVector<QPoint>& area);
	void GetMoveArea_XIANG(Item item,QVector<QPoint>& area);
	void GetMoveArea_SHI(Item item,QVector<QPoint>& area);
	void GetMoveArea_SHUAI(Item item,QVector<QPoint>& area);
	void GetMoveArea_PAO(Item item,QVector<QPoint>& area);
	void GetMoveArea_BING(Item item,QVector<QPoint>& area);
protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
	void timerEvent(QTimerEvent *);
private:
	//void DrawChessboard();
	//void DrawItems();


private:
    Ui::MainWindow *ui;

	int m_nItemWidth;
	int m_nItemHeight;
	QPixmap m_ItemsImage;

	//QMap<QPoint,Item> m_items;
	QVector<Item> m_items;

	bool m_bHasSelected;
	Item m_SelectedItem;
	//QPoint m_pSelectedItemPoint;

	bool m_bIsRedTurn;	//当前该红棋下
	
};

#endif // MAINWINDOW_H
