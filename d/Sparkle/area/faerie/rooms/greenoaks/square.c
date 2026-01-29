/*
 * Square in the center of Green Oaks
 * Drink function borrowed from Gondor
 * By Finwe, August 2004
 */
 
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit WATER_BASE;
inherit TOWN_BASE;

#define MINSTREL "/d/Terel/guilds/minstrels/living/travelling_repairer"

object minstrel;

void
reset_town_room()
{
    if(!objectp(minstrel))
    {
        minstrel = clone_object(MINSTREL);
        minstrel->move(TO, 1);
    }
}

void
create_town_room()
{
    set_short("A large fountain in the center of Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "This is " +
        "the center of town. In the middle of the square " +
        "is a large fountain. The water shoots up and out, creating a " +
        "rainbow of colors in the water. A large park surrounds the " +
        "square, creating a relaxing area in the center of Green Oaks.\n");
    add_item(({"square"}),
        "The square is wide and circular, made white flagstones " +
        "It is one of the largest areas of the village, " +
        "and surrounded by lovely gardens. A large fountain is in the " +
        "center of the square.\n");
    add_item(({"fountain", "pool"}),
        "The fountain is large and deep. Its circular design looks like " +
        "a small lake in the center of the square. In the center of " +
        "the fountain, large jets of water shoot up. A quarter of the " +
        "way into the fountain, jets of water spray inward, forming " +
        "arches in the pool of water.\n");
    add_item(({"water jets", "jets of water", "jets"}),
        "They spray up from the center of the fountain and and inward " +
        "gracefully from partway in the fountain. The ends of the water " +
        "jets land in the center of the fountain, forming a cloud of " +
        "rainbow lights.\n");
    add_item(({"arch", "arches"}),
        "The arches are streams of water that curve and sprayed from " +
        "the jets. They land in the center of the fountain.\n");
    add_item(({"cloud of rainbow lights", "rainbow", "rainbow lights", 
            "rainbow of lights", "rainbows"}),
        "They are formed where the jets of water splash into the " +
        "water at the center of the fountain. The lights are small sparkles " +
        "of red, blue, green, yellow, and a myriad of colors in between.\n");
    add_item(({"water"}),
        "The water is clear and cool looking. Light sparkles on it " +
        "like little diamonds. Small ripples lap in the  " +
        "fountain. Rainbows dance across the surface of the water in " +
        "the middle of the fountain.\n");  
    add_item(({"ripples"}),
        "These are small waves that move across the surface of the " +
        "fountain. They radiate from the middle where the jets of water " +
        "splash into the fountain.\n");
    add_item(({"surface", "surface of the water", "water's surface"}),
        "It is the top of the water in the fountain. It ripples and " +
        "moves about in random patterns.\n");
        
    set_add_park();
    set_add_road();
    
    set_drink_from( ({ "fountain", "pool"}) );   
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);  
    
    add_exit(GO_DIR + "park02", "north");
    add_exit(GO_DIR + "park07", "south");
    add_exit(GO_DIR + "park05", "east");
    add_exit(GO_DIR + "park04", "west");
    add_exit(GO_DIR + "park03", "northeast");
    add_exit(GO_DIR + "park01", "northwest");
    add_exit(GO_DIR + "park08", "southeast");
    add_exit(GO_DIR + "park06", "southwest");

    reset_town_room();

}

/*
 * Function name:	init
 * Description	:	add the drinking and river verbs
 */
public void
init()
{
    ::init();
    init_drink();
}
