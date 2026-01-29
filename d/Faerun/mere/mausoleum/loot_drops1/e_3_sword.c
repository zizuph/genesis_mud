/*
 *  /d/Ravenloft/droptables/fos_drops/e_fos_sword.c
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
    set_name("_e_fos_sword");
    add_name( ({"blade", "sword"}) );

    set_adj("rune-etched");
    add_adj("obsidian");

    set_short("rune-etched obsidian longsword"); 
    set_pshort("rune-etched obsidian longswords");

    set_long("This sword has crimson runes running down "
    +"it's blade, all the way to the crossguard. The crossguard "
    +"is made out of blue steel and looks relatively unadorned "
    +"except for a huge crimson jewel that serves as the swords "
    +"pommel.\n");

    add_item(({ "jewel" }), "The jewel "
    +"pulses with a faint crimson light. You notice the rythm of "
    +"the light is syncronized with the runes on the blade.\n");

    add_item(({ "runes"}), "The crimson runes pulse "
    +"with a faint light, but you cannot decipher the runes.\n");

    set_default_weapon(FOS_E_SWORD_HIT, FOS_E_SWORD_PEN, 
    W_SWORD, W_SLASH | W_IMPALE, W_ANYH, this_object());

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(MAGIC_AM_MAGIC,({ 60, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({ "This weapon has been enhanced by "
        + "magic.\n",1,
        "The enhancement makes the weapon deadlier than "
        + "normal weapons.\n",20,
        "The weapon will magically enhance the speed of "
        +"the wielder.\n", 30 }));

    add_prop(OBJ_S_WIZINFO, "This is en epic weapon dropping from the "
        + "monsters in Forest of Shadows, Ravenloft. It "
        + "adds " + FOS_E_SWORD_HASTE_BONUS + " to _live_i_quickness at "
        + "the wielder.\n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(FOS_E_SWORD_PEN, W_SWORD));
    add_prop(OBJ_I_VOLUME, FOS_E_SWORD_VOLUME);
    add_prop(OBJ_I_VALUE, FOS_E_SWORD_VALUE);

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

    if (this_player()->query_skill(SS_WEP_SWORD) < 50)
    {
        write("The " + short() + " refuses you as its wielder!\n");
        return -1;
    }

    this_player()->add_prop(LIVE_I_QUICKNESS,
    this_player()->query_prop(LIVE_I_QUICKNESS)
    + FOS_E_SWORD_HASTE_BONUS);

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
    - FOS_E_SWORD_HASTE_BONUS);

    set_alarm(0.1, 0.0, "unwield_mes");
    return 0;
}