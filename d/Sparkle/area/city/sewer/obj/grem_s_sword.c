/*
 * /d/Sparkle/area/city/sewer/obj/grem_scimitar.c
 *
 * Created FEB 22 2009, by Aeg (Matthew Morin)
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
    set_name("scimitar");
    add_name("sword");
    set_short("light curved scimitar"); 
    set_long("This scimitar is created of a light, yet durable metal and "
           + "seems to shine, regardless of dirtiness. The hilt is "
           + "ornate and chipped in some places.\n");
    add_adj("curved");
    add_adj("light");

    set_hit(30);                /* To hit value        */
    set_pen(21);                /* Penetration value   */
    add_prop(OBJ_I_WEIGHT, 1000); 
    add_prop(OBJ_I_VOLUME,  500);

    set_wt(W_SWORD);            /* Sword                */
    set_dt(W_SLASH);            /* 'slash'              */

    set_hands(W_LEFT); /* Lets make it a lefty for kicks */
}
