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
    set_short("tarnished iron helmet");
    set_adj(({"tarnished","iron"}));
    set_long("This "+short()+" looks like it was made by the trolls. " +
        "It's not as nice as most helmets but provides some " +
        "protection to the head during battles.\n");
        
    set_ac(29);
    set_at(A_HEAD);
    
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 750+random(500));
    add_prop(OBJ_I_VOLUME, 1000);
}
