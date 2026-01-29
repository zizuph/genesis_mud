/*
 *  /d/Kalad/common/farmland/camps/wep/goblin_spear.c
 *
 *  This is a one handed spear used by the goblins in the Red Fang
 *  camp in Kalad
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
string *ArrAdj1 = ({ "hefty","short","heavy","primitive","crude" });
string *ArrAdj2 = ({ "rusty","dented","cruel","wicked","bloody" });
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 

public void
create_weapon()
{ 
    set_name("spear");
    add_adj( ({ Adj1, Adj2 }) );
    set_short( Adj1+ " "+ Adj2 +" spear");
    set_long("This " +Adj1 + " " + Adj2 + " spear looks very poorly"
      + " crafted. A crude iron pole with a sharp end, some kind of"
      + " dried animal hide is wrapped the middle of the of the"
      + " spear. To provide some better grip to the once wielding"
      + " it. It is not a beautiful weapon but it looks like it"
      + " could inflict some damage.\n");

    set_default_weapon(GOBLIN_WEP_STAT,
                       GOBLIN_WEP_STAT,
                       W_POLEARM,
                       W_BLUDGEON | W_IMPALE,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(GOBLIN_WEP_STAT,
                                                   W_POLEARM) + random(30));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(GOBLIN_WEP_STAT,
                                         GOBLIN_WEP_STAT) + random(45));
} /* create_weapon */
