/* /d/Faerun/kryptg/wep/undull_black_dagger.c
 *
 * This is the reward for releasing the spirit from
 * the possessed_black_dagger.
 *
 * It's a 35/38 weapon, nondull, and with 50 haste.
 * It can only be wielded in right hand.
 *
 * Nerull 2020
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;
inherit "/lib/keep";

#define HASTE_VALUE             50


void
create_faerun_weapon()
{
    seteuid(getuid());

   set_name("dagger");
    add_pname(({"daggers"}));
    
    set_adj("long");
    set_adj("black");
    
    set_short("long black dagger");
    set_pshort("long black daggers");
   
    set_long("The blade of this dagger is about five fingers wide "
        +"and 28 inches long with a somewhat rounded and strengthened "
        +"point making the blade able to punch through the thickest "
        +"armours as well as cutting. On closer inspection there is a "
        +"multicoloured aura of white, red and dark purple running the "
        +"length of the blade that makes it seem almost alive. The hilt "
        +"and blade is made out of a dull black metal known as adamantine, "
        +"rumored to be the hardest metal in existence. The crossguard "
        +"is V shaped and points up to the sides slightly past the base "
        +"of the blade and the hilt itself seems to be made from a "
        +"purple dragon scale.\n");

    set_default_weapon(35, 38, 
    W_KNIFE, W_SLASH | W_IMPALE, W_RIGHT, this_object());
    
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    
    add_prop(MAGIC_AM_MAGIC,({ 60, "enchantment" }));
    
    add_prop(MAGIC_AM_ID_INFO, ({ "This blade has been enhanced by "
        + "powerful magic.\n",1,
        "The enhancement will hasten the wielder, and it will "
        +"not dull by ordinary means.\n", 50 }));
        
    add_prop(OBJ_S_WIZINFO, "This is the reward for releasing the "
        +"spirit from the possessed_black_dagger. It's a 35/38 weapon, "
        +"nondull, and with 50 haste. It can only be wielded in right "
        +"hand. Drops from monster /d/Faerun/kryptg/npcs/mutated_human.c "
        +"which starts in /d/Faerun/underdark/dark_dom/rooms/tu62.\n");
        
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(38, W_KNIFE));
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 15000);
    
    // Make it keepable by default.
    set_keep();
}


int set_dull(int du)
{
    return 0;
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
    
    wielder->catch_msg("You feel quicker when "
        +"you wield the " + short() + ".\n");
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
    
    wielder->catch_msg("You feel slower when "
        +"you unwield the " + short() + ".\n");
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
    
    if (this_player()->query_skill(SS_WEP_KNIFE) < 80)
    {
        write("The " + short() + " refuses you as its wielder!\n");
        return -1;
    }
    
    this_player()->add_prop(LIVE_I_QUICKNESS, 
    this_player()->query_prop(LIVE_I_QUICKNESS) 
    + HASTE_VALUE);
    
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
    - HASTE_VALUE);
    
    set_alarm(0.1, 0.0, "unwield_mes");
    
    return 0;
}