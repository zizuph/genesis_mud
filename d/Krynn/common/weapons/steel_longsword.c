/*
 * File name: steel_longsword.c
 * Ordinary steel longsword.
 *
 * 9.11.2003
 * Blizzard
 */
 
inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("longsword");
    set_adj("thin");
    add_adj("steel");
    add_name("sword");
    set_short("thin steel longsword");
    set_long("This is a three-foot length of sharpened cold steel, bladed " +
        "along one edge. Its blade is thin and designed for thrusting, but " +
        "it is so sharp that even the slightest touch with the edge could " +
        "sever a fnger.\n");
        

    set_hit(34);
    set_pen(32);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(34, 33));
}

