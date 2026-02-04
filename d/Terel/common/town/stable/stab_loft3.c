/* room1.c
   Mort 911004 */
/* Modified by Azireon, August 15, 1992, stab_loft3.c
   "All generations shall call me blessed"  Assumption 1992 */

inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

int  needle_gone = 0;

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room()
{
    set_short("Stable loft, on top of hay");
    set_long(break_string(
      "This is the stable's loft, a wide open space as large as the " +
      "entire building.  Above your head, the rafters are lost in " +
      "an enveloping blanket of darkness.  You are standing on top " +
      "of a vast supply of straw and hay that has been stored here.  " +
      "A narrow walkspace can be seen below.\n", 70) );

    add_item( ({ "rafter", "rafters" }), break_string(
      "It's too dark to see much but you can hear the flutter of " +
      "wings from time to time.\n", 70) );

    add_item( ({ "hay", "straw", "supply", "bale", "bales" }),
      break_string(
      "It is impossible to tell just how much hay is stored here.  " +
      "People must value being prepared for anything in these " +
      "conditions.\n", 70) );

    add_item( ({ "walkway", "walkspace", "space" }),
      "It leads westward, down beneath you.\n");

    add_cmd_item(
        ({ "hay", "straw", "bale", "bales", "down", "back down" }),
        "climb",
        "@@climb");

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    add_exit(TOWNDIR + "stable/stab_loft2", "down", 0);

    clone_object(TOWNDIR + "stable/haystack.c")
        ->move(this_object());
}

/*
 * Function name: climb
 * Description  : Climb back down the haystack.
 */

climb()
{
    write("You climb down into the narrow walkway.\n");
    this_player()->move_living("climbing downward",
                             TOWNDIR + "stable/stab_loft2");
    return 1;
}
