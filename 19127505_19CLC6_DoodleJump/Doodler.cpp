#include "header.h"



//DOODLER

Doodler::Doodler(Texture* doodler) {
	x = 2000; y = 0;
	sDood.setTexture(*doodler);
}

void Doodler::move(RenderWindow& app,float& dy) {
	x = Mouse::getPosition(app).x - 45;			//follow mouse

	dy += 0.2;
	y += dy;	
}

bool Doodler::isLost() {
	return y > 800;
}

void Doodler::draw(RenderWindow& app) {
	sDood.setPosition(x, y);
	app.draw(sDood);
}



//PLATFORM (SOMETIMES CALLED TILES)

Plat::Plat(Texture* platform) {
	sPlat.setTexture(*platform);

}

void Plat::draw(RenderWindow& app) {
	for (int i = 0; i < pos.size(); i++) {
		sPlat.setPosition(pos[i]);
		app.draw(sPlat);
	}
}





//MISSLE AND JETPACK

Missle::Missle(Texture* mis) {
	sMis.setOrigin(sMis.getGlobalBounds().width / 2, sMis.getGlobalBounds().height / 2);
	sMis.setTexture(*mis);
	x = rand() % 1280;
	y = -(rand() % 5000 + 3000);
}

Jetpack::Jetpack(Texture* jet) {
	sJet.setOrigin(sJet.getGlobalBounds().width / 2, sJet.getGlobalBounds().height / 2);
	sJet.setTexture(*jet);
	x = rand() % 1280;
	y = -(rand() % 5000 + 1000);
}

void Missle::draw(RenderWindow& app) {
	if (y > -100) {
		sMis.setPosition(x, y);
		app.draw(sMis);
	}
}

void Jetpack::draw(RenderWindow& app) {
	if (y > -100) {
		sJet.setPosition(x, y);
		app.draw(sJet);
	}
}




//STAR

Star::Star(Texture* mis) {

	sStar.setOrigin(sStar.getGlobalBounds().width / 2, sStar.getGlobalBounds().height / 2);
	sStar.setTexture(*mis);
	x = rand() % 1280;
	y = -(rand() % 1000 + 5000);
}

void Star::draw(RenderWindow& app) {
	sStar.setPosition(x, y);
	app.draw(sStar);
}