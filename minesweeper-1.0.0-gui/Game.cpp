#include "Game.h"
#include "test.h"

SDL_Renderer* Game::renderer_ = nullptr;

Game::Game()
{
    height_ = 0;
    width_ = 0;
    running_ = false;
    current_scene_ = 0;
    previous_scene_ = 0;
    button_type_ = 0;

    flag = 0;
    mines_ = 0;
    mine_counter_ = nullptr;

    time_counter_ = nullptr;

    font_ = nullptr;
    window_ = nullptr;
}

void Game::quit()
{
    release_assets();

    //free font
    TTF_CloseFont(font_);
    font_ = nullptr;
    //destroy window
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
    SDL_DestroyWindow(window_);
    window_ = nullptr;
    time_counter_ = nullptr;
    mine_counter_ = nullptr;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Game::is_running()
{
    return running_;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flag)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        {
            return false;
        }
        if (TTF_Init() == -1)
        {
            return false;
        }
        font_ = TTF_OpenFont("Assets/alisha.ttf", 28);
        window_ = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
        if (window_)
        {
            width_ = width;
            height_ = height;
            renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
            if (renderer_)
            {
                running_ = true;
            }
        }
    }
    else
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        running_ = false;
    }
    load_assets();
    reset_time();
    return running_;
}

void Game::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running_ = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            Sint32 x = event.button.x;
            Sint32 y = event.button.y;
            int button_type = 0;
            //cout << "mouse donw at (" << event.button.x << "," << event.button.y << ")" << endl;
            switch (current_scene_)
            {
            case 0:
            {
                for (auto it : texture_location_)
                {
                    if ((x >= it.x && x <= it.x + it.w) &&
                        (y >= it.y && y <= it.y + it.h))
                    {
                        break;
                    }
                    ++button_type;
                }
                if (button_type == 4)
                {
                    running_ = false;
                    break;
                }
                else if (button_type != 3)
                {
                    button_type_ = button_type;
                    current_scene_ = 1;
                }
                else
                {
                    current_scene_ = 2;
                }
                load_assets();
            }break;
            case 1:
            {
                //·½¿éµã»÷ÅÐ¶Ï
                click_title(x, y,event); 
                //°´Å¥ÊÂ¼þÅÐ¶Ï
                for (int i = 1; i < 3; ++i)
                {
                    if ((x >= texture_location_[i].x && x <= texture_location_[i].x + texture_location_[i].w) &&
                        (y >= texture_location_[i].y && y <= texture_location_[i].y + texture_location_[i].h))
                    {
                        button_type = i;
                        break;
                    }
                }
                if (button_type == 1)
                {
                    load_assets();
                    time_.stop();
                    SDL_DestroyTexture(time_counter_);
                    reset_time();
                    count_mines();
                    init_title(title_status_[0].size(), title_status_.size());
                    set_mines();
                    flag = 0;
                }
                else if (button_type == 2)
                {
                    current_scene_ = 0;
                    load_assets();
                    time_.stop();
                    SDL_DestroyTexture(time_counter_);
                    reset_time();
                }
            }break;
            case 2:
            {
                for (int i = 0; i < 2; ++i)
                {
                    if ((x >= texture_location_[i].x && x <= texture_location_[i].x + texture_location_[i].w) &&
                        (y >= texture_location_[i].y && y <= texture_location_[i].y + texture_location_[i].h))
                    {
                        break;
                    }
                    ++button_type;
                }
                if (button_type == 0)
                {
                    current_scene_ = 0;
                    load_assets();
                }
                else if (button_type == 1)
                {
                    load_file(0);
                    load_assets();
                }
            }break;
            default:break;
            }
        }
    }
}

void Game::renderer()
{
    SDL_RenderClear(renderer_);
    switch (current_scene_)
    {
    case 0:
    {
        set_window(640, 480, "Minesweeper", 0, 0, 0);
        /*SDL_SetWindowSize(window_, 640, 480);
        SDL_SetWindowTitle(window_, "Minesweeper");*/
        for (int i = 0; i < current_scene_textures_.size(); ++i)
        {
            SDL_RenderCopy(renderer_, current_scene_textures_[i], nullptr, &texture_location_[i]);
        }
        SDL_SetRenderDrawColor(renderer_, 119, 135, 171, 255);
    }break;
    case 1:
    {
        int row(0), col(0);
        SDL_Rect time_counter_rect = { 0 };
        if (button_type_ == 0)
        {
            row = 9, col = 9;
            set_window(300, 300, "Easy", 10, row, col);
            time_counter_rect= { 190,30,80,20 };
        }
        else if (button_type_ == 1)
        {
            row = 16, col = 16;
            set_window(480, 480, "Medium",40, row, col);
            time_counter_rect = { 370,30,80,20 };
        }
        else if (button_type_ == 2)
        {
            row = 16, col = 30;
            set_window(850, 480, "Hard",99, row, col);
            time_counter_rect = { 710,30,80,20 };
        }
        //restart key location
        texture_location_[1] = { texture_location_[0].x + col / 2 * texture_location_[0].w - 5,texture_location_[0].y - 35,30,30 };
        SDL_Rect temp = texture_location_[0];
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (flag == -1&&title_status_[i][j]==-3)
                {
                    SDL_RenderCopy(renderer_, current_scene_textures_[5], nullptr, &temp);
                    SDL_RenderCopy(renderer_, current_scene_textures_[3], nullptr, &temp);
                }
                else if (title_status_[i][j] == -1 || title_status_[i][j] == -3)
                {
                    SDL_RenderCopy(renderer_, current_scene_textures_[0], nullptr, &temp);
                }
                else if(title_status_[i][j] == -2 || title_status_[i][j] == -4)
                {
                    SDL_RenderCopy(renderer_, current_scene_textures_[0], nullptr, &temp);
                    SDL_RenderCopy(renderer_, current_scene_textures_[4], nullptr, &temp);
                }
                else if (title_status_[i][j] >= 0)
                {
                    SDL_RenderCopy(renderer_, current_scene_textures_[5], nullptr, &temp);
                    SDL_RenderCopy(renderer_, current_scene_textures_[5 + title_status_[i][j]], nullptr, &temp);
                }
                temp.x += 25;
            }
            temp.x = texture_location_[0].x;
            temp.y += 25;
        }
        for (int i = 1; i < 3; ++i)
        {
            SDL_RenderCopy(renderer_, current_scene_textures_[i], nullptr, &texture_location_[i]);
        }
        temp = { 50,30,80,20 };
        SDL_RenderCopy(renderer_, mine_counter_, nullptr, &temp);
        count_time();
        SDL_RenderCopy(renderer_, time_counter_, nullptr, &time_counter_rect);
        SDL_SetRenderDrawColor(renderer_, 178, 143, 143, 255);
    }break;
    case 2:
    {
        for (int i = 0; i < current_scene_textures_.size(); ++i)
        {
            SDL_RenderCopy(renderer_, current_scene_textures_[i], nullptr, &texture_location_[i]);
        }
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
        SDL_Rect temp = { 60,60,550,400 };
        SDL_RenderDrawRect(renderer_, &temp);
        SDL_SetRenderDrawColor(renderer_, 119, 135, 171, 255);
    }break;
    }
    SDL_RenderPresent(renderer_);
}

void Game::load_assets()
{
    release_assets();
    switch (current_scene_)
    {
    case 0:
    {
        current_scene_textures_.push_back(load_texture("Assets/easy-option.png"));
        current_scene_textures_.push_back(load_texture("Assets/medium-option.png"));
        current_scene_textures_.push_back(load_texture("Assets/hard-option.png"));
        current_scene_textures_.push_back(load_texture("Assets/record-option.png"));
        for (int i = 0; i < texture_location_.size(); ++i)
        {
            texture_location_[i].x = 245;
            texture_location_[i].y = 130 + i * 80;
            texture_location_[i].w = static_cast<int>(texture_location_[i].w * 0.75);
            texture_location_[i].h = static_cast<int>(texture_location_[i].h * 0.75);
        }
        current_scene_textures_.push_back(load_texture("Assets/quit-button.png"));
        texture_location_[texture_location_.size() - 1] = { 0,0,48,48 };
    }break;
    case 1:
    {
        current_scene_textures_.push_back(load_texture("Assets/title.png"));
        texture_location_[0] = { 50,60,25,25 };
        current_scene_textures_.push_back(load_texture("Assets/smile-restart.png"));
        current_scene_textures_.push_back(load_texture("Assets/back-button.png"));
        texture_location_[2] = { 0,0,48,48 };

        //current_scene_textures_.push_back(load_texture("Assets/crying-restart.png"));
        current_scene_textures_.push_back(load_texture("Assets/Mine.png"));
        current_scene_textures_.push_back(load_texture("Assets/flag.png"));

        current_scene_textures_.push_back(load_texture("Assets/title-selected.png"));
        current_scene_textures_.push_back(load_text_texture("1", { 0,0,255 }));
        current_scene_textures_.push_back(load_text_texture("2", { 0,128,0 }));
        current_scene_textures_.push_back(load_text_texture("3", { 255,0,0 }));
        current_scene_textures_.push_back(load_text_texture("4", { 0,0,128 }));
        current_scene_textures_.push_back(load_text_texture("5", { 128,0,0 }));
        current_scene_textures_.push_back(load_text_texture("6", { 0,128,128 }));
        current_scene_textures_.push_back(load_text_texture("7", { 2,2,2 }));
        current_scene_textures_.push_back(load_text_texture("8", { 128,128,128 }));
    }break;
    case 2:
    {
        current_scene_textures_.push_back(load_texture("Assets/back-button.png"));
        current_scene_textures_.push_back(load_texture("Assets/delete-button.png"));
        texture_location_[0] = { 0,0,48,48 };
        texture_location_[1] = { 0,50,48,48 };
        SDL_Color color = { 0,0,0 };
        current_scene_textures_.push_back(load_text_texture("Difficulty", color));
        current_scene_textures_.push_back(load_text_texture("Time", color));
        current_scene_textures_.push_back(load_text_texture("Play Record", color));
        for (int i = 2; i < texture_location_.size(); ++i)
        {
            texture_location_[i].x = 150 + (i - 2) * 300;
            texture_location_[i].y = 65;
        }
        texture_location_[4].x = 250;
        texture_location_[4].y = 10;
        load_file(2);
    }break;
    default:break;
    }

}

void Game::release_assets()
{
    if (current_scene_textures_.size() > 0)
    {
        for (auto i : current_scene_textures_)
        {
            SDL_DestroyTexture(i);
            i = nullptr;
        }
        vector<SDL_Texture*>().swap(current_scene_textures_);
    }
    if (texture_location_.size() > 0)
    {
        vector<SDL_Rect>().swap(texture_location_);
    }
    SDL_DestroyTexture(mine_counter_);
}

SDL_Texture* Game::load_texture(const char* file)
{
    SDL_Surface* temp = IMG_Load(file);
    SDL_Rect rect = { 0,0,temp->w,temp->h };
    texture_location_.push_back(rect);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, temp);
    SDL_FreeSurface(temp);
    return texture;
}

SDL_Texture* Game::load_text_texture(string text, SDL_Color color)
{
    SDL_Surface* temp = TTF_RenderText_Blended(font_, text.c_str(), color);
    SDL_Rect rect = { 0,0,temp->w,temp->h };
    texture_location_.push_back(rect);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, temp);
    SDL_FreeSurface(temp);
    return texture;
}

void Game::load_file(int flag)
{
    switch (flag)
    {
    case 0:
    {
        std::ofstream out("record.txt", std::ios::out);
    }break;
    case 1:
    {
        string s = "";
        if (button_type_ == 0)
        {
            s = "Easy " + std::to_string(time_.get_time());
        }
        else if (button_type_ == 1)
        {
            s = "Medium " + std::to_string(time_.get_time());
        }
        else if (button_type_ == 2)
        {
            s = "Hard " + std::to_string(time_.get_time());
        }
        std::fstream out;
        out.open("record.txt", std::ios::out | std::ios::ate | std::ios::app);
        out << s << endl;
        out.close();
    }break;
    default:
    {
        std::ifstream in;
        in.open("record.txt", std::ios::in);
        if (!in.is_open())
        {
            cout << "error" << endl;
            return;
        }
        string buf = "";
        while (std::getline(in, buf))
        {
            int size = 16;
            string::iterator it = buf.begin();
            while (*it != ' ')
            {
                ++it;
            }
            buf.insert(it, size, ' ');
            buf += 's';
            SDL_Color color = { 0,0,0 };
            current_scene_textures_.push_back(load_text_texture(buf, color));
            for (int i = 5; i < texture_location_.size(); ++i)
            {
                texture_location_[i].x = 175;
                texture_location_[i].y = 115 + (i - 5) * 60;
            }
        }
        in.close();
    }break;
    }
}

void Game::click_title(int x,int y, SDL_Event& e)
{
    int base_x(texture_location_[0].x), base_y(texture_location_[0].y);
    if (button_type_ == 0 && (x > base_x && x<(base_x + 25 * 9)) && (y>base_y && y<(base_y + 25 * 9)) ||
        button_type_ == 1 && ( x>base_x && x<(base_x + 25 * 16)) && (y>base_y && y < (base_y + 25 * 16)) ||
        button_type_ == 2 && ( x>base_x && x<(base_x + 25 * 30)) && (y>base_y && y < (base_y + 25 * 16)))
    {
        x = (x - base_x) / 25;
        y = (y - base_y) / 25;
        if (time_.is_running() == false)
        {
            while (title_status_[y][x] == -3)
            {
                set_mines();
            }
            time_.start();
        }
        std::cout << "\n  start:\n";
        output(title_status_, title_status_.size(), title_status_[0].size());
        if (e.button.button == SDL_BUTTON_RIGHT)
        {
            if (title_status_[y][x] == -1)
            {
                --mines_;
                count_mines();
                title_status_[y][x] = -2;
            }
            else if(title_status_[y][x] == -2)
            {
                ++mines_;
                count_mines();
                title_status_[y][x] = -1;
            }
            else if (title_status_[y][x] == -3)
            {
                --mines_;
                count_mines();
                title_status_[y][x] = -4;
            }
            else if(title_status_[y][x] == -4)
            {
                ++mines_;
                count_mines();
                title_status_[y][x] = -3;
            }
        }
        else if (title_status_[y][x] == -3)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Failure", "You are lose.", nullptr);
            flag = -1;
            time_.stop();
        }
        else
        {
            search(y, x);
        }
        std::cout << "\n  end:\n";
        output(title_status_, title_status_.size(), title_status_[0].size());
        cout << "you click title at (" << x << "," << y << ")" << endl;
    }
    //ÅÐ¶ÏÊÇ·ñÊ¤Àû
    check();
}

void Game::count_mines()
{
    if (mine_counter_ != nullptr)
    {
        SDL_DestroyTexture(mine_counter_);
    }
    string s = "Mines " + std::to_string(mines_);
    SDL_Color color = { 0,0,0 };
    SDL_Surface* temp = TTF_RenderText_Blended(font_, s.c_str(), color);
    mine_counter_ = SDL_CreateTextureFromSurface(renderer_, temp);
    SDL_FreeSurface(temp);
}

void Game::count_time()
{
    if (time_.is_running() == true)
    {
        if (time_counter_ != nullptr)
        {
            SDL_DestroyTexture(time_counter_);
        }
        string s = "Time " + std::to_string(time_.get_time());
        SDL_Color color = { 0,0,0 };
        SDL_Surface* temp = TTF_RenderText_Blended(font_, s.c_str(), color);
        time_counter_ = SDL_CreateTextureFromSurface(renderer_, temp);
        SDL_FreeSurface(temp);
    }
}

void Game::reset_time()
{
    time_.reset();
    string s = "Time 0";
    SDL_Color color = { 0,0,0 };
    SDL_Surface* temp = TTF_RenderText_Blended(font_, s.c_str(), color);
    time_counter_ = SDL_CreateTextureFromSurface(renderer_, temp);
    SDL_FreeSurface(temp);
}

void Game::set_window(int x, int y, const char* title,int mine,int row, int col)
{
    if (strcmp(SDL_GetWindowTitle(window_),title)!=0)
    {
        SDL_SetWindowSize(window_, x, y);
        SDL_SetWindowTitle(window_, title);
        if (mine != 0)
        {
            mines_ = mine;
            count_mines();
        }
        if (row != 0)
        {
            init_title(row, col);
            set_mines();
        }
    }
}

void Game::init_title(int x, int y)
{
    vector<vector<int>>().swap(title_status_);
    for (int i = 0; i < x; ++i)
    {
        vector<int> temp;
        for (int j = 0; j < y; ++j)
        {
            temp.push_back(-1);
        }
        title_status_.push_back(temp);
    }
}

void Game::set_mines()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 8);
    int x(0), y(0);
    for (int i = 0; i < 10; ++i)
    {
        x = dis(gen);
        y = dis(gen);
        if (title_status_[x][y] != -3 && title_status_[x][y] < 0)
        {
            title_status_[x][y] = -3;
        }
        else if (title_status_[x][y] == -3)
        {
            while (1)
            {
                x = dis(gen);
                y = dis(gen);
                if (title_status_[x][y] != -3 && title_status_[x][y] < 0)
                {
                    title_status_[x][y] = -3;
                    break;
                }
            }
        }
    }
}

bool Game::exisit(std::deque<position>& q, int x, int y)
{
    for (int i = 0; i < q.size(); ++i)
    {
        if (q[i].x == x && q[i].y == y)
        {
            return true;
        }
    }
    return false;
}

void Game::search(int x, int y)
{
    int max_x = title_status_.size() - 1;
    int max_y = title_status_[x].size() - 1;
    std::deque<position> q;
    position f = { x,y };
    q.push_back(f);
    int count = 0;
    while (!q.empty())
    {
        position temp = q.back();
        q.pop_back();
        int mines = 0;
        int numbers = 0;
        for (int dx = (temp.x > 0 ? -1 : 0); dx <= (temp.x < max_x ? 1 : 0); ++dx)
        {
            for (int dy = (temp.y > 0 ? -1 : 0); dy <= (temp.y < max_y ? 1 : 0); ++dy)
            {
                if (dx != 0 || dy != 0)
                {
                    if (title_status_[temp.x + dx][temp.y + dy] == -1 || title_status_[temp.x + dx][temp.y + dy] == -2)
                    {
                        if (!exisit(q, temp.x + dx, temp.y + dy))
                        {
                            ++numbers;
                            q.push_back({ temp.x + dx ,temp.y + dy });
                        }
                    }
                    else if (title_status_[temp.x + dx][temp.y + dy] == -3 || title_status_[temp.x + dx][temp.y + dy] == -4)
                    {
                        ++mines;
                    }
                }
            }
        }
        title_status_[temp.x][temp.y] = mines;
        if (mines != 0)
        {
            while (numbers > 0)
            {
                q.pop_back();
                --numbers;
            }
        }
    }
}

void Game::check()
{
    for (int i = 0; i < title_status_.size(); ++i)
    {
        for (int j = 0; j < title_status_[0].size(); ++j)
        {
            if (title_status_[i][j] == -1 || title_status_[i][j] == -2)return;
        }
    }
    if (flag == 0)
    {
        flag = 1;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Win", "You are Win.", nullptr);
        time_.stop();
        load_file(1);
    }
}