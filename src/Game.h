
#ifndef WHACKAMOLESFML_GAME_H
#define WHACKAMOLESFML_GAME_H

#include <SFML/Graphics.hpp>


class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);


 private:
  bool collisionCheck(sf::Vector2i click, sf::Sprite sprite);
  void spawn();

  sf::RenderWindow& window;
  sf::Sprite background;
  sf::Texture background_texture;
  sf::Sprite bird;
  sf::Texture bird_texture;
  sf::Font font;
  sf::Text title_text;

  bool in_menu = true;
  sf::Text menu_text;
  sf::Text play_option;
  sf::Text quit_option;
  sf::Text score_text;
  bool play_selected = true;

  bool reverse = false;
  float speed = 210;

  int score = 0;
  int Speed = 1;
};

#endif // WHACKAMOLESFML_GAME_H
