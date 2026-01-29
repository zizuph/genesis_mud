/* Gallery 10
 *  expansion based off other gallery rooms
 *  Lilith, Oct 2021
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(10, "This is the East Wing of the museum. "
      +"The floor is smooth marble tile that runs flawlessly to "
	  +"the curving gneiss walls that seem to sparkle with "
	  +"inset gems. West is the "
	  +"central atrium. The Source shines through the dome over"
	  +"head, creating perfect lighting for viewing sculptures."); 

}


void create_room()
{
    set_short("East Wing");
    add_descs(); 
    update_statues();
    add_item("statues", "@@exa_statues@@");

    add_exit(STAT9,  "northwest");
    add_exit(STAT11, "southwest");
	add_exit(STAT6,  "west", 0, 1, 1); // non-obvious
}
