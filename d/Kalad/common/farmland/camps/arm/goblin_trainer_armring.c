/*
 *  /d/Kalad/common/farmland/camps/arm/goblin_armring.c
 *
 *  This is a armring worn by the goblins in the red
 *  fang camp in Kalad, a token of their status as trainees
 *  of the Red Fang. Also a item used for a quest
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
string *ArrAdj1 = ({ "massive" });
string *ArrAdj2 = ({ "gold"});
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 


void
create_armour()
{
    set_name("armring");
    set_adj( ({ Adj1, Adj2 }) );

    set_short( Adj1+ " "+ Adj2 +" armring");
    set_long("A well crafted " +Adj1 + " " + Adj2 + " arm ring." 
      + " This item indicates that the former owner held the rank of"
      + " trainer within the Red Fang clans, its worn on the wrist.\n");
    set_default_armour(12, A_ANY_WRIST, ({ 3, -2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(12) + random(50));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(12, A_ANY_WRIST) 
            + random(20));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
}