/* Gallery 5
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(5, "Just south of the central atrium of the museum. "
      +"The floor is smooth marble tiles which run seamlessly through"
	  +"out the trefoil-shaped building. Source-light streams into "
	  +"the room, setting the curving gneiss walls asparkle. South "
	  +"is the long gallery leading toward the entrance of the building."); 
}


void create_room()
{
    set_short("north end of gallery");
    add_descs(); 
    update_statues(); 
    add_item("statues", "@@exa_statues@@");

    add_exit(STAT4, "south");
    add_exit(STAT6, "north");
}
