/* Gallery 6
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(6, "The domed ceilings of the three wings of "
      +"the museum meet and overlap here, in the light-filled central "
	  +"atrium. The floor is smooth marble tiles that run seamlessly up "
	  +"to the curving gneiss walls that seem to sparkle with inset "
	  +"gems. The museum's cafe, Goatfeathers, "
	  +"lies to the north, and beyond it, the North Wing. South is the "
	  +"gallery leading toward the entrance. The East and West Wings of "
	  +"the museum are directly accessible from here."); 
}

void create_room()
{
    set_short("south-central atrium");
    add_descs(); 
	update_statues();
    add_item("statues", "@@exa_statues@@");

    add_exit(STAT5, "south");
    add_exit(STAT9, "northeast");
    add_exit(STAT11,"southeast");
    add_exit(STAT14,"northwest");
    add_exit(STAT12,"southwest");
    add_exit(CENTER,"north");
	add_exit(STAT10, "east", 0, 1, 1); // non-obvious
	add_exit(STAT13, "west", 0, 1, 1); // non-obvious
	
}
