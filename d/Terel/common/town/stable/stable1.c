/* room1.c
   Mort 911004 */
/* stable1.c, modified by Azireon, August 5, 1992 */

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
    set_short("Stable");
    set_long(break_string(
      "You are in a large stable.  The temperature is warmer here " +
      "than the outside, but not by much.  In the faint light " +
      "you can see little, but snorting, stamping, neighing " +
      "and other horse noises can be heard.  Straw covering the " +
      "floor seems to dampen sound here as it echoes softly into the " +
      "loft above.  Arches to the north and south lead to the horse " +
      "stalls and there is a large central room to the west.  A " +
      "yellow wooden ladder leads up through a hole in the ceiling " +
      "into the loft.\n", 70) );

    add_item( ({ "horse", "horses" }), break_string(
      "Although you can't see the horses, you can hear them in their " +
      "stalls and you can certainly smell them.\n", 70) );

    add_item( ({ "straw", "floor" }), break_string(
      "Yellow-green straw covers the wooden floor.  Because it is wet " +
      "from the snow that has been tracked in, it fills the stable " +
      "with a pleasnt, musty smell.\n", 70) );

    add_item( ({ "arch", "arches" }),
      "The archways lead to the stalls where the horses are kept.\n");

    add_item( ({ "loft", "ladder" }), break_string(
      "A yellow ladder climbs up to the loft which is high above, " +
      "hidden from view.\n", 70) );

    add_prop(ROOM_I_INSIDE, 1);  /* Thi is an insid room */

    add_exit(TOWNDIR + "stable/field_1", "out", 0);
    add_exit(TOWNDIR + "stable/stable2", "north", "@@closed");
    add_exit(TOWNDIR + "stable/stable3", "south", "@@closed");
    add_exit(TOWNDIR + "stable/stable4", "west", "@@locked");
    add_exit(TOWNDIR + "stable/stab_loft1", "up", 0);
}

/*
 * Function name:
 * Description  :
 */

closed()
{
    write("You head toward the arch but the smell of horse is\n");
    write("too strong and you decide you can't go that way.\n");
    return 1;
}

locked()
{
    write("The door to the central room to the west is locked.\n");
    return 1;
}
