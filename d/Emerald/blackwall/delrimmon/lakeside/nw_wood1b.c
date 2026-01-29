/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_wood1b.c
 *
 *  This area of forest is in the northwestern region of the woods
 *  which surround the shores of Del Rimmon in the Blackwall Mountains of
 *  Emerald. A Large boulder rests here.
 *
 *  Copyright (c) August 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define    BOULDER_NAME    "large mossy boulder"

/* global variables */
public mixed       Portal;

/* prototypes */
void    create_tree_room();
public void        reset_room();
public void        leave_inv(object ob, object to);
public string      describe();
public string      maeltars_finger();

/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with area presets
 */
void
create_tree_room()
{
    add_name(BOULDER);
    set_loc(2);
    set_side("northwest");
    set_show_area_desc();

    set_extraline(describe);

    add_item( ({ "shadow", "large shadow", "point" }), maeltars_finger);
    add_item( ({"cluster", "thick cluster"}), BSN(
        "The trees have grown thickly in this area, forming somewhat"
      + " of a thick cluster around the large boulder which rests upon"
      + " the ground here."));
    add_item( ({"boulder", "large boulder", "large mossy boulder"}), BSN(
        "The boulder is extremely large, rising perhaps four feet"
      + " from its base to its top. Shaggy green moss covers its"
      + " rocky surface."));
    add_item( ({"base", "base of the boulder"}), BSN(
        "The base of the boulder lies mostly in shadow, and seems to"
      + " have sunk somewhat below the surface of the forest bed."));
    add_item( ({"ground", "forest bed", "bed"}), BSN(
        "Moss and other undergrowth crowd the ground of the forest,"
      + " except where a large boulder rests in the midst of the"
      + " many trees here."));
    add_item( ({"top", "top of the boulder"}), BSN(
        "The top of the boulder is rough and pointed. Moss clings to"
      + " its surface and hangs down its sides."));
    add_item( ({"sides", "side", "sides of the boulder",
                "side of the boulder", "surface",
                "surface of the boulder"}), BSN(
        "The sides of the boulder are rough and ragged, except where"
      + " shaggy green moss clings to its surface."));
    add_item( ({"moss", "green moss", "shaggy moss",
                "shaggy green moss"}), BSN(
        "The moss on the boulder resembles the moss which grows on"
      + " the ground here. It is very green, and where it has grown"
      + " for a long period of time, it hangs in shaggy swaths."));
    add_item( ({"swath", "swaths", "shaggy swath", "shaggy swaths"}),
    BSN("The shaggy swaths of moss cling damply to the surface of"
      + " the large boulder, making its sides somewhat slippery."));

    add_cmd_item( ({"boulder", "large boulder", "large mossy boulder"}),
                  ({"climb"}), BSN(
        "Grasping the sides firmly, you manage to climb up onto the"
      + " large boulder, only to slide down off of the slippery moss"
      + " which clings to its peaked top."));
    add_cmd_item( ({"boulder", "large boulder", "large mossy boulder"}),
                  ({"search", "push", "pull"}), BSN(
        "The boulder is very solid, and must weigh many tons. The"
      + " moss which clings to its surface makes it very slippery."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff2","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2b", "northeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore5", "southeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5b", "southwest",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff1","west",check_sitting,1,1);


    set_no_exit_msg( ({ "northwest" }),
        "Struggling with the underbrush, you discover that movement"
      + " in that direction will not be possible.\n");
} /* create_tree_room */


/*
 * Function name:        reset_room
 * Description  :        clone the portal to the room
 */
public void
reset_room()
{
    if (!present("_del_rimmon_portal", this_object()))
    {
        Portal = clone_object(DELRIMMON_DIR + "obj/portal");
        Portal->move(this_object());
    }

    return;
} /* reset_room */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just leaved this inventory
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (Portal->query_standing() == ob)
    {
        Portal->remove_standing();
    }
} /* leave_inv */


/*
 * Function name:        describe
 * Description  :        provide a description for the room.
 * Returns      :        string - the room description
 */
public string
describe()
{
    string txt = "The trees cluster thickly together here, where they"
               + " have encircled a large boulder that rests within"
               + " the forest.";

    if (!query_beacon())
    {
        return txt;
    }

    if (MANAGER->query_door_location(this_player()) == BOULDER)
    {
        txt += " A large shadow extends into the area here, its point"
             + " ending directly over the boulder.";
    }

    return txt;
} /* describe */


/*
 * Function name:        maeltars_finger
 * Description  :        provide a description for the shadow
 * Returns      :        string - the description
 */
public string
maeltars_finger()
{
    if (!query_beacon())
    {
        return "You find no " + Exa_arg + ".\n";
    }

    if (MANAGER->query_door_location(this_player()) != BOULDER)
    {
        return "The shadows which are cast by the brilliant illumination"
             + " all point west northwest, as if the source of the light"
             + " were coming from the southeastern end of the lake.\n";
    }

    return "The shadow extends into the area like a vast finger. It"
         + " is pointing directly at the boulder.\n";
} /* maeltars_finger */
