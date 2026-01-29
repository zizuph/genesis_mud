/*
  Pax Tharkas, Mountain road towards the open iron ore mine.

  iron_mine2.c
  ------------

  Coded ........: 95/03/31
  By ...........: Jeremiah

  Latest update : 95/04/16
  By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXOUTROOM;

int seq = 0;
string do_sledge();

void
create_pax_room()
{
    set_short("Open iron ore mine");
    set_long("You are standing in the center of an iron ore mine, also " +
        "known as the Tharkadan iron mine. The mine has excavated " +
        "by mining away the rock to get to the precious iron ore, " +
        "leaving a huge scar on the mountain side. A band of dull " +
        "red streaks the rocky surface of the mountain side. Iron " +
        "ore. Hundreds of male humans toil to scrape the rock away " +
        "to get to the rusty red rocks.\n");

    OUTSIDE;

    add_item("humans", "These are all male humans working hard to " +
        "gather the valuable red ore. They are all looking pale " +
        "and undernourished. Some of them, throws you a quick " +
        "glance as you pass by them.\n");   

    add_item(({"streaks", "red streaks"}), "Rust red streaks across " +
        "the mountain side. This is the precious iron ore.\n");

    add_item(({"cart", "carts", "wooden cart", "wooden carts"}), 
        "This is the typical kind of cart you would expect in " +
        "a mining area. A low wooden cart on four wheels, that " +
        "could be made to run on tracks, if needed.\n");

    set_tell_time(30);
    add_tell("The humans hack and scrape away at the mountain " +
        "sides with picks and shovels.\n");
    add_tell("@@do_sledge@@");
   
    add_exit(COURT_YARD + "iron_mine3", "north", 0);
    add_exit(COURT_YARD + "iron_mine1", "south", 0);
}




string
do_sledge()
{
    string message;

    switch(seq)
    {
    case 0: message = "Some of the humans load the rocks and gravel, " +
                "loosened from the mountain side, onto low wooden carts.\n";
        break;
    case 1: message = "A group of humans push the fully loaded carts " +
                "northwards, into another part of the mine.\n";
        break;
    case 2: message = "Humans, dragging empty wooden carts, arrive " +
                "from the north.\n";
    }
    tell_room(TO, message);

    seq ++;
    if(seq > 2)
        seq = 0;
    return "";
}

