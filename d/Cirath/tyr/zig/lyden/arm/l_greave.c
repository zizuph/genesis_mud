/* l_greave.c: The pants of Lyden. Revised by Serpine, 11/24/95. */
 
#pragma strict_types
 
inherit "std/armour";
#include "/sys/wa_types.h"
#include "../local.h"
 
void
create_armour()
{
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
    set_am(({ -5, 3, 4}));
 
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2500);
}
