/* Gallery 7
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(7, "This is the northern-most section of the museum. "
      +"The floor is the same smooth marble tile that runs seamlessly "
	  +"through the rest of the trefoil-shaped building. Curving gneiss "
	  +"walls sparkle in the light of the Source pouring from the "
	  +"glass-domed ceiling above. "
      +"South is the cafe, and the rest of the museum beyond it."); 
}

void create_room()
{
    set_short("North Wing");
    make_statues(7, "This is the northern-most section of the museum. "
      +"The floor is the same smooth marble tile that runs seamlessly "
	  +"through the rest of the trefoil-shaped building. Curving gneiss "
	  +"walls sparkle in the light of the Source pouring from the "
	  +"glass-domed ceiling above. "
      +"South is the cafe, and the rest of the museum beyond it."); 
    add_descs(); 
    update_statues();
    add_item("statues", "@@exa_statues@@");

	add_exit(CENTER, "south");
    add_exit(STAT15, "southwest");
    add_exit(STAT8,  "southeast");

}
