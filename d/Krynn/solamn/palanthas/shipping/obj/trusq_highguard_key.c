/*
 * Temporarily cloned key to keep the Trusq high guard's room
 * closed and locked.
 *
 * Mortis 07.2006
 */


inherit "/std/key";

#include "../../local.h"

create_key() 
{
	set_name("key");
	set_short("thin-edged steel key");
	set_adj("thin");
	add_adj("steel");
	set_long("Flat with thin-edged teeth, this steel key is of good "
	+ "quality and construction.\n");
   
	set_key("trusq_guardroom_door");
}
