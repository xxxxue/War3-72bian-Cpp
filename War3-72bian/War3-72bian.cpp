#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


#include "dm/GetDmObject.h"

Idmsoft* _dm;
long _hwnd;
auto _processName = "Warcraft III";
auto _jinYanAddress = "[[[<Game.dll>+00BE87A4]+30]+1F0]+8c";
auto _liLiangAddress = "[[[<Game.dll>+00BE87A4]+30]+1F0]+94";
auto _minJieAddress = "[[[<Game.dll>+00BE87A4]+30]+1F0]+A8";

auto _zhiLiAddress = "[[[[<Game.dll>+00BC5FF4]+30]+5C]+28]+F8";
auto _firstSkillTimeAddress = "[[[[[[<Game.dll>+00BE9F24]+54]+8]+4]+8]+48]+69C";
auto _yiSuAddress = "[[<Game.dll>+00B59790]+1EC]+70";

auto _positionXAddress = "[<Game.dll>+00BC5FF4]+78";
auto _positionYAddress = "[<Game.dll>+00BC5FF4]+7C";

map<string, string> _bossPositionMap = {
	{"出生点", "49.8,29.4"},
	{"竞技场", "246,201"},

	{"小海龟", "105,135.5"},
	{"小虾兵", "101.6,94"},
	{"蟹将", "187.5,34.2"},

	{"黑熊精", "77.1,362.4"},
	{"白骨精", "142,357.7"},
	{"羊力大仙", "264.5,44.4"},
	{"鹿力大仙", "333.8,127.5"},
	{"虎力大仙", "582.5,230.9"},
	{"九头虫", "500.7,331.7"},
	{"金鱼精", "452.2,448.5"},

	{"主城", "442,548"},

	{"白面狐狸", "585.3,528.8"},
	{"玉面狐狸", "588.4,584.7"},
	{"银角大王", "273.6,489.8"},
	{"金角大王", "296,564.5"},

	{"七蜘蛛", "142.2,604.2"},
	{"五/六蜘蛛", "184.8,455.2"},
	{"剩余蜘蛛", "277.3,342.3"},

	{"红孩儿", "679,593.2"},
	{"铁扇公主", "717.2,414.8"},
	{"牛魔王", "714,332"},

	{"青毛狮子", "658.5,184.7"},
	{"黄牙老象", "721.9,125.1"},
	{"金翅大鹏", "652.3,64.1"},

	{"女儿国巫师", "493.7,715.9"},
	{"女儿国国师", "716.9,714.9"},
	{"女儿国国王", "722.1,648.9"},

	{"黄风怪", "410.5,715.5"},
	{"黄袍怪", "302.2,706.5"},
	{"黄眉大王", "187.9,708.4"},
};

void WriteInt(_bstr_t address, long value)
{
	_dm->WriteInt(_hwnd, address, 0, value);
}
void WriteFloat(_bstr_t address, float value)
{
	_dm->WriteFloat(_hwnd, address, value);
}

void ModifyJingYan(long value)
{
	WriteInt(_jinYanAddress, value);
}

void SetLevel5()
{
	ModifyJingYan(2222);
}
void SetLevel25()
{
	ModifyJingYan(3800);
}
void SetLevelMax()
{
	ModifyJingYan(3821192);
}

void SetLiLiang()
{
	WriteInt(_liLiangAddress, 50000);
}
void SetMinJie()
{
	WriteInt(_minJieAddress, 10000);
}
void SetZhiLi()
{
	WriteInt(_zhiLiAddress, 100000);
}
void SetYiSu()
{
	WriteFloat(_yiSuAddress, 522);
}
void SetFirstSkillTime()
{
	WriteFloat(_firstSkillTimeAddress, 0.3f);
}
void SetPosition(float x, float y)
{
	WriteFloat(_positionXAddress, x);
	WriteFloat(_positionYAddress, y);
}

/// <summary>
/// 分割字符串
/// </summary>
/// <param name="src">要分割的字符串</param>
/// <param name="separator">作为分隔符的字符</param>
/// <param name="dest">存放分割后的字符串的vector向量</param>
void Split(const std::string& src, const std::string& separator, std::vector<std::string>& dest) //字符串分割到数组
{
	string str = src;
	string substring;
	string::size_type start = 0, index;
	dest.clear();
	index = str.find_first_of(separator, start);
	do
	{
		if (index != string::npos)
		{
			substring = str.substr(start, index - start);
			dest.push_back(substring);
			start = index + separator.size();
			index = str.find(separator, start);
			if (start == string::npos) break;
		}
	} while (index != string::npos);

	//the last part
	substring = str.substr(start);
	dest.push_back(substring);
}

/// <summary>
/// 字符串转数字(泛型方法)
/// </summary>
/// <typeparam name="Type">泛型</typeparam>
/// <param name="str">字符串</param>
/// <returns></returns>
template <class Type>
Type StringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

void ShunYi(string bossName)
{
	for (auto& item : _bossPositionMap)
	{
		if (item.first == bossName)
		{
			vector<string> value;
			Split(item.second, ",", value);
			cout << "瞬移:" << bossName << "---" << value[0] << " : " << value[1] << endl;
			SetPosition(StringToNum<float>(value[0]), StringToNum<float>(value[1]));

			break;
		}
	}
}

/// <summary>
/// 移动到某个点,并点击鼠标 (默认是 左键单击)
/// </summary>
/// <param name="pos">xy位置</param>
/// <param name="isLeft">true鼠标左键/false鼠标右键</param>
/// <param name="doubleClick">true双击/false单击</param>
void MoveToClick(int pos[2], bool isLeft = true, bool doubleClick = false)
{
	_dm->MoveTo(pos[0], pos[1]);
	Sleep(500);
	if (isLeft)
	{
		if (doubleClick)
		{
			_dm->LeftClick();
			Sleep(100);
			_dm->LeftClick();
		}
		else {

			_dm->LeftClick();
		}

	}
	else {

		if (doubleClick)
		{
			_dm->RightClick();
			Sleep(100);
			_dm->RightClick();
		}
		else {
			_dm->RightClick();
		}
	}
	Sleep(500);
}
void ClearMsg()
{
	system("cls");
}

void ShowMsg(string msg)
{
	cout << msg << endl;
}

void DelayMsg(string msg, int ms)
{
	for (int i = ms / 1000; i >= 0; i--)
	{
		cout << msg << ": " << i << endl;
		Sleep(1000);
	}
	ClearMsg();
}

void AutoKillBoss()
{

	auto platformTitleName = L"RPG - 魔兽争霸官方对战平台";
	int platformStartGameBtnPosition[2] = { 576, 569 };
	int gameSelectModePosition[2] = { 722, 465 };
	int gameHeroPosition[2] = { 168, 583 };
	int gameHeroHeadImagePosition[2] = { 34, 74 };
	int gameShopPosition[2] = { 871, 216 };
	int gameBabyHeadImagePosition[2] = { 35, 633 };
	int gameNpcPosition[2] = { 380, 249 };
	int gameLiLiangFruitPosition[2] = { 1006, 750 };
	int gameExitBtnPosition[2] = { 629, 76 };

	auto platformHwnd = _dm->FindWindowW("", platformTitleName);

	auto ret = _dm->BindWindow(platformHwnd, "normal", "normal", "normal", 0);

	if (ret == 0)
	{
		cout << "平台窗口绑定失败" << endl;
		return;
	}
	// 点击平台开始游戏按钮
	_dm->MoveTo(platformStartGameBtnPosition[0], platformStartGameBtnPosition[1]);
	_dm->LeftClick();

	DelayMsg("等待加载游戏", 40000);

	_hwnd = _dm->FindWindowW("", _processName);
	cout << "游戏句柄:" << _hwnd << endl;
	if (_hwnd <= 0)
	{
		cout << "游戏窗口绑定失败" << endl;
		return;
	}

	ret = _dm->BindWindow(_hwnd, "normal", "normal", "normal", 0);

	if (ret == 0)
	{
		cout << "平台窗口绑定失败" << endl;
		return;
	}


	DelayMsg("选择模式", 2000);

	// 选择模式
	MoveToClick(gameSelectModePosition);

	DelayMsg("选择英雄", 3000);

	// 双击选择英雄
	MoveToClick(gameHeroPosition, true, true);

	Sleep(5000);

	ShowMsg("移动到商店");

	// 移动到商店
	MoveToClick(gameShopPosition, false);

	Sleep(2000);

	ShowMsg("初始化属性");

	// 初始化属性
	SetLevel5();
	SetLiLiang();
	SetZhiLi();

	Sleep(2000);

	ShowMsg("点击宠物头像");

	// 点击宠物头像	
	MoveToClick(gameBabyHeadImagePosition);

	Sleep(2000);

	ShowMsg("移动到npc");

	// 移动到npc	
	MoveToClick(gameNpcPosition, false);

	Sleep(1000);

	ShowMsg("选择商店");

	// 选择商店
	MoveToClick(gameShopPosition);

	Sleep(1000);

	ShowMsg("点击力量果实");

	// 点击力量果实
	MoveToClick(gameLiLiangFruitPosition);

	Sleep(1000);

	ShowMsg("点击角色头像");

	// 点击角色头像	
	MoveToClick(gameHeroHeadImagePosition);

	Sleep(1000);

	auto initStep = 0;
	for (int i = 0; i < 18; i++)
	{
		ShunYi("小海龟");

		auto jinYanValue = _dm->ReadInt(_hwnd, _jinYanAddress, 0);

		if (initStep == 0 && jinYanValue != 2222)
		{
			ShowMsg("经验max");

			SetLevelMax();
			initStep = 1;
		}

		if (initStep = 1 && jinYanValue > 2222)
		{
			if (_dm->ReadFloat(_hwnd, _firstSkillTimeAddress) >= 1)
			{
				ShowMsg("一技能冷却");

				SetFirstSkillTime();
			}
		}
		Sleep(1000);
	}

	for (int i = 0; i < 10; i++)
	{
		ShunYi("小虾兵");
		Sleep(1000);
	}

	Sleep(3000);

	string igNameArr[5] = { "出生点","竞技场","主城","小海龟","小虾兵" };


	// 扫荡boss
	for (auto& item : _bossPositionMap)
	{
		auto isIg = false;
		for (auto& igItem : igNameArr)
		{
			if (igItem == item.first)
			{
				isIg = true;
				break;
			}
		}

		if (isIg)
		{
			continue;
		}

		ShunYi(item.first);
		Sleep(500);
		ShunYi(item.first);
		Sleep(500);
	}

	DelayMsg("等待结束", 14000);

	ShowMsg("点击退出");

	// 点击退出
	MoveToClick(gameExitBtnPosition);

}


int main()
{
	_dm = GetDmObject();
	cout << "大漠版本:" << _dm->Ver() << endl;

	system("pause");

	AutoKillBoss();
	/*_hwnd = _dm->FindWindowW("", "RPG - 魔兽争霸官方对战平台");
	cout << _hwnd << endl;*/
	system("pause");
}