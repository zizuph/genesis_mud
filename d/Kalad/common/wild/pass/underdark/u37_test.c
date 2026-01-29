/*
 * /d/Kalad/common/wild/pass/underdark/u37.c
 * Purpose    : There is a secret command here to go to between_planes.c
 * Located    : Underdark
 * Created By : Antharanos ??.??.??
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 */

#pragma strict_types
#include "dark_dom.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#define TO   this_object()
#define TP   this_player()
inherit DARK_DOM;

void
create_dark_dom()
{
    set_short("Shadowgloom's Lair");
    set_long("This enormous oval chamber is the grand lair of " +
        "the greatly feared and respected Shadowgloom, the most " +
        "powerful dragon of the Dark Dominion. Within this massive " +
        "cavern, the floor, walls and ceiling have been worn smooth " +
        "by the massive bulk of the ancient deep dragon. Not a " +
        "single rough spot marres the cavern's surface, so smooth " +
        "and reflective is the stone that you get the impression of "+
        "being suspended in utter darkness. A geyser filled with " +
        "hot, steaming water and from which yellow vapors emerges, " +
        "lies near the eastern side of this cavern. At the far end " +
        "of the chamber is a massive pile of gold and jewels, a " +
        "king's ransom!\n");
    add_item(({"chamber","lair","cavern"}),"The enormous enclosed " +
        "space that surrounds you from all sides.\n");
    add_item(({"floor"}),"There is not one stalagmite or other such "+
      "debris cluttering the ground. It is just bare stone.\n");
    add_item(({"walls"}),"You vainly try to look at all the walls of the "+
      "chamber at once...and fail.\n");
    add_item(({"wall"}),"The reflective black stone of one of " +
        "the chamber's sides looks to be a near-perfect mirror " +
        "image of the chamber you are standing in, including the " +
        "walls, floor, ceiling, and pool.\n");
    add_item(({"mirror image","image"}),"It looks like a reflection of "+
      "the surrounding area.\n");
    add_item(({"pool"}),"There is no pool in this chamber!\n");
    add_item(({"ceiling"}),"Made of dark, unyielding stone, it looks "+
      "quite strong.\n");
    add_item(({"surface"}),"The surface of the rock in this cavern is "+
      "as smooth as silk.\n");
    add_item(({"stone"}),"The rock here is extremely dark, almost "+
      "unusually so.\n");
    add_item(({"geyser"}),"A small fountain of water that spouts a "+
      "yellowish vapor, in addition to water.\n");
    add_item(({"water"}),"It has been tainted yellow from the gas, it "+
      "doesn't look safe to drink.\n");
    add_item(({"yellow vapors","vapors","yellow vapor","vapor"}),
      "It looks like sulphuric gas...quite dangerous if inhaled.\n");
    add_item(({"pile of gold and jewels","pile","king's ransom"}),
      "The largest collection of treasure and loot you have ever laid "+
      "your eyes upon. It lies in a gleaming pile as high as a hill giant!\n");
    add_exit(DARK(u38), "east");
    reset_room();
}

void
reset_room()
{
    object dragon;

    if (sizeof(FILTER_PLAYERS(all_inventory(TO))))
        return;

    dragon = (present("shadowgloom", TO));

    if(!(dragon))
    {
        dragon = clone_object("/d/Kalad/common/wild/pass/npc/dragon_test");
        dragon->move(this_object());
    }
    else
        dragon->reset_heal();
    return;
}

void
init()
{
    ::init();
        add_action("enter_pool","enter");
        add_action("push_wall","push");
        add_action("kick_dragon","kick");
}

void
enter_inv(object ob, object from)
{
::enter_inv();

    if (ob->id("sword of thanar"))
{
        if (present("shadowgloom", TO))
        {
            object dragon = (present("shadowgloom", TO));
            dragon->react_sword(from);
        }
    }
}

int
enter_pool(string str)
{
    if ((str) && (str == "geyser"))
    {
        write("You step into the scalding hot waters of the geyser...\n");
        write("You are burned!\n");
        TP->heal_hp(-100);
        if (TP->query_hp() <= 0)
            TP->do_die(TO);
        return 1;
    }
    return 0;
}

int
push_wall(string str)
{
    if ((str) && (str == "wall"))
    {
        object dragon = (present("shadowgloom", TO));

        if (dragon)
        {
            write("The dragon stops you from approaching " +
                "the wall.\n");
            say(QCTNAME(TP) + " moves towards the wall " +
                "but is effectively blocked by the dragon.\n");
            return 1;
        }
        object room = find_object(DARK(u37a));
        room->teleledningsanka();
        write("You are suddenly pulled inside the wall!\n");
        say(QCTNAME(TP) + " disappears through a secret door " +
            "in the wall.\n");
        TP->move_living("M", DARK(u37a));
        return 1;
    }
    return 0;
}

int
kick_dragon(string str)
{
    if ((str) && ((str == "dragon") || (str = "deep dragon")))
        object dragon = (present("shadowgloom", TO));

        if (dragon)
        {
            dragon->react_attack(TP);
            return 1;
        }
    return 0;
}

