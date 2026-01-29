/* Gallery 13
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"


public void update_statues()
{
    make_statues(13, "The gneiss walls curve away toward the north "
	  +"and south here, sparkling "
	  +"as if inset with gems. The Source shines overhead, pouring "
	  +"through the dome and setting the pristine marble floors "
	  +"aglow. It is quiet here, in this trefoil-shaped "
	  +"building. East is the central atrium of the museum.");
}
void create_room()
{
    set_short("West Wing");
	update_statues();
    add_descs(); 
    add_item("statues", "@@exa_statues@@");

    add_exit(STAT14, "northeast");
    add_exit(STAT12, "southeast");
    add_exit(STAT6,  "east", 0, 1, 1);
}
