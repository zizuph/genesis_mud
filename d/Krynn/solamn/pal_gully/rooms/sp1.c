/* 
 * sp1.c, Road leading to Dewar Gully from Palanthas
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_CONNECT_BASE;

/*
 * Function name: reset_pal_connecting_room
 * Description  : Resets the room
 */
void
reset_pal_connecting_room()
{
	
}

/*
 * Function name: create_pal_connecting_room
 * Description  : Constructor, redefine this to configure your room
 */
void 
create_pal_connecting_room()
{
    set_short("overgrown path");
    set_long("This overgrown path cuts away from the main "
	+"city of Palanthas and leads through the moors. The "
	+"brush and overhanging trees make this area cool and "
	+"shaded. In the distance you think you see a mine and "
	+"some caverns.\n");
	
    add_item(({"mine", "mines", "abandoned mine"}), "You can barely "
        +"see the mines from here. They appear like "
        +"little humps in the distance.\n");
    add_item(({"cave", "caverns", "well-kept caverns", "well-kept caves", 
    "old cavern"}), "You can barely see the "
        +"caverns from here. They look more like a hump "
        +"in the distance.\n");
    add_item(({"brush", "overgrown path", "path", "growth"}), "The brush "
	+"is really annoying. Prickles and thistles jab at your legs as you "
	+"make your way along the path. It's well trodden but still not easy "
        +"to travel.\n");
    add_item(({"prickles", "thistles"}), "The bushes on the path have "
	+"prickles and thistles on them that stick out into and scratch "
	+"at whoever walks by.\n");
    add_item(({"trees", "tree", "overhanging tree", "overhanging trees"}),
	"The trees on either side of the path have grown tall and hang over "
	+"the path.\n");
        
    add_exit(RDIR + "sp2","west",0);
    add_exit("/d/Krynn/solamn/palanthas/merchants/nwr8.c", "southeast", 0);
    reset_pal_connecting_room();
    
}