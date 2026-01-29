/*
 * Belt worn by all the minotaur citizens.
 * 
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
    
    set_name("belt");
    arr = ({"wide", "thick", "thin", "narrow", "old",
            "iron-sudded", "steel-studded"});
    n = random(sizeof(arr));
    if (strlen(arr[n])) set_adj(arr[n]);
    set_adj("leather");
    set_short(arr[n]+ " leather belt");
    set_ac(5);
    set_at(A_WAIST);
    set_long("A belt made from leather with a large steel buckle. "+
      "It is unusually " +arr[n]+ ", covering the entire waist.\n");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(5, A_WAIST));
}