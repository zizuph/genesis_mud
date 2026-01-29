inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>
#include "/d/Ansalon/common/defs.h"

#define A_BITE  0
#define A_TAIL 1

#define H_BODY 0

create_creature() {

    if (!IS_CLONE)
	return;
    set_name("wyvern");
    set_race_name("wyvern");
    set_short("greater wyvern");
    add_adj("greater");
    set_long("This nasty looking beast resembles a winged " + 
      "serpent, with a scorpionlike poisoned stinger at the end " +
      "of its long tail. It looks at you menacingly with its " +
      "beady red eyes.\n");

    set_gender(G_NEUTER);
    set_stats(({ 130,119,130,45,45,87 }));
    /* str, dex, con, int, wis, dis */

    set_skill(SS_DEFENCE, 80);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 700000);
    add_prop(OBJ_I_VOLUME, 450000);
    add_prop(OBJ_I_NO_INS, 1);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE, 40, 25, W_SLASH, 80, "bite");
    set_attack_unarmed(A_TAIL, 25, 40, W_IMPALE, 20, "poisonous stinger");

    /* Hit_loc,   *Ac (impale/slash/bludgeon),   %hit,   hit_desc */
    set_hitloc_unarmed(H_BODY, ({ 30, 40, 30 }), 100, "body");

    set_act_time(10);
    add_act("emote hisses at you menacingly.");
    add_act("emote gazes at you with its red eyes, " +
      "its scorpionlike tail curling, ready to strike.");
    add_act("emote beats the air with its wings in agitation.");

    add_leftover("/std/leftover","stinger",1,"",0,0);
    add_leftover("/std/leftover","wing",2,"",0,0);
}

/*
 * Function name: cr_did_hit
 * Description:   This function is called from the combat object to give
 *                appropriate messages.  We shall remain content to let 
 *                the default messages be sent, but we will give poison 
 *                to the hit creature.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                       If this is negative, it indicates fail
 */

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;

    /* I believe the spider poisons the player each bite. it should of course
     * be harder to poison the player again and again, Nick */

    if(aid==A_TAIL) {
	say("The wyvern strikes " + QTNAME(enemy) + " with its " + 
	  "poisonous stinger.\n");
	tell_object(enemy, "The wyvern strikes you with its " +
	  "poisonous stinger with amazing swiftness.\n");

	if(!P("wyvern_talisman",enemy))
	{
	    poison = clone_object("/std/poison_effect");
	    if(poison) {
		poison->move(enemy);
		poison->set_time(600);
		poison->set_short("wyvern poison");
		poison->set_interval(20);
		poison->set_strength(40);
		poison->set_damage(({POISON_HP, 175}));
		poison->start_poison();

	    }
	}
	else
	    tell_object(enemy, "The feathered talisman grows warm! "+
	      "You are unaffected by the wyverns poison.\n");
    }

    return 0;
}
