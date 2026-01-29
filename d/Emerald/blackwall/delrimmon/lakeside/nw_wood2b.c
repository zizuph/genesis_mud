/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_wood2b.c
 *
 *  A depression has been created on the forest floor here, where a pool
 *  of water once rested among the trees, many ages ago, in this
 *  northwest corner along the lakeside of Del Rimmon in the Blackwall
 *  Mountains.
 *
 *  Copyright (c) August 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
public mixed       Portal;

/* prototypes */
void    create_tree_room();
public void        reset_room();
public void        leave_inv(object ob, object to);
public string      describe();
public string      maeltars_finger();

/*
 * Function name:    create_tree_room
 * Description  :    allows us to create the room with area presets
 */
void
create_tree_room()
{
    add_name(SAND);
    set_loc(2);
    set_side("northwest");
    set_show_area_desc();

    set_extraline(describe);

    add_item( ({ "shadow", "large shadow", "point" }), maeltars_finger);
    add_item( ({"ground", "forest floor", "floor"}), BSN(
        "The forest floor is marked here by a wide depression which"
      + " has sunk rather deeply in the ground."));
    add_item( ({"depression", "large depression",
                "wide depression"}), BSN(
        "Ferns grow thickly in this bowl-like pit in the forest floor."
      + " It looks to be roughly four feet deep and twelve meters"
      + " in diameter."));
    add_item( ({"pit", "bowl-like pit"}), BSN(
        "From the look of this depression, there was perhaps a pool"
      + " of water which rested here long ago."));
    add_item( ({"fern", "ferns", "large fern", "large ferns",
                "many large ferns"}), BSN(
        "Ferns crowd closely together in the depression, clinging"
      + " to its gradually sloping sides."));
    add_item( ({"sides", "sloping sides", "gradually sloping sides",
                "side of the depression", "sides of the depression"}),
    BSN("The sides of the depression are chocked with many large ferns"
      + " which grow closely together. The ferns extend down into the"
      + " base of the pit, but seem to stop growing in the middle of"
      + " the base of the pit."));
    add_item( ({"middle", "middle of the base", "base",
                "base of the pit", "middle of the pit",
                "middle of the base of the pit"}), BSN(
        "The middle of the base of the pit is devoid of plant life,"
      + " and marked only by a dusty patch of earth."));
    add_item( ({"patch", "dusty patch", "patch of earth",
                "dusty patch of earth"}), BSN(
        "The dust which covers the patch of earth is very fine, and"
      + " soft to the touch."));
    add_item( ({"dust", "dust which covers the patch of earth"}), BSN(
        "There does not appear to be anything special about this"
      + " dust. Perhaps it is the last remnants of an ancient pool"
      + " basin."));

    add_cmd_item( ({ "dust", "dust which covers the patch of earth",
                     "dusty patch of earth", "patch", "patch of earth" }),
              ({"search", "dig"}), BSN(
        "You dig around a little in the dust which covers the patch of"
      + " earth. It is extremely fine, and reminds you of the sort of"
      + " earthen residue which might build up on the bottom of a dried"
      + " up puddle."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff3","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3b", "northeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore1", "southeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1b", "southwest",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff2","west",check_sitting,1,1);

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
        if (to->id("del_rimmon_fallroom"))
        {
            Portal->remove_standing(1);
            return;
        }
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
    string txt = "The ground is rather sunken here, where a large"
               + " depression in the forest floor has overgrown"
               + " with many large ferns.";

    if (!query_beacon())
    {
        return txt;
    }

    if (MANAGER->query_door_location(this_player()) == SAND)
    {
        txt += " A large shadow extends into the area here, its point"
             + " ending directly over the ferns.";
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

    if (MANAGER->query_door_location(this_player()) != SAND)
    {
        return "The shadows which are cast by the brilliant illumination"
             + " all point west northwest, as if the source of the light"
             + " were coming from the southeastern end of the lake.\n";
    }

    return "The shadow extends into the area like a vast finger. It"
         + " is pointing directly at the ferns.\n";
} /* maeltars_finger */
