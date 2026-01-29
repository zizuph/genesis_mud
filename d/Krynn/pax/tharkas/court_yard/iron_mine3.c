/*
  Pax Tharkas, iron ore mine.

  iron_mine3.c
  ------------

  Coded ........: 95/03/31
  By ...........: Jeremiah

  Latest update : 95/07/28
  By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <composite.h>

inherit PAXOUTROOM;

int seq1 = 0;
int seq2 = 0;

string do_carts1();
string do_carts2();

void
create_pax_room()
{
    set_short("Open iron ore mine");
    set_long("You are standing in the center of an iron ore mine, also " +
        "known as the Tharkadan iron mine. The mine has excavated " +
        "by mining away the rock to get to the precious iron ore, " +
        "leaving a huge scar on the mountain side. A band of dull " +
        "red streaks the rocky surface of the mountain side. Iron " +
        "ore. There's a hole in the ground here. Hundreds of " +
        "male humans toil to scrape the rock away to get to the " +
        "rusty red rocks.\n");

    OUTSIDE;

    add_item("humans", "These are all male humans working hard to " +
        "gather the valuable red ore. They are all looking pale " +
        "and undernourished. Some of them, throw you a quick " +
        "glance as you pass by them.\n");

    add_item(({"streaks", "red streaks"}), "Rust red streaks across " +
        "the mountain side. This is the precious iron ore.\n");

    add_item("hole", "A hole going like a vertical shaft down into " +
        "the mountain. Far below, in the shaft, you can see a " +
        "faint flickering red light.\n");
           
    add_item(({"cart", "carts", "wooden cart", "wooden carts"}),
        "This is the typical kind of cart you would expect in " +
        "a mining area. A low wooden cart on four wheels, that " +
        "could be made to run on tracks, if needed.\n");

    set_tell_time(30);
    add_tell("Humans prisoners hack and scrape away at the mountain " +
        "sides with picks and shovels.\n");
    add_tell("@@do_carts1@@");
    add_tell("@@do_carts2@@");
   
    add_exit(COURT_YARD + "iron_mine2", "south", 0);
}

string
do_carts1()
{
    string message;

    switch(seq1)
    {
    case 0: message = "Prisoners load the rocks and gravel, loosened " +
                "from the mountain side, onto low wooden carts.\n";
        break;
    case 1: message = "A group of humans push the fully loaded wooden " +
                "carts towards the hole in the ground.\n";
        break;
    case 2: message = "The prisoners unload the rocks and gravel from " +
                "the loaded carts into the hole in the ground.\n";  
    }
    tell_room(TO, message);

    seq1 ++;
    if(seq1 > 2)
        seq1 = 0;
    return "";
}


string
do_carts2()
{
    string message;

    switch(seq2)
    {
    case 0: message = "A group of prisoners pushing a low wooden cart, " +
                "loaded with rocks and gravel, arrives from the south.\n";
        break;
    case 1: message = "Prisoners, pushing empty wooden carts, " +
                "leave south.\n";
    }
    tell_room(TO, message);

    seq2 ++;
    if(seq2 > 1)
        seq2 = 0;
    return "";
}
