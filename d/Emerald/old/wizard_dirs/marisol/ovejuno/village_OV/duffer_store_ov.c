/* Peddler_store.c coded by Amelia
 * Use by for the new Re Albi by Marisol (2/4/98)
* Modified by Marisol (07/20/98) to be used in the village of
* Ovejuno in Emerald.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Emerald/std/room";
inherit "/lib/store_support";

#include "/sys/stdproperties.h"
#include "defs.h"



void
create_emerald_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");


    reset_room();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}                 
