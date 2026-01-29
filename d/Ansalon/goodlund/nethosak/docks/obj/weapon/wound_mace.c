/*
 * /d/Ansalon/goodlund/nethosak/docks/obj/weapon/wound_mace.c
 *
 * glain
 *
 * This is a magical mace that is wielded by the minotaur captain of
 * the ship, Stormseeker.  The mace leaves behind crippling wounds on
 * the victims it hits.  After the battle they bleed to death if they
 * do not monitor their health values carefully or they are close to
 * death as is.  The mace has been handed down from father to son for
 * generations in the captains family.  They do not know that the
 * weapon actually dates back to pre-cataclysm times.
 *
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/local.h"

#define WOUNDS 1

object wound;

void
create_weapon()
{
    set_name("mace");
    set_adj("long");
    add_adj("spiked");
    set_long("Rows of sharp, barbed spikes adorn the head of this long " +
      "mace.  At the handle this mace is very narrow, but gradually " +
      "gets broader as it ends in its mass of deadly barbed spikes.  It " +
      "feels extremely light for a weapon of its size.\n");
    set_short("long spiked mace");
    set_default_weapon(40,38, W_CLUB, W_BLUDGEON | W_IMPALE, W_ANYH);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"These maces were a common weapon " +
	"among the High Priests of Istar before the Cataclysm.  " +
	"Forged from a long forgotten mixture of metals that give it " +
	"its durability and light weight, it was then enchanted to " +
	"leave ghastly wounds that could not be healed through normal means.  " +
	"Many of the High Priests enemies slowly bled to death " +
	"attempting to flee from the cruel oppressors.\n", 35}));

    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 2500);

    set_likely_dull(0);
    set_likely_break(0);

    seteuid(getuid());
}

public mixed 
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{

    if ((dam > 80) && (dt == W_IMPALE))
    {
	switch (random(WOUNDS))
	{
	default:
	    wielder->catch_msg("You feel a tug on the " + short() +
	      " as you rip flesh out of the " + hdesc + " of " +
	      QTNAME(enemy) + " with the barbed spikes on the head " +
	      "of the " + short() + ", leaving behind a nasty " +
	      "bleeding wound.\n");
	    enemy->catch_msg("Pain shoots through your " + hdesc +
	      " as your flesh is torn off from the barbed spikes on " +
	      "the head of the " + short() + ", leaving behind a " +
	      "nasty bleeding wound.\n");
	    wielder->tell_watcher(QCTNAME(wielder) + " rips the flesh " +
	      "out of the " + hdesc + " of " + QTNAME(enemy) + " with " +
	      "the babed spikes on the head of the " + short() +
	      ", leaving behind a nasty bleeding wound.\n", enemy);
	    break;
	}

	wound = clone_object(DOBJ + "bleed_obj");
	wound->move(enemy, 1);
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
