/*
 * Key to the Lieutenant's rooms in the Tower of Arms in Palanthas.
 *
 * Mortis 09.2014
 */

#include "../../../local.h"

inherit "/std/key";

create_key() 
{
    set_name("key");
    set_short("clover-handled iron key");
    set_adj("iron");
    add_adj(({"clover", "clover-handled"}));
    set_long("Flat with an ornate, clover-ended handle, this iron key is of "
    + "high quality and construction. An -L- can be found engraved in the "
    + "center of the clover design.\n");
   
    set_key("toa_lieutenant_door");
}
