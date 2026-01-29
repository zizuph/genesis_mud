/*
 * /d/Gondor/lebennin/wolfcave/ranger_caves/ledge1.c
 *
 * Coded by Tigerlily--October 23, 2004
 * For use with ranger task #8
 * Revision history:
 * 
 */
#pragma strict_types

inherit "/std/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#include "cave_defs.h"

int found = 0;

//prototypes
string do_search(object player, string str); 
int climb_down(string str);

void
reset_room()
{
    found = 0;
    
}

void
create_room()
{
    set_short("rock ledge");
    set_long("This ledge is accessible only by climbing " +
        "up a steep rockface on a rope from the cavern below. " +
        "It is moderately dry, and debris is " +
        "scattered on the rock floor. Another ledge is " +
        "above this one and appears somewhat narrower. \n");

    add_item(({"debris", "rock floor", "floor"}), 
        "You look through the debris and find what " +
        "appear to be human bones.\n");
    add_item(({"bones", "human bones", "skeleton"}), "The bones tell " +
        "a sad story. It is the skeleton of a tall man, " +
        "and is almost intact, except that you notice the " +
        "left thigh bone is broken in " +
        "two places. Perhaps while trying to reach the ledge " +
        "above, the man fell here, and being injured and unable " +
        "to leave, he died alone. Some artifacts, including " +
        "a torn piece of cloth, lie next to the skeleton.\n");
    add_item(({"artifacts", "torn piece of cloth","cloth", 
        "remnants", "remants of a cloak"}),
        "Examining the piece of cloth, you see that " +
        "it is the remnants of a ranger cloak, bloodied and torn. " +
        "You can also see, however, that it still retains a diamond " +
        "brooch and its grey-green colour. There appears to be " +
        "something underneath it, wrapped in a leather casing.\n");
    add_item(({"casing", "leather casing", "leather"}), "The " +
        "leather is somewhat decomposed.\n");
    add_item(({"ledge", "rock ledge"}), "You are standing " +
        "on a rock ledge, while there is a somewhat narrower " +
        "ledge several meters above. Only an extremely adept " +
        "climber would be able to reach it.\n");
    add_item("narrower ledge", "The narrower ledge is a " +
        "couple of meters above, and only a highly skilled " +
        "climber could reach it.\n");
    add_item(({"down", "way down"}), "You could probably climb " +
        "down the way you came.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN,"do_search");

}

string
do_search(object player, string str) 
{
    object sword;

    if(!strlen(str) || (str != "leather" && str != "casing" && 
        str != "leather casing" ) )
    {
        return "You find nothing of value there.\n";
    }


    if(!found)
    {
        seteuid(getuid(TO));
        sword = clone_object(RANGERS_OBJ + "numenorean_sword");
        sword->move(TO, 1);
        found = 1;
        say(QCTNAME(player) + " searches the casing, and it " +
            "crumbles away under " + player->query_possessive() + 
            " hands, revealing an ancient longsword!\n");
        return "The leather crumbles away under your fingers " +
            "to reveal an ancient longsword beneath it!\n";

    }
    return "You find nothing of value there.\n";
}

void
init()
{
    ::init();
    add_action(&climb_down(), "climb");
}

int
climb_down(string str)
{
    object tp = this_player();
    if (str == "up" || str == "up wall")
    {
        notify_fail("You try to climb up the rock wall, but " +
            "fall back down with a crash!\n");
        return 0;
    }
    if ((str != "down") && (str != "rope") && (str != "down rope"))
    {
        notify_fail("Climb what?\n");
        return 0;
    }
    write("You climb down the rope.\n");
    say(QCTNAME(tp) + " leaves climbing down the rope.\n");
    tp->move_living("M", CAVE_PATH + "tcave", 1, 0);
    say(QCTNAME(tp) + " arrives climbing down the rope.\n");
    return 1;
}



