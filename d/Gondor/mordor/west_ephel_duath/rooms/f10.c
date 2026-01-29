/*
 * Western slopes of Ephel Duath outdoor room
 *
 * --Raymundo, May 2020
 */

#pragma strict_types

inherit "/d/Gondor/mordor/west_ephel_duath/lib/base_room";

#include <macros.h>
#include "/d/Gondor/defs.h"
//#include "defs.h"

string my_long();

void
create_plains()
{
    set_short("Alongside the Mountains of Shadow");
    set_long("@@my_long@@");


    add_exit(ED_W_ROOM + "f7", "northwest");
    add_exit(ED_W_ROOM + "f9", "west");
    add_exit(ED_W_ROOM + "f12", "southwest", 0, 0, 1);
    add_exit(ED_W_ROOM + "f13", "southeast");
       
    here = this_object();

    plains_herbs_2();
    add_mountains_close("east", "m7");
    add_forest_floor();
    
    add_item( ({"fence", "rock fence"}), "Steep and tall, the mountains "
        + "make it nearly impossible to go any further east.\n");
    add_item( ({"cave", "cave"}), "The cave is recessed into the face of the "
        + "mountain. It's little more than a crack from here, but you could "
        + "likely eneter it.\n");
    add_item( ({"crack", "cave", "gap", "crevice"}), "The crack is completely "
        + "black, showing no sign of light whatsoever. It's wide enough that "
        + "you could squeeze into it, but not so wide as to call attention "
        + "to itself.\n");
    add_cmd_item( ({"crack", "cave", "gap", "crevice", "into crack", "into cave", "into gap", "into crevice"}), ({"enter", "squeeze", "crawl"}), "@@enter_cave@@");
    add_item( ({"mountain", "mountains"}), "The mountains are very tall, looking "
        + "like a rock fence here. Their peaks are lost in shadow and fog, so "
        + "standing this close, you have no idea how tall they actually are. "
        + "The base of the mountains are covered with rocks and boulders, as "
        + "well as some bushes. You notice a rather large crack between two "
        + "of the boulders.\n");
    add_item( ({"rock", "rocks", "boulders", "boulder", "base"}),
        "The boulders are large rocks, nearly as grey as the eastern sky. "
        + "Mostly, they are the size of a small horse. You notice an odd "
        + "black gap between two of them.\n");
}

string
my_long()
{
    string description1, description2;
    description1 = "Steep and tall, the mountains rise up like a fence. "
        + "Their base is covered with boulders and shrubs. ";
    description2 = "To the west is a forest. It's open enough that you "
        + "can walk through it, although your visibility is limited.";
    if(TP->query_wiz_level())
    {
        write("\n"+
        "********************************************************\n"+
        "*                                                      *\n"+
        "*   THIS ROOM NEEDS TO HAVE c1 CODED AND ADDED TO IT   *\n"+
        "*   THE c1 IS A CAVE THAT HAD SOME RANGERS IN IT. THEY *\n"+
        "*   HAVE BEEN CAPTURED AND TAKEN TO THE CASTLE. THERE  *\n"+
        "*   ARE SIGNS THAT THEY'VE BEEN HERE:                  *\n"+
        "*   CLOAKS                                             *\n"+
        "*   A MISSIVE FROM THE RANGER CAPTAIN                  *\n"+
        "*   SOME FOOD                                          *\n"+
        "*   THE REMAINS OF A CAMPFIRE                          *\n"+
        "*   DRAG MARKS AND BOOTPRINTS LEADING OUT              *\n"+
        "*                                                      *\n"+
        "********************************************************\n\n");
    }
        
    return(description1 + time_description() + description2 +  "\n");
}

void
reset_room()
{
    set_searched(0);

    
}

int
enter_cave()
{
    say(QCTNAME(TP) + " squeezes into the crack, entering the cave.\n");
    write("You enter the cave, squeezing into the crack.\n");
    tell_room(ED_W_ROOM + "c1", QCTNAME(TP) + " arrives from outside.\n");
    TP->move_living("M", ED_W_ROOM + "c1");
    return 1;
}