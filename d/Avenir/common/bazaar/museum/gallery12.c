/* Gallery 12
 *  expansion based off other gallery rooms
 *  Lilith, Oct 2021
 */
 
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"

public void update_statues()
{
    make_statues(12, "This is the south section of the West Wing. "
      +"Here, the floor is smooth marble tile that glows in the "
	  +"light of the Source shining through the dome overhead. "
	  +"The curving gneiss walls that seem to sparkle with inset "
	  +"gems are an excellent backdrop for the many sculptures on "
	  +"view. Northeast is the central atrium of the museum."); 

}


void create_room()
{
    set_short("West Wing");
    update_statues();
    add_descs(); 
    add_item("statues", "@@exa_statues@@");

    add_exit(STAT6, "northeast");
    add_exit(STAT13,"northwest");
	add_exit(STAT14, "north", 0,1,1);
}
