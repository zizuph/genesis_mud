/*
 *  /d/Sparkle/area/orc_temple/doors/1_weapon_e.c
 *
 *  This is the east side of the door to the weaponry on the first
 *  level of the Orc Dungeon in Sparkle.
 *
 *  Created August 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit DOORS_DIR + "dungeon_door";

/* Prototypes */
public void        create_dungeon_door();


/*
 * Function name:        create_dungeon_door
 * Description  :        constructor for the door object
 */
public void
create_dungeon_door()
{
    ::create_dungeon_door();

    set_door_id("1_weapon");
    set_pass_command( ({ "w" ,"west" }) );
    set_door_name( ({ "door", "black door", "metal door",
                      "black metal door",
                      "doorway", "black doorway", "metal doorway",
                      "black metal doorway",
                      "west door", "western door",
                      "west doorway", "western doorway",
                      "door to the west", "doorway to the west" }) );

    set_open_desc("There is an open black metal door leading west.\n");
    set_closed_desc("There is a closed black metal door leading west.\n");

    set_fail_pass("The black metal door is closed.\n");
    set_open_mess( ({ "opens the black metal door.\n",
                      "The black metal door opens.\n" }) );
    set_close_mess( ({ "closes the black metal door.\n",
                       "The black metal door closes.\n" }) );

    set_door_desc("A black metal door is set firmly in the western"
      + " wall of the corridor here. It is completely filthy, and"
      + " looks to have been made with little care for craftsmanship."
      + " A sturdy casing surrounds a thin keyhole situated beneath"
      + " the rugged handle which juts out from one side of the door.\n");

    add_item( ({ "casing", "sturdy casing", "lock" }),
        "The casing is comprised of the same black metal from which"
      + " the door has been constructed. It houses a thin keyhole right"
      + " at its center.\n");
    add_item( ({ "keyhole", "thin keyhole" }),
        "The key to fit this keyhole would be thinner than most.\n");
    add_item( ({ "handle", "rugged handle" }),
        "Most doors have such things as this ... well, except in the"
      + " legendary Kingdom of Kurplop where everyone is rumoured to"
      + " be born with suction cups for hands. I guess there handles"
      + " are pretty much superfluous.\n");

    set_other_room(ROOMS_DIR + "1_weaponry");

    set_lock_command("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key("_orc_temple_1_weapon_key");
} /* create_dungeon_door */