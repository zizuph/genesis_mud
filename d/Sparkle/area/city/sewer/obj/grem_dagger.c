/*
 * /w/aeg/sparkle/sewer/obj/grem_dagger.c
 *
 * Created FEB 07 2009, by Aeg (Matthew Morin)
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
    set_name("machete");
    set_short("light dirty machete"); 
    set_long("This machete is longer than average daggers, but shorter than "
           + "a sword. It appears to be balanced for great control, but the "
           + "rust and dirt make it's effectiveness questionable.\n");
    add_adj("dirty");
    add_adj("light");

    set_hit(22);                /* To hit value        */
    set_pen(25);                /* Penetration value   */
    add_prop(OBJ_I_WEIGHT, 1000); 
    add_prop(OBJ_I_VOLUME,  500);

    set_wt(W_KNIFE);            /* Knife                */
    set_dt(W_SLASH | W_IMPALE); /* 'slash' and 'impale' */

    set_hands(W_LEFT); /* Lets make it a lefty for kicks */
}
