/* Gallery 4
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(4, "This is the north end of the gallery leading from "
      +"the museum entrance into the main trefoil-shaped building. The "
	  +"floor is smooth marble tile that runs seamlessly to the long "
	  +"gneiss walls that seem to sparkle with inset gems. Light streams "
	  +"in from overhead, creating a nimbus around the heads of the "
	  +"sculptures."); 
}

void create_room()
{
    set_short("north end of gallery");
    add_descs(); 
    update_statues();
    add_item("statues", "@@exa_statues@@");
    add_descs(); update_statues();
    add_exit(STAT3, "south");
    add_exit(STAT5, "north");
}
