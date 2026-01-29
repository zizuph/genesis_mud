inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"

#define A_BITE  0
#define A_LEG 1

#define H_THORAX 0
#define H_ABDOMEN 2 

create_creature() {

    if (!IS_CLONE)
	return;
    set_name("spider");
    set_race_name("spider");
    set_short("giant spider");
    add_adj("spider");
    set_long("This creature of nightmares is a giant spider! Standing " +
       "twice the height of a man on eight clawed legs, it stares " +
       "upon you hungrily with its unblinking soulless eyes that " +
       "are arrayed across its plated thorax that protects a bulbous " +
       "black abdomen.\n");
    set_aggressive(1, 100);

    set_gender(G_NEUTER);
    set_stats(({ 120,149,150,85,85,85 }));
    /* str, dex, con, int, wis, dis */

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_UNARM_COMBAT, 80);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_VOLUME, 250000);
    add_prop(OBJ_I_NO_INS, 1);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE, 40, 45, W_SLASH, 60, "poisonous fangs");
    set_attack_unarmed(A_LEG, 40, 20, W_IMPALE, 40, "clawed legs");

    /* Hit_loc,   *Ac (impale/slash/bludgeon),   %hit,   hit_desc */
    set_hitloc_unarmed(H_THORAX, ({ 50, 45, 60 }), 80, "plated thorax");
    set_hitloc_unarmed(H_ABDOMEN, ({ 20, 20, 20 }), 20, "bulbous abdomen");

    set_act_time(10);
    add_act("emote chitters hungrily.");
    add_act("emote gazes at you with its soulless black eyes.");
    add_act("emote skitters along a thick web, positioning itself.");

    set_cact_time(10);
    add_act("emote chitters hungrily.");
    add_act("emote gazes at you with its soulless black eyes.");
    add_act("emote skitters along a thick web, positioning itself.");

    add_leftover("/std/leftover","leg",8,"",0,0,10);
    add_leftover("/std/leftover","eye",8,"",0,0);
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

    // One in six chance the bite poisons

    if(aid==A_BITE && (random(8) == 0)) 
    {
	tell_room(E(TO), QCTNAME(enemy) + " is poisoned by the giant " +
             "spider!\n", enemy, TO);
	tell_object(enemy, "You are bitten by the giant spider!\n");

	poison = clone_object("/std/poison_effect");
	if(poison) 
        {
		poison->move(enemy);
		poison->set_time(300);
		poison->set_short("spider poison");
		poison->set_interval(10);
		poison->set_strength(10);
		poison->set_damage(({POISON_HP, 100}));
		poison->start_poison();
	}
    }

    return 0;
}

// loot corpse spawns on death.

public void
do_die(object killer)
{
    if (query_hp() > 0)
        return;

    object corpse;

    tell_room(E(TO), "As the giant spider collapses into wild death " +
         "throws, it dislodges a cocoon from its webs.\n", ({ }) ); 

    corpse = clone_object(TOBJ + "cocoon_corpse");
    corpse->move(E(TO), 1);   

    ::do_die(killer);
}
