 
/* Digit 02 FEB 95 
    Modified Maniac 7/3/95
    Modified Amelia 22/4/95
    added new exits, Maniac, 1.5.95
    short changed, Maniac, 23/5/95
    typo corrected, Maniac, 13/7/95
    west exit re-opened (finally) for sea area, Maniac, 13/9/96
    added insertion of staff for Spirit Circle entrance quest
    An obelisk only appears here if a player is on the Spirit
    Circle entrance quest AND if they are here. Nobody else 
    can see the obelisk, Jaacar, September 4, 2003
  */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"
#define NORTHEAST_CONNECT "/d/Calia/argos/nwterr/rooms/r1"

#define LIVE_I_INSERTED_PSUCHAE_STAFF "_live_i_inserted_psuchae_staff"

string scop_quest = "";

void
create_room()
{
    set_short("Road through Calian westlands");
    set_long("You are on a cobbled road running north-south in the "+
     "mid-western regions of Calia. The land " +
     "around you is changing. To the north you " +
     "can see a busy urban setting, the mighty gates of Gelan " +
     "and the bustling area near to the docks, but around you now " +
     "there are but few dwelling places and the land is more untamed. " +
      "To the west extends a row of low sand dunes. "+
     "To the south, southeast and southwest you see bleak moorland " +
     "opening out in a rolling landscape, stretching far into the " +
     "distance. You see a small path leading to the west. @@scop_quest@@\n");

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

string
scop_quest()
{
    if (present("_psuchae_staff_",TP))
    {
        scop_quest = "Here a tall obelisk, some ten feet high, stands ";
        scop_quest += "upright, at the centre of a level circle of ground. ";
        scop_quest += "There is a small hole on the top of the obelisk. ";
        scop_quest += "You could probably insert something into it if ";
        scop_quest += "you wanted to. <insert (itemname)>";
    }
    else if (TP->query_prop(LIVE_I_INSERTED_PSUCHAE_STAFF))
    {
        scop_quest = "There is a black staff sticking out of a small hole ";
        scop_quest += "on the top of the obelisk.";
    }
    else
        scop_quest = "";

    return scop_quest;
}

int
do_insert(string str)
{
    object staff;

    if (!str)
        return 0;
    
    staff = present("_psuchae_staff_",TP);
    if (!staff)
        return 0;

    if (parse_command(str, ({}), 
        "[the] [staff] 'black' [in] [the] [small] [hole]"))
    {
        NF("Insert what coloured staff in the small hole?\n");
        return 0;
    }

    write("You place the black staff into the hole.\n");
    say(QCTNAME(TP)+" appears to have placed something into thin air!\n");
    staff->remove_object();
    TP->add_prop(LIVE_I_INSERTED_PSUCHAE_STAFF,1);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_insert,"insert");
}