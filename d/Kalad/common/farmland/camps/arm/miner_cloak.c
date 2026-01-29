/*
 *  /d/Kalad/common/farmland/camps/arm/miner_cloak.c
 *
 *  This is a low-level cloak used by a miner in Kalad
 *
 *  Copyright (c) Februari 2016, by Andreas Bergstrom (Zignur)
 */
#pragma strict_types;
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

/* Global Variables */
string *ArrAdj1 = ({ "torn"});
string *ArrAdj2 = ({ "bloodstained"});
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2);


void
create_armour()
{
    set_name("cloak");
    set_adj( ({ Adj1, Adj2 }) );

    set_short( Adj1+ " "+ Adj2 +" cloak");
    set_long("A very poorly crafted " +Adj1 + " " + Adj2 + " cloak." 
      + " This piece of armour is worn over the shoulders, but"
      + " it seems to offer very little protection.\n");
    set_default_armour(5, A_ROBE, ({ 3, -2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(12) + random(50));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(12, A_BODY)
             + random(20));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
}