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
    set_short("battered steel helmet");
    set_adj(({"battered","steel"}));
    set_long("This is an battered steel helmet. It is dull and " +
        "looks like it may have been very nice at one time. Now " +
        "it's looking pretty sad and has probably been used in " +
        "many wars.\n");
        
    set_ac(35 + random(5));
    set_at(A_HEAD);
    
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 750+random(500));
    add_prop(OBJ_I_VOLUME, 1000);
}
