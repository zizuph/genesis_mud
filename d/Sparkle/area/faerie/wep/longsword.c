/*
 * Longsword for Faerie NPCs
 * by Finwe, April 2005
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int hit = 20,
    pen = 20;
void
create_weapon()
{

    set_name("sword");
    add_name("longsword");
    set_adj("sharp");
    set_adj("steel");
    set_short("sharp steel longsword"); 
    set_long("This is a " + short() + ". It is a common sword used by elves " +
        "to protect themselves. The blade is long and made of steel with a " +
        "nice handle.\n");

    set_hit(hit);
    set_pen(pen);

    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);

    set_hands(W_ANYH); 
}

