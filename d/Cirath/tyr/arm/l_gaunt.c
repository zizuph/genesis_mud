/* l_gaunt.c: The Gauntlets of Lyden. Revised by Serpine, 11/24/95. */
 
#pragma strict_types
 
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"
 
void
create_armour()
{
    set_name("gauntlets");
    set_adj("bloodied");
    add_adj("chitin");
    set_short("bloodied chitin gauntlets");
    set_long("These mighty gauntlets are well used, probably by someone "
            +"who could dismember people with his bare hands.\n");
    set_ac(35);
    set_at(A_HANDS | A_ARMS);
 
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 1000);
}
