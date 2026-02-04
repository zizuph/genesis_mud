/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tcavet.c
 *
 * 
 */

#include "/d/Terel/include/Terel.h"
inherit TROLL_CAVE_DIR + "tcave_room";

public string*
query_object_list()
{
    return ({LOD_DIR + "armour/dark_helmet",
                 LOD_DIR + "weapon/battle_sword",
             "/d/Terel/common/town/fancy_chainmail",
             "/d/Terel/common/town/fancy_sword",
                 TROLL_CAVE_DIR + "armour/tbracers",
                TROLL_CAVE_DIR + "obj/bones"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + 
               "You are in the back of the giant trolls' cave.  It seems "+
               "whatever is thrown back here is quickly forgotten about "+
               "if it's not edible.\n");
    
    add_exit(TROLL_CAVE_DIR + "tcave14",   "south");
    reset_room();
}


