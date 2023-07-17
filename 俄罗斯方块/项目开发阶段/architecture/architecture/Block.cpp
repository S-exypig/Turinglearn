#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "Block.h"
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <fstream>
#include <iostream>
#include <string>

IMAGE* Block::imgs[7] = { nullptr, };
int Block::size = 36;
Block::Block() {
	if (imgs[0] == nullptr) {
		IMAGE tempImg;
		loadimage(&tempImg, L"res/tiles.png");
		SetWorkingImage(&tempImg);
		for (int i = 0; i < 7; i++) {
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);
		}
		SetWorkingImage();
	}
	int blocks[7][4] = {
		1,3,5,7,//I
		2,4,5,7,//Z
		3,5,4,6,//Z
		3,5,4,7,//T
		2,3,5,7,//L
		3,5,7,6,//j
		2,3,4,5,//田
	};
	blockType = rand() % 7 + 1;
	for (int i = 0; i < 4; i++) {
		position[i].row = blocks[blockType - 1][i] / 2;
		position[i].col = blocks[blockType - 1][i] % 2;
	}
	img = imgs[blockType - 1];
}

Block::Block(int reverse) {
	if (imgs[0] == nullptr) {
		IMAGE tempImg;
		loadimage(&tempImg, L"res/tiles.png");
		SetWorkingImage(&tempImg);
		for (int i = 0; i < 7; i++) {
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);
		}
		SetWorkingImage();
	}
	int blocks[7][4] = {
		1,3,5,7,//I
		2,4,5,7,//Z
		3,5,4,6,//Z
		3,5,4,7,//T
		2,3,5,7,//L
		3,5,7,6,//j
		2,3,4,5,//田
	};
	blockType = rand() % 7 + 1;
	for (int i = 0; i < 4; i++) {
		position[i].row = 19 - blocks[blockType - 1][i] / 2;
		position[i].col = blocks[blockType - 1][i] % 2;
	}
	img = imgs[blockType - 1];
}

//Block::Block(double bigMode) {
//}


void Block::drop() {
	for (auto& block : position) {
		block.row++;
	}
}


void Block::dropForReverse() {
	for (int i = 0; i < 4; i++) {
		position[i].row--;
	}
}


void Block::move(int dx) {
	for (int i = 0; i < 4; i++) {
		position[i].col += dx;
	}
}



void Block::rotate() {
	Position p = position[1];
	for (int i = 0; i < 4; i++) {
		Position tmp = position[i];
		position[i].col = p.col - tmp.row + p.row;
		position[i].row = p.row + tmp.col - p.col;
	}
}

void Block::draw(int leftMargin, int topMargin) {
	for (int i = 0; i < 4; i++) {
		int x = leftMargin + position[i].col * size;
		int y = topMargin + position[i].row * size;
		putimage(x, y, img);
	}
}



IMAGE** Block::getImgs() {
	return imgs;
}

Block& Block::operator=(const Block& other) {
	// TODO: 在此处插入 return 语句
	if (this == &other) {
		return *this;
	}
	this->blockType = other.blockType;
	for (int i = 0; i < 4; i++) {
		this->position[i].row = other.position[i].row;
		this->position[i].col = other.position[i].col;
	}
	return *this;
}


bool Block::checkPositionIsValid(const std::vector<std::vector<int>>& map) {
	int rows = map.size();
	int cols = map[0].size();
	for (int i = 0; i < 4; i++) {
		if (position[i].row < 0 || position[i].row >= rows ||
			position[i].col < 0 || position[i].col >= cols ||
			map[position[i].row][position[i].col] != 0) {
			return false;
		}
	}
	return true;
}

void Block::solidy(std::vector<std::vector<int>>& map) {
	for (int i = 0; i < 4; i++) {
		map[position[i].row][position[i].col] = blockType;
	}
}

void Block::drawForReverse(int leftMargin, int topMargin) {
	for (int i = 0; i < 4; i++) {
		int x = leftMargin + position[i].col * size;
		int temp = 19 - position[i].row;
		int y = topMargin + temp * size;
		putimage(x, y, img);
	}
}
