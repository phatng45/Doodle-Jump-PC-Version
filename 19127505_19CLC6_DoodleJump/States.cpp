#include "header.h"



//MAIN MENU STATE

MainMenuState::MainMenuState(int musicOpt) : gameMenu(textureManager,musicOpt) {
	musicOption = musicOpt;	
	if (musicOption == 1) soundManager.setVolumes(100);
	else
		soundManager.setVolumes(0);

	if (soundManager.mBGM.getStatus() != Music::Status::Playing) {
		soundManager.mBGM.setLoop(true);
		soundManager.mBGM.play();
	}

	soundManager.sBonk.play();
}

GameState* MainMenuState::handleInput(RenderWindow& app) {
	switch (gameMenu.getChoice(app)) {
	case 1:
		return new PlayingState();
	case 2:
		return new LeaderboardState();
	case 3:
		app.close();
		return nullptr;
	case 4: {
		return new MainMenuState(!musicOption);
	}
	default:
		return nullptr;
	}
}

void MainMenuState::draw(RenderWindow& app) {
	gameMenu.draw(app);
}





//PLAYING STATE

PlayingState::PlayingState() : doodler(textureManager.Dood), plats(textureManager.Plat), plat2s(textureManager.Plat2), playerInput(), score(0),star(textureManager.Star),
							   h(200), dy(0), allowedRemove(false), jet(textureManager.Jetpack),mis(textureManager.Missle)
{
	for (int i = 0; i < 4; i++) {
		plats.pos.push_back(Vector2f(rand() % 1280, rand() % 200));
		plats.pos.push_back(Vector2f(rand() % 1280, rand() % 200 + 200));
		plats.pos.push_back(Vector2f(rand() % 1280, rand() % 200 + 400));
	}
	plats.pos.push_back(Vector2f(rand() % 1280, rand() % 200));
	plats.pos.push_back(Vector2f(rand() % 1280, rand() % 200 + 200));

	sBg.setTexture(*textureManager.Background);

	bahnschrift.loadFromFile("font/bahnschrift.ttf");
	tScore.setPosition(640, 550);
	tScore.setFont(bahnschrift);
	tScore.setCharacterSize(20);
	tScore.setFillColor(Color::Black);
	tScore.setStyle(Text::Bold);

	soundManager.sBonk.play();
	srand(time(nullptr)); //new seed
}

GameState* PlayingState::handleInput(RenderWindow& app) {

	doodler.move(app, dy);

	while (app.pollEvent(playerInput)) {
		switch (playerInput.type) {
		case Event::Closed:
			app.close();
		case Event::KeyPressed:
			if (playerInput.key.code == Keyboard::Escape) return new MainMenuState(musicOption);
		default: return nullptr;
		}
	}
	return nullptr;
}

int PlayingState::ScoreReq[13] = { 1000,5000,10000,20000,30000,50000,70000,120000,
								   1800000,250000,360000,460000,600000 };

void PlayingState::update() {
	if (doodler.y < h) {
		score += (doodler.y / 10);

		doodler.y = h;

		//MISSLE JETPACK STAR
		{
			mis.y -= dy;
			jet.y -= dy;
			star.y -= dy;

			if (mis.y > 600) {
				mis.x = rand() % 1280;
				mis.y = -(rand() % 10000 + 5000);
			}
			if (jet.y > 600) {
				jet.x = rand() % 1280;
				jet.y = -(rand() % 5000 + 5000);
			}
			if (star.y > 600) {
				star.x = rand() % 1280;
				star.y = -(rand() % 1000 + 1000);
			}
		}

		for (int i = 0; i < plats.pos.size(); i++)
		{

			plats.pos[i].y -= dy;
			if (plats.pos[i].y > 600)
				if (allowedRemove) {
					plats.pos.erase(plats.pos.begin() + i);
					plat2s.pos.push_back(Vector2f(rand() % 1280, rand() % 2));
					allowedRemove = false;
				}
				else {
					plats.pos[i].y = -(rand() % 2);
					plats.pos[i].x = rand() % 1280;
				}

		}

		for (int i = 0; i < plat2s.pos.size(); i++)
		{
			plat2s.pos[i].y -= dy;
			if (plat2s.pos[i].y > 600){
				
					plat2s.pos[i].y = -(rand() % 2);
					plat2s.pos[i].x = rand() % 1280;
				}

		}
	}
	if (diff < 13 && score > ScoreReq[diff]) {					//increase diff
		allowedRemove = true;
		diff++;
	}
};

GameState* PlayingState::handleLogic() {

	//Collision check copied from https://www.youtube.com/watch?v=7Vf_vQIUk5Q
	for (int i = 0; i < plats.pos.size(); i++)
		if ((doodler.x + 50 > plats.pos[i].x) && (doodler.x + 20 < plats.pos[i].x + 68)
			&& (doodler.y + 70 > plats.pos[i].y) && (doodler.y + 70 < plats.pos[i].y + 14) && (dy > 0)) {
			dy = -10;
			soundManager.sBonk.play();
		}
	for (int i = 0; i < plat2s.pos.size(); i++)
		if ((doodler.x + 50 > plat2s.pos[i].x) && (doodler.x + 20 < plat2s.pos[i].x + 68)
			&& (doodler.y + 70 > plat2s.pos[i].y) && (doodler.y + 70 < plat2s.pos[i].y + 14) && (dy > 0)) {
			dy = -10;
			plat2s.pos[i].y = 602;
			soundManager.sSand.play();
			soundManager.sBonk.play();
		}
	if ((doodler.x + 50 > mis.x) && (doodler.x + 20 < mis.x + 68)
			&& (doodler.y  > mis.y) && (doodler.y  < mis.y + 30)) {
		dy = -35;
		mis.y = 602;
		soundManager.sMis.play();
	}	
	if ((doodler.x + 50 > star.x) && (doodler.x + 20 < star.x + 68)
		&& (doodler.y  > star.y) && (doodler.y  < star.y + 30)) {
		score += 5000;
		star.y = 602;
		soundManager.sStar.play();
	}
	if ((doodler.x + 50 > jet.x) && (doodler.x + 20 < jet.x + 68)
		&& (doodler.y  > jet.y) && (doodler.y  < jet.y + 30)) {
		dy = -20;
		jet.y = 602;
		soundManager.sJet.play();
	}
	if (doodler.isLost())
		return new LoseState(score);
	return nullptr;
}

void PlayingState::draw(RenderWindow& app) {
	app.draw(sBg);
	tScore.setString(std::to_string(score));
	plat2s.draw(app);
	plats.draw(app);
	jet.draw(app);
	mis.draw(app);
	star.draw(app);
	app.draw(tScore);
	doodler.draw(app);
}




//LOSE STATE

LoseState::LoseState(int score) : gameMenu(textureManager,score){

	// read scores from save.txt
	std::string line;
	int scores[10] = { 0 };
	std::ifstream reader("save.txt");

	int k(0);
	if (reader.is_open())
	{
		while (std::getline(reader, line))
		{
			scores[k] = std::stoi(line);
			k++;
		}
	}

	reader.close();

	// if newest score is higher than lowest score in file, replace it with lowest score then sort again
	if (score > scores[9]) {
		scores[9] = score;

		for (int j = 0; j < 9; j++) {
				if (scores[9] > scores[j])
					std::swap(scores[9], scores[j]);
		}

		// write to file
		std::ofstream writer("save.txt", std::ios::out);
		for (int i = 0; i < 10; i++) {
			writer << std::to_string(scores[i]) << std::endl;
		}

		writer.close();
	}
}

GameState* LoseState::handleInput(RenderWindow& app) {
	switch (gameMenu.getChoice(app)) {
	case 1:
		return new PlayingState();
	case 2:
		return new MainMenuState(musicOption);
	default:
		return nullptr;
	}
}

void LoseState::draw(RenderWindow& app) {
	gameMenu.draw(app);
}



//LEADERBOARD STATE

LeaderboardState::LeaderboardState() :gameMenu(textureManager) {
	soundManager.sBonk.play();
}

GameState* LeaderboardState::handleInput(RenderWindow& app) {
	switch (gameMenu.getChoice(app)) {
	case 1:
		return new MainMenuState(musicOption);
	default:
		return nullptr;
	}
}

void LeaderboardState::draw(RenderWindow& app) {
	gameMenu.draw(app);
}