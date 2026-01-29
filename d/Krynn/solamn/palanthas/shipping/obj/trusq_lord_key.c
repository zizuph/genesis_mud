/*
 * Temporarily cloned key to keep the Trusq master suite
 * closed and locked.
 *
 * Mortis 07.2006
 */


inherit "/std/key";

#include "../../local.h"

create_key() 
{
	set_name("key");
	set_short("thin steel key");
	set_adj("thin");
	add_adj("steel");
	set_long("Flat with fine, intricate teeth, this steel key is of high "
	+ "quality and construction.\n");
   
	set_key("trusq_master_door");
}
