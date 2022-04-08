#include "header.h"



//TEXTURE

texture::texture() {
	Background = new Texture;
	Plat = new Texture;
	Plat2 = new Texture;
	Dood = new Texture;
	Exit = new Texture;
	Play = new Texture;
	Jetpack = new Texture;
	Missle = new Texture;
	Leaderboard = new Texture;
	Leaderboard2 = new Texture;
	Retry = new Texture;
	Return = new Texture;
	Return2 = new Texture;
	Logo = new Texture;
	Mute = new Texture;
	Unmute = new Texture;
	Star = new Texture;
		
	Background->loadFromFile("images/background.png");
	Plat->loadFromFile("images/platform.png");
	Plat2->loadFromFile("images/platform2.png");
	Dood->loadFromFile("images/doodle.png", IntRect(0, 0, 80, 80));
	Exit->loadFromFile("images/exit.png");
	Play->loadFromFile("images/play.png");
	Jetpack->loadFromFile("images/jetpack.png", IntRect(0, 0, 80, 80));
	Missle->loadFromFile("images/missle.png", IntRect(0, 0, 80, 80));
	Star->loadFromFile("images/star.png", IntRect(0, 0, 80, 80));
	Leaderboard->loadFromFile("images/leaderboard.png");
	Leaderboard2->loadFromFile("images/leaderboard2.png");
	Retry->loadFromFile("images/retry.png");
	Return->loadFromFile("images/returnToMenu.png");
	Return2->loadFromFile("images/returnToMenu2.png");
	Logo->loadFromFile("images/logo.png");
	Mute->loadFromFile("images/mute.png");
	Unmute->loadFromFile("images/unmute.png");
}

texture::~texture() {
	delete Background;
	delete Plat;
	delete Dood;
	delete Exit;
	delete Play;
	delete Jetpack;
	delete Missle;
	delete Leaderboard;
	delete Leaderboard2;
	delete Return;
	delete Return2;
	delete Retry;
	delete Logo;
	delete Mute;
	delete Unmute;
	delete Star;
}



//SOUND

sound::sound() {
	Bonk = new SoundBuffer;
	Missle = new SoundBuffer;
	Jetpack = new SoundBuffer;
	Star = new SoundBuffer;
	Sand = new SoundBuffer;

	Bonk->loadFromFile("sounds/bonk.wav");
	sBonk.setBuffer(*Bonk);

	Missle->loadFromFile("sounds/missle.wav");
	sMis.setBuffer(*Missle);

	Jetpack->loadFromFile("sounds/jetpack.wav");
	sJet.setBuffer(*Jetpack);

	Star->loadFromFile("sounds/star.wav");
	sStar.setBuffer(*Star);

	Sand->loadFromFile("sounds/sand.wav");
	sSand.setBuffer(*Sand);

	mBGM.openFromFile("sounds/bgm.ogg");
}

sound::~sound() {
	delete Bonk;
	delete Star;
	delete Sand;
	delete Missle;
	delete Jetpack;
}

void sound::setVolumes(int volume) {
	sBonk.setVolume(volume);
	sMis.setVolume(volume);
	sJet.setVolume(volume);
	sStar.setVolume(volume);
	sSand.setVolume(volume);
	
	mBGM.setVolume(volume);
}