/*  /d/Ravenloft/droptables/fos_drops/e_fos_sight_ring.c
 *
 *  Epic ring. Drops from monsters in the
 *  Forest of Shadows.
 *
 *  Allows the wearer to see in darkness and see
 *  invisible creatures.
 *
 *  Nerull, 2015
 *
 */

inherit "/std/armour";
inherit "/lib/keep";
#include "../defs.h";
#include "/d/Ravenloft/defs/magicalitems_stats.h"
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <const.h>
#include <wa_types.h>

object wearer;

void
create_armour()
{
	set_name("ring");

	set_adj("thin");
	add_adj("gold");

	set_short("thin gold ring");
	set_pshort("thin gold rings");

	set_long("This is a very narrow band of plain "
	+"gold. It has no markings on it beside signs "
	+"of regular wear.\n");

	set_at(A_ANY_FINGER);

	set_ac(FOS_E_FOS_SIGHT_RING_AC);

	set_af(this_object());

	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

	add_prop(MAGIC_AM_MAGIC, ({ 60,"enchantment" }));

	add_prop(MAGIC_AM_ID_INFO, ({ "This item enhances the wearer "
	+"to see in darkness, and to see invisible creatures.\n",20 }));

	add_prop(OBJ_S_WIZINFO, "This item adds "
	+ FOS_E_FOS_SIGHT_RING_BONUS
	+" points of live_i_see_dark and live_i_see_invis.\n");

	add_prop(OBJ_I_WEIGHT, FOS_E_FOS_SIGHT_RING_WEIGHT);
	add_prop(OBJ_I_VOLUME, FOS_E_FOS_SIGHT_RING_VOLUME);
	add_prop(OBJ_I_VALUE, FOS_E_FOS_SIGHT_RING_VALUE);
}



/*
* Function name: wear_message()
* Description  : Tells the wearer and the environment about the changes.
*/
void
wear_message()
{
	if (environment(this_object()) != wearer)
	return;

	wearer->catch_msg("Your vision blurs for a moment, and you "
	+"suddenly see the world in a different light.\n");

	tell_room(environment(wearer), QCTNAME(wearer) 
	+"'s eyes glows for a short moment.\n", wearer);
}


mixed
wear(object what)
{
	this_player()->add_prop(LIVE_I_SEE_DARK, 
	this_player()->query_prop(LIVE_I_SEE_DARK) 
	+ FOS_E_FOS_SIGHT_RING_BONUS);

	this_player()->add_prop(LIVE_I_SEE_INVIS,
	this_player()->query_prop(LIVE_I_SEE_INVIS)
	+ FOS_E_FOS_SIGHT_RING_BONUS);

	wearer = this_player();

	set_alarm(0.1, 0.0, "wear_message");

	return 0;
	
}


mixed
remove(object what)
{
	if (wearer)
	{
		wearer->add_prop(LIVE_I_SEE_DARK,
		wearer->query_prop(LIVE_I_SEE_DARK)
		- FOS_E_FOS_SIGHT_RING_BONUS);

		wearer->add_prop(LIVE_I_SEE_INVIS,
		wearer->query_prop(LIVE_I_SEE_INVIS)
		- FOS_E_FOS_SIGHT_RING_BONUS);

		wearer->catch_msg("Your vision returns to normal.\n");

		tell_room(environment(wearer), QCTNAME(wearer)
		+ "'s eyes radiates a dull glow for a short moment.\n", wearer);

		wearer = 0;
		return 0;
	}
	   
	wearer = 0;
	return 0;
}


void
leave_env(object ob, object from)
{
	if (wearer)
		remove(this_object());

	::leave_env(ob, from);
}