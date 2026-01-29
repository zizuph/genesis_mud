/*
 * Varian - 2016
 */

inherit "/std/weapon";

#include <wa_types.h>

void
create_weapon()
{

    set_name("shortsword");

    add_name("sword");

    set_short("plain steel shortsword");

    set_adj("plain");

    add_adj("steel");

    set_long("This shortsword appears to be a rather plain, if " +
        "servicable, weapon. Probably standard issue for a soldier.\n");
    	    
    set_wt(W_SWORD);

    set_dt(W_IMPALE);

    set_hands(W_ANYH);

    set_hit(20);

    set_pen(20);
}