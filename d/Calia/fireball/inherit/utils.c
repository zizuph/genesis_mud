
/*
 *  /d/Calia/fireball/inherit/utils.c
 *
 *  Some general utility functions for fireball, useful to inherit.  
 *
 *  Coded by Maniac, 29/11/97
 */ 

#include "defs.h"
#include <filter_funs.h>
#include FIREBALL_HEADER




/* 
 * Function:     query_distance
 * Description:  returns the distance in tenths of yards between two 
 *               coordinates. 
 */ 
int
query_distance(int x1, int y1, int x2, int y2)
{
    int x, y;  

    x = x2 - x1; 
    y = y2 - y1; 

    return ftoi(100.0 * pow(itof(x * x + y * y), 0.5)); 
}


int
is_able_to_play(object player)
{
    return (!(player->query_prop(FIREBALL_LIVE_I_RECOVERING)) && 
            ((player->query_hp() * 100) / player->query_max_hp()) > 15); 
}

/* 
 * find_first_opponent() returns an opponent of the specified player
 * in the specified room who is currently able to play.
 */ 
object
find_first_opponent(object room, object player, int pkd)
{
    int c, tmp; 
    object *player_list; 

    player_list = FILTER_LIVE(all_inventory(room)) - ({ player }); 

    for (c = 0; c < sizeof(player_list); c++)
        if ((tmp = player_list[c]->query_prop(FIREBALL_LIVE_I_KICK_DIRECTION))
            && (tmp != pkd) && is_able_to_play(player_list[c])) 
            return player_list[c];  

    return 0;
}

/* 
 * find_first_team_mate() returns an opponent of the specified player
 * in the specified room who is currently able to play.
 */ 
object
find_first_team_mate(object room, object player, int pkd)
{
    int c, tmp; 
    object *player_list; 

    player_list = FILTER_LIVE(all_inventory(room)) - ({ player }); 

    for (c = 0; c < sizeof(player_list); c++)
        if ((tmp = player_list[c]->query_prop(FIREBALL_LIVE_I_KICK_DIRECTION))
            && (tmp == pkd) && is_able_to_play(player_list[c])) 
            return player_list[c];  

    return 0;
}

nomask string
query_proper_team_name(string nm)
{
    return implode(map(explode(lower_case(nm), " "), capitalize), " ");
}

string
query_arena_room_path(int x, int y)
{
    return (FIREBALL_ARENA + "ar_" + x + "_" + y + ".c"); 
}
