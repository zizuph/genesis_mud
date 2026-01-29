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

int hit = 10 + random (5)+1,
    pen = 10 + random (5)+1;
void
create_weapon()
{

    set_name("axe");
    add_name("battleaxe");
    add_name("_ch_battleaxe_");
    set_adj("cruel");
    set_adj("bloody");
    set_short("cruel bloody battleaxe"); 
    set_long("This is a " + short() + ". It's evil looking and smeared " +
        "with blood. It looks like it was made by orcs and has seen lots " +
        "of battles. The battleaxe look like it could cleave anything in half.\n");
    

    set_hit(hit);
    set_pen(pen);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);

    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1150);

    set_hands(W_ANYH); 
}

