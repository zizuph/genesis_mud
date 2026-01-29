/*
 * Base room for castle walls
 * Finwe, August 2004
 */
 
#include "defs.h"
 
inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";
void create_wall_room() {}
 
create_room()
{
    set_short("On the castle wall");
    
    add_item(({"walls", "wall", "castle walls", "castle wall"}),
        "The walls are made of large stones, stacked on top of " +
        "each other. They are put together so well that no seams " +
        "are visible. Arrow slits are cut into the wall at " +
        "regular intervals with steel doors set into the wall " +
        "to the left of each slit.\n");
    add_item(({"stones"}),
        "The stones are polished smooth and stacked one on top " +
        "of each other. They are about the height of an elf and " +
        "look to be quite thick. No seams are visible where each " +
        "stone joins each other. Slits are cut into the wall at " +
        "regular intervals.\n");
    add_item(({"slits", "arrow slits"}),
        "They are about a span wide and run about two-thirds " +
        "the length of the wall. They are designed to allow " +
        "guards to defend the castle. Attached to the left of " +
        "each slit is a steel door. They slide over the slits, " +
        "closing them off and protecting guards who patrol the " +
        "wall.\n");
    add_item(({"steel doors", "steel door", "slit covers", 
            "slit cover", "cover"}),
        "They are a span wide and a little shorter than the wall. " +
        "They slide over the arrow slits, effectively covering the " +
        "openings.\n");
    add_item(({"sky", "up"}),
        "The sky is bright blue with a few clouds floating in " +
        "it.\n");
    add_item(({"down", "ground", "walkway"}),
        "The stones are polished smooth and stacked next to " +
        "each other. No seams are visible where each stone " +
        "joins each other. The walkway is quite wide, allowing " +
        "at least fifteen elves to walk abreast down it. The " +
        "stones merge seamlessly with the wall forming a " +
        "perfect fit.\n");
      
    create_wall_room();

}
