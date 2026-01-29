/*
 *  /d/Sparkle/area/orc_temple/doors/2_cell_door.c
 *
 *  This is one of the doors for the prison cells on the 2nd level of
 *  the dunegeon beneath the Orc Temple in Sparkle.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit DOORS_DIR + "dungeon_door";


/* Prototypes */
public void        create_dungeon_door();
public void        configure_cell_door(string s);


/*
 * Function name:        create_dungeon_door
 * Description  :        constructor for the door object
 */
public void
create_dungeon_door()
{
    ::create_dungeon_door();

    set_door_id("orc_temple_2_cell");

    /* set some dummy values just so the thing will load */
    set_pass_command( ({ "north" }) );
    set_door_name( ({ "door" }) );

    set_open_desc("An open door that is not configured.\n");
    set_closed_desc("A closed door that is not configured.\n");
    set_door_desc("This door is not yet configured.\n");
    /* Good. now the real stuff. */

    set_fail_pass("The rusty cell door is closed.\n");
    set_open_mess( ({ "opens the rusty cell door.\n",
                      "The rusty cell door opens.\n" }) );
    set_close_mess( ({ "closes the rusty cell door.\n",
                       "The rusty cell door closes.\n" }) );

    add_item( ({ "casing", "square casing", "metal casing", "lock" }),
        "The casing surrounding the lock looks like it has been"
      + " dented and scraped many times. A rectangular keyhole is"
      + " located right in the center.\n");
    add_item( ({ "keyhole", "rectangular keyhole" }),
        "It looks pretty standard. In other words, a key is needed.\n");
    add_item( ({ "handle", "door handle" }),
        "The door doesn't really seem to have a handle. Probably,"
      + " anyone wanting to open it would just grasp the bars and"
      + " tug or shove in the right direction.\n");
    add_item( ({ "bar", "rusty bar", "rusty bars",
                 "vertical bar", "vertical bars",
                 "iron bar", "iron bars",
                 "rusty iron bar", "rusty iron bars",
                 "rusty vertical bar", "rusty vertical bars",
                 "vertical iron bar", "vertical iron bars",
                 "rusty vertical iron bar", "rusty vertical iron bars" }),
        "These look like the sort of thing one might get VERY tired of"
      + " looking at after a good 2 weeks with no decent"
      + " food, water, or clothing. Alas for those captured by these"
      + " orcs!\n");

    set_other_room("/d/Nowhere/no_room");

    set_lock_command("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key("_orc_temple_2_cell_key");
} /* create_dungeon_door */


/*
 * Function name:        configure_cell_door
 * Description  :        set up the door, allowing us to tell the
 *                       door which direction it is leading.
 * Arguments    :        string s - the direction the door leads
 *                                  default: "east"
 */
public void
configure_cell_door(string s)
{
    set_pass_command( ({ s[0..0] ,s }) );
    set_door_name( ({ "door", "rusty door", "cell door",
                      "rusty cell door",
                      "doorway", "rusty doorway", "cell doorway",
                      "rusty cell doorway",
                      s + " door", s + "ern door",
                      s + " doorway", s + "ern doorway",
                      "door to the " + s, "doorway to the " + s }) );

    set_open_desc("There is an open rusty cell door leading " + s + ".\n");
    set_closed_desc("There is a closed rusty cell door leading " + s + ".\n");

    set_door_desc("Rusty vertical iron bars comprise this cell"
      + " door which has been set in the " + s + "ern wall. A square"
      + " metal casing on one side of the bars contains a keyhole.\n");
} /* configure_cell_door */