#include"tetris.hpp"

Tetris::Tetris() { // 构造函数
	area.resize(lines); // 设置棋盘行数
	for(std::size_t i{};i<area.size();++i)
		area[i].resize(cols); // 设置棋盘列数
	forms = { // 参考https://zhuanlan.zhihu.com/p/145339927
		{1,3,5,7}, // I
		{2,4,5,7}, // Z
		{3,5,4,6}, // Z
		{3,5,4,7}, // T
		{2,3,5,7}, // L
		{3,5,7,6}, // J
		{2,3,4,5}, // 田
	};

	window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(360, 720), "Tetris",
		sf::Style::Titlebar | sf::Style::Close // 既有标题栏又有关闭按钮
		); // 创建窗口
	window->setPosition(sf::Vector2i(100, 100)); // 设置窗口位置

	tiles.loadFromFile(""); // 加载方块纹理
	sprite = std::make_shared<sf::Sprite>(); // 创建方块精灵
	sprite->setTexture(tiles); // 设置方块精灵的纹理
	sprite->setTextureRect(sf::IntRect(0, 0, 36, 36)); // 设置方块精灵的纹理矩形

	bg.loadFromFile(""); // 加载背景纹理
	background = std::make_shared<sf::Sprite>(); // 创建背景精灵
	background->setTexture(bg); // 设置背景精灵的纹理
	// 初始化变量
	dirx = score = { 0 }; 
	rotate = gameover = { false }; 
	timercount = { 0.f }; 
	delay = { 0.3f };
	color = { 1 };

	std::uint32_t number = std::rand() % shapes; // 随机生成方块形状
	for (std::size_t i{}; i < squares; ++i) {
		z[i].x = forms[number][i] % 2;
		z[i].y = forms[number][i] / 2;
	}

	font.loadFromFile(""); // 加载字体
	txtScore.setFont(font); // 设置分数文本的字体
	txtScore.setPosition(100.f,10.f); // 设置分数文本的位置
	txtScore.setString("SCORE: " + std::to_string(score));
	txtScore.setCharacterSize(30); // 设置分数文本的字号
	txtScore.setOutlineThickness(3); // 设置分数文本的描边厚度
	
	txtGameOver.setFont(font); // 设置游戏结束文本的字体
	txtGameOver.setPosition(30.f, 300.f); // 设置游戏结束文本的位置
	txtGameOver.setString("GAME OVER"); // 设置游戏结束文本的内容
	txtGameOver.setCharacterSize(50); // 设置游戏结束文本的字号
	txtGameOver.setOutlineThickness(3); // 设置分数文本的描边厚度


	//window->setFramerateLimit(60); // 设置帧率
	//clock.restart(); // 重启时钟
	//resetValues(); // 重置游戏变量

}

void Tetris::events() {
	float time = clock.getElapsedTime().asSeconds(); // 创建以来经过的时间，并将其转换为秒数
	clock.restart(); // 重启时钟
	timercount += time; // 计时器累加

	auto e = std::make_shared<sf::Event>(); // 创建事件
	while (window->pollEvent(*e)) {
		if(e->type== sf::Event::Closed) // 关闭窗口
			window->close();
		if (e->type == sf::Event::KeyPressed) { // 按键事件
			if (e->key.code == sf::Keyboard::Up) // 上键
				rotate = true;
			else if (e->key.code == sf::Keyboard::Right) // 右键
				++dirx;
			else if (e->key.code == sf::Keyboard::Left) // 左键
				--dirx;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		delay = 0.05f; // 按下下键，方块下落速度加快
	}
}

void Tetris::draw() {
	window->clear(sf::Color::Black); // 清屏
	window->draw(*background); // 绘制背景
	for (std::size_t i{}; i < lines; ++i) {
		for (std::size_t j{}; j < cols; ++j) {
			if (area[i][j] != 0) { // 棋盘上没有方块
				sprite->setTextureRect(sf::IntRect(area[i][j] * 36, 0, 36, 36)); // 设置方块精灵的纹理矩形
				sprite->setPosition(j * 36, i * 36); // 设置方块精灵的位置
				window->draw(*sprite); // 绘制方块
			}
		}
	}
	for (std::size_t i{}; i < squares; ++i) {
		sprite->setTextureRect(sf::IntRect(color * 36, 0, 36, 36)); // 设置方块精灵的纹理矩形
		sprite->setPosition(z[i].x * 36, z[i].y * 36); // 设置方块精灵的位置
		window->draw(*sprite); // 绘制方块
	}

	window->draw(txtScore);
	if (gameover)
		window->draw(txtGameOver);
	window->display(); // 显示
}

void Tetris::run() {
	while (window->isOpen()) {
		events();
		if (!gameover) {
			changePosition();
			setRotate();
			moveToDown();
			setScore();
			resetValues();
		}
		draw();
	}
}

void Tetris::moveToDown() {
	if (timercount > delay) { // 计时器大于延迟时间
		for (std::size_t i{}; i < squares; ++i) { // 遍历方块
			k[i] = z[i]; // 保存方块的位置
			++z[i].y; // 方块下移
		}
		if (maxLimit()) { // 判断方块是否到达底部
			for (std::size_t i{}; i < squares; ++i) {
				area[k[i].y][k[i].x] = color; // 将方块的位置设置为方块的颜色
			}
			color = std::rand() % shapes + 1; // 随机生成方块颜色
			std::uint32_t number = std::rand() % shapes; // 随机生成方块形状
			for (std::size_t i{}; i < squares; ++i) {
				z[i].x = forms[number][i] % 2; // 设置方块的位置
				z[i].y = forms[number][i] / 2; // 设置方块的位置
			}
		}
		timercount = 0; // 计时器归零
	}
}

void Tetris::setRotate() { // 旋转
	if (rotate) { // 旋转标志为真
		Coords coords = z[1]; // 保存方块的位置
		for (std::size_t i {}; i < squares; ++i) {
			int x = z[i].y - coords.y; // 旋转
			int y = z[i].x - coords.x;

			z[i].x = coords.x - x;
			z[i].y = coords.y + y;
		}

		if (maxLimit()) { // 边界检测
			for (std::size_t i {}; i < squares; ++i) {
				z[i] = k[i];
			}
		}
	}
}

void Tetris::resetValues() { // 重置值
	dirx = 0;
	rotate = false;
	delay = 0.3f;
}

void Tetris::changePosition() { // 改变位置
	for (std::size_t i {}; i < squares; ++i) {
		k[i] = z[i];
		z[i].x += dirx;
	}

	if (maxLimit()) {
		for (std::size_t i {}; i < squares; ++i) {
			z[i] = k[i];
		}
	}
}

bool Tetris::maxLimit() { // 边界检测
	for (std::size_t i {}; i < squares; ++i) {
		if (z[i].x < 0 ||
			z[i].x >= cols ||
			z[i].y >= lines ||
			area[z[i].y][z[i].x]) {
			return true;
		}
	}
	return false;
}

void Tetris::setScore() { // 设置分数
	std::uint32_t match = lines - 1;
	for (std::size_t i = match; i >= 1; --i) {
		std::uint32_t sum {};
		for (std::size_t j {}; j < cols; ++j) {
			if (area[i][j]) {
				if (i == 1) {
					gameover = true;
				}
				++sum;
			}
			area[match][j] = area[i][j];
		}
		if (sum < cols) {
			--match;
		}
		else {
			txtScore.setString("SCORE: " + std::to_string(++score));
		}
	}
}