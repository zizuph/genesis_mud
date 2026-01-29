/*
 *  /d/Emerald/blackwall/delrimmon/obj/arm/bone_shield.c
 * 
 *  This shield is worn by the orc captain in the caves at
 *  Del Rimmon.
 *
 *  Copyright (c) September 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"


/*
 * Function name:        create_armour
 * Description  :        set up the armour
 */
public void
create_armour()
{
    set_name("shield");
    add_adj( ({ "massive", "bone-spiked", "bone", "spiked" }) );
    set_short("massive bone-spiked shield");
    set_long("Great spines stick out from the corners of"
        + " this massive shield which is comprised entirely of"
        + " bones which have been bound together in a tight"
        + " formation. The bones glisten, for they have been"
        + " dipped in some vile liquid which has since hardened"
        + " and added an unnatural strength to the already strong"
        + " material.\n");

    set_default_armour(45, A_SHIELD, ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(50, A_SHIELD));  
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45)+random(700)-50);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(MAGIC_AM_MAGIC,( ({20, "abjuration"}) )); 
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_AM_ID_INFO, ({
        "This shield has been coated with an enchanted solution, which"
      + " has strengthened its surface, giving it much greater resistance"
      + " to damage against violence!\n", 25 }) );

    add_prop(OBJ_S_WIZINFO, "The shield of the orc captain "
      + " (/d/Emerald/blackwall/delrimmon/npc/captain). "
      + "It is enchanted to have higher armour class.\n");
} /* create_armour */

int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
}

public string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + query_keep_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
    init_keep_recover(arg);
}
