#include"tetris.hpp"

Tetris::Tetris() { // ���캯��
	area.resize(lines); // ������������
	for(std::size_t i{};i<area.size();++i)
		area[i].resize(cols); // ������������
	forms = { // �ο�https://zhuanlan.zhihu.com/p/145339927
		{1,3,5,7}, // I
		{2,4,5,7}, // Z
		{3,5,4,6}, // Z
		{3,5,4,7}, // T
		{2,3,5,7}, // L
		{3,5,7,6}, // J
		{2,3,4,5}, // ��
	};

	window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(360, 720), "Tetris",
		sf::Style::Titlebar | sf::Style::Close // ���б��������йرհ�ť
		); // ��������
	window->setPosition(sf::Vector2i(100, 100)); // ���ô���λ��

	tiles.loadFromFile(""); // ���ط�������
	sprite = std::make_shared<sf::Sprite>(); // �������龫��
	sprite->setTexture(tiles); // ���÷��龫�������
	sprite->setTextureRect(sf::IntRect(0, 0, 36, 36)); // ���÷��龫����������

	bg.loadFromFile(""); // ���ر�������
	background = std::make_shared<sf::Sprite>(); // ������������
	background->setTexture(bg); // ���ñ������������
	// ��ʼ������
	dirx = score = { 0 }; 
	rotate = gameover = { false }; 
	timercount = { 0.f }; 
	delay = { 0.3f };
	color = { 1 };

	std::uint32_t number = std::rand() % shapes; // ������ɷ�����״
	for (std::size_t i{}; i < squares; ++i) {
		z[i].x = forms[number][i] % 2;
		z[i].y = forms[number][i] / 2;
	}

	font.loadFromFile(""); // ��������
	txtScore.setFont(font); // ���÷����ı�������
	txtScore.setPosition(100.f,10.f); // ���÷����ı���λ��
	txtScore.setString("SCORE: " + std::to_string(score));
	txtScore.setCharacterSize(30); // ���÷����ı����ֺ�
	txtScore.setOutlineThickness(3); // ���÷����ı�����ߺ��
	
	txtGameOver.setFont(font); // ������Ϸ�����ı�������
	txtGameOver.setPosition(30.f, 300.f); // ������Ϸ�����ı���λ��
	txtGameOver.setString("GAME OVER"); // ������Ϸ�����ı�������
	txtGameOver.setCharacterSize(50); // ������Ϸ�����ı����ֺ�
	txtGameOver.setOutlineThickness(3); // ���÷����ı�����ߺ��


	//window->setFramerateLimit(60); // ����֡��
	//clock.restart(); // ����ʱ��
	//resetValues(); // ������Ϸ����

}

void Tetris::events() {
	float time = clock.getElapsedTime().asSeconds(); // ��������������ʱ�䣬������ת��Ϊ����
	clock.restart(); // ����ʱ��
	timercount += time; // ��ʱ���ۼ�

	auto e = std::make_shared<sf::Event>(); // �����¼�
	while (window->pollEvent(*e)) {
		if(e->type== sf::Event::Closed) // �رմ���
			window->close();
		if (e->type == sf::Event::KeyPressed) { // �����¼�
			if (e->key.code == sf::Keyboard::Up) // �ϼ�
				rotate = true;
			else if (e->key.code == sf::Keyboard::Right) // �Ҽ�
				++dirx;
			else if (e->key.code == sf::Keyboard::Left) // ���
				--dirx;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		delay = 0.05f; // �����¼������������ٶȼӿ�
	}
}

void Tetris::draw() {
	window->clear(sf::Color::Black); // ����
	window->draw(*background); // ���Ʊ���
	for (std::size_t i{}; i < lines; ++i) {
		for (std::size_t j{}; j < cols; ++j) {
			if (area[i][j] != 0) { // ������û�з���
				sprite->setTextureRect(sf::IntRect(area[i][j] * 36, 0, 36, 36)); // ���÷��龫����������
				sprite->setPosition(j * 36, i * 36); // ���÷��龫���λ��
				window->draw(*sprite); // ���Ʒ���
			}
		}
	}
	for (std::size_t i{}; i < squares; ++i) {
		sprite->setTextureRect(sf::IntRect(color * 36, 0, 36, 36)); // ���÷��龫����������
		sprite->setPosition(z[i].x * 36, z[i].y * 36); // ���÷��龫���λ��
		window->draw(*sprite); // ���Ʒ���
	}

	window->draw(txtScore);
	if (gameover)
		window->draw(txtGameOver);
	window->display(); // ��ʾ
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
	if (timercount > delay) { // ��ʱ�������ӳ�ʱ��
		for (std::size_t i{}; i < squares; ++i) { // ��������
			k[i] = z[i]; // ���淽���λ��
			++z[i].y; // ��������
		}
		if (maxLimit()) { // �жϷ����Ƿ񵽴�ײ�
			for (std::size_t i{}; i < squares; ++i) {
				area[k[i].y][k[i].x] = color; // �������λ������Ϊ�������ɫ
			}
			color = std::rand() % shapes + 1; // ������ɷ�����ɫ
			std::uint32_t number = std::rand() % shapes; // ������ɷ�����״
			for (std::size_t i{}; i < squares; ++i) {
				z[i].x = forms[number][i] % 2; // ���÷����λ��
				z[i].y = forms[number][i] / 2; // ���÷����λ��
			}
		}
		timercount = 0; // ��ʱ������
	}
}

void Tetris::setRotate() { // ��ת
	if (rotate) { // ��ת��־Ϊ��
		Coords coords = z[1]; // ���淽���λ��
		for (std::size_t i {}; i < squares; ++i) {
			int x = z[i].y - coords.y; // ��ת
			int y = z[i].x - coords.x;

			z[i].x = coords.x - x;
			z[i].y = coords.y + y;
		}

		if (maxLimit()) { // �߽���
			for (std::size_t i {}; i < squares; ++i) {
				z[i] = k[i];
			}
		}
	}
}

void Tetris::resetValues() { // ����ֵ
	dirx = 0;
	rotate = false;
	delay = 0.3f;
}

void Tetris::changePosition() { // �ı�λ��
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

bool Tetris::maxLimit() { // �߽���
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

void Tetris::setScore() { // ���÷���
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