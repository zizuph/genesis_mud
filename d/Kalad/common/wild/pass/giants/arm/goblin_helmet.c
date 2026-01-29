/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/arm/
*   Copied for goblin raiders from:
*
*  /d/Kalad/common/farmland/camps/arm/goblin_helmet.c
*
*  This is a low-level helmet used by the goblins in
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
string *ArrAdj1 = ({ "rusty"});
string *ArrAdj2 = ({ "black"});
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2);


void
create_armour()
{
    set_name("helmet");
    set_adj( ({ Adj1, Adj2 }) );

    set_short( Adj1+ " "+ Adj2 +" helmet");
    set_long("A very poorly crafted " +Adj1 + " " + Adj2 + " helmet." 
      + " This piece of armour is worn on the head, but"
      + " it seems to offer very little protection.\n");
    set_default_armour(12, A_HEAD, ({ 3, -2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(12) + random(50));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(12, A_HEAD)
             + random(20));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
}