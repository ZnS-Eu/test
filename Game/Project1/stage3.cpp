#include <easyx.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include "game.h"
#include "loadresource.h"
#include "player.h"
#include "stage.h"
#include "boss.h"
#include "bossbullet.h"
#include "tool.h"
#define  PI 3.14159265

extern IMAGE img[500];
extern Games Game1;
extern Players* Player;
extern Stage* stage;

//Stage3 stage[3];

void Stage3::Createstage()
{
	clear = false;

	int i;
	int n;

	x = 350;
	y = 0;

	tclear = 0;
	for (i = 0; i < 2; i++)
	{
		tim[i] = 5000 + 1000 * i;
	}
	for (i = 0; i < 19; i++)
	{
		tim[i + 19] = 5500 + 3000 * i;
	}
	tim[39] = 30000;
	headboss = new BossA;
	endboss = headboss;
	headboss->Init(0, 0, 0);
	headbullet = new BossBulletA;
	endbullet = headbullet;
	headtool = new Tool1;
	endtool = headtool;
	for (n = 0; n < 70; n++)
	{
		tim2[n] = 1000 + 6000 * n;
	}
}

void Stage3::Clearstage()
{
	int i;
	for (i = 0; i < 20; i++)
	{
		tim[i] = 0;
	}
	/*Boss* a;
	Boss* b;
	a = headboss;
	while (a != NULL)
	{
		b = a;
		a = a->next;
		delete (b);
	}*/

	/*清除自机子弹*/
	headtool = NULL;
	endtool = NULL;
	PlayerBullet* p1;
	PlayerBullet* q1;
	p1 = Player->head;
	q1 = p1;
	while (p1 != NULL)
	{
		q1 = p1;
		p1 = p1->next;
		delete(q1);
	}
	Player->head = NULL;
	/*清除boss*/
	Boss* p2;
	Boss* q2;
	p2 = headboss;
	q2 = p2;
	while (p2 != NULL)
	{
		q2 = p2;
		p2 = p2->next;
		delete(q2);
	}
	headboss = NULL;
	/*清除boss子弹*/
	BossBullets* p3;
	BossBullets* q3;
	p3 = headbullet;
	q3 = p3;
	while (p3 != NULL)
	{
		q3 = p3;
		p3 = p3->next;
		delete(q3);
	}
	headbullet = NULL;
	/*清除道具*/
	/*清除关卡*/
	delete(stage);
	stage = NULL;

	/*清除自机*/
	//delete(Player);
}

void Stage3::Createboss()
{
	int i;
	if (Game1.t >= tim[0] && tim[0] != 0)
	{
		tim[0] = 0;
		Boss* a = new BossE;
		endboss->next = a;
		endboss->next->Init(580, 10, 0);
		endboss = a;
		a = NULL;

	}
	if (Game1.t >= tim[1] && tim[1] != 0)
	{
		tim[1] = 0;
		Boss* a = new BossE;
		endboss->next = a;
		endboss->next->Init(760, 10, 0);
		endboss = a;
		a = NULL;

	}
	if (Game1.t >= tim[39] && tim[39] != 0)
	{
		tim[39] = 0;
		Boss* a = new BossF;
		endboss->next = a;
		endboss->next->Init(680, 15, 0);
		endboss = a;
	}
	Boss* it = headboss;
	while (it != NULL)
	{
		if (it != headboss)
		{
			it->t = (Game1.t - it->t0);   //以毫秒为单位计时
			if (it->state == alive)
			{
				it->Move();
				it->Draw();
			}
			if (it->state == dying)
			{
				it->Drawdying(Game1.t);
			}
			it->Shoot(it);
		}
		it->Check(it);
		it = it->next;
	}

	BossBullets* itt = headbullet;
	while (itt != NULL)
	{
		itt->t = (Game1.t - itt->t0);   //以毫秒为单位计时
		itt->Move();
		itt->Draw();
		itt->BulletCheck();
		itt = itt->next;
	}
	if (Game1.t - stage->tclear > 3000 && stage->tclear != 0)
		stage->clear = true;
}

void Stage3::Creattool()
{
	int n;
	for (n = 0; n < 10; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0)
		{
			tim2[n] = 0;
			Tools* a = new Tool1;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 11; n < 20; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0)
		{
			tim2[n] = 0;
			Tools* a = new Tool5;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 21; n < 30; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0)
		{
			tim2[n] = 0;
			Tools* a = new Tool2;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 31; n < 40; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0)
		{
			tim2[n] = 0;
			Tools* a = new Tool3;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 0; n < 50; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0 && Game1.power < 4)
		{
			tim2[n] = 0;
			Tools* a = new Tool6;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 0; n < 60; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0 && Game1.power < 4)
		{
			tim2[n] = 0;
			Tools* a = new Tool7;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	for (n = 0; n <= 70; n++)
	{
		if (Game1.t > tim2[n] && tim2[n] != 0 && Game1.power < 4)
		{
			tim2[n] = 0;
			Tools* a = new Tool4;
			endtool->next = a;
			endtool->next->Init(rand() % (990 - 370) + 370, 15, 0);
			endtool = a;
		}
	}
	Tools* it = headtool;
	while (it != NULL)
	{
		it->t = (Game1.t - it->t0);   //以毫秒为单位计时
		it->Move();
		it->Draw();
		it->Check();
		it = it->next;
	}
}

void Stage3::Draw()
{
	putimage(stage->x, stage->y, &img[12]);
	putimage(stage->x, stage->y - 767, &img[12]);
	if (stage->y >= 767)
		stage->y = 0;
	stage->y = stage->y + 1;
}


void Stage3::Drawprestage()
{
	long t0 = clock();
	int f = 184;
	BeginBatchDraw();
	while (true)
	{
		if (clock() - t0 >= 100)
		{
			transparentimage(NULL, x, y, &img[f]);
			t0 = clock();
			f++;
		}
		else
		{
			transparentimage(NULL, x, y, &img[f]);
		}
		FlushBatchDraw();
		cleardevice();
		if (f > 197)
			break;
	}
}
