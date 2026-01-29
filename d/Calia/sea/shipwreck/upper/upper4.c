/*   upper4.c
 *
 * Upper levels of the Shipwreck.
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
    set_short("Main deck of a wrecked ship");
    set_long("You are floating underwater at the central parts of the "+
        "open main deck of the shipwreck. The broken main mast, that "+
        "once was raised with sails, blowing in the wind, now lies "+
        "decayed and rotting across the deck. "+
        "In the very center of the deck a big hatch leads further down "+
        "into the ship and you can swim to the other sections of the "+
        "main deck by going north, south or west. You can enter the "+
        "Captain's cabin through a open door on the east side and wooden "+
        "stairs have been constructed on the east side as well, to access "+
        "the quarter-deck.\n");

/* Room tells borrowed from the sea rooms, created by Maniac & Khail. */
    set_tell_time(45);
    add_tell("A great, dark shape cuts through the water off to one " +
        "side, but it's gone again before you can see any details.\n");
    add_tell("A school of small, brightly coloured fish appear directly " +
        "in front of you, and accelerate around you on their way past. " +
        "Tickles a bit, doesn't it?\n");
    add_tell("The deep water darkens slightly as the sun is blocked by " +
        "a cloud high above.\n");
    add_tell("Something bumps you playfully from behind, at least you hope " +
        "it was playful, because it was gone when you looked around.\n");

    add_item(({"railwork","rails","railing"}),"They are etched "+   
        "with what was once, obviously, detailed engravings but have "+ 
        "now rotted beyond recognition.\n");
    add_item(({"wreck","shipwreck"}),"It used to be a pretty small ship, "+
        "about 25 meters, some sort of transportation ship. The ship is "+
        "decayed and rotting, it must have been down here for quite some "+
        "time. The salty water probably did its share of corroding too.\n");
    add_item(({"mast", "main mast", "broken mast", "broken main mast"}), ""+
        "It once used to point high into the skies with majestic sails, "+
        "blowing in the wind. Now it lies decaying on the wooden deck.\n");
    add_item("sails","There are no sails!\n");
    add_item(({"big hatch", "hatch"}), "It is a big hatch leading down "+
        "to the lower sections of the shipwreck.\n");
    add_item(({"captain's cabin","cabin"}),"It is quite obvious this is the "+
        "Captain's cabin. The framework of the doorway is nicely decorated.\n");
    add_item(({"wooden stairs","stairs"}),"They lead up to the quarter-"+
        "deck.\n");
    add_item(({"quarterdeck","quarter-deck", "quarter deck"}), "You can "+
        "access it by using the stairs. It is where the captain of the "+
        "ship used to stand calling out orders for the ship-crew.\n");
    add_item("deck", "It is the floorlike covering of the ship's surface. "+
        "It is made of wood, you can't see anything special about it.\n");

    add_swim_exit(WRECKU + "upper2","west");
    add_swim_exit(WRECKU + "upper3","north");
    add_swim_exit(WRECKU + "upper5","south");
    add_swim_exit(WRECKU + "captains","enter");
    add_swim_exit(WRECKU + "upper6","stairs");
    add_swim_exit(WRECKL + "lower2","down");    
}
