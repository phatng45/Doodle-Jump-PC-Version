#include "header.h"

texture  GameState::textureManager;
sound  GameState::soundManager;
int  GameState::musicOption;

bool checkFile() {
	std::string nameFile[23] = { 
		"images/background.png",
		"images/platform.png",
		"images/platform2.png",
		"images/doodle.png",
		"images/exit.png",
		"images/play.png",
		"images/jetpack.png",
		"images/missle.png",
		"images/star.png",
		"images/leaderboard.png",
		"images/leaderboard2.png",
		"images/retry.png",
		"images/returnToMenu.png",
		"images/returnToMenu2.png",
		"images/logo.png",
		"images/mute.png",
		"images/unmute.png",
		"sounds/bonk.wav",
		"sounds/bgm.ogg",
		"sounds/missle.wav",
		"sounds/jetpack.wav",
		"sounds/star.wav",
		"font/bahnschrift.ttf" };

	std::ifstream reader;
	for (int i = 0; i < 23; i++) {
		reader.open(nameFile[i]);
		if (!reader.is_open()) {
			throw nameFile[i];
		}
	}
	reader.close();
	return true;
}


int main()
{
	try {
		checkFile();
	}
	catch (std::string& error) {
		std::ofstream writer;
		writer.open("log.txt");
		writer << "missing file " << error << std::endl;
		writer.close();
		return 0;
	}

	RenderWindow app(VideoMode(1280, 600), "Doodle Jump", Style::Titlebar | Style::Close);
	app.setFramerateLimit(60);
	app.setKeyRepeatEnabled(false);


	GameState* newState, * currentState;
	currentState = new MainMenuState;
	newState = nullptr;

	while (app.isOpen()) {
		//Input
		newState = currentState->handleInput(app);
		if (newState != nullptr) {
			delete currentState;
			currentState = newState;
			newState = nullptr;
		}

		//Update
		currentState->update();

		//Logic
		newState = currentState->handleLogic();
		if (newState != nullptr) {
			delete currentState;
			currentState = newState;
			newState = nullptr;
		}

		//Draw
		app.clear();
		currentState->draw(app);
		app.display();
	}
	delete newState;
	delete currentState;
	return 0;
}