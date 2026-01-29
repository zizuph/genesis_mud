/*
 *  Epic weapon from the Red Cliffs in Faerun.
 *
 *  The weapon gives haste to the wielder.

 *  Nerull 2018
 *
 */


#pragma strict_types

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>


#define EPIC_DROP_VALUE               10000
#define E_2HWEAPON_HIT                50
#define E_2HWEAPON_PEN                50
#define E_2HWEAPON_VALUE              EPIC_DROP_VALUE
#define E_2HWEAPON_VOLUME             1000
#define E_2HWEAPON_HASTE_BONUS        50

inherit "/std/weapon";
inherit "/lib/keep";

/* 
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */ 
public void
create_weapon()
{
    set_name("_e_2haxe");
    add_name( ({"axe", "waraxe", "war axe"}) );

    set_adj("moon-bladed");
	add_adj("spiked");

    set_short("moon-bladed spiked waraxe"); 
    set_pshort("moon-bladed spiked waraxes");

    set_long("The waraxe is fully crafted from some unknown glowing "
	+"metal. The hilt is pock - marked and looks unpleasant to hold. It "
	+"attaches to the center of the moon or blade of the axe. Unlike other "
	+"axes, the circle of the double blades actually completes and is "
	+"held via one of seven spikes in the center of its icon.\n");

    add_item(({ "pock-marks", "pocks", "marks" }), "Chipped and dimpled "
	+"from ages of use, the pocks appear to be almost living. They pulsate "
	+"with a dark energy and seem unpleasant to touch.\n");

    add_item(({ "spikes", "seven spikes", "spike"}), "Seven long spikes "
	+"complete the double bladed axe making it shaped more like a crescent "
	+"moon. The spikes surround the center icon which rests in the middle "
	+"of the blade.\n");
	
	add_item(({ "icon", "center icon", "centre icon"}), "Resting directly "
	+"in the centre of the blade is a small glimmering icon of a skull. It "
	+"seems to be grinning although there are no lips, the image is at "
	+"the same time frightening as well as comforting.\n");

    set_default_weapon(E_2HWEAPON_HIT, E_2HWEAPON_PEN,
	W_AXE, W_SLASH | W_IMPALE, W_BOTH, this_object());

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(MAGIC_AM_MAGIC,({ 60, "enchantment" }));

	add_prop(MAGIC_AM_ID_INFO, ({ "This weapon has been enhanced by "
		+ "magic.\n",1,
		"The enhancement makes the weapon deadlier than "
		+ "normal weapons.\n",20,
		"The weapon will magically enhance the speed of "
		+ "the wielder.\n", 30 }));

	add_prop(OBJ_S_WIZINFO, "This is en epic weapon dropping from the "
		+ "loot chest in the Red Cliffs, Faerun. It "
		+ "adds "+ E_2HWEAPON_HASTE_BONUS+" to _live_i_quickness at "
		+ "the wielder.\n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(E_2HWEAPON_PEN, W_AXE));
    add_prop(OBJ_I_VOLUME, E_2HWEAPON_VOLUME);
    add_prop(OBJ_I_VALUE, E_2HWEAPON_VALUE);

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
	+"speed when you unwield the " + short() + ".\n");
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

	if (this_player()->query_skill(SS_WEP_AXE) < 50)
	{
		write("The " + short() + " refuses you as its wielder!\n");
		return -1;
	}

	this_player()->add_prop(LIVE_I_QUICKNESS,
	this_player()->query_prop(LIVE_I_QUICKNESS)
	+ E_2HWEAPON_HASTE_BONUS);

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
	- E_2HWEAPON_HASTE_BONUS);

	set_alarm(0.1, 0.0, "unwield_mes");
	return 0;
}