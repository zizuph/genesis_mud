/*
 *  /d/Ravenloft/droptables/fos_drops/e_fos_2hspear.c
 *
 *  Epic weapon from the Forest of Shadows.
 *
 *  The weapon gives haste to the wielder.
 *
 *
 *
 *  Nerull 2015
 *
 */


#pragma strict_types

#include "/d/Ravenloft/defs/magicalitems_stats.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/weapon";
inherit "/lib/keep";

/* 
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */ 
public void
create_weapon()
{
    set_name("_e_fos_2hspear");
    add_name( ({"spear"}) );

    set_adj("scrimshaw");
    add_adj("tipped");
	add_adj("long");

    set_short("long scrimshaw tipped spear"); 
    set_pshort("long scrimshaw tipped spears");

    set_long("Made light by the walnut shaft, this spear is easily "
    +"seven feet in length and quite sturdy. The scrimshaw head shows a "
    +"scene of a shaman slaying a large whale underwater. There are "
    +"three red coloured leather tassles which hang from the base of "
    +"the head. Each tassle entwines several decent - sized bone "
    +"splinters.\n");

    add_item(({ "shaft",}), "The shaft of this scrimshaw is made from "
    +"solid walnut. It is rather sturdy.\n");

    add_item(({ "scene", "head", "scrimshaw head", "head scene"}), "The "
    +"head of the scrimshaw is engraved with an intricate scene of a shaman "
    +"underwater slaying a large white whale.\n");
    
    add_item(({"tassles", "red tassles", "red coloured leather tassles",
    "leater tassles", "red leather tassles"}), "Three red leather tassles "
    +"hand from the base of the scrimshaw's head. Entwined in each of the "
    +"tassles are large pieces of bone.\n");
    
    add_item(({"bone","bone splinters", "splinters",}), "Entwined in each "
    +"of the three red tassles are large pieces of bone. They glisten "
    +"white and have been polished to shimmer. They appear to be bones "
    +"from a large beast, perhaps a whale.\n");

    set_default_weapon(FOS_E_2HSPEAR_HIT, FOS_E_2HSPEAR_PEN,
    W_POLEARM, W_SLASH | W_IMPALE, W_BOTH, this_object());

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(MAGIC_AM_MAGIC,({ 60, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({ "This weapon has been enhanced by "
        + "magic.\n",1,
        "The enhancement makes the weapon deadlier than "
        + "normal weapons.\n",20,
        "The weapon will magically enhance the speed of "
        + "the wielder.\n", 30 }));

    add_prop(OBJ_S_WIZINFO, "This is en epic weapon dropping from the "
        + "monsters in Forest of Shadows, Ravenloft. It "
        + "adds " + FOS_E_2HSPEAR_HASTE_BONUS + " to _live_i_quickness at "
        + "the wielder.\n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(FOS_E_2HSPEAR_PEN, W_POLEARM));
    add_prop(OBJ_I_VOLUME, FOS_E_2HSPEAR_VOLUME);
    add_prop(OBJ_I_VALUE, FOS_E_2HSPEAR_VALUE);

    // Make it keepable by default.
    set_keep();
}


/*
* Function:    wield_mes()
* Description: The message and any extra functions/mechanics to
*              the weapon when it's wielded.
*/
void
wield_mes()
{
    if (environment(this_object()) != wielder)
        return;

    wielder->catch_msg("The world around you seems to go pass much slower "
        + "when you wield the " + short() + ".\n");
}



/*
* Function:    unwield_mes()
* Description: The message and any extra functions/mechanics to
*              the weapon when it's unwielded.
*/
void
unwield_mes()
{
    if (!objectp(wielder))
        return;

    wielder->catch_msg("The world around you seems to return to normal "
        + "speed when you unwield the " + short() + ".\n");
}



/*
* Function name:        wield
* Description  :        we only allow players with sufficient
*                       sword skill to wield this weapon
* Arguments    :        object wep - this object
* Returns      :        -1 : cannot wield
*                        0 : okay to wield
*/
mixed
wield(object what)
{
    wielder = this_player();

    if (this_player()->query_skill(SS_WEP_POLEARM) < 50)
    {
        write("The " + short() + " refuses you as its wielder!\n");
        return -1;
    }

    this_player()->add_prop(LIVE_I_QUICKNESS,
    this_player()->query_prop(LIVE_I_QUICKNESS)
    + FOS_E_2HSPEAR_HASTE_BONUS);

    set_alarm(0.1, 0.0, "wield_mes");
    return 0;
}



/*
* Function name: unwield
* Description  : This function might be called when someone tries to unwield
*                this weapon. To have this function called, use the function
*                set_wf().
* Arguments    : object obj - the weapon to stop wielding.
* Returns      : int  0 - the weapon can be unwielded normally.
*                     1 - unwield the weapon, but print no messages.
*                    -1 - do not unwield the weapon, print default messages.
*                string - do not unwield the weapon, use this fail message.
*/
mixed
unwield(object what)
{
    wielder = this_player();

    this_player()->add_prop(LIVE_I_QUICKNESS,
    this_player()->query_prop(LIVE_I_QUICKNESS)
    - FOS_E_2HSPEAR_HASTE_BONUS);

    set_alarm(0.1, 0.0, "unwield_mes");
    return 0;
}