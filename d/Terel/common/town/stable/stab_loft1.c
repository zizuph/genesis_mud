/* room1.c
   Mort 911004 */
/* Modified by Azireon, August 15, 1992, stab_loft.c
   "All generations shall call me blessed"  Assumption 1992 */

inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room()
{
    set_short("Stable loft");
    set_long(break_string(
      "This is the stable's loft, a wide open space as large as the " +
      "entire building.  Above your head, the rafters are lost in " +
      "an enveloping blanket of darkness.  A vast supply of straw " +
      "and hay has been stored here, in bales stacked up nearly " +
      "twelve feet.  A narrow walkspace leads away to the west.\n", 70) );

    add_item( ({ "rafter", "rafters" }), break_string(
      "It's too dark to see much but you can hear the flutter of " +
      "wings from time to time.\n", 70) );

    add_item( ({ "hay", "straw", "supply", "bale", "bales" }),
      break_string(
      "It is impossible to tell just how much hay is stored here.  " +
      "People must value being prepared for anything in these " +
      "conditions.\n", 70) );

    add_item( ({ "walkway", "walkspace", "space" }),
      "It leads westward into darkness.\n");

    add_cmd_item(
        ({ "hay", "straw", "bale", "bales" }),
        "climb",
        "@@climb");

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    add_exit(TOWNDIR + "stable/stable1", "down", 0);
    add_exit(TOWNDIR + "stable/stab_loft2", "west", 0);

}

/*
 * Function name: climb
 * Description  : Automatically fails climb attempt--whets players'
 *    appetite for climb in next room...
 */

climb()
{
    write("You can't seem to get a good grip to climb up.\n");
    say(break_string(QCNAME(this_player()) + " tries to climb up " +
        "the bales but does not succeed.\n", 70) );
    return 1;
}
