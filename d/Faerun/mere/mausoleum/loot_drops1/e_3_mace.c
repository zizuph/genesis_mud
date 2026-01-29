/*
 *  /d/Ravenloft/droptables/fos_drops/e_fos_mace.c
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
    set_name("_e_fos_mace");
    add_name( ({"club", "mace"}) );

    set_adj("ivory");
    add_adj("spiked");

    set_short("ivory spiked mace"); 
    set_pshort("ivory spiked maces");

    set_long("This mace has been sculpted from a massive ivory "
    +"tusk. The handle has been carved with indentations for "
    +"fingers which then begin to gradually spiral up to the head. "
    +"The head is exactly that, a bull - head with two horns "
    +"positioned to allow for extreme piercing of the hardest "
    +"metals. Each horn has been capped in some unknown dull "
    +"grey substance.\n");

    add_item(({ "indentation", "indentations", "handle" }), "The handle "
    +"of this massive mace have been carved, intricately, to allow for "
    +"your fingers to grip it tightly. They seem almost unnatural in "
    +"the light as if they've shifted specifically to fit your hand.\n");

    add_item(({ "head", "bull", "bull-head", "bull head"}), "Eerily, this "
    +"head of a bull almost looks as if it is alive. The two massive "
    +"horns sitting on its head glisten in the light and it's eyes "
    +"stare, eternily, forward.\n");
    
    add_item(({ "horn", "horns", "substance", "unknown substance",
    "grey substance", "unknown grey substance"}), "The horns of the bull's "
    +"head are long and sharp. They appear to have been shifted upon the "
    +"head to maximize the piercing ability when striking a foe. They "
    +"are capped with a grey substance that is dull and odd. Straing at it "
    +"makes your eyes cross.\n");

    set_default_weapon(FOS_E_MACE_HIT, FOS_E_MACE_PEN, 
    W_CLUB, W_BLUDGEON | W_IMPALE, W_ANYH, this_object());

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
        + "adds " + FOS_E_MACE_HASTE_BONUS + " to _live_i_quickness at "
        + "the wielder.\n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(FOS_E_MACE_PEN, W_CLUB));
    add_prop(OBJ_I_VOLUME, FOS_E_MACE_VOLUME);
    add_prop(OBJ_I_VALUE, FOS_E_MACE_VALUE);

    set_hit(FOS_E_MACE_HIT);
    set_pen(FOS_E_MACE_PEN);

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

    if (this_player()->query_skill(SS_WEP_CLUB) < 50)
    {
        write("The " + short() + " refuses you as its wielder!\n");
        return -1;
    }

    this_player()->add_prop(LIVE_I_QUICKNESS,
    this_player()->query_prop(LIVE_I_QUICKNESS)
    + FOS_E_MACE_HASTE_BONUS);

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
    - FOS_E_MACE_HASTE_BONUS);

    set_alarm(0.1, 0.0, "unwield_mes");
    return 0;
}