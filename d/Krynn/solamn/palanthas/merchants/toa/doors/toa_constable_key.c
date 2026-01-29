/*
 * Key to the Constable's rooms in the Tower of Arms in Palanthas.
 *
 * Mortis 09.2014
 */

#include "../../../local.h"

inherit "/std/key";

create_key() 
{
    set_name("key");
    set_short("marble-handled iron key");
    set_adj("iron");
    add_adj(({"marble", "marble-handled"}));
    set_long("Flat with an ornate, marble-ended handle, this iron key is of "
    + "high quality and construction. A -C- can be found engraved in the "
    + "center of the clover design.\n");
   
    set_key("toa_constable_door");
}
