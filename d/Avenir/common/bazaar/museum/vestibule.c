/* Gallery 1
 *  Cirion 040296
 */
#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
#include "museum.h"
#include "gallery.h"
#include "/d/Avenir/smis/sys/statserv.h"


void create_room()
{
    set_short("gallery entrance");
    set_long("This is a vestibule off the main gallery of "
	  +"the Museum of Sybarus. Through the doorway you can see "
      +"the light of the Source setting the sculptures on display "
	  +"aglow. It seems to be used to store surplus stone for the "
	  +"sculptor, as there are numerous massive blocks stationed "
	  +"against the gneiss walls. There is a door leading east with "
	  +"an 'exit only' sign on it.\n");
    add_exit(STAT3, "west");
    add_exit(BAZAAR+"extr/str16", "east", 0, 1, 1); // non-obvious
	add_exit(BAZAAR+"extr/str16", "door", 0, 1, 1);
	add_descs();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob) &&
	(file_name(from) == (BAZAAR + "extr/str16")))
	STATSERV_LOG_EVENT("bazaar", "Museum: used side door");
}
