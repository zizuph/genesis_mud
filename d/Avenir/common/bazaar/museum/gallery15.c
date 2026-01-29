/* Gallery 15
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"
#include "/d/Avenir/smis/sys/statserv.h"


public void update_statues()
{
    make_statues(15, "This is the North Wing of the museum. "
      +"The floor is the same marble tile which flows through the "  
	  +"rest of the trefoil-shaped building. The gneiss walls curve "
	  +"away to the north and south, sparkling in the light of the "
	  +"Source that streams through the dome overhead. Southwest is "
	  +"Goatfeathers, and beyond it, the rest of the museum and the "
	  +"collection of sculptures placed within."); 
}


void create_room()
{
    set_short("North Wing");
    add_descs(); 
    update_statues();
    add_item("statues", "@@exa_statues@@");
    add_exit(STAT7, "northeast");
    add_exit(STAT8, "east", 0, 1, 1);
    add_exit(CENTER, "southeast");
}

