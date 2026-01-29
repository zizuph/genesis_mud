/*   lower3.c
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
    set_short("Northern bunks in a wrecked ship");
    set_long("You are swimming in the northern bunks, this is "+
        "probably where the ships crew slept. The room is very "+
        "spartan, only three old decaying bunks are lined on the "+
        "western wall. The only way out of here is to the south.\n");

/* Room tells borrowed from the sea rooms, created by Maniac & Khail. */
    set_tell_time(45);
    add_tell("A great, dark shape cuts through the water off to one " +
        "side, but it's gone again before you can see any details.\n");
    add_tell("A school of small, brightly coloured fish appear directly " +
        "in front of you, and accelerate around you on their way past. " +
        "Tickles a bit, doesn't it?\n");
    add_tell("Something bumps you playfully from behind, at least you hope " +
        "it was playful, because it was gone when you looked around.\n");
    
    add_item(({"bunks","bunk"}),"Old, decaying and rotting. Hopefully "+
        "the bunks where in better shape when the ship sailed the seas.\n");

    add_swim_exit(WRECKL + "lower2","south");
    
}
