/*   lower4.c
 *
 * lower levels of the Shipwreck.
 *
 * Baldacin@Genesis, July 2003
 */

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Storage room on a wrecked ship");
    set_long("You are floating underwater in a storage room in the "+
        "shipwreck. A fairly big cage is standing on the west end "+
        "and water barrels to the east end of the storage room. "+
        "It is possible to swim southwest to reach the lower central "+
        "part of the ship.\n");

/* Room tells borrowed from the sea rooms, created by Maniac & Khail. */
    set_tell_time(45);
    add_tell("A great, dark shape cuts through the water off to one " +
        "side, but it's gone again before you can see any details.\n");
    add_tell("A school of small, brightly coloured fish appear directly " +
        "in front of you, and accelerate around you on their way past. " +
        "Tickles a bit, doesn't it?\n");
    add_tell("Something bumps you playfully from behind, at least you hope " +
        "it was playful, because it was gone when you looked around.\n");
    
    add_item(({"cage", "big cage"}),"It used to be a food storage "+
        "cage, but now it is old and decaying.\n");
    add_item(({"barrels","water barrels"}),"Old barrels filled with "+
        "some kind of liquid, most likely old water.\n");

    add_swim_exit(WRECKL + "lower2","southwest");
    
}
