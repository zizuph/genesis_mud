/*
 * /d/Faerun/obj/basic_dagger.c
 *
 * Created June 14, 2016 by Twire
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
    set_name("dagger");
    set_short("steel dagger"); 
    set_long("This is a basic steel dagger It is double-bladed and"
           + "has a simple leather hilt that allows it to be wielded"
           + "in either hand.\n");
    add_adj("sword");
    add_adj("steel");
    set_hit(22);                /* To hit value        */
    set_pen(25);                /* Penetration value   */
    add_prop(OBJ_I_WEIGHT, 500); 
    add_prop(OBJ_I_VOLUME,  500);
    set_wt(W_KNIFE);            /* KNIFE            */
    set_dt(W_STAB | W_SLASH); 
    set_hands(W_ANYH); 
}

