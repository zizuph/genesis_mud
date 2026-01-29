/* l_greave.c: The pants of Lyden. Revised by Serpine, 11/24/95. */
 
#pragma strict_types
 
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"
 
void
create_armour()
{
    ::create_armour();
    set_name("greaves");
    set_adj("well-worn");
    add_adj("mekillot-hide");
    set_short("pair of well-worn mekillot-hide greaves");
    set_pshort("pairs of well-worn mekillot-hide greaves");
    set_long("The gigantic scaled plates of the trade wagon pulling "
            +"mekillot can be made into fine armour: Though this set "
            +"of greaves looks like its seen many battles, being covered "
            +"in blood and cuts.\n");
 
    set_ac(35);
    set_at(A_LEGS);
    set_am(({ -7, 3, 4}));
 
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2500);
}
