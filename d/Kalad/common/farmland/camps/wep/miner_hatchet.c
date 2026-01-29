/*
 *  /d/Kalad/common/farmland/camps/wep/miner_hatchet.c
 *
 *  This is a hatchet used by the miner in Kalad
 *
 *  Copyright (c) Februari 2016, by Andreas Bergstrom (Zignur)
 */
#pragma strict_types
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

/* Global Variables */
string *ArrAdj1 = ({ "short"});
string *ArrAdj2 = ({ "bloody"});
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 

public void
create_weapon()
{ 
    set_name("hatchet");
    add_adj( ({ Adj1, Adj2 }) );
    set_short( Adj1+ " "+ Adj2 +" hatchet");
    set_long("This " +Adj1 + " " + Adj2 + " hatchet looks very poorly"
      + " crafted. A crude iron head is attached to a carved"
      + " wood handle. Some kind of dried animal hide is wrapped"
      + " around the handle. It is probably not worth much as a"
      + " weapon, but you can probably mine with it.\n");

    set_default_weapon(GOBLIN_WEP_STAT,
                       GOBLIN_WEP_STAT,
                       W_AXE,
                       W_BLUDGEON | W_SLASH,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(GOBLIN_WEP_STAT,
                                                   W_AXE) + random(30));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(GOBLIN_WEP_STAT,
                                         GOBLIN_WEP_STAT) + random(45));
} /* create_weapon */
