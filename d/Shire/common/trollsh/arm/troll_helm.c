/*
 * Helmet used by trolls in Trollshaws
 * -- Finwe October 2001
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name(({"helmet", "helm"}));
    set_short("dented iron helmet");
    set_adj(({"dented","iron"}));
    set_long("This is an old helmet that the trolls seized from " +
        "somewhere in one of their battles. It's rusty and covers " +
        "the head adequetly, providing some protection in battle.\n");
        
    set_ac(27);
    set_at(A_HEAD);
    
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 750+random(500));
    add_prop(OBJ_I_VOLUME, 1000);
}
