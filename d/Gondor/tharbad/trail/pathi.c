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
    set_short("Near the center of the clearing");

    set_long("In every direction, there is a clearing, hastily made "
        + "by chopping down trees. Far to the east is the river, which "
        + "can occasionally be heard. There are signs of people living "
        + "here--the kind of people that like to get a little too drunk "
        + "and have a little too good of a time. Trees still stand on "
        + "the edges of the clearing, more for privacy than shade, "
        + "though.\n");

    add_landscape();
    add_trash();
    
    add_exit("pathf", "northeast");
    add_exit("pathe", "northwest");
    add_exit("pathj", "east");
    add_exit("pathh", "west");
    add_exit("pathl", "southwest");
    add_exit("pathm", "southeast");
    
  
 
}   /* end create_gondor () */

