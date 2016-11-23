//
// Created by Valentin on 28/10/2016.
//

#include <iostream>
#include <fstream>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "Model.h"

const float vitesseDepDefaut = 12.f;

Model::Model(bool debug) {
	this->debug = debug;
	InitFont();
	InitialiseMusic("music2.wav");
	InitialiseSoundPiece("ting.wav");

	piece_height = 1;
	camera.x = 20;
	camera.y = 20;

	camera.z = 1.5;    // Défaut : 1.5
	camera.eyeZ = camera.z;
	ResetVitesseDep();
}

/*Model::Model(bool debug) {	// Surcharge de constructeur inutile, valeur par défaut pour param disponible en C++
	//this(); ou équivalent apparemment impossible en C++
	this->debug = debug;
}*/

void Model::InitFont() {
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "/!\\ Erreur chargement font \"arial.ttf\"" << std::endl;
		std::exit(1);
	}
}

sf::Image Model::LoadImgMap(sf::String nomFichier) {
	sf::Image map_image;
	if (!map_image.loadFromFile(nomFichier)) {
		std::cout << "Failure to load map : " << nomFichier.toAnsiString() << std::endl;
		std::exit(1);
	}
	return map_image;
}

void Model::DefineTailleMap(sf::Image image) {
	map.x = image.getSize().x;
	map.y = image.getSize().y;
}

CoordMap &Model::getMap() {
	return map;
}

void Model::CreateMatrix(sf::Image image) {
	DefineTailleMap(image);
	matrice = new int *[map.x];
	for (unsigned int i = 0; i < map.x; ++i) {
		matrice[i] = new int[map.y];
	}

	for (unsigned int x = 0; x < map.x; x++) {
		for (unsigned int y = 0; y < map.y; y++) {
			if (image.getPixel(x, y) == color.Black) {
				matrice[x][y] = 1;
			} else if (image.getPixel(x, y) == color.White) {
				matrice[x][y] = 0;
			} else if (image.getPixel(x, y) == color.Red) {
				matrice[x][y] = 2;
				IncremNombreTotalPiece();
			} else if (image.getPixel(x, y) == color.Green) {
				matrice[x][y] = 3;
			}
		}
	}
}

void Model::DestructionMatrix() {
	for (unsigned int i = 0; i < map.x; ++i) {
		delete matrice[i];
	}
	delete matrice;
}

int **Model::getMatrice() {
	return matrice;
}

void Model::setMatrice(int x, int y, int val) {
	Model::matrice[x][y] = val;
}

bool Model::isDebug() const {
	return debug;
}

sf::Font &Model::getFont() {
	return font;
}

float Model::getVitesseDep() {
	return vitesseDep;
}

void Model::setVitesseDep(float v) {
	vitesseDep = v;
}

void Model::ResetVitesseDep() {
	vitesseDep = vitesseDepDefaut;
}

int Model::getHauteurPiece() {
	return piece_height;
}

int Model::getNombreTotalPiece() {
	return nombreDePieces;
}

void Model::IncremNombreTotalPiece() {
	nombreDePieces++;
}

sf::VideoMode Model::getResolution() {
	return sf::VideoMode::getDesktopMode();
}

void Model::InitialiseSoundPiece(sf::String nomFichier) {
	if (!buf_SoundPiece.loadFromFile(nomFichier)) {
		std::cout << "Failure to load sound coin : " << nomFichier.toAnsiString() << std::endl;
		std::exit(1);
	}
	Sound_piece = sf::Sound(buf_SoundPiece);
	Sound_piece.setPitch(1.2);
}

void Model::JoueSoundPiece() {
	Sound_piece.play();
}

void Model::InitialiseMusic(sf::String nomFichier) {
	if (!music.openFromFile(nomFichier)) {
		std::cout << "Failure to load music : " << nomFichier.toAnsiString() << std::endl;
		std::exit(1);
	}
	music.setLoop(true);
}

void Model::LanceMusic() {
	music.play();
}

void Model::ChangeMusicPitch(float val) {
	music.setPitch(val);
}

void Model::ResetMusicPitch() {
	music.setPitch(1);
}

std::string Model::toString(double dble) {
	std::ostringstream os;
	os << dble;
	return os.str();
}

std::string Model::toString(float flt) {
	std::ostringstream os;
	os << flt;
	return os.str();
}

std::string Model::toString(int integer) {
	std::ostringstream os;
	os << integer;
	return os.str();
}

Model::~Model() {
	std::cout << "Destructeur de model" << std::endl;
	DestructionMatrix();
}