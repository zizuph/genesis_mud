/*
 *  /d/Emerald/blackwall/delrimmon/obj/arm/black_skull.c
 *
 *  This helm has been enchanted by the Darklings, and is worn by
 *  the orc captain they have sent into Del Rimmon to investigate
 *  the ancient outposts of the elves.
 *
 *  Copyright (c) October 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

/* prototypes */
public void        create_armour();


/*
 * Function name:        create_armour
 * Description  :        set up the armour
 */
public void
create_armour()
{
    set_name( ({ "helm", "helmet", "skull" }) );
    set_short( "great black skull");
    set_adj( ({ "great", "black", }) );

    set_long("There is a dark and evil look about this helmet. At first"
      + " glance, it actually appears to be a great black skull. However,"
      + " the jawbone is missing, and has been replaced by a dark leather"
      + " strap used to fix the skull securely on the wearer's head. The"
      + " mottled and boiling texture of the surface suggests that this"
      + " skull was dipped into a black fluid of some kind, which has since"
      + " hardened, and perhaps through dark magic cooled harder than steel."
      + " The skull itself looks like it once belonged to a large ogre.\n");

    set_default_armour(50, A_HEAD, ({ 0, 0, 0, 0}), this_object());
    add_prop(OBJ_I_WEIGHT, 3300);
    add_prop(OBJ_I_VOLUME,  900);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(50) + random(500) + 500);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(MAGIC_AM_MAGIC,( ({60, "abjuration"}) )); 
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_AM_ID_INFO, ({
        "This helmet has been coated with an enchanted solution, which"
      + " has strengthened its surface, giving it much greater resistance"
      + " to damage against violence!\n", 25 }) );

    add_prop(OBJ_S_WIZINFO, "The helm of the orc captain "
      + " (/d/Emerald/blackwall/delrimmon/npc/captain). "
      + "It is enchanted to have higher armour class.\n");
} /* create_armour */

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
