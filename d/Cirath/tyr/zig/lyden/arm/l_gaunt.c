/* l_gaunt.c: The Gauntlets of Lyden. Revised by Serpine, 11/24/95. */
/*  2021-11-05 Meton Changed to unarmed_enhancer*/
 
#pragma strict_types
 
inherit "/std/unarmed_enhancer";
#include "/sys/wa_types.h"
#include "../local.h"
 
void
create_unarmed_enhancer()
{
    set_name("gauntlets");
    set_adj("bloodied");
    add_adj("chitin");
    set_short("bloodied chitin gauntlets");
    set_long("These mighty gauntlets are well used, probably by someone "
            +"who could dismember people with his bare hands.\n");
    
    set_default_enhancer(35, 34, W_BLUDGEON, 35, A_HANDS, ({ 0, 0, 0 }),
        this_object());

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 1000);
}
