/* Gallery 1
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"
#include "/d/Avenir/smis/sys/statserv.h"

public void update_statues()
{
    make_statues(1, "This is a massive entrance to the Museum of "
      +"Sybarus. To the south, thick marble "
      +"pillars frame the open doorway leading out into the "
      +"bazaar, and to the north a wide hallway "
      +"leads to a juncture. The light of the Source sets "
	  +"the scultpures aglow.");

}

void create_room()
{
    set_short("gallery entrance");
    add_descs(); 
	update_statues();
    add_item("statues", "@@exa_statues@@");

    add_exit(STAT2, "north");
    add_exit(BAZAAR+"extr/str16", "southwest");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob) &&
	(file_name(from) == (BAZAAR + "extr/str16")))
	STATSERV_LOG_EVENT("bazaar", "Visited the Museum");
}


	
	