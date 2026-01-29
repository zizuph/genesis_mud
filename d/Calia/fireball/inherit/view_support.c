
/* 
    ~Calia/fireball/inherit/view_support.c 

    This is support for views of a fireball game and the match score. 

    Coded by Maniac@Genesis, 1999

    Copyright (C) Miguel Leith 1999
*/ 

#pragma strict_types

#include "defs.h"
#include FIREBALL_HEADER


int
do_exa(string str)
{
    if (str == "game" || str == "fireball game" || 
        str == "game proceedings" || str == "match" ||
        str == "fireball match" || str == "match proceedings")
        return FIREBALL_GAME_HANDLER->check_arena_display();  
    else if (str == "scoreboard" ||
             str == "score" || str == "game score" || 
             str == "fireball score" || str == "match score")
        return FIREBALL_GAME_HANDLER->check_match_score();
 
    return 0; 
}


void
init_view_support()
{
    add_action(do_exa, "exa"); 
    add_action(do_exa, "examine"); 
}
