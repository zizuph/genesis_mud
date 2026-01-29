/*
 *  /d/Sparkle/area/tutorial/castle/hallway_6.c
 *
 *  Within the castle of Baron von Krolock. This room teaches about
 *  Light and Darkness.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

/* Definitions */
#define  TUTORIAL_CHAPTER    39  /* the chapter for the sign */

/* Prototypes */
public void        create_castle_room();
public void        enter_inv(object ob, object from);
public void        reset_room();

/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("before a descending staircase in the castle");
    set_long("The air within this corridor has become stifling, and every"
      + " breath you take seems to labor in your chest. A growing sense"
      + " of panic grips you as you gaze to the west upon stone steps"
      + " which descend into blackness. The hallway travels north, east,"
      + " and south from here.\n\n");

    add_item( ({ "hall", "hallway", "corridor", "here" }),
        "The hallway narrows to the east where it travels through an"
      + " archway. North and south, it appears to lead toward rooms of"
      + " some kind.\n");
    add_item( ({ "room", "rooms" }),
        "Little can be seen of the rooms from this distance.\n");
    add_item( ({ "arch", "archway" }),
        "The archway to the east allows guards to control passage along"
      + " the corridor.\n");
    add_item( ({ "step", "steps", "stone step", "stone steps", "west",
                 "down", "blackness" }),
        "To the west, a set of dusty stone steps lead down into darkness."
      + " Every fiber of your being seems to warn you not to go down"
      + " those steps.\n");

    add_castle_items();
    add_torch_items();

    add_exit("hallway_6n", "north");
    add_exit("hallway_5", "east");
    add_exit("hallway_6s", "south");
    add_exit("dungeon", "down");

    reset_room();
} /* create_castle_room */


/* 
 * Function name: enter_inv
 * Description:   Broadcast the Baron's voice to players who enter
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    string    txt = "";

    ::enter_inv(ob, from);

    if (from->query_trigger_room() != "hallway" ||
        !interactive(ob))
    {
        return;
    }

    set_this_player(ob);

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return;
    }
    else
    {
        txt = one_of_list( ({
            "COME NO FURTHER, WRETCHED FOOL!",
            "LEAVE NOW, BEFORE I COME UP AND DEAL WITH YOU MYSELF!",
            "SO, YOU HAVE ELECTED TO TEST MY PATIENCE? BEGONE NOW!" }) );
    }

    set_alarm(0.5, 0.0, &broadcast(txt, ob));
} /* enter_inv */


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


