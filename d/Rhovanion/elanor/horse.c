/*
 * This is the horse proper.  It will be loaded by a stable upon
 * entrance of a player owning a horse.  The horse will age, and
 * also, upon reaching old age, die.
 */

inherit "/d/Rhovanion/elanor/steed";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/std/combat/combat.h"
#include "steed.h"

int underfed;

void
create_steed()
{
    set_name( ({ "battlehorse", "horse", "steed" }) );
    set_race_name("horse");
    set_adj("unconfigured");

    my_long = "This is a rather big battle-horse. It looks like it might "+
	      "hold you.";

    add_prop(CONT_I_MAX_WEIGHT, 600000 + random(160000));
    add_prop(CONT_I_MAX_VOLUME, 600000 + random(160000));
    add_prop(CONT_I_WEIGHT, query_prop(CONT_I_MAX_WEIGHT) * 2 / 3);
    add_prop(CONT_I_VOLUME, query_prop(CONT_I_MAX_VOLUME) * 2 / 3);
}

void
check_age()
{
    object poison;
    int stuffed, max;

    ::check_age();
    /*
     * Increase stats if properly fed, leave as is if too much or too
     * little food, reduce stats if underfed.  If underfed for too
     * long, add poison.
     */
    stuffed = query_stuffed();
    max = query_prop(LIVE_I_MAX_EAT);
    if (stuffed < (max / 10)) {
	underfed++;
	tell_room(environment(), QCTNAME(this_object()) + " sags a bit, but "+
		  "regains " + query_possessive() + " footing.\n",
		  this_object());
	tell_room(this_object(), QCTNAME(this_object()) + " sags a bit, but "+
		  "regains " + query_possessive() + " footing.\n",
		  this_object());
	/*
	 * Reduce stats
	 */
	if (underfed >= 3 && !present(POISON_ID)) {
	    poison = clone_object(POISON_PATH);
	    poison->move(this_object(), 1);
	    poison->start_poison();
	}
    }
    else {
	underfed = 0;
	if (stuffed > (max * (6 + random(3)) / 10)) {
	    poison = present(POISON_ID);
	    if (poison)
		poison->remove_object();
	    return;
	}
	/*
	 * Increase stats
	 */
    }
}

/*
 * Everything that states it is horse food can be eaten
 */
int
query_is_food(object ob)
{
    return ob->query_is_horse_food();
}

/*
 * Function name: hit_steed
 * Description:   Called to check if the steed or its rider should
 *                take the damage of a hit
 * Arguments:     attacker - the object hurting us
 *                att_id   - the attack identifier
 * Returns:       1 to hit the steed, 0 to hit the rider
 */
int
hit_steed(object attacker, int att_id)
{
    object cobj, weapon;
    mixed *attack;

    cobj = attacker->query_combat_object();
    attack = cobj->query_attack(att_id);
    weapon = cobj->cb_query_weapon(att_id);

    /*
     * Determine who gets the hit based on attack type and weapon
     */
    if (attack[ATT_DAMT] == MAGIC_DT)	/* Magic -> 33/66 horse/rider */
	return random(3) == 0;

    if (!weapon)			/* Unarmed -> 75/25 horse/rider */
	return random(4) > 0;

    switch (weapon->query_wt()) {
	case W_KNIFE:			/* 75/25 horse/rider */
	    return random(4) > 0;
	case W_MISSILE:			/* 50/50 horse/rider */
	case W_SWORD:
	case W_AXE:
	case W_CLUB:
	    return random(2);
	case W_POLEARM:			/* 25/75 horse/rider */
	case W_JAVELIN:
	    return random(4) == 0;
	default:			/* This should never happen! */
	    return random(2);
    }
}
