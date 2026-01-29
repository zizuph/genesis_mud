/* Gallery 14
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"
#include "/d/Avenir/smis/sys/statserv.h"


public void update_statues()
{
    make_statues(14, "Here in the West Wing of the museum, all "
      +"is peaceful and quiet. The light of the Source has set "
	  +"the pristine marble floors aglow. From this angle, you "
	  +"can see the three domes of the building and where they "
	  +"intersect overhead in the east, forming a large atrium. "
	  +"The curved gneiss walls sparkle as if inset with gems.");
}

void create_room()
{
    set_short("West Wing");
	update_statues();
    add_descs();
    add_item("statues", "@@exa_statues@@");
    add_exit(CENTER, "east");
    add_exit(STAT6,  "southeast");
    add_exit(STAT13, "southwest");
	add_exit(STAT12, "south");
}

