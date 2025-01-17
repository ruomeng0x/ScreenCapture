﻿#include "MainWin.h"


void MainWin::drawSubToolBackground(const int& btnCount, const bool isCenter)
{
	painter->paintCtx->setFillStyle(BLRgba32(255, 255, 255, 255));
	auto x = toolBoxMain.x0 + (double)selectedToolIndex * toolBtnWidth + toolBtnWidth / 2 ;
	auto y = toolBoxMain.y1 + toolBoxSpan / 2;
	painter->paintCtx->fillTriangle(x, y, x + 6, y + toolBoxSpan / 2, x - 6, y + toolBoxSpan / 2);
	if (isCenter) {
		toolBoxSub.x0 = x- btnCount * toolBtnWidth/2;
		toolBoxSub.y0 = toolBoxMain.y1 + toolBoxSpan;
		toolBoxSub.x1 = x + btnCount * toolBtnWidth / 2;
		toolBoxSub.y1 = toolBoxSub.y0 + toolBoxHeight;
	}
	else
	{
		toolBoxSub.x0 = toolBoxMain.x0;
		toolBoxSub.y0 = toolBoxMain.y1 + toolBoxSpan;
		toolBoxSub.x1 = toolBoxSub.x0 + btnCount * toolBtnWidth;
		toolBoxSub.y1 = toolBoxSub.y0 + toolBoxHeight;
	}
	painter->paintCtx->fillBox(toolBoxSub);
}

void MainWin::drawSubTool()
{
	switch (selectedToolIndex)
	{
		case 0:
		{
			drawSubToolNormal(Icon::Name::rectFill);
			break;
		}
		case 1:
		{
			drawSubToolNormal(Icon::Name::ellipseFill);
			break;
		}
		case 2:
		{
			drawSubToolNormal(Icon::Name::arrowFill);
			break;
		}
		case 3://Number		
		{
			drawSubToolNormal(Icon::Name::numberFill);
			break;
		}
		case 4:
		{
			drawSubToolPen();
			break;
		}
		case 5://Line
		{
			drawSubToolLine();
			break;			
		}
		case 6: //Text
		{
			drawSubToolText();
			break;
		}
		case 7: //Mosaic
		{
			drawSubToolMosaic();
			break;
		}
		case 8: //Eraser
		{
			drawSubToolEraser();
			break;
		}
	}
}
void MainWin::drawSubToolNormal(const Icon::Name& icon)
{
	drawSubToolBackground(isFill?9:12);
	BLPoint point;
	point.x = toolBoxSub.x0 + iconLeftMargin;
	point.y = toolBoxSub.y0 + 38;
	drawBtnCheckable(point, icon, isFill, mouseEnterSubToolIndex == 0);	
	if (!isFill) {
		point.x += toolBtnWidth;
		drawStrokeWidthBtns(point, 1);
		drawColorBtns(point, 4);
	}
	else
	{
		drawColorBtns(point, 1);
	}	
}

void MainWin::drawSubToolLine()
{
	drawSubToolBackground(12);
	BLPoint point;
	point.x = toolBoxSub.x0 + iconLeftMargin;
	point.y = toolBoxSub.y0 + 38;
	drawBtnCheckable(point, Icon::Name::transparent, !isFill, mouseEnterSubToolIndex == 0);
	point.x += toolBtnWidth;
	drawStrokeWidthBtns(point, 1);
	drawColorBtns(point, 4);
}

void MainWin::drawSubToolPen()
{
	drawSubToolBackground(11);
	BLPoint point;
	point.x = toolBoxSub.x0 + iconLeftMargin;
	point.y = toolBoxSub.y0 + 38;
	drawStrokeWidthBtns(point,0);
	drawColorBtns(point,3);
}

void MainWin::drawSubToolText()
{
	drawSubToolBackground(8,true);
	BLPoint point;
	point.x = toolBoxSub.x0 + iconLeftMargin - toolBtnWidth;
	point.y = toolBoxSub.y0 + 38;
	drawColorBtns(point, 0);
}

void MainWin::drawSubToolMosaic()
{
	drawSubToolBackground(4,true);
	BLPoint point;
	point.x = toolBoxSub.x0 + iconLeftMargin;
	point.y = toolBoxSub.y0 + 38;
	drawBtnCheckable(point, Icon::Name::rectFill, isFill, mouseEnterSubToolIndex == 0);
	point.x += toolBtnWidth;
	drawStrokeWidthBtns(point, 1);
}

void MainWin::drawSubToolEraser()
{
	drawSubToolBackground(isFill?1:4,true);
	BLPoint point;
	point.x = toolBoxSub.x0 + iconLeftMargin;
	point.y = toolBoxSub.y0 + 38;
	drawBtnCheckable(point, Icon::Name::rectFill, isFill, mouseEnterSubToolIndex == 0);	
	if (!isFill) {
		point.x += toolBtnWidth;
		drawStrokeWidthBtns(point, 1);
	}
}

void MainWin::drawColorBtns(BLPoint& point,const int& index)
{
	for (size_t i = 0; i < std::size(colors); i++)
	{
		point.x += toolBtnWidth;
		Icon::Name name = i == colorBtnIndex ? Icon::Name::colorChecked : Icon::Name::colorUnChecked;
		drawBtnColors(point, name, i==colorBtnIndex, mouseEnterSubToolIndex == index+i, colors[i]);
	}
}

void MainWin::drawStrokeWidthBtns(BLPoint& point,const int& index)
{
	drawBtnStrokeWidth(point, strokeBtnIndex == 0, mouseEnterSubToolIndex == index);
	point.x += toolBtnWidth;
	auto font = Font::Get()->fontIcon;
	font->setSize(56.0f);
	drawBtnStrokeWidth(point, strokeBtnIndex == 1, mouseEnterSubToolIndex == index+1);
	point.x += toolBtnWidth;
	font->setSize(86.0f);
	drawBtnStrokeWidth(point, strokeBtnIndex == 2, mouseEnterSubToolIndex == index+2);
	font->setSize(28.0f);
}

void MainWin::subToolBtnClick()
{
	switch (selectedToolIndex)
	{
		case 0://矩形
		case 1://椭圆
		case 2://箭头
		case 3://标号
		{
			clickSubToolNormal();
			break;
		}
		case 4: //Pen
		{
			clickSubToolPen();
			break;
		}
		case 5://Line
		{
			clickSubToolNormal();
			break;
		}
		case 6://Text
		{
			clickSubToolText();
			break;
		}
		case 7://Mosaic
		{
			clickSubToolMosaic();
			break;
		}
		case 8://Eraser
		{
			clickSubToolEraser();
			break;
		}
	}
}
void MainWin::clickSubToolNormal()
{
	auto index = mouseEnterSubToolIndex;
	if (selectedToolIndex < 4 && index != 0 && isFill) index += 3;
	switch (index)
	{
		case 0:
		{
			isFill = !isFill;
			break;
		}
		case 1:
		case 2:
		case 3:
		{
			strokeBtnIndex = index - 1;
			break;
		}
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		{
			colorBtnIndex = index - 4;
			break;
		}
	}
	InvalidateRect(hwnd, nullptr, false);
}
void MainWin::clickSubToolPen()
{
	switch (mouseEnterSubToolIndex)
	{
	case 0:
	case 1:
	case 2:
	{
		strokeBtnIndex = mouseEnterSubToolIndex;
		break;
	}
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	{
		colorBtnIndex = mouseEnterSubToolIndex - 3;
		break;
	}
	}
	InvalidateRect(hwnd, nullptr, false);
}

void MainWin::clickSubToolMosaic()
{
	switch (mouseEnterSubToolIndex)
	{
		case 0:
		{
			isFill = !isFill;
			break;
		}
		case 1:
		case 2:
		case 3:
		{
			strokeBtnIndex = mouseEnterSubToolIndex-1;
			break;
		}
	}
	InvalidateRect(hwnd, nullptr, false);
}

void MainWin::clickSubToolEraser()
{
	switch (mouseEnterSubToolIndex)
	{
		case 0:
		{
			isFill = !isFill;
			break;
		}
		case 1:
		case 2:
		case 3:
		{
			strokeBtnIndex = mouseEnterSubToolIndex - 1;
			break;
		}
	}
	InvalidateRect(hwnd, nullptr, false);
}

void MainWin::clickSubToolText()
{
	colorBtnIndex = mouseEnterSubToolIndex;
	InvalidateRect(hwnd, nullptr, false);
}