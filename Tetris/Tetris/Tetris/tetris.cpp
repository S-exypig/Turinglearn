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

