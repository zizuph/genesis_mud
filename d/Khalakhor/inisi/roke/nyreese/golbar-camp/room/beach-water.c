 /*
  * Water room besides the Cadu pier, leads to path to Golbar camp
  */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
    
inherit "/std/room";

void
create_room()
{
    set_short("shallow water near the beach");
    set_long("You are standing in shallow water, with the Cadu pier slighty above you " +
             "to the west. A ladder leads up from the water onto the pier. A little to " +
             "north there is a small patch of beach.\n");

    add_item("pier",
             "The pier stands just next to you and continues further to the west. " +
             "A ladder leads up from the water making it possible to climb up onto " +
             "the pier.\n");
    add_item("ladder",
             "It's a rickety ladder but looks like it should be able to hold you if you try " +
             "to climb up onto the pier.\n");
    add_item(({"beach", "small beach", "patch of beach", "small patch of beach"}),
             "The beach lies a little to the north across the water and looks really nice.\n");
    add_item("water",
             "The water reaches up a bit on your legs, and looks nice and clear. You notice a " +
             "narrow passage in the water where it looks shallow enough to wade north to the beach.\n");
    add_item(({"narrow passage", "passage", "shallow water", "sandbank"}),
             "Between the pier and beach you see a sandbank under the surface, creating a " +
             "narrow passage where it's shallow enough to wade north to the beach.\n");
             
    WATER;
 }

 int
 climb(string s)
 {
     notify_fail("Climb where?\n");
     if (s != "u" && s != "up" && s != "ladder")
     {
         return 0;
     }
 
     write("You climb up the rickety ladder. It wobbles and sounds like it " +
           "may break, but you make it up to the pier.\n");
     say(QCTNAME(this_player()) + " leaves climbing up the ladder with a cracking noise " +
           "for every step.\n");
     tell_room(NYREESEDIR + "cadu_pier5",
           "The ladder starts to make cracking noises above you as " +
           QCNAME(this_player()) + " climbs down from the pier.\n");
     this_player()->move_living("M", NYREESEDIR + "cadu_pier5", 0, 0);
     
     return 1;
}

int
wade(string s)
{
    if(s == "n" || s == "north")
    {
        write("You wade out in the water and find the pasage to the beach.\n");
        say(QCTNAME(this_player()) + " wades out to the north towards the beach.\n");
        tell_room(CAMP_ROOM + "beach-landing",
            QCTNAME(this_player()) + " arrives wading from the south.\n");
        this_player()->move_living("M", CAMP_ROOM + "beach-landing", 0, 0);
        return 1;
    }
    if(s == "w" || s == "west")
    {
        notify_fail("The pier is in the way.\n");
        return 0;
    }
    if(s == "nw" || s == "ne" || s == "e" || s == "se" || s == "s" || s == "sw" ||
       s == "northwest" || s == "northeast" || s == "east" || s == "southeast" ||
       s == "south" || s == "southwest")
    {
        notify_fail("The water is too deep in that direction to wade there.\n");
        return 0;
    }
    if(s == "u" || s == "up")
    {
        notify_fail("If you want up, try the ladder!\n");
        return 0;
    }
    if(s == "d" || s == "down")
    {
        notify_fail("Down? You don't really wade downwards. Anyway the water is too shallow to dive down here.\n");
        return 0;
    }
    else
    {
        notify_fail("Wade where?\n");
        return 0;
    }
}

void
init()
{
    ::init();
    add_action(climb, "climb");
    add_action(wade, "wade");
}