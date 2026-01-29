/*   lower2.c
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
    set_short("Lower central parts on a wrecked ship");
    set_long("You are floating underwater at the lower central parts "+
      "of the shipwreck. A sturdy wooden ladder leads up to the main "+
      "deck and passages west and north seems to be leading to the "+
      "crew bunks. The other exits are most likely leading off to "+
      "storage rooms.\n");

/* Room tells borrowed from the sea rooms, created by Maniac & Khail. */
    set_tell_time(45);
    add_tell("A great, dark shape cuts through the water off to one " +
        "side, but it's gone again before you can see any details.\n");
    add_tell("A school of small, brightly coloured fish appear directly " +
        "in front of you, and accelerate around you on their way past. " +
        "Tickles a bit, doesn't it?\n");
    add_tell("Something bumps you playfully from behind, at least you hope " +
        "it was playful, because it was gone when you looked around.\n");
    
    add_item(({"ladder","wooden ladder","stern wooden ladder", "stern ladder"}),
      "A stern wooden ladder, leading up to the main deck of the shipwreck.\n");
    add_item("bunks","The exists west and north seems to be leading to the "+
      "crews sleeping quarters.\n");
    add_item("storage rooms","Exits northeast, east and southeast most likely "+
      "leads of to some storage rooms.\n");

    add_swim_exit(WRECKU + "upper4","up");
    add_swim_exit(WRECKL + "lower1","west");
    add_swim_exit(WRECKL + "lower3","north");
    add_swim_exit(WRECKL + "lower4","northeast");
    add_swim_exit(WRECKL + "lower5","east");
    add_swim_exit(WRECKL + "lower6","southeast");
    
}
