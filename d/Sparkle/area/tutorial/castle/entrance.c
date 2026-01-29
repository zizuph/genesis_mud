/*
 *  /d/Sparkle/area/tutorial/castle/entrance.c
 *
 *  Within the castle of Baron von Krolock.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

/* Prototypes */
public void        create_castle_room();
public void        enter_inv(object ob, object from);

/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("at the entrance to the castle");
    set_long("A wide corridor travels east toward a narrow archway"
      + " that leads out of the castle here. North and south, cold"
      + " stone walls travel deeper into the castle, framing the"
      + " corridor with their unfriendly surfaces.\n\n");

    add_item( ({ "surfaces", "surface", "unfriendly surfaces" }),
        "The walls seem to almost close in on you. You gaze in"
      + " amazement at the images printed on some of the tapestries.\n");

    add_castle_items();
    add_torch_items();

    add_exit("hallway_1n", "north");
    add_exit("portcullis", "east");
    add_exit("hallway_1s", "south");

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

    if (!strlen(from->query_trigger_room()) ||
        !interactive(ob))
    {
        return;
    }

    set_this_player(ob);

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        txt = "WELCOME, FAITHFUL SERVANT.";
    }
    else
    {
        txt = one_of_list( ({
            "WHO DARES TO ENTER MY CASTLE?",
            "NONE WHO ENTER THE CASTLE OF BARON VON KROLOCK SHALL LIVE!",
            "FOOL! WHO ARE YOU WHO DARES TO TRESPASS?" }) );
    }

    set_alarm(0.5, 0.0, &broadcast(txt, ob));
} /* enter_inv */

