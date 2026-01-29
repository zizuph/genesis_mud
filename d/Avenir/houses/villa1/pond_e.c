/*
 * villa1/pond_e.c
 *
 * Lilith, Nov 2021
 *
 */

#pragma strict_types

#include "villa1.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit V1 +"housebase";


#define BRIDGE ({"/d/Avenir/houses/villa1/w_garden"})

public string 
see_bridge(void)
{
    object *live = get_view(BRIDGE);

    if (!sizeof(live))
	return "";

    return "You can see "+ COMPOSITE_LIVE(live) +" standing on it. ";
}


/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */
void 

create_house_room()

{
    set_short("east side of pond");

    set_long("An open-air water-garden unfolds around you. "+
      "West, a bridge formed from a slab of banded white "+
      "onyx crosses the center of the pond. @@see_bridge@@"+
      "Fish flit around you and "+
      "then seek the shadows beneath the flowering lotuses. "+
      "The water is clear, and very cold. You're not sure "+
      "how long you'll be able to remain in here.\n");

    add_help_topic("here",  "/d/Avenir/houses/help/general");
    add_help_topic("room",  "/d/Avenir/houses/help/general");

    add_item( ({"villa", "house", "facade", "north wall"}),
      "The facade of the house is made of white onyx.\n");
    add_item( ({"onyx", "white onyx", "bands", "stripes"}),
      "The onyx is milky white, banded with stripes both "+
      "translucent and opaque.\n");		
    add_item( ({"south wall", "southern wall", "curtain of water",
	"cliffwall", "cliff wall", "waterfall"}),
      "The southern wall of the water garden is rough, natural " +
      "stone. A curtain of water seeps from it into the pond.\n");
    add_item( ({"east wall", "eastern wall", "east"}),
      "The eastern wall of the garden is rough, natural stone.\n");
    add_item( ({"west wall", "western wall", "west"}),
      "The western wall of the garden is rough, natural stone.\n");	
    add_item( ({"wall", "walls", "north", "south"}), 
      "The walls of this space are mostly "+
      "natural stone, except the north wall, which is polished onyx.\n");		
    add_item( ({"stone", "natural stone"}),
      "The rough stone of the walls is a natural contrast "+
      "to the highly polished onyx bridge.\n");
    add_item( ({"stones", "stepping stones"}),
      "Textured white onyx stepping stones provide secure "+
      "footing across the bed of black pebbles.\n");
    add_item( ({"bed", "pebbles", "bed of pebbles", "black pebbles" }),
      "Black pebbles polished smooth by water mark the end of the "+
      "pond.\n");
    add_item( ({"pond", "water garden", "east pond", "west pond"}),
      "The pond makes a serene water garden in which fish and "+
      "lotuses float.\n");
    add_item( ({"ceiling", "sky", "Source"}), 
      "There is open air above. You can see the Source glowing "+
      "and the ceiling of the great cavern far overhead.\n");		
    add_item( ({"bridge", "onyx bridge", "floor", "ground"}),
      "The bridge is made of a slab of white onyx. It spans the "+
      "pond from the entryway to the front hall of the house.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop("_live_i_can_fish", ({"freshwater"}));

    add_exit("w_garden", "west");

}

void
enter_inv(object ob, object from)
{
    ::enter_inv();
    write("You wade knee-deep into the water.\n");
}
