/*
 *  /d/Kalad/common/farmland/camps/wep/goblin_dagger.c
 *
 *  This is a dagger used by the goblins in Red Fang camp
 *  in Kalad
 *
 *  Copyright (c) October 2015, by Andreas Bergstrom (Zignur)
 */
#pragma strict_types
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

/* Global Variables */
string *ArrAdj1 = ({ "long","short","jagged","curved","crude" });
string *ArrAdj2 = ({ "rusty","dented","cruel","wicked","bloody" });
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 

public void
create_weapon()
{ 
    set_name("dagger");
    add_adj( ({ Adj1, Adj2 }) );
    set_short( Adj1+ " "+ Adj2 +" dagger");
    set_long("This " +Adj1 + " " + Adj2 + " knife looks very poorly"
      + " crafted. A crude iron blade is attached to a carved"
      + " wood handle. Some kind of animal hide is wrapped around"
      + " the handle. It is not a beautiful weapon but it looks"
      + " sharp enough to inflict some damage.\n");

    set_default_weapon(GOBLIN_WEP_STAT,
                       GOBLIN_WEP_STAT,
                       W_KNIFE,
                       W_SLASH | W_IMPALE,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(GOBLIN_WEP_STAT,
                                                   W_KNIFE) + random(10));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(GOBLIN_WEP_STAT,
                                         GOBLIN_WEP_STAT) + random(45));
} /* create_weapon */
