/*
 * Charity box weapon
 * by Finwe, April 2005
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int hit = 10 + random (5),
    pen = 10 + random (5);
void
create_weapon()
{

    set_name("sword");
    add_name(({"rapier"}));
    add_name("_ch_rappier_");
    add_adj(({"long"}));
    set_short("long rapier");
    set_pshort("long rapiers");
    set_long("This long rapier. It looks like an heirloom of a traveller " +
        "who passed by. The blade is flexible and looks dangerous.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 

    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);

    set_hands(W_ANYH); 
}

