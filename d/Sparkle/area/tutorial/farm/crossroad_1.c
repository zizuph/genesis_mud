/*
 *  /d/Sparkle/area/tutorial/farm/crossroad_1.c
 *
 *  A road just north of Greenhollow, south of the crossroads.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* global variables */
#define     TUTORIAL_CHAPTER        33       /* chapter for the sign */

/* prototypes */
public void        create_silverdell();
public string      describe(string arg);
public string      which_room();
public void        reset_room();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("just beyond the north gate of Greenhollow");
    set_long(&describe("long"));

    add_outdoor_items();
    add_road_items();

    add_item( ({ "here", "area" }), &describe("long"));
    add_item( ({ "gate", "north gate", "rubble", "pile of rubble",
                 "pile", "collapsed gate", "collapsed north gate",
                 "north gate of town", "collapsed north gate of town" }),
        &describe("gate"));
    add_item( ({ "town", "south", "greenhollow",
                 "town of greenhollow", "burning town", "fire",
                 "inferno" }),
        &describe("town"));
    add_item( ({ "hedge", "well-trimmed hedge", "trim hedge",
                 "hedges" }),
        &describe("hedge"));
    add_item( ({ "crossroad", "crossroads", "north" }),
        "The crossroads are visible in the distance to the north.\n");

    add_exit("crossroads", "north");
    add_exit(which_room, "south");

    reset_room();
} /* create_silverdell */


/*
 * Function name:        describe
 * Description  :        provide a status dependant descriptions
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - various descriptions of things
 */
public string
describe(string arg)
{
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        switch(arg)
        {
            case "long":
                return "Cries of terror echo to the south, where the"
                  + " town of Greenhollow appears to be on fire."
                  + " Peering over the collapsed North Gate of town,"
                  + " you are delighted to see people working hopelessly"
                  + " to save their town from the inferno. The crossroads"
                  + " are to the north.\n\n";
                break;
            case "hedge":
                return "The hedges have been ripped down and burned.\n";
                break;
            case "town":
                return "Greenhollow is burning! So much for Lars'"
                  + " promise to protect the town from harm. It seems"
                  + " that even he couldn't protect them from you.\n";
                break;
            case "gate":
                return "The North Gate of Greenhollow lies in a pile of"
                  + " rubble just to the south, clearly having been"
                  + " recently destroyed. You smile to"
                  + " yourself and relish your deadly handiwork.\n";
        }
    }

    switch(arg)
    {
        case "long":
            return "A road runs out from beneath the North Gate of"
              + " Greenhollow which is just to the south here. Well-"
              + "trimmed hedges trace its edges as it winds north to"
              + " meet with a crossroads.\n\n";
            break;
        case "hedge":
            return "The hedges are trim and attractive. They frame the"
              + " road for quite some distance until just before it"
              + " meets with a crossroads to the north.\n";
            break;
        case "town":
            return "Greenhollow is a ways to the south, beyond the"
              + " north gate of town.\n";
            break;
        case "gate":
            return "The North Gate of Greenhollow rises just south of"
              + " the road here, leading back into town.\n";
    }
} /* describe */


/*
 * Function name:        which_room
 * Description  :        define which room the exit leads to
 * Returns      :        string - the filename
 */

public string
which_room()
{
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return TOWN_DIR + "street_7_ash";
    }

    return TOWN_DIR + "street_7";
} /* which_room */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */
