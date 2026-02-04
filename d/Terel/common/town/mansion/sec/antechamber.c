/* Basic room, ready-made for modification, Azireon. */
/* Modified by Azireon, Sept. 6, 1992, antechamber.c */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Terel/common/terel_defs.h"

create_room()
{
    set_short("Antechamber");
    set_long(break_string(
        "This large rectangular room is bare except for a massive " +
        "marble fountain, its water now filled with algae and " +
        "garbage.  Directly over the fountain, pale light filters " +
        "through a large stained glass window in the ceiling, at " +
        "least 30 feet above, at the point where four graceful " +
        "arches reaching from the room's corners come together.  " +
        "Archways lead north and south and doors east and west.\n", 70));

    add_item("fountain",
        break_string(
        "Made of marble, this massive fountain consists of a large " +
        "sculpture in the center of a vast ovalur pool.  It depicts " +
        "a gigantic and outlandish pile of writhing, wailing " +
        "stone gargoyles, seemingly frozen in a moment of intense " +
        "agony.  Brass nozzles protrude from their mouths although " +
        "water stopped spurting forth from them long ago.  The smell " +
        "of the greenish brown water is as repulsive as the " +
        "sculpture itself.\n", 70) );

    add_item( ({ "algae", "garbage" }),
        break_string(
        "The fountain is filled with putrid water as well as leaves, " +
        "pieces of broken glass, mud, some dead animals and all sorts " +
        "of garbage.  A slow drip of water falls heavily from the " +
        "cracked window above.\n", 70) );

    add_item("window",
        break_string(
        "Although there are several cracks and a large portion of " +
        "it missing, the window is still impressive.  You can make " +
        "out images of a pack of snowy wolves, people in blue habits " +
        "being attacked, some dead, and a large horse that seems "+
        "to be on fire.\n", 70) );

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room. */
    add_prop(ROOM_HAS_WATER, 1);  /* For Dust's quest! */

    add_exit(MANSION + "second/staircase1", "west", 0);
    add_exit(MANSION + "second/staircase2", "east", 0);
    add_exit(MANSION + "second/concert_hall", "north", 0);
}
