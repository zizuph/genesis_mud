/*
 * File : elven_blade.c
 * Elven blade, sword given randomly to the player who had solved the quest 
 * in past (cloned instead of the magic one).
 * 
 * Blizzard, 13.06/2003
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

inherit "/lib/keep";

create_weapon()
{
    set_name("sword");
    add_name("longsword"); 
    set_short("old azure-bladed longsword");
    set_adj( ({ "azure-bladed", "old", "long", "slender" }) );
    set_long("This long and slender sword is an elegant weapon, clearly of " +
        "elven craft. Its hilt and pommel are made of silver, the blade of " +
        "finely forged, strange azure metal is perfectly balanced, what " +
        "could afford quick recovery in combat. In past it was probably " +
        "a great weapon, but now its value is rather sentimental.\n");
   
    set_default_weapon(34, 33, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);

    add_prop(OBJ_I_VOLUME, 1800);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,38) + 1000);
   
    set_keep(1);
}

