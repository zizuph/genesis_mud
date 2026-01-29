 
/* Digit 02 FEB 95 
    Modified Maniac 7/3/95
    Modified Amelia 22/4/95
    added new exits, Maniac, 1.5.95
    short changed, Maniac, 23/5/95
    typo corrected, Maniac, 13/7/95
    west exit re-opened (finally) for sea area, Maniac, 13/9/96
    added 'feeling' for the Walkers guild to give them a clue
        about the upcoming quest, Jaacar, 18/3/98
  */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"
#define NORTHEAST_CONNECT "/d/Calia/argos/nwterr/rooms/r1"

string
long_description()
{
    string long_desc;

    long_desc = "You are on a cobbled road running north-south in the "+
     "mid-western regions of Calia. The land " +
     "around you is changing. To the north you " +
     "can see a busy urban setting, the mighty gates of Gelan " +
     "and the bustling area near to the docks, but around you now " +
     "there are but few dwelling places and the land is more untamed. " +
      "To the west extends a row of low sand dunes. "+
     "To the south, southeast and southwest you see bleak moorland " +
     "opening out in a rolling landscape, stretching far into the " +
     "distance. You see a small path leading to the west. ";

    if (TP->query_skill(WALKER_SKILL))
    {
        long_desc += "You feel a magical presence in this room, but "+
            "cannot tell where it is coming from or what exactly "+
            "it is.";
    }

    long_desc += "\n";

    return long_desc;
}

void
create_room()
{
    set_short("Road through Calian westlands");
    set_long("@@long_description");

    add_item(({"dwelling places"}), "The are few dwelling places " +
       "in this area, simple huts typically belonging to the " +
       "poor.\n"); 

    add_item(({"dock", "docks"}), "The dock area is not far to " +
       "the northwest, it is typically a very busy area thriving " +
       "with traders and travellers.\n");

    add_item(({"gelan", "town", "gates"}), "All you can see of Gelan " +
       "from here are its towering gates and walls.\n");

    add_item(({"moor", "moorland", "land", "lands"}),
       "A wide area of open " +
       "uncultivated moorland stretches south, southeast and  " +
       "southwest, with a cobbled road winding through " +  
       "it on its lonely path.\n");

    add_item(({"road", "cobbled road"}),
        "A simple road leading from Gelan and the docks into the " +
        "moorland to the south. It is " +
        "made of smallish grey stones that are " +
        "closely cobbled together. It might create a slightly " +
        "bumpy ride for carriages.\n");
    add_item((({"dunes", "row", "sand dunes"})),
        ("The dunes are small hills of white sand, "+
        "covered in clumps of pampas grass, "+
        "which waves gracefully in the breezes.\n"));
    add_item((({"path", "small path"})),
        ("A small path leads west toward the dunes.\n"));

    add_exit(ROAD+"road20","northwest"); 
    add_exit(ROAD+"road19","north");
    add_exit(ROAD+"road17","south");
    add_exit(BEACH+"sea_path1","west");
    add_exit(ROAD+"m01", "southwest");
    add_exit(ROAD+"m02", "southeast");
    add_exit(NORTHEAST_CONNECT, "northeast"); 
}


int
block()
{
    this_player()->catch_msg("That section is closed, major work in " +
                             "progress, will open SOON WE HOPE.\n");
    return 1;
}

