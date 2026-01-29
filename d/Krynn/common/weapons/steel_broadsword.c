/*
 * File name: steel_broadsword.c
 * Ordinary steel broadsword, used by city guards in Palanthas.
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
    set_name("broadsword");
    set_adj("shiny");
    add_adj("steel");
    add_name("sword");
    set_short("shiny steel broadsword");
    set_long("This is an extremely well crafted blade of a strong, " +
        "brilliantly shining metal. Its apparent age has not affected " +
        "its condition and it still holds a sharp edge.\n");
        

    set_hit(31);
    set_pen(34);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(31, 34));
}

