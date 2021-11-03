#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"Timer.h"

#include<string>
#include<vector>
#include<fstream>
#include<thread>
#include<random>
#include<deque>
using std::string;
using std::vector;

struct position
{
    int x;
    int y;
};

class Game
{
public:
    Game();
    ~Game() = default;

    bool init(const char* title, int xpos, int ypos, int width, int height, int flag);
    bool is_running();
    void handle_events();
    void renderer();
    void quit();

    void load_assets();
    void release_assets();

    void click_title(int x, int y,SDL_Event& e);

    SDL_Texture* load_texture(const char* file);
    SDL_Texture* load_text_texture(string text, SDL_Color color);
    void load_file(int flag);
    void count_mines();
    void count_time();
    void reset_time();
    void set_window(int x, int y, const char* title, int mine,int row,int col);
    void init_title(int x, int y);
    void set_mines();
    bool exisit(std::deque<position>& q, int x, int y);
    void search(int x, int y);
    void check();

    static SDL_Renderer* renderer_;
private:
    int width_;
    int height_;
    bool running_;
    int current_scene_;
    int previous_scene_;
    int button_type_;
    vector<SDL_Texture*> current_scene_textures_;
    vector<SDL_Rect> texture_location_;

    int flag;
    int mines_;
    vector<vector<int>> title_status_;
    SDL_Texture* mine_counter_;
    Timer time_;
    SDL_Texture* time_counter_;

    TTF_Font* font_;
    SDL_Window* window_;
};

