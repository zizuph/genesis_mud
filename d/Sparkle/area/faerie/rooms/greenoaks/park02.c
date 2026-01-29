/*
 * Outdoor room in Green Oaks
 * By Finwe, August 2004
 */
 
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit TOWN_BASE;
 
void
create_town_room()
{
    set_short("North side of the park in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It is quiet " +
        "and relaxing. Wisteria grow over the trellis that runs around " +
        "the outside of the park. Flower boxes are scattered around " +
        "the area, providing splashes of color.\n");
        
    set_add_park();
    set_add_road();
    
    add_exit(GO_DIR + "square", "south");
    add_exit(GO_DIR + "park03", "east");
    add_exit(GO_DIR + "park01", "west");

 
}

/*
 * Function name:	init
 * Description	:	
 */
public void
init()
{
    ::init();

}
