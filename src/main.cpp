#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;
int sizeX = 1050;
int sizeY = 850;
int cellSize = 50;


float bulletSize = 5.f;

float posXRed = float(cellSize/2);
float posYRed = float(cellSize/2);
int countRedWins = 0;



float posXGreen = float(sizeX - (cellSize/2));
float posYGreen = float(sizeY - (cellSize/2));
int countGreenWins = 0;

Font font("../include/minecraft.ttf");
Text PlayerRedWins(font);
Text PlayerGreenWins(font);

Texture redTankTexture("../include/RedTank.png");
Sprite playerRed(redTankTexture);
Texture greenTankTexture("../include/GreenTank.png");
Sprite playerGreen(greenTankTexture);

struct Bullet {
    RectangleShape data;
    float posX;
    float posY;
    string direction;
};
vector<Bullet> Bullets;

void startPlayerRed() {
    posXRed = float(cellSize/2);
    posYRed = float(cellSize/2);
    countGreenWins++;
    PlayerGreenWins.setString(L"Green: " + to_string(countGreenWins));
}
void startPlayerGreen() {
    posXGreen = float(sizeX - (cellSize/2));
    posYGreen = float(sizeY - (cellSize/2));
    countRedWins++;
    PlayerRedWins.setString(L"Red: " + to_string(countRedWins));
}
void renderBullets() {
    for (int i = static_cast<int>(Bullets.size()) - 1; i >= 0; i--) {
        if (Bullets[i].posX < bulletSize/2 || Bullets[i].posY < bulletSize/2 || Bullets[i].posX > sizeX - bulletSize/2 || Bullets[i].posY > sizeY - bulletSize/2) {
            Bullets.erase(Bullets.begin() + i);
        } else {
            if (Bullets[i].data.getFillColor() == Color::Red) {
                if ((Bullets[i].posX >= float(posXGreen - cellSize/2) && Bullets[i].posX <= float(posXGreen + cellSize/2)) &&
                    (Bullets[i].posY >= float(posYGreen - cellSize/2) && Bullets[i].posY <= float(posYGreen + cellSize/2))) {
                    Bullets.erase(Bullets.begin() + i);
                    startPlayerGreen();
                }
            } else if (Bullets[i].data.getFillColor() == Color::Green) {
                if ((Bullets[i].posX >= float(posXRed - cellSize/2) && Bullets[i].posX <= float(posXRed + cellSize/2)) &&
                    (Bullets[i].posY >= float(posYGreen - cellSize/2) && Bullets[i].posY <= float(posYGreen + cellSize/2))) {
                    Bullets.erase(Bullets.begin() + i);
                    startPlayerRed();
                }
            }
            if (Bullets[i].direction == "Up") {
                Bullets[i].posY -= 2.f;
            } else if (Bullets[i].direction == "Left") {
                Bullets[i].posX -= 2.f;
            } else if (Bullets[i].direction == "Down") {
                Bullets[i].posY += 2.f;
            } else if (Bullets[i].direction == "Right") {
                Bullets[i].posX += 2.f;
            }
        }
    }
}
bool isEat() {
    return (posXRed == posXGreen) && (posYRed == posYGreen);
}
int main() {
    RenderWindow window(VideoMode({static_cast<unsigned int>(sizeX), static_cast<unsigned int>(sizeY)}), "My window");
    window.setFramerateLimit(60); 


    
    Texture tileTexture("../include/grass.png");
    vector<Sprite> tiles;
    for (int i = 0; i < sizeX / cellSize; i++) {
        for (int j = 0; j < sizeY / cellSize; j++) {
            Sprite tile(tileTexture);
            tile.setPosition({float(i * cellSize), float(j * cellSize)});
            tile.setScale({float(cellSize) / tileTexture.getSize().x,
                          float(cellSize) / tileTexture.getSize().y});
            tiles.push_back(tile);
        }
    }

    playerRed.setOrigin({redTankTexture.getSize().x / 2.f, redTankTexture.getSize().y / 2.f});
    playerRed.setScale({float(cellSize) / redTankTexture.getSize().x, float(cellSize) / redTankTexture.getSize().y});
    playerRed.setPosition({posXRed, posYRed});

    PlayerRedWins.setString(L"Red: " + to_string(countRedWins));
    PlayerRedWins.setCharacterSize(24);
    PlayerRedWins.setFillColor(Color::White);
    PlayerRedWins.setPosition({50.f, 20.f});







    playerGreen.setOrigin({greenTankTexture.getSize().x / 2.f, greenTankTexture.getSize().y / 2.f});
    playerGreen.setScale({float(cellSize) / greenTankTexture.getSize().x, float(cellSize) / greenTankTexture.getSize().y});
    playerGreen.setPosition({posXGreen, posYGreen});

    Text PlayerGreenWins(font);
    PlayerGreenWins.setString(L"Green: " + to_string(countGreenWins));
    PlayerGreenWins.setCharacterSize(24);
    PlayerGreenWins.setFillColor(Color::White);
    PlayerGreenWins.setPosition({50.f, 40.f});

    vector<Bullet> greenBullets;


    string directionRed = "Right";
    string directionGreen = "Left";

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
            if (event->is<Event::KeyPressed>()) {
                auto keyEvent = event->getIf<Event::KeyPressed>();
                if (keyEvent->code == Keyboard::Key::Escape) {
                    window.close();
                }
                if (keyEvent->code == Keyboard::Key::W) {
                    if (posYRed > cellSize/2) {
                        posYRed -= cellSize;
                    }
                    directionRed = "Up";
                    playerRed.setRotation(degrees(0));
                    if (isEat()) {
                        startPlayerGreen();
                    }
                }
                if (keyEvent->code == Keyboard::Key::A) {
                    if (posXRed > cellSize/2) {
                        posXRed -= cellSize;
                    }
                    directionRed = "Left";
                    playerRed.setRotation(degrees(-90));
                    if (isEat()) {
                        startPlayerGreen();
                    }
                }
                if (keyEvent->code == Keyboard::Key::S) {
                    if (posYRed < sizeY - (cellSize/2)) {
                        posYRed += cellSize;
                    }
                    directionRed = "Down";
                    playerRed.setRotation(degrees(180));
                    if (isEat()) {
                        startPlayerGreen();
                    }
                }
                if (keyEvent->code == Keyboard::Key::D) {
                    if (posXRed < sizeX - (cellSize/2)) {
                        posXRed += cellSize;
                    }
                    directionRed = "Right";
                    playerRed.setRotation(degrees(90));
                    if (isEat()) {
                        startPlayerGreen();
                    }
                }
                if (keyEvent->code == Keyboard::Key::E) {
                    RectangleShape redBullet({bulletSize, bulletSize});
                    redBullet.setOrigin({bulletSize/2, bulletSize/2});
                    float posBulletXRed = posXRed;
                    float posBulletYRed = posYRed;
                    redBullet.setPosition({posBulletXRed, posBulletYRed});
                    redBullet.setFillColor({Color::Red});
                    Bullets.push_back(Bullet({redBullet, posBulletXRed, posBulletYRed, directionRed}));
                }


                if (keyEvent->code == Keyboard::Key::I) {
                    if (posYGreen > cellSize/2) {
                        posYGreen -= cellSize;
                    }
                    directionGreen = "Up";
                    playerGreen.setRotation(degrees(0));
                    if (isEat()) {
                        startPlayerRed();
                    }
                }
                if (keyEvent->code == Keyboard::Key::J) {
                    if (posXGreen > cellSize/2) {
                        posXGreen -= cellSize;
                    }
                    directionGreen = "Left";
                    playerGreen.setRotation(degrees(-90));
                    if (isEat()) {
                        startPlayerRed();
                    }
                }
                if (keyEvent->code == Keyboard::Key::K) {
                    if (posYGreen < sizeY - (cellSize/2)) {
                        posYGreen += cellSize;
                    }
                    directionGreen = "Down";
                    playerGreen.setRotation(degrees(180));
                    if (isEat()) {
                        startPlayerRed();
                    }
                }
                if (keyEvent->code == Keyboard::Key::L) {
                    if (posXGreen < sizeX - (cellSize/2)) {
                        posXGreen += cellSize;
                    }
                    directionGreen = "Right";
                    playerGreen.setRotation(degrees(90));
                    if (isEat()) {
                        startPlayerRed();
                    }
                }
                if (keyEvent->code == Keyboard::Key::U) {
                    RectangleShape GreenBullet({bulletSize, bulletSize});
                    GreenBullet.setOrigin({bulletSize/2, bulletSize/2});
                    float posBulletXGreen = posXGreen;
                    float posBulletYGreen = posYGreen;
                    GreenBullet.setPosition({posBulletXGreen, posBulletYGreen});
                    GreenBullet.setFillColor({Color::Green});
                    Bullets.push_back(Bullet({GreenBullet, posBulletXGreen, posBulletYGreen, directionGreen}));
                }
            }
        }
        playerRed.setPosition({posXRed, posYRed});
        playerGreen.setPosition({posXGreen, posYGreen});
        renderBullets();


        window.clear(Color::Blue);
        
        for (auto &tile : tiles) {
            window.draw(tile);
        }
        window.draw(PlayerRedWins);
        window.draw(PlayerGreenWins);


        window.draw(playerRed);
        window.draw(playerGreen);

        for (Bullet bullet : Bullets) {
            bullet.data.setPosition({bullet.posX, bullet.posY});
            window.draw(bullet.data);
            
        }

        window.display();
    }
}