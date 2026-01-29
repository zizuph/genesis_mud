/*
 *  /w/zignur/KaladProject/wep/goblin_mace.c
 *
 *  This is a mace used by the goblins in red fang camp
 *  in Kalad
 *
 *  Copyright (c) Mars 2015, by Andreas Bergstrom (Zignur)
 */
#pragma strict_types
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

/* Global Variables */
string *ArrAdj1 = ({ "long","short","heavy","primitive","crude" });
string *ArrAdj2 = ({ "rusty","spiked","cruel","wicked","bloody" });
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 

public void
create_weapon()
{ 
    set_name("mace");
    add_name("club");
    add_adj( ({ Adj1, Adj2 }) );
    set_short( Adj1+ " "+ Adj2 +" mace");
    set_long("This " +Adj1 + " " + Adj2 + " mace looks very poorly"
      + " crafted. A crude iron pole is attached to a carved"
      + " wood handle. Some kind of dried animal hide is wrapped"
      + " around the handle. It is not a beautiful weapon but it"
      + " looks like it could inflict some damage.\n");

    set_default_weapon(GOBLIN_WEP_STAT,
                       GOBLIN_WEP_STAT,
                       W_CLUB,
                       W_BLUDGEON,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(GOBLIN_WEP_STAT,
                                                   W_CLUB) + random(30));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(GOBLIN_WEP_STAT,
                                         GOBLIN_WEP_STAT) + random(45));
} /* create_weapon */
