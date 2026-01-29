/* Gallery 8
 *  expansion based off other gallery rooms
 *  Lilith, Oct 2021
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(8, "This is the eastern section of the museum's North "
      +"Wing. The floor is smooth marble tile which runs flawlessly to"
	  +"ward curving gneiss walls that seem to sparkle with inset gems. "
	  +"The light of the Source pouring the the dome overhead sets causes "
	  +"everything in the room to glow faintly. Southwest is the cafe, "
	  +"and the rest of the museum beyond it."); 
}


void create_room()
{
    set_short("North Wing");
    add_descs(); 
    update_statues();
    add_item("statues", "@@exa_statues@@");

    add_exit(CENTER, "southwest");
    add_exit(STAT7,  "northwest");
	add_exit(STAT15, "west", 0, 0, 1);

}
