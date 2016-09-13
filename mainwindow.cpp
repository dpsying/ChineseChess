#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmessagebox.h"

#define CHESS_ROWS		9
#define CHESS_COLUMES	8
#define RECT_WIDTH		94
#define RECT_HEIGHT		96

#define START_X	(62-RECT_WIDTH/2)		//62-96/2 �������϶�������ֵ��62��76�������̵ĸ��Ӵ�С��96��96��
#define START_Y	(76-RECT_HEIGHT/2)			//76-96/2

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->mainToolBar->hide();
	ui->menuBar->hide();

	//resize((CHESS_COLUMES + 1)*RECT_WIDTH  ,(CHESS_ROWS + 1)*RECT_HEIGHT);

	QPixmap pixChessBoard(":/image/image/ChessBoard.png");
	resize(pixChessBoard.size());

	QPalette palette;
	palette.setBrush( QPalette::Window,QBrush(pixChessBoard));
	setPalette(palette); 
	
	m_ItemsImage = QPixmap(":/image/image/items.png");
	m_nItemWidth = m_ItemsImage.width() / COLOR_MAX;
	m_nItemHeight = m_ItemsImage.height() / ITEM_MAX;

	NewGame();
	startTimer(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent( QPaintEvent * )
{
	QPainter painter(this);
	for (int i = 0; i<m_items.size(); i++)
	{
		DrawItem(painter,m_items[i]);
	}
	update();
}

void MainWindow::DrawItem(QPainter& painter, Item item )
{
	if (!item.m_bShow)
	{
		return;
	}
	QRect rcSrc(m_nItemWidth*item.m_color,m_nItemHeight*item.m_type,m_nItemWidth,m_nItemHeight);


	QRect rcTarget(	START_X + item.m_pt.x()*RECT_WIDTH,
					START_Y + item.m_pt.y()*RECT_HEIGHT,
					RECT_WIDTH,RECT_HEIGHT);

	painter.drawPixmap(rcTarget,m_ItemsImage,rcSrc);
}

void MainWindow::InitItems()
{
	m_items.clear();

	Item item1(ITEM_JU,COLOR_BLACK,QPoint(0,0));
	Item item2(ITEM_MA,COLOR_BLACK,QPoint(1,0));
	Item item3(ITEM_XIANG,COLOR_BLACK,QPoint(2,0));
	Item item4(ITEM_SHI,COLOR_BLACK,QPoint(3,0));
	Item item5(ITEM_SHUAI,COLOR_BLACK,QPoint(4,0));
	Item item6(ITEM_SHI,COLOR_BLACK,QPoint(5,0));
	Item item7(ITEM_XIANG,COLOR_BLACK,QPoint(6,0));
	Item item8(ITEM_MA,COLOR_BLACK,QPoint(7,0));
	Item item9(ITEM_JU,COLOR_BLACK,QPoint(8,0));
	Item item10(ITEM_PAO,COLOR_BLACK,QPoint(1,2));
	Item item11(ITEM_PAO,COLOR_BLACK,QPoint(7,2));
	Item item12(ITEM_BING,COLOR_BLACK,QPoint(0,3));
	Item item13(ITEM_BING,COLOR_BLACK,QPoint(2,3));
	Item item14(ITEM_BING,COLOR_BLACK,QPoint(4,3));
	Item item15(ITEM_BING,COLOR_BLACK,QPoint(6,3));
	Item item16(ITEM_BING,COLOR_BLACK,QPoint(8,3));

	Item item_1(ITEM_JU,COLOR_RED,QPoint(0,9));
	Item item_2(ITEM_MA,COLOR_RED,QPoint(1,9));
	Item item_3(ITEM_XIANG,COLOR_RED,QPoint(2,9));
	Item item_4(ITEM_SHI,COLOR_RED,QPoint(3,9));
	Item item_5(ITEM_SHUAI,COLOR_RED,QPoint(4,9));
	Item item_6(ITEM_SHI,COLOR_RED,QPoint(5,9));
	Item item_7(ITEM_XIANG,COLOR_RED,QPoint(6,9));
	Item item_8(ITEM_MA,COLOR_RED,QPoint(7,9));
	Item item_9(ITEM_JU,COLOR_RED,QPoint(8,9));
	Item item_10(ITEM_PAO,COLOR_RED,QPoint(1,7));
	Item item_11(ITEM_PAO,COLOR_RED,QPoint(7,7));
	Item item_12(ITEM_BING,COLOR_RED,QPoint(0,6));
	Item item_13(ITEM_BING,COLOR_RED,QPoint(2,6));
	Item item_14(ITEM_BING,COLOR_RED,QPoint(4,6));
	Item item_15(ITEM_BING,COLOR_RED,QPoint(6,6));
	Item item_16(ITEM_BING,COLOR_RED,QPoint(8,6));

	m_items.push_back(item1);
	m_items.push_back(item2);
	m_items.push_back(item3);
	m_items.push_back(item4);
	m_items.push_back(item5);
	m_items.push_back(item6);
	m_items.push_back(item7);
	m_items.push_back(item8);
	m_items.push_back(item9);
	m_items.push_back(item10);
	m_items.push_back(item11);
	m_items.push_back(item12);
	m_items.push_back(item13);
	m_items.push_back(item14);
	m_items.push_back(item15);
	m_items.push_back(item16);
	
	m_items.push_back(item_1);
	m_items.push_back(item_2);
	m_items.push_back(item_3);
	m_items.push_back(item_4);
	m_items.push_back(item_5);
	m_items.push_back(item_6);
	m_items.push_back(item_7);
	m_items.push_back(item_8);
	m_items.push_back(item_9);
	m_items.push_back(item_10);
	m_items.push_back(item_11);
	m_items.push_back(item_12);
	m_items.push_back(item_13);
	m_items.push_back(item_14);
	m_items.push_back(item_15);
	m_items.push_back(item_16);

}

void MainWindow::mousePressEvent(QMouseEvent * e)
{
	QPoint pt;
	pt.setX( (e->pos().x() - START_X ) / RECT_WIDTH);
	pt.setY( (e->pos().y() - START_Y ) / RECT_HEIGHT);

	if(m_bHasSelected)
	{
		if (pt == m_SelectedItem.m_pt)
		{
			//�ٴε���Ѿ�ѡ������ӣ�ʲôҲ����
			return;
		}
		Item ClickedItem;
		if (FindItemAtPoint(pt,ClickedItem))
		{
			//�����ͬɫ������һ�����ӣ���ѡ
			if ( (m_bIsRedTurn && ClickedItem.m_color == COLOR_RED) ||
				 (!m_bIsRedTurn && ClickedItem.m_color != COLOR_RED))
			{
				SetItemShow(m_SelectedItem,true);
				m_SelectedItem = ClickedItem;
				return;
			}
		}
		QVector<QPoint> moveArea;
		GetItemCanMoveArea(m_SelectedItem,moveArea);
		if (moveArea.contains(pt))
		{
			bool bDeleteSHUAI = false;
			DeleteItemAtPoint(pt,bDeleteSHUAI);
			ChangeItemPoint(m_SelectedItem.m_pt,pt);
			if (bDeleteSHUAI)
			{
				QString str = m_bIsRedTurn?QStringLiteral("�췽ʤ����"):QStringLiteral("�ڷ�ʤ����");
				QMessageBox::information(NULL,  "GAME OVER  ",str, QMessageBox::Yes , QMessageBox::Yes);
				NewGame();
				return ;
			}
			m_bHasSelected = false;
			m_bIsRedTurn = !m_bIsRedTurn;
			update();
			return ;
		}
		else
		{
			return ;
		}
	}
	else
	{
		Item ClickedItem;
		if (FindItemAtPoint(pt,ClickedItem))
		{
			if ( (m_bIsRedTurn && ClickedItem.m_color == COLOR_RED) ||
				(!m_bIsRedTurn && ClickedItem.m_color == COLOR_BLACK))
			{
				m_SelectedItem = ClickedItem;
				m_bHasSelected = true;
				return;
			}
		}
		
	}

}



bool MainWindow::MoveItem(Item item,QPoint pt)
{
	QVector<QPoint> moveArea;
	GetItemCanMoveArea(item,moveArea);
	if (moveArea.contains(pt))
	{
		bool bDeleteSHUAI = false;
		DeleteItemAtPoint(pt,bDeleteSHUAI);
		ChangeItemPoint(item.m_pt,pt);
		if (bDeleteSHUAI)
		{
			QString str = m_bIsRedTurn?QStringLiteral("�췽ʤ����"):QStringLiteral("�ڷ�ʤ����");
			QMessageBox::information(NULL,  "GAME OVER  ",str, QMessageBox::Yes , QMessageBox::Yes);
			NewGame();
		}
		return true;
	}
	else
	{
		return false;
	}
}


bool MainWindow::FindItemAtPoint(QPoint pt,Item& item)
{
	for (int i = 0; i<m_items.size(); i++)
	{
		if (m_items[i].m_pt == pt)
		{
			item = m_items[i];
			return true;
		}
	}
	return false;
}

bool MainWindow::DeleteItemAtPoint(QPoint pt,bool& bDeleteSHUAI)
{
	bool bDeleted = false;
	for (int i = 0; i<m_items.size(); i++)
	{
		if (m_items[i].m_pt == pt)
		{
			bDeleteSHUAI = (m_items[i].m_type == ITEM_SHUAI);

			m_items.erase(m_items.begin()+i);
			bDeleted = true;
			break;
		}
	}
	return bDeleted;
}


void MainWindow::GetItemCanMoveArea(Item item,QVector<QPoint>& moveArea)
{
	switch (item.m_type)
	{
	case ITEM_JU:
		{
			GetMoveArea_JU(item,moveArea);
			break;
		}
	case ITEM_MA:
		{
			GetMoveArea_MA(item,moveArea);
			break;
		}
	case ITEM_XIANG:
		{
			GetMoveArea_XIANG(item,moveArea);
			break;
		}
	case ITEM_SHI:
		{
			GetMoveArea_SHI(item,moveArea);
			break;
		}
	case ITEM_SHUAI:
		{
			GetMoveArea_SHUAI(item,moveArea);
			break;
		}
	case ITEM_PAO:
		{
			GetMoveArea_PAO(item,moveArea);
			break;
		}
	case ITEM_BING:
		{
			GetMoveArea_BING(item,moveArea);
			break;
		}
	}
}

void MainWindow::ChangeItemPoint(QPoint ptItem,QPoint pt)
{
	for (int i = 0; i<m_items.size(); i++)
	{
		if (m_items[i].m_pt == ptItem)
		{
			m_SelectedItem.m_pt = QPoint(-1,-1);
			m_items[i].m_pt = pt;
			m_items[i].m_bShow = true;
			break;
		}
	}
}

void MainWindow::timerEvent( QTimerEvent * )
{
	for (int i = 0; i<m_items.size(); i++)
	{
		if (m_items[i].m_pt == m_SelectedItem.m_pt)
		{
			m_items[i].m_bShow = !m_items[i].m_bShow;
		}
	}
}

void MainWindow::GetMoveArea_JU(Item item,QVector<QPoint>& moveArea)
{
	//���ӡ������ļ�����ƶ������㷨��飺
	//1����4�����������α����㣬�ѿյ㶼���롣
	//����������ʱֹͣ�������ͬɫ���ӣ������룻����ɫ���ӣ�����루�ô���Ϊ���ߣ���Ϊ���Գ��ӣ�
	//���
	int x = item.m_pt.x() - 1;
	while(x>=0)
	{
		QPoint ptNew = QPoint(x,item.m_pt.y());
		Item item2;
		if (FindItemAtPoint(ptNew ,item2))
		{
			if (item.m_color != item2.m_color)
			{
				moveArea.append(ptNew);
			}
			break;
		}
		moveArea.append(ptNew);
		x--;
	}
	//�ұ�
	x = item.m_pt.x() + 1;
	while(x<=8)
	{
		QPoint ptNew = QPoint(x,item.m_pt.y());
		Item item2;
		if (FindItemAtPoint(ptNew ,item2))
		{
			if (item.m_color != item2.m_color)
			{
				moveArea.append(ptNew);
			}
			break;
		}
		moveArea.append(ptNew);
		x++;
	}

	//�ϱ�
	int y = item.m_pt.y() - 1;
	while(y>=0)
	{
		QPoint ptNew = QPoint(item.m_pt.x(),y);
		Item item2;
		if (FindItemAtPoint(ptNew ,item2))
		{
			if (item.m_color != item2.m_color)
			{
				moveArea.append(ptNew);
			}
			break;
		}
		moveArea.append(ptNew);
		y--;
	}
	//�·�
	y = item.m_pt.y() + 1;
	while(y<=9)
	{
		QPoint ptNew = QPoint(item.m_pt.x(),y);
		Item item2;
		if (FindItemAtPoint(ptNew ,item2))
		{
			if (item.m_color != item2.m_color)
			{
				moveArea.append(ptNew);
			}
			break;
		}
		moveArea.append(ptNew);
		y++;
	}
}

void MainWindow::GetMoveArea_MA( Item item,QVector<QPoint>& moveArea )
{
	//���ӡ����ļ�����ƶ������㷨��飺
	//1�����8����ѡλ�ã�8��λ�õ�ƫ���ǣ�-2��-1����-2��1����2��-1����2��1����1��-2����1��2����-1��-2����-1��2�����ڹ�ϵ��|x|+|y|=3
	//2���жϴ�ѡλ���Ƿ���������
	//3���ж��м��Ƿ��п�λ������
	//4��λ�����Ƿ��Ѵ���ͬɫ����
	Item item2;
	for (int i = -2; i<=2; i++)
	{
		for(int j = -2; j<=2; j++)
		{
			if (qAbs(i) + qAbs(j) == 3)
			{
				QPoint ptNew = item.m_pt + QPoint(i,j);
				if (ptNew.x() >= 0 && ptNew.x() <= 8 && ptNew.y()>=0 && ptNew.y() <= 9)
				{

				}
				else
				{
					continue;
				}

				//��÷�������·�ߵ� ��λԪ��λ��
				QPoint ptDirect(0,0);	
				if (qAbs(i) > qAbs(j))
				{
					if (i>0)
					{
						ptDirect = QPoint(1,0);
					}
					else
					{
						ptDirect = QPoint(-1,0);
					}
				}
				else
				{
					if (j>0)
					{
						ptDirect = QPoint(0,1);
					}
					else
					{
						ptDirect = QPoint(0,-1);
					}
				}
				QPoint ptHit = item.m_pt + ptDirect;	//��Ŀ�λԪ��λ��
				if (FindItemAtPoint(ptHit,item2))
				{
					//��λ
					continue;
				}
				if (FindItemAtPoint(ptNew ,item2) && item.m_color == item2.m_color)
				{
					//�б���item
					continue;
				}
				moveArea.append(ptNew);
			}
		}
	}
}

void MainWindow::GetMoveArea_XIANG( Item item,QVector<QPoint>& moveArea )
{
	//���ӡ��ࡱ�ļ�����ƶ������㷨��飺
	//1�����4����ѡλ��
	//2���ж��Ƿ��ڸá��ࡱ��Ӧ�İ��������
	//3���ж��м��Ƿ��п�λ������
	//4��λ�����Ƿ��Ѵ���ͬɫ����
	QVector<QPoint> directions;
	directions.push_back(QPoint(-2,-2));
	directions.push_back(QPoint(2,-2));
	directions.push_back(QPoint(2,2));
	directions.push_back(QPoint(-2,2));

	for (int i = 0; i<directions.size(); i++)
	{
		QPoint ptNew = item.m_pt + directions[i];									//�ƶ���ĵ�
		if (item.m_pt.y() <= 4)														//�Ϸ���
		{
			if (ptNew.x() >= 0 && ptNew.x() <= 8 && ptNew.y()>=0 && ptNew.y() <= 4)		//�ƶ����������ϰ�����
			{

			}
			else
			{
				continue;
			}
		}
		else
		{
			if (ptNew.x() >= 0 && ptNew.x() <= 8 && ptNew.y()>=5 && ptNew.y() <= 9)		//�ƶ����������°�����
			{

			}
			else
			{
				continue;
			}
		}

		QPoint ptHit = item.m_pt + QPoint(directions[i].x()/2,directions[i].y()/2);		//��λ�����е�
		Item item2;
		if (FindItemAtPoint(ptHit,item2))
		{
			//���ڿ�λ����
			continue;
		}
		if (FindItemAtPoint(ptNew ,item2) && item.m_color == item2.m_color)
		{
			//�յ���ͬɫ������
			continue;
		}
		moveArea.append(ptNew);
	}
}

void MainWindow::GetMoveArea_SHI( Item item,QVector<QPoint>& moveArea )
{
	//�ƶ��㷨��������
	//4����ѡ��λ��ƫ��
	QVector<QPoint> directions;
	directions.push_back(QPoint(-1,-1));
	directions.push_back(QPoint(1,-1));
	directions.push_back(QPoint(1,1));
	directions.push_back(QPoint(-1,1));

	for (int i = 0; i<directions.size(); i++)
	{
		QPoint ptNew = item.m_pt + directions[i];									//�ƶ���ĵ�
		if (item.m_pt.y() <= 4)														//�Ϸ���
		{
			if (ptNew.x() >= 3 && ptNew.x() <= 5 && ptNew.y()>=0 && ptNew.y() <= 2)		//�ƶ����������̵�(3,0)~(5,2)������
			{

			}
			else
			{
				continue;
			}
		}
		else
		{
			if (ptNew.x() >= 3 && ptNew.x() <= 5 && ptNew.y()>=7 && ptNew.y() <= 9)		//�ƶ����������°�����
			{

			}
			else
			{
				continue;
			}
		}

		//QPoint ptHit = item.m_pt + QPoint(directions[i].x()/2,directions[i].y()/2);		//��λ�����е�
		Item item2;
		//if (FindItemAtPoint(ptHit,item2))
		//{
		//	//���ڿ�λ������
		//	continue;
		//}
		if (FindItemAtPoint(ptNew ,item2) && item.m_color == item2.m_color)
		{
			//�յ���ͬɫ������
			continue;
		}
		moveArea.append(ptNew);
	}
}

void MainWindow::GetMoveArea_SHUAI( Item item,QVector<QPoint>& moveArea )
{
	QVector<QPoint> directions;
	directions.push_back(QPoint(-1,0));
	directions.push_back(QPoint(1,0));
	directions.push_back(QPoint(0,1));
	directions.push_back(QPoint(0,-1));

	for (int i = 0; i<directions.size(); i++)
	{
		QPoint ptNew = item.m_pt + directions[i];									//�ƶ���ĵ�
		if (item.m_pt.y() <= 4)														//�Ϸ���
		{
			if (ptNew.x() >= 3 && ptNew.x() <= 5 && ptNew.y()>=0 && ptNew.y() <= 2)		//�ƶ����������̵�(3,0)~(5,2)������
			{

			}
			else
			{
				continue;
			}
		}
		else
		{
			if (ptNew.x() >= 3 && ptNew.x() <= 5 && ptNew.y()>=7 && ptNew.y() <= 9)		//�ƶ����������°�����
			{

			}
			else
			{
				continue;
			}
		}
		Item item2;
		if (FindItemAtPoint(ptNew ,item2) && item.m_color == item2.m_color)
		{
			//�յ���ͬɫ������
			continue;
		}
		moveArea.append(ptNew);
	}
}

void MainWindow::GetMoveArea_PAO( Item item,QVector<QPoint>& moveArea )
{
	//�ڵĿ��ƶ������Ϊ�����֣���һ����ͬ���������ڶ�����Ϊֱ���ϸ�һ�����Ӻ����ɫ����
	//QVector<QPoint> juMoveArea;
	//GetMoveArea_JU(item,moveArea);

	//���
	bool bFind = false;
	int x = item.m_pt.x() - 1;
	while(x>=0)
	{
		QPoint ptNew = QPoint(x,item.m_pt.y());
		Item item2;
		if (FindItemAtPoint(ptNew ,item2))
		{
			if (bFind)
			{
				//���֮ǰ�ҵ���һ���㣬��ô���ǵ�2����
				if(item.m_color != item2.m_color)
				{
					//������2��������ɫ�ģ���ô�ǿ��ԳԵ�
					moveArea.append(ptNew);
				}
				break;
			}
			bFind = true;
			x--;
			continue;
		}
		if (!bFind)
		{
			moveArea.append(ptNew);
		}
		x--;
		
	}
	//�ұ�
	bFind = false;
	x = item.m_pt.x() + 1;
	while(x<=8)
	{
		QPoint ptNew = QPoint(x,item.m_pt.y());
		Item item2;
		if (FindItemAtPoint(ptNew ,item2))
		{
			if (bFind)
			{
				//���֮ǰ�ҵ���һ���㣬��ô���ǵ�2����
				if(item.m_color != item2.m_color)
				{
					//������2��������ɫ�ģ���ô�ǿ��ԳԵ�
					moveArea.append(ptNew);
				}
				break;
			}
			bFind = true;
			x++;
			continue;
		}
		if (!bFind)
		{
			moveArea.append(ptNew);
		}
		x++;
		
	}

	//�ϱ�
	bFind = false;
	int y = item.m_pt.y() - 1;
	while(y>=0)
	{
		QPoint ptNew = QPoint(item.m_pt.x(),y);
		Item item2;
		if (FindItemAtPoint(ptNew ,item2))
		{
			if (bFind)
			{
				//���֮ǰ�ҵ���һ���㣬��ô���ǵ�2����
				if(item.m_color != item2.m_color)
				{
					//������2��������ɫ�ģ���ô�ǿ��ԳԵ�
					moveArea.append(ptNew);
				}
				break;
			}
			bFind = true;
			y--;
			continue;
		}
		if (!bFind)
		{
			moveArea.append(ptNew);
		}
		y--;
		
	}
	//�·�
	bFind = false;
	y = item.m_pt.y() + 1;
	while(y<=9)
	{
		QPoint ptNew = QPoint(item.m_pt.x(),y);
		Item item2;
		if (FindItemAtPoint(ptNew ,item2))
		{
			if (bFind)
			{
				//���֮ǰ�ҵ���һ���㣬��ô���ǵ�2����
				if(item.m_color != item2.m_color)
				{
					//������2��������ɫ�ģ���ô�ǿ��ԳԵ�
					moveArea.append(ptNew);
				}
				break;
			}
			bFind = true;
			y++;
			continue;
		}
		if (!bFind)
		{
			moveArea.append(ptNew);
		}
		y++;
		
	}
}

void MainWindow::GetMoveArea_BING( Item item,QVector<QPoint>& moveArea )
{
	QVector<QPoint> directions;
	
	if (item.m_color == COLOR_RED)
	{
		directions.push_back(QPoint(0,-1));	//��ɫ����
		if (item.m_pt.y() < 5 )			//��ɫ���·���y<5�����Ѿ����ӣ����Ժ����ƶ�
		{
			directions.push_back(QPoint(-1,0));
			directions.push_back(QPoint(1,0));
		}
	}
	else
	{
		directions.push_back(QPoint(0,1));	//��ɫ����
		if (item.m_pt.y() >= 5 )			//��ɫ���Ϸ���y>=5�����Ѿ����ӣ����Ժ����ƶ�
		{
			directions.push_back(QPoint(-1,0));
			directions.push_back(QPoint(1,0));
		}
	}

	for (int i = 0; i<directions.size(); i++)
	{
		QPoint ptNew = item.m_pt + directions[i];									//�ƶ���ĵ�
		if (ptNew.x() >= 0 && ptNew.x() <= 8 && ptNew.y()>=0 && ptNew.y() <= 9)		//�ƶ�������������
		{

		}
		else
		{
			continue;
		}
		Item item2;
		if (FindItemAtPoint(ptNew ,item2) && item.m_color == item2.m_color)
		{
			//�յ���ͬɫ������
			continue;
		}
		moveArea.append(ptNew);
	}

}

void MainWindow::NewGame()
{
	InitItems();
	m_SelectedItem.m_pt = QPoint(-1,-1);
	m_bIsRedTurn = true;
	m_bHasSelected = false;
	
	
}

void MainWindow::SetItemShow( Item item,bool bShow )
{
	for (int i = 0; i<m_items.size(); i++)
	{
		if (m_items[i].m_pt == item.m_pt)
		{
			m_items[i].m_bShow = bShow;
			break;
		}
	}
}


