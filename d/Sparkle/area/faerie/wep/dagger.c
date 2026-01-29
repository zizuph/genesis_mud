/*
 * Dagger for Faerie NPCs
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

    set_name("dagger");
    set_adj("long");
    set_adj("sharp");
    add_adj("metal"); /* It is, isn't it? - Gorboth */
    set_short("long sharp dagger"); 
    set_long("This is a " + short() + ". It is long, and almost a " +
        "shortsword. It's a common weapon for travellers to carry who " +
        "don't want to be seen with a sword. The blade is sharp and " +
        "would probably hurt anything.\n");

    set_hit(hit);
    set_pen(pen);

    set_wt(W_KNIFE); 
    set_dt(W_SLASH | W_IMPALE); 
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);

    set_hands(W_ANYH); 
}

