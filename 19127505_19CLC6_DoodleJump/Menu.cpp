#include "header.h"

bool isInSprite(const Sprite& sprite, const RenderWindow& window) {
	if (Mouse::getPosition(window).x > sprite.getGlobalBounds().left &&
		Mouse::getPosition(window).x < (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) &&
		Mouse::getPosition(window).y > sprite.getGlobalBounds().top&&
		Mouse::getPosition(window).y < (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height))
		return true;
	return false;
}

//MAIN MENU

mainMenu::mainMenu(texture& textureList,int musicOpt) {
	sPlay.setTexture(*textureList.Play); sLeaderboard.setTexture(*textureList.Leaderboard); 
	sExit.setTexture(*textureList.Exit); sBg.setTexture(*textureList.Background);
	sLogo.setTexture(*textureList.Logo);

	if(musicOpt)
		sSound.setTexture(*textureList.Unmute);
	else
		sSound.setTexture(*textureList.Mute);

	sLogo.setPosition(340,25);
	sSound.setPosition(900, 220);
	sPlay.setPosition(450, 220);
	sLeaderboard.setPosition(450, 340);
	sExit.setPosition(450, 460);
}

void mainMenu::draw(RenderWindow &app) {
	app.draw(sBg);
	app.draw(sPlay);
	app.draw(sLogo);
	app.draw(sLeaderboard);
	app.draw(sExit);
	app.draw(sSound);
}

int mainMenu::getChoice(RenderWindow &app) {
	Event event;
	while (app.pollEvent(event)) {
		if (event.type == Event::Closed)
			app.close();

		//click on a sprite
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button==Mouse::Left) {
			if (isInSprite(sPlay, app))
				return 1;
			if (isInSprite(sLeaderboard, app))
				return 2;
			if (isInSprite(sExit, app))
				return 3;
			if (isInSprite(sSound, app)) {
				return 4;
			}
		}
	}
	return -1;
}






//LOSE MENU

loseMenu::loseMenu(texture& textureList,int score){
	sRetry.setTexture(*textureList.Retry); sReturn2.setTexture(*textureList.Return2); sBg.setTexture(*textureList.Background);
	sRetry.setPosition(450,250);
	sReturn2.setPosition(450, 370);

	bahnschrift.loadFromFile("font/bahnschrift.ttf");
	tScore.setFont(bahnschrift);
	tScore.setString("Your Score: " + std::to_string(score));
	tScore.setPosition(500, 100);
	tScore.setCharacterSize(30);
	tScore.setFillColor(Color::White);
	tScore.setStyle(Text::Bold);
}

void loseMenu::draw(RenderWindow& app) {
	app.draw(sBg);
	app.draw(tScore);
	app.draw(sRetry);
	app.draw(sReturn2);
}

int loseMenu::getChoice(RenderWindow& app) {
	Event event;
	while (app.pollEvent(event)) {
		if (event.type == Event::Closed)
			app.close();

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (isInSprite(sRetry, app))
				return 1;
			if (isInSprite(sReturn2, app))
				return 2;
		}
	}
	return -1;
}




//LEADERBOARD MENU

leaderboardMenu::leaderboardMenu(texture& textureList) {
	sBg.setTexture(*textureList.Background); sLead.setTexture(*textureList.Leaderboard2); sReturn.setTexture(*textureList.Return);
	sReturn.setPosition(1000, 480);

	bahnschrift.loadFromFile("font/bahnschrift.ttf");
	tScore.setFont(bahnschrift);
	tScore.setCharacterSize(25);
	tScore.setFillColor(Color::White);
	tScore.setStyle(Text::Bold);
}
 
int leaderboardMenu::getChoice(RenderWindow& app) {
	Event event;
	while (app.pollEvent(event)) {
		if (event.type == Event::Closed)
			app.close();

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (isInSprite(sReturn, app)) 
				
				return 1;
		}
	}
	return -1;
}

void leaderboardMenu::draw(RenderWindow& app) {
	app.draw(sBg);
	app.draw(sLead);
	app.draw(sReturn);
	std::string line;

	std::ifstream reader("save.txt");

	int k(0);
	if (reader.is_open())
	{
		while (std::getline(reader, line))
		{
			tScore.setString(line);
			tScore.setPosition(600, 100 + k * 44);
			app.draw(tScore);
			k++;
		}
	}

	reader.close();
}