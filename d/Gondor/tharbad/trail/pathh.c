/*
 * Corsair room
 *
 * Raymundo, June 2020
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/tharbad/trail/base_room";
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void  create_gondor();


/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    set_short("The western edge of the clearing");

    set_long("The clearing opens to the east, creating a staging "
        + "area for corsairs on their raids. The ground looks to be "
        + "mostly dirt, with only a little grass. There are many "
        + "tree stumps here, hacked close to the ground so that "
        + "they're mostly unnoticeable as you walk. Broken boxes "
        + "litter the ground.\n");

    add_landscape();
    add_item( ({"box", "boxes", "broken box", "broken boxes"}),
        "These boxes look like the standard boxes you would see used for "
        + "transporting goods up and down the river by boat. However, "
        + "they have been crushed and broken, whatever items they held "
        + "has long since been used or sold.\n");        
    add_cmd_item( ({"trees", "bushes", "through trees", "through bushes"}), 
        "peer", "You try to peer through the trees but are unable to do "
        + "so.\n");
    
    add_exit("pathe", "northeast");
    add_exit("pathi", "east");
    add_exit("pathl", "southeast");
    
  
 
}   /* end create_gondor () */

