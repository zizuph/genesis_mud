/* Gallery 11
 *  expansion based off other gallery rooms
 *  Lilith, Oct 2021
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(11, "The light of the Source streams through the "
      +"dome overhead, setting the smooth marble floor aglow. "
	  +"Curving gneiss walls seem to sparkle with inset gems. "
	  +"Northwest is the central atrium and the rest of the museum. "
	  +"Here in the East Wing, there is plenty of peace and "
      +"quiet to view the sculptures on display."); 

}


void create_room()
{
    set_short("East Wing");
    add_descs(); 
    update_statues();
    add_item("statues", "@@exa_statues@@");

    add_exit(STAT10, "northeast");
    add_exit(STAT6,  "northwest");
	add_exit(STAT9,  "north", 0, 1, 1); // non-obvious
}
