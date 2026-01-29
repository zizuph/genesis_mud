
/* 
 * /d/Calia/fireball/surround/wizard_box.c
 * 
 * A room in the Firedrome stand. Private viewing for
 * wizards, also contains some special commands. 
 * 
 * Coded by Maniac@Genesis, January/March 1999
 * 
 * Copyright (C) Miguel Leith 1999
 */ 

#include "defs.h"
#include FIREBALL_HEADER

inherit FIREBALL_STAND_ROOM; 


void
create_room()
{
    make_stand_room(); 
    set_short("Wizard's box in the Firedrome"); 
    set_long("You're in the wizard's box in the Firedrome. " +
          "The view here is excellent and there is plenty " +
          "of space. " + 
          "Wizards who have write access here may use the " +
          "the following commands:\n" + 
          "   terminate [reason]     - emergency stop for a game.\n" + 
          "   startpr                - start a practice.\n" + 
          "   endpr                  - end a practice.\n" +
          "   addpr <name>           - add a new player to the practice.\n" +
          "   score <team> = <score> - patch a team's score.\n"); 

    add_exit(FIREBALL_ARENA + "ar_6_4", "arena"); 
    add_exit(FIREBALL_STAND + "stand2", "stand");
    add_exit(FIREBALL_SURROUND + "foyer", "foyer"); 
}


int
do_terminate_match(string str)
{
    return FIREBALL_GAME_HANDLER->do_terminate_match(str); 
}


int
do_start_practice(string str)
{
    return FIREBALL_GAME_HANDLER->do_start_practice(str); 
}

int
do_end_practice(string str)
{
    return FIREBALL_GAME_HANDLER->do_end_practice(str); 
}

int
do_patch_score(string str)
{
    return FIREBALL_GAME_HANDLER->do_patch_score(str); 
}

int
do_add_practicer(string str)
{
    return FIREBALL_GAME_HANDLER->do_add_practicer(str); 
}


void
init()
{
    ::init();
    add_action(do_terminate_match, "terminate");  
    add_action(do_start_practice, "startpr"); 
    add_action(do_end_practice, "endpr"); 
    add_action(do_add_practicer, "addpr"); 
    add_action(do_patch_score, "score"); 
}
