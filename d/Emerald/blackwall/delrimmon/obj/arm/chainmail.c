/*
 *  /d/Emerald/blackwall/delrimmon/obj/arm/chainmail.c
 *
 *  This chainmail is worn by the orcs in the Army of Darkness. Not all
 *  soldiers are fortunate enough to receive this sort of gear.
 *
 *  Copyright (c) October 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types;
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

void
create_armour() 
{
    set_name("coat");
    add_name("chainmail");
    set_adj(({"blackened", "plated", "iron"}));
    set_short("coat of blackened chainmail");
    set_pshort("coats of blackened chainmail");
    set_long(BSN(
        "Many iron rings make up the mesh of this chainmail, which"
      + " seems to have been blackened by some evil process. A breast"
      + "plate adorns the midsection of the armour, upon which has"
      + " been painted a large grey skull."));
    set_default_armour(26,A_BODY,({-1,2,-1}),0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(26)+random(200)-100);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(26,A_BODY)+random(400)-200);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
