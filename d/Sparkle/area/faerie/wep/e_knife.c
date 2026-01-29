/*
 * Common dagger for elf npcs
 * by Finwe, August 2004
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int hit = 12,
    pen = 12;

void
create_weapon()
{

    set_name("knife");
    set_adj("small");
    set_adj("silver");
    set_short("small silver knife"); 
    set_long("This is a " + short() + ". It has a short blade which " +
        "is sharp on one side. It was forged by the elves and is a " +
        "deadly weapon in the proper hands.\n");

    set_hit(hit);
    set_pen(pen);

    set_wt(W_KNIFE); 
    set_dt(W_SLASH | W_IMPALE); 
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);

    set_hands(W_ANYH); 
}

