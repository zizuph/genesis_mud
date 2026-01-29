/*
 * /w/aeg/sparkle/sewer/obj/grem_slapjack.c
 *
 * Created FEB 11 2009, by Aeg (Matthew Morin)
 * 
 */

inherit "/std/weapon";

#include <wa_types.h>  
#include <formulas.h>
#include <wa_types.h>
#include "../defs.h"

void
create_weapon()
{
    set_name("slapjack");
    set_short("dirty weighted slapjack"); 
    set_long("This dirty weighted slapjack is a sack that appears to be "
           + "filled with owlrat beaks. This would hurt if swung in "
           + "combat.\n");
    add_adj("dirty");
    add_adj("weighted");

    set_hit(20);                /* To hit value        */
    set_pen(25);                /* Penetration value   */
    add_prop(OBJ_I_WEIGHT, 5000); 
    add_prop(OBJ_I_VOLUME,  500);

    set_wt(W_CLUB);             /* Club       */
    set_dt(W_BLUDGEON);         /* 'Bludgeon' */

    set_hands(W_LEFT); /* Lets make it a lefty for kicks */
}
