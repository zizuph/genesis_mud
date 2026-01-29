/*
 *  /d/Kalad/common/farmland/camps/arm/goblin_shield.c
 *
 *  This is a low-level shield used by the goblins in
 *  the Red Fang camp in Kalad
 *
 *  Copyright (c) October 2015, by Andreas Bergstrom (Zignur)
 *  2018-02-06 Zignur Changed the descs to a fixed desc on Gorboths request. 
 */
#pragma strict_types;
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

/* Global Variables */
string *ArrAdj1 = ({ "black"});
string *ArrAdj2 = ({ "cracked"});
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2);


void
create_armour()
{
    set_name("shield");
    set_adj( ({ Adj1, Adj2 }) );

    set_short( Adj1+ " "+ Adj2 +" shield");
    set_long("A very poorly crafted " +Adj1 + " " + Adj2 + " shield." 
      + " This piece of armour is worn on the arm, but"
      + " it seems to offer very little protection.\n");
    set_default_armour(12, A_SHIELD, ({ 3, -2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(12) + random(50));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(12, A_SHIELD)
             + random(20));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
}