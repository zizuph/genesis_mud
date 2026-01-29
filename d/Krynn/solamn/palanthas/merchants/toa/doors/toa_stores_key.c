/*
 * Key to the Tower of Arms store room.
 *
 * Mortis 09.2014
 */

#include "../../../local.h"

inherit "/std/key";

create_key() 
{
    set_name("key");
    set_short("square-handled iron key");
    set_adj("iron");
    add_adj(({"square", "square-handled"}));
    set_long("Flat with a square-ended handle, this iron key is of high "
    + "quality and construction.\n");
   
    set_key("toa_store_door");
}
