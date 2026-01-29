/* Gallery 9
 *  expansion based off other gallery rooms
 *  Lilith, Oct 2021
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(9, "Just east of the museum cafe, this is the northern-"
      +"most section of the East Wing of museum. The floor is smooth "
	  +"marble tile that runs seamlessly to curving gneiss walls which "
      +"seem to sparkle with inset gems. The light of the Source shines "
	  +"through the dome overhead, highlighting the airiness of the "
      +"central atrium to the southwest."); 
}


void create_room()
{
    set_short("East Wing");
    add_descs(); 
    update_statues();
    add_item("statues", "@@exa_statues@@");
    add_exit(CENTER, "west");
	add_exit(STAT6,  "southwest");
    add_exit(STAT10, "southeast");
	add_exit(STAT11, "south", 0, 1, 1); // non-obvious
}
