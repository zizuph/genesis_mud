/* Gallery 2
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(2, "The tiled marble floor of this gallery leads "
      +"north, deeper into the trefoil-shaped building that houses "
      +"the museum and its massive collection of sculptures. Gneiss "
	  +"walls glitter as if inset with gemstones. South is "
      +"the grand entrance, which opens onto the bazaar.");
}

void create_room()
{
    set_short("south end of entrance gallery");
    add_item("statues", "@@exa_statues@@");
    add_descs(); 
	update_statues();
    add_exit(STAT3, "north");
    add_exit(STAT1, "south");
}
