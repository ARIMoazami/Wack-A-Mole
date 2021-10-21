
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  if(!background_texture.loadFromFile("Data/Images/background.png"))
  {
    std::cout << "background texture did not load \n";
  }
  background.setTexture(background_texture);
  if(!bird_texture.loadFromFile("Data/Images/bird.png"))
  {
    std::cout << "bird texture did not load \n";
  }
  bird.setTexture(bird_texture);
  bird.setPosition(400,490);
  bird.setScale(0.5,0.5);

  if(!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load\n";
  }
  title_text.setString("Whack-A-Mole");
  title_text.setFont(font);
  title_text.setCharacterSize(100);
  title_text.setFillColor(sf::Color(255,140,0));

  title_text.setPosition(
    window.getSize().x/2 - title_text.getGlobalBounds().width/2,
    window.getSize().y/10 - title_text.getGlobalBounds().height/2);

  menu_text.setString("WELCOME TO WHACK-A-MOLE");
  menu_text.setFont(font);
  menu_text.setCharacterSize(60);
  menu_text.setFillColor(sf::Color(148,0,211));

  menu_text.setPosition(
    window.getSize().x/2.3 - menu_text.getGlobalBounds().width/2,
    window.getSize().y/7 - menu_text.getGlobalBounds().height/2);

  play_option.setString("PLAY GAME");
  play_option.setFont(font);
  play_option.setCharacterSize(50);
  play_option.setFillColor(sf::Color(148,0,211));

  play_option.setPosition(
    window.getSize().x/2.5 - play_option.getGlobalBounds().width/2,
    window.getSize().y/3 - play_option.getGlobalBounds().height/2);


  quit_option.setString("QUIT GAME");
  quit_option.setFont(font);
  quit_option.setCharacterSize(50);
  quit_option.setFillColor(sf::Color(148,0,211));

  quit_option.setPosition(
    window.getSize().x/2.5 - quit_option.getGlobalBounds().width/2,
    window.getSize().y/2 - quit_option.getGlobalBounds().height/2);


  score_text.setFont(font);
  score_text.setCharacterSize(60);
  score_text.setFillColor(sf::Color(148,0,211));

  score_text.setPosition(
    window.getSize().x/2 - score_text.getGlobalBounds().width/2,
    window.getSize().y/5 - score_text.getGlobalBounds().height/2);

  return true;
}

void Game::update(float dt)
{
  if((bird.getPosition().x > (window.getSize().x - bird.getGlobalBounds().width))||
    (bird.getPosition().x < 0 ))
  {
    reverse = !reverse;
  }
  if (reverse == true){
    bird.setTextureRect(sf::IntRect(0, 0,
    bird.getLocalBounds().width, bird.getLocalBounds().height));
    bird.move(1.0f*speed*dt, 0);
  }
  else
  {
    bird.move(-1.0f * speed * dt, 0);
    bird.setTextureRect(sf::IntRect(
      bird.getLocalBounds().width,
      0,
      -bird.getLocalBounds().width,
      bird.getLocalBounds().height));
  }

  }


void Game::render()
{
  if (in_menu == true){
    window.draw(play_option);
    window.draw(quit_option);
    window.draw(menu_text);
  }
  else{
    in_menu = false;
    window.draw(background);
    window.draw(bird);
    window.draw(title_text);
    window.draw(score_text);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  // check if in bounds of bird Sprite
  if (collisionCheck(click, bird))
  {
  }
}

void Game::keyPressed(sf::Event event)
{
  if(
    (event.key.code == sf::Keyboard::A)||
    (event.key.code == sf::Keyboard::D))
  {
    play_selected = !play_selected;
    if(play_selected)
    {
      play_option.setString(">>> PLAY GAME <<<");
      quit_option.setString("QUIT GAME");
    }
    else
    {
      play_option.setString("PLAY GAME");
      quit_option.setString(">>> QUIT GAME <<<");
    }
  }
  else if (event.key.code == sf::Keyboard::Enter)
  {
    if(play_selected)
    {
      in_menu = false;
    }
    else
    {
      window.close();
    }
  }
}


bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
  //creating float variable to get the spirte collisonbox
  sf::FloatRect CollisionBox = bird.getGlobalBounds();

  //this is checking to see if the spirte box has the mouse click inside it
  if (CollisionBox.contains(click.x, click.y))
  {
    score += 1;
    spawn();
    score_text.setString(std::to_string(score));
    return true;
  }
  else
  {
    return false;
  }
}

void Game::spawn()
{
  //setting variable to random number from 801 and 0
  //(resolution minus pixel sprite) (1080 - 279)
  int random_x = rand() % 801;
  //setting variable to random number from 457 and 0
  //(720 - 263)
  int random_y = rand() % 457;

  //setting bird position with both variables
  bird.setPosition(random_x, random_y);

}
