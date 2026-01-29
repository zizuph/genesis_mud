/* Gallery 3
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(3, "This is the center of the south gallery "
      +"of the museum. The walls are here are lined with statues. " 
      +"The floor is smooth marble tile, perfectly fitted "
      +"together and running seamlessly to the long gneiss walls "
      +"that seem to sparkle with inset gems.");
}

void create_room()
{
    set_short("center of the south gallery");
    add_descs(); 
	update_statues();
    add_item("statues", "@@exa_statues@@");

    add_exit(STAT2, "south");
    add_exit(STAT4, "north");
    add_exit(STUDIO, "west"); 
	add_exit(MUS +"vestibule", "east");
}
