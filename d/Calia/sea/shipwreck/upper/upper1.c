/*   upper1.c
 *
 * Upper levels of the Shipwreck.
 *
 * Orignal creator, unknown.
 * Modified by Baldacin@Genesis, July 2003
 *
 * Previous update 2003/08/17
 * Typos, Lavellan 2010/09/02
 */

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Bow of a wrecked ship");
    set_long("You are floating underwater at the bow of the shipwreck, "+
        "although you see signs of decay all around. The figurehead, "+
        "which once watched the waters ahead of the ship but now lays "+
        "on its side here on the deck, seems strangely untouched by the "+ 
        "destructive environment. The wooden railwork, once a fine "+
        "example of craftmanship, now rots in the salt water that "+
        "has become its final resting place. You are able to swim "+
        "east, further into the shipwreck.\n");

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
        "with what were once, obviously, detailed engravings but have "+ 
        "now rotted beyond recognition.\n");
    add_item("figurehead","The carved figure that used to sit on the "+
        "prow of the ship. It resembles a woman's body with a large lion's "+
        "head. The figure is holding up one of its hands to its forehead, "+
        "spying into the distance.\n");
    add_item(({"wreck","shipwreck"}),"It used to be a pretty small ship, "+
        "about 25 meters, some sort of transportation ship. The ship is "+
        "decayed and rotting, it must have been down here for quite some "+
        "time. The salty water probably did its share of corroding too.\n");
    add_item("deck", "It is the floorlike covering of the ship's surface. "+
        "It is made of wood, you can't see anything special about it.\n");
    
    add_swim_exit(WRECKU + "upper2","east");    
}
