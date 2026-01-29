/*
 * /d/Gondor/common/npc/mosquito.c
 *
 * In the tower at Cirith Untol you may find mosquitos. They will sting
 * and that may be a bother to you.
 *
 * Since I'd hate to see people fight a mosquito and aim for the leg or
 * head, I've adjusted combat against them. Therefore, mosquitos do not
 * have hitlocation or attack locations, but the attacker will try to
 * splash it every round of combat.
 *
 * /Mercade, May 16 1994
 *
 * Revision history:
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <const.h>
#include <macros.h>
#include <math.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define ADJECTIVES   ({ "irritating", "buzzing", "blood-thirsty", \
			"blood-craven", "ravenous" })

#define HIT_VERBS    ({ "hit", "crush", "smash", "splat", "squash" })

#define LEFT_RIGHT   ({ "left", "right" })
#define DOUBLE_PARTS ({ "biceps", "hand", "cheek", "ear", "leg", "thigh", \
			"fore-arm", "upper arm", "calf" })
#define SINGLE_PARTS ({ "nose", "belly", "breast", "chin", "forehead" })

#define RANGER_I_NOT_BRAWL "_ranger_i_not_brawl"
#define BASE_DEX           5
#define DEX_LIMIT          5

#define MOSQUITO_POISON    "/d/Rhovanion/milan/mosquito_sting"

#ifndef SQUARE_ROOT
#define SQUARE_ROOT(i) ftoi(pow(itof(i), 0.5))
#endif

/*
 * Global variables
 */
string *hit_verbs    = HIT_VERBS;
string *double_parts = DOUBLE_PARTS;
string *single_parts = SINGLE_PARTS;

void
create_creature()
{
  string adj = ONE_OF_LIST(ADJECTIVES);

    set_race_name("mosquito");
    set_name("mosquito");
    set_pname("mosquitos");

    add_adj(adj);

    set_gender(G_NEUTER);

    set_long("This "+adj+" mosquito keeps buzzing around you.\n");

    /* Anyone should be able to kill it. */
    set_stats( ({ 5, 5, 5, 5, 5, 5 }) );

    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE,       50);

    /* This is one of the few creatures with no alignment. */
    set_alignment(0);

    add_prop(LIVE_I_NEVERKNOWN,  1);
    add_prop(LIVE_I_SEE_DARK,  100);
    add_prop(LIVE_I_NO_CORPSE,   1);
    add_prop(CONT_I_HEIGHT,      5);
    add_prop(OBJ_I_VOLUME,       5);
    add_prop(OBJ_I_WEIGHT,       5);
    add_prop(OBJ_M_NO_TELEPORT,  1);
    add_prop(RANGER_I_NOT_BRAWL, 1);

    set_alarm(0.0, 0.0, "set_move_message");
}

/*
 * The messages are set after create_creature() is called so we have to
 * do it ourselves with a little alarm.
 */
void
set_move_message()
{
    set_mm_in("buzzes arround your head.");
    set_mm_out("buzzes out of ear-shot.");
    set_m_in("buzzes into ear-shot.");
    set_m_out("buzzes away");
}

/*
 * Try to sting someone.
 */
void
try_sting(object victim)
{
    object sting;
    int    part;
    string body_part;

    if (random(2))
    {
	return;
    }

    part = random(2 * sizeof(double_parts) + sizeof(single_parts));

    body_part = ((part < sizeof(single_parts)) ? single_parts[part] :
	LEFT_RIGHT[(part - sizeof(single_parts)) % 2] + " " +
	double_parts[(part - sizeof(single_parts)) / 2]);

    seteuid(getuid());

    sting = clone_object(MOSQUITO_POISON);
    sting->move(victim, 1);
    sting->set_body_part(body_part);
    sting->start_poison();

    victim->catch_msg("The buzzing noise comes closer and you feel an itch " +
	"in your " + body_part + " and you think you have been stinged by " +
	query_art_name() + ".\n");
}

/*
 * This function is called when the mosquito is attacked to try to sting
 * the attacker.
 */
void
attacked_by(object attacker)
{
    ::attacked_by(attacker);

    try_sting(attacker);

    attacker->add_prop(LIVE_O_SPELL_ATTACK, TO);
}


/*
 * function called when attacker tries to hit us
 * returns: 0 - allow to hit,  1 - don't allow to hit
 */
int
query_not_attack_me(object attacker, int att_id)
{
    int dark_attack = 100;
    int dex;

    /* In the darkness, you will need SS_BLIND_COMBAT or SS_HEARING.
     */
    if (!CAN_SEE(attacker, TO))
    {
	dark_attack = attacker->query_skill(SS_BLIND_COMBAT) +
	    attacker->query_skill(SS_HEARING);

	/* dark_attack should be in [40..100] */
	dark_attack = ((dark_attack <  40) ?  40 :
	    ((dark_attack > 100) ? 100 : dark_attack));
    }

    dex = (attacker->query_stat(SS_DEX) * dark_attack) / 100;
    dex = BASE_DEX + SQUARE_ROOT(dex);

    if (random(dex) < DEX_LIMIT)
    {
	attacker->tell_watcher(QCTNAME(attacker) + " manages to " +
	    ONE_OF_LIST(hit_verbs) + " " + QTNAME(TO) + ".\n", TO);
	attacker->catch_msg("You manage to " + ONE_OF_LIST(hit_verbs) +
	    " " + QTNAME(TO) + "!\n");

        set_hp(0);
        do_die(attacker);

	return 1;
    }

    attacker->tell_watcher(QCTNAME(attacker) + " tries to " +
	ONE_OF_LIST(hit_verbs) + " " + QTNAME(TO) +
	", but fails to hit it.\n", TO);
    attacker->catch_msg("You try to " + ONE_OF_LIST(hit_verbs) + " " +
	QTNAME(TO) + ", but fail to hit it!\n");
    return 1;
}

