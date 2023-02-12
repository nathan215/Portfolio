#include "GameEngine.h"

using namespace std;

// Please do not change the following already implemented code

void GameEngine::print_active_monsters()
{
    int i = 0;
    cout << "Active Monsters:" << endl;
    MonsterNode *cur = head;
    while (cur != nullptr)
    {
        cout << cur->data->get_display_str();
        cout << "@(" << cur->data->get_x();
        cout << "," << cur->data->get_y() << "), ";
        cur = cur->next;
        i++;
        if (i == 4)
        {
            i = 0;
            cout << endl;
        }
    }
}

bool GameEngine::player_win() const
{
    int px, py;
    player->get_position(px, py);
    if (px == MAP_SIZE - 1 && py == MAP_SIZE - 1)
    {
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
                if (map[i][j]->get_unit_type() == UnitType::MONSTER && map[i][j]->is_valid())
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
        return false;
}

GameEngine::GameEngine()
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if (i > 8 && i < 12 && j > 2 && j < 6)
                map[i][j] = new Wall(i, j);
            else if (i > 14 && i < 18 && j > 2 && j < 6)
                map[i][j] = new Grass(i, j);
            else if (i > 2 && i < 6 && j == 9)
                map[i][j] = new Gem(i, j, GemType::RUBY);
            else if (i > 2 && i < 6 && j == 10)
                map[i][j] = new Gem(i, j, GemType::EMERALD);
            else if (i > 2 && i < 6 && j == 11)
                map[i][j] = new Gem(i, j, GemType::SAPPHIRE);
            else if (i > 8 && i < 12 && j > 8 && j < 12)
                map[i][j] = new Book(i, j);
            else if (i > 14 && i < 18 && j > 8 && j < 12)
                map[i][j] = new Medicine(i, j);
            else if (i > 2 && i < 6 && j > 14 && j < 18)
                map[i][j] = new Zombie(i, j);
            else if (i > 8 && i < 12 && j > 14 && j < 18)
                map[i][j] = new Warlock(i, j);
            else if (i > 14 && i < 18 && j > 14 && j < 18)
                map[i][j] = new ShadowPriest(i, j);
            else
                map[i][j] = new EmptyLand(i, j);
        }
    }
}

char GameEngine::input()
{
    char c;
    cin >> c;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
    return c;
}

void GameEngine::run()
{
    string name;
    cout << "Please enter your name:" << endl;
    cin >> name;
    cout << "Please choose your role:" << endl;
    cout << "1 Warrior" << endl;
    cout << "2 Archer" << endl;
    cout << "3 Mage" << endl;

    int x = 0, y = 0;
    char role = input();
    switch (role)
    {
    case '1':
        create_player(x, y, name, Role::WARRIOR);
        break;
    case '2':
        create_player(x, y, name, Role::ARCHER);
        break;
    case '3':
        create_player(x, y, name, Role::MAGE);
        break;
    default:
        exit(0);
        break;
    }
    ui.refresh(this->map, *player);

    while (true)
    {
        switch (input())
        {
        case 'w':
            this->player_move(Direction::UP);
            break;
        case 'a':
            this->player_move(Direction::LEFT);
            break;
        case 's':
            this->player_move(Direction::DOWN);
            break;
        case 'd':
            this->player_move(Direction::RIGHT);
            break;
        case 'h':
            this->player_attack();
            break;
        case 'j':
            this->player_skill();
            break;
        default:
            break;
        }
        if (player_win())
        {
            cout << endl;
            cout << "You win." << endl;
            break;
        }
        player_discover();
        activate_monsters();
        monster_follow();
        monster_act();
        ui.refresh(this->map, *player);
        print_active_monsters();
        if (!player->is_alive())
        {
            cout << endl;
            cout << "You lose." << endl;
            break;
        }
    }
}

// write your code here

GameEngine::~GameEngine()
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int k = 0; k < MAP_SIZE; k++)
        {
            delete map[MAP_SIZE][MAP_SIZE];    /////// 
        }
    }
    delete player;

    MonsterNode *p = head;
    for (; p != nullptr; head = p)
    {
        p = p->next;
        delete head;
    }
}

void GameEngine::create_player(int x, int y, const string &name, Role role)
{
    if (role == WARRIOR)
        player = new Warrior(x, y, name);
    if (role == ARCHER)
        player = new Archer(x, y, name);
    if (role == MAGE)
        player = new Mage(x, y, name);
    return;
}

void GameEngine::activate_monster(Monster *monster)
{
    if (monster->is_valid() && !(monster->is_active()))
    {
        monster->set_active();
        MonsterNode *add = new MonsterNode;
        add->data = monster;
        add->next = head;
        head = add;
    }
    return;
}

void GameEngine::activate_monsters()
{
    int p_x, p_y;
    player->get_position(p_x, p_y);
    Monster *m;
    for (int i = -1; i < 2; i++)
    {
        if (p_x + i >= 0 && p_x + i < MAP_SIZE)
        {
            for (int k = -1; k < 2; k++)
            {
                if (p_y + k >= 0 && p_y + k < MAP_SIZE)
                {
                    if (i != 0 || k != 0)
                    {
                        if (map[p_x + i][p_y + k]->get_unit_type() == MONSTER)
                        {
                            m = static_cast<Monster *>(map[p_x + i][p_y + k]);
                            activate_monster(m);
                        }
                    }
                }
            }
        }
    }
    return;
}

void GameEngine::deactivate_monster(Monster const *const monster)
{
    MonsterNode *p = head;
    MonsterNode *d;
    if (p == nullptr)
        return;
    if (p->data == monster)
    {
        head = p->next;
        delete p;
        return;
    }

    for (; p->next != nullptr; p = p->next)
    {
        if (p->next->data == monster)
        {
            d = p->next;
            p->next = d->next;
            delete d;
            return;
        }
    }
    return;
}

void GameEngine::player_move(Direction d)
{
    int p_x, p_y;
    player->get_position(p_x, p_y);
    if (d == UP)
    {
        if (p_y + 1 < MAP_SIZE)
        {
            if (!(map[p_x][p_y + 1]->is_blocked()))
                player->move(d, 1);
            else
                player->move(d, 0);
        }
        else
            player->move(d, 0);
    }
    else if (d == DOWN)
    {
        if (p_y - 1 >= 0)
        {
            if (!(map[p_x][p_y - 1]->is_blocked()))
                player->move(d, 1);
            else
                player->move(d, 0);
        }
        else
            player->move(d, 0);
    }
    else if (d == LEFT)
    {
        if (p_x - 1 >= 0)
        {
            if (!(map[p_x - 1][p_y]->is_blocked()))
                player->move(d, 1);
            else
                player->move(d, 0);
        }
        else
            player->move(d, 0);
    }
    else if (d == RIGHT)
    {
        if (p_x + 1 < MAP_SIZE)
        {
            if (!(map[p_x + 1][p_y]->is_blocked()))
                player->move(d, 1);
            else
                player->move(d, 0);
        }
        else
            player->move(d, 0);
    }

    player->get_position(p_x, p_y);
    map[p_x][p_y]->triggered_by(*player);
    return;
}

void GameEngine::player_discover()
{
    int p_x, p_y;
    player->get_position(p_x, p_y);

    for (int i = -2; i < 3; i++)
    {
        if (p_x + i >= 0 && p_x + i < MAP_SIZE)
        {
            for (int k = -2; k < 3; k++)
            {
                if (p_y + k >= 0 && p_y + k < MAP_SIZE)
                {
                    if (i != 0 || k != 0)
                        map[p_x + i][p_y + k]->set_discovered();
                }
            }
        }
    }
    return;
}

void GameEngine::player_attack()
{
    int p_x, p_y, p_atk, p_def;
    player->get_position(p_x, p_y);
    player->get_atk_def(p_atk, p_def);
    Direction dir = player->get_direction();

    Monster *m;

    for (int i = 1; i <= player->get_range(); i++)
    {
        if (dir == UP)
        {
            if (p_y + i < MAP_SIZE)
            {
                if (map[p_x][p_y + i]->get_unit_type() == MONSTER)
                {

                    m = static_cast<Monster *>(map[p_x][p_y + i]);
                    if (m->attacked_by(p_atk) > 0)
                    {
                        deactivate_monster(m);
                        player->gain_exp(1);
                    }
                    else
                    {
                        if (m->is_active() == false)
                        {
                            m->set_discovered();
                            activate_monster(m);
                        }
                    }
                }
                else if (map[p_x][p_y + i]->get_unit_type() == ITEM)
                {
                    map[p_x][p_y + i]->attacked_by(p_atk);
                }
            }
        }
        else if (dir == DOWN)
        {
            if (p_y - i >= 0)
            {
                if (map[p_x][p_y - i]->get_unit_type() == MONSTER)
                {

                    m = static_cast<Monster *>(map[p_x][p_y - i]);
                    if (m->attacked_by(p_atk) > 0)
                    {
                        deactivate_monster(m);
                        player->gain_exp(1);
                    }
                    else
                    {
                        if (m->is_active() == false)
                        {
                            activate_monster(m);
                            m->set_discovered();
                        }
                    }
                }
                else if (map[p_x][p_y - i]->get_unit_type() == ITEM)
                {
                    map[p_x][p_y - i]->attacked_by(p_atk);
                }
            }
        }
        else if (dir == LEFT)
        {
            if (p_x - i >= 0)
            {
                if (map[p_x - i][p_y]->get_unit_type() == MONSTER)
                {
                    m = static_cast<Monster *>(map[p_x - i][p_y]);
                    if (m->attacked_by(p_atk) > 0)
                    {
                        deactivate_monster(m);
                        player->gain_exp(1);
                    }
                    else
                    {
                        if (m->is_active() == false)
                        {
                            activate_monster(m);
                            m->set_discovered();
                        }
                    }
                }
                else if (map[p_x - i][p_y]->get_unit_type() == ITEM)
                {
                    map[p_x - i][p_y]->attacked_by(p_atk);
                }
            }
        }
        else if (dir == RIGHT)
        {
            if (p_x + i < MAP_SIZE)
            {
                if (map[p_x + i][p_y]->get_unit_type() == MONSTER)
                {

                    m = static_cast<Monster *>(map[p_x + i][p_y]);
                    if (m->attacked_by(p_atk) > 0)
                    {
                        deactivate_monster(m);
                        player->gain_exp(1);
                    }
                    else
                    {
                        if (m->is_active() == false)
                        {
                            activate_monster(m);
                            m->set_discovered();
                        }
                    }
                }
                else if (map[p_x - i][p_y]->get_unit_type() == ITEM)
                {
                    map[p_x - i][p_y]->attacked_by(p_atk);
                }
            }
        }
    }
    return;
}

void GameEngine::player_skill()
{
    int p_x, p_y, p_atk, p_range;
    player->get_position(p_x, p_y);
    p_range = player->get_range();
    Direction dir = player->get_direction();

    Monster *m;

    if (player->skill(p_atk, p_range) == 1)
        return;

    for (int i = 1; i <= p_range; i++)
    {
        if (dir == UP)
        {
            if (p_y + i < MAP_SIZE)
            {
                if (map[p_x][p_y + i]->get_unit_type() == MONSTER)
                {
                    m = static_cast<Monster *>(map[p_x][p_y + i]);
                    if (m->attacked_by(p_atk) > 0)
                    {
                        deactivate_monster(m);
                        player->gain_exp(1);
                    }
                    else
                    {
                        if (m->is_active() == false)
                        {
                            activate_monster(m);
                            m->set_discovered();
                        }
                    }
                }
                else if (map[p_x][p_y + i]->get_unit_type() == ITEM)
                {
                    map[p_x][p_y + i]->attacked_by(p_atk);
                }
            }
        }
        else if (dir == DOWN)
        {
            if (p_y - i >= 0)
            {
                if (map[p_x][p_y - i]->get_unit_type() == MONSTER)
                {
                    m = static_cast<Monster *>(map[p_x][p_y - i]);
                    if (m->attacked_by(p_atk) > 0)
                    {
                        deactivate_monster(m);
                        player->gain_exp(1);
                    }
                    else
                    {
                        if (m->is_active() == false)
                        {
                            activate_monster(m);
                            m->set_discovered();
                        }
                    }
                }
                else if (map[p_x][p_y - i]->get_unit_type() == ITEM)
                {
                    map[p_x][p_y - i]->attacked_by(p_atk);
                }
            }
        }
        else if (dir == LEFT)
        {
            if (p_x - i >= 0)
            {
                if (map[p_x - i][p_y]->get_unit_type() == MONSTER)
                {
                    m = static_cast<Monster *>(map[p_x - i][p_y]);
                    if (m->attacked_by(p_atk) > 0)
                    {
                        deactivate_monster(m);
                        player->gain_exp(1);
                    }
                    else
                    {
                        if (m->is_active() == false)
                        {
                            activate_monster(m);
                            m->set_discovered();
                        }
                    }
                }
                else if (map[p_x - i][p_y]->get_unit_type() == ITEM)
                {
                    map[p_x - i][p_y]->attacked_by(p_atk);
                }
            }
        }
        else if (dir == RIGHT)
        {
            if (p_x + i < MAP_SIZE)
            {
                if (map[p_x + i][p_y]->get_unit_type() == MONSTER)
                {
                    m = static_cast<Monster *>(map[p_x + i][p_y]);
                    if (m->attacked_by(p_atk) > 0)
                    {
                        deactivate_monster(m);
                        player->gain_exp(1);
                    }
                    else
                    {
                        if (m->is_active() == false)
                        {
                            activate_monster(m);
                            m->set_discovered();
                        }
                    }
                }
            }
        }
    }
    return;
}

void GameEngine::monster_follow()
{
    MonsterNode *p = head;

    for (; p != nullptr; p = p->next)
    {
        p->data->follow(*player, map);
    }
    return;
}

void GameEngine::monster_act()
{
    MonsterNode *p = head;

    for (; p != nullptr; p = p->next)
    {
        p->data->action(*player, map);
    }
    return;
}
