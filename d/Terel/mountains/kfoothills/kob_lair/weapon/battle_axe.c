/*
 *  battle_axe.c
 *
 *  Britanica 160322
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>

inherit STDWEAPON;

#include <stdproperties.h>

/*
 * Function name: create_weapon
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_weapon()
{
    set_name("axe");
    set_short("battle axe");
    set_long("It's a battle axe.\n");
    set_adj("battle");
    set_hit(20);
    set_pen(20);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 700);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);
}
