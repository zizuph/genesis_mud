/*
 * File : elven_blade.c
 * Elven blade, Sarist's family sword. Part of quest.
 *
 * Blizzard, 03/03/2003
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

create_weapon()
{
    set_name("blade");
    add_name(({"_sarist_sword_", "sword", "longsword" })); 
    set_short("long elven blade");
    set_adj( ({"long", "elven", "slender" }) );
    set_long("This long and slender sword is an elegant weapon, clearly of " +
        "elven craft. The hilt and pommel glimmer with a silvery light. " + 
        "There are some decorations along the steel blade.\n");
   
    add_item(({"blade", "decoration", "decorations", "engravings"}),
        "Delicate and shallow engravings seem to dance along the blade. " +
        "The sword must belong to some noble person, because in hands of " +
        "a common warrior, they would be destroyed very fast. Someone " +
        "really cares about this weapon.\n");
 
    set_default_weapon(22, 20, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 1800);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,40) + random(500) );
}


