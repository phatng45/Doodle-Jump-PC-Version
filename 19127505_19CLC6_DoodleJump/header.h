#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <string>
#include <vector>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace sf;


//Hold all the Texture
class texture {
public:
	texture();
	~texture();
	Texture* Dood, * Background, * Plat, * Plat2, * Exit, * Play, * Jetpack, * Missle, * Leaderboard,
		* Retry, * Return, * Return2, * Leaderboard2, * Logo, * Star,
		* Mute, * Unmute;
};


//Hold all the Sound and BGM
class sound {
private:
	SoundBuffer* Bonk, * Missle, * Jetpack, * Star, * Sand;
public:
	Sound sBonk, sMis, sJet, sStar, sSand;
	Music mBGM;
	sound();
	void setVolumes(int);
	~sound();
};


class Doodler {
public:
	Doodler(Texture*);
	void move(RenderWindow&, float&);
	bool isLost();
	void draw(RenderWindow&);
private:
	Sprite sDood;
	float x;
	float y;
	friend class PlayingState;
};

class Jetpack {
public:
	Jetpack(Texture*);
	void draw(RenderWindow&);
private:
	Sprite sJet;
	float x;
	long double y;
	friend class PlayingState;
};


class Missle {
public:
	Missle(Texture*);
	void draw(RenderWindow&);
private:
	Sprite sMis;
	float x;
	long double y;
	friend class PlayingState;
};

class Star {
public:
	Star(Texture*);
	void draw(RenderWindow&);
private:
	Sprite sStar;
	float x;
	double y;
	friend class PlayingState;
};


class Plat {
public:
	Plat(Texture*);
	void draw(RenderWindow&);
	std::vector<Vector2f> pos;
private:
	Sprite sPlat;
};


class mainMenu {
private:
	Sprite sPlay, sLeaderboard, sExit, sBg, sLogo, sSound;
public:
	mainMenu(texture&,int);
	void draw(RenderWindow&);
	int getChoice(RenderWindow&);
	~mainMenu() = default;
	friend bool isInSprite(const Sprite&, const RenderWindow&);
};

class leaderboardMenu {
private:
	Text tScore;
	Sprite sLead, sBg, sReturn;
	Font bahnschrift;
public:
	leaderboardMenu(texture&);
	void draw(RenderWindow&);
	int getChoice(RenderWindow&);
	~leaderboardMenu() = default;
	friend bool isInSprite(const Sprite& sprite, const RenderWindow& window);
};

class loseMenu {
private:
	Text tScore;
	Sprite sRetry, sReturn2, sBg;
	Font bahnschrift;
public:
	loseMenu(texture&, int);
	void draw(RenderWindow&);
	int getChoice(RenderWindow&);
	~loseMenu() = default;
	friend bool isInSprite(const Sprite& sprite, const RenderWindow& window);
};


class GameState {
public:
	//The pointers shall be deleted at client code
	virtual GameState* handleInput(RenderWindow&) = 0;
	virtual void update() = 0;
	virtual GameState* handleLogic() = 0;
	virtual void draw(RenderWindow&) = 0;
	virtual ~GameState() = default;
protected:
	static texture textureManager;
	static sound soundManager;

	//0 = Off, 1 = On
	static int musicOption;
};

class MainMenuState : public GameState {
public:
	MainMenuState(int = 1);

	//Playing, Leaderboard, Exit
	GameState* handleInput(RenderWindow&) override;

	//Do nothing
	void update() override {};
	GameState* handleLogic() override { return nullptr; }

	void draw(RenderWindow&) override;
	~MainMenuState() = default;
private:
	mainMenu gameMenu;
};

class PlayingState : public GameState {
public:
	PlayingState();

	//ESC = quit
	GameState* handleInput(RenderWindow&) override;

	//Update, check if tiles are offscreen
	void update() override;

	//Check collision
	GameState* handleLogic() override;

	//Draw
	void draw(RenderWindow&) override;

	~PlayingState() = default;
private:
	int diff;
	unsigned long int score;
	static int ScoreReq[13];
	const int h;
	float dy;
	Text tScore;
	Event playerInput;
	Doodler doodler;
	Plat plats;
	Plat plat2s;
	Missle mis;
	Jetpack jet;
	Star star;
	Sprite sBg;
	Font bahnschrift;
	bool allowedRemove;
};

class LoseState : public GameState {
public:
	LoseState(int = 0);

	//Play again, Menu
	GameState* handleInput(RenderWindow&) override;

	//Do nothing
	void update() override {};
	GameState* handleLogic() override { return nullptr; };

	//Draw
	void draw(RenderWindow&) override;
	~LoseState() = default;
private:
	int score;
	loseMenu gameMenu;
};

class LeaderboardState : public GameState {
public:
	LeaderboardState();

	//Menu
	GameState* handleInput(RenderWindow&) override;

	//Do nothing
	void update() override {};
	GameState* handleLogic() override { return nullptr; };

	//Draw
	void draw(RenderWindow&) override;
	~LeaderboardState() = default;
private:
	leaderboardMenu gameMenu;
};

	