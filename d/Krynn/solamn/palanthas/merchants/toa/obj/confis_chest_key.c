/*
 * Key to the chest of confiscated items in the Tower of Arms in Palanthas.
 * Not currently available.
 *
 * Mortis 09.2014
 */

#pragma strict_types

#include "../../../local.h"

inherit "/std/key";

create_key() 
{
    set_name("key");
    set_short("x-handled iron key");
    set_adj("iron");
    add_adj(({"marble", "x-handled"}));
    set_long("Flat with an ornate, 'X' for its handle, this iron key is of "
    + "high quality and construction.\n");
   
    set_key("confis_chest_key");
}
