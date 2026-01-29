/*
 * Belt worn by all the minotaur citizens.
 */
#pragma strict_types

inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    mixed *arr;
    int n;

    set_name("harness");
    arr = ({"heavy", "thick", "light", "brown", "black",
            "fancy", "well-worn", "bright", "elegant",
            "red", "green", "gray", "blue", "white"});
    n = random(sizeof(arr));
    set_adj("leather");
    set_short(arr[n]+ " leather harness");
    if (strlen(arr[n])) set_adj(arr[n]);
    set_ac(10);
    set_at(A_BODY);
    set_am( ({ 0, 0, 0 }) );
    set_long("This is a leather harness, which has been "+
    "constructed from " +arr[n]+ " leather. The harness has "+
    "been made rather big, and it would fit perfectly "+
    "around the body of a muscular dwarf or goblin.\n"); 

    add_prop(OBJ_I_VOLUME, 5500);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_BODY));
}