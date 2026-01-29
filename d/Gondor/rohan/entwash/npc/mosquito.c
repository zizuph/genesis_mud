/*
 * /d/Gondor/common/npc/mosquito.c
 *
 * Copyright (C) Stas van der Schaaf - May 16 1994
 *               Mercade @ Genesis
 *
 * In the tower at Cirith Untol you may find mosquitos. They will sting
 * and that may be a bother to you.
 *
 * Since I'd hate to see people fight a mosquito and aim for the leg or
 * head, I've adjusted combat against them. Therefore, mosquitos do not
 * have hitlocation or attack locations, but the attacker will try to
 * splash it every round of combat.
 *
 * Revision history:
 *     Changed poison #define to modify damage, Gorboth 1995
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <const.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <math.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define ADJECTIVES   ({ "irritating", "buzzing", "blood-thirsty", \
			"blood-craven", "ravenous" })

#define HIT_VERBS    ({ "hit", "crush", "smash", "splat", "squash", \
			"massacre" })

#define LEFT_RIGHT   ({ "left", "right" })
#define DOUBLE_PARTS ({ "biceps", "hand", "cheek", "ear", "leg", "thigh", \
			"fore-arm", "upper arm", "calf" })
#define SINGLE_PARTS ({ "nose", "belly", "breast", "chin", "forehead" })

#define RANGER_I_NOT_BRAWL "_ranger_i_not_brawl"
#define BASE_DEX           (5)
#define DEX_LIMIT          (5)

#define MOSQUITO_POISON    (ENTWASH_DIR + "obj/mosquito_sting")
#define ALARM_TIME	   (90)
#define COMPUTE_ALARM_TIME (random((ALARM_TIME) / 2) + ((ALARM_TIME) / 2))

/*
 * Prototypes.
 */
void sting_sequence();

/*
 * Global variables
 */
string *hit_verbs    = HIT_VERBS;
string *double_parts = DOUBLE_PARTS;
string *single_parts = SINGLE_PARTS;

void
create_creature()
{
    set_race_name("mosquito");
    set_pname("mosquitos");

    set_gender(G_NEUTER);
    set_adj(ONE_OF_LIST(ADJECTIVES));
    set_short(query_adj() + " mosquito");
    set_pshort(query_adj() + " mosquitos");

    set_long(BSN("It is " + LANG_ADDART(short()) + " and it keeps buzzing " +
	"around your head. It looks like it fancies your blood, which it " +
	"needs to survive. Mosquitos like these are known to spread " +
	"diseases."));

    /* Anyone should be able to kill it, doesn't give much exp. though. */
    set_stats( ({ 5, 5, 5, 5, 5, 5 }) );

    /* In fact, it does not need much skills, but some guild-combat may
     * use them. DUH! Using guild-skils against a mosquito.
     */
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE,       50);

    /* This hitlocation is only added for guild attack commands. */
    set_hitloc_unarmed(A_BODY, ({ 1, 1, 1 }), 100, "body");

    /* This is one of the few creatures with no alignment. */
    set_alignment(0);

    add_prop(LIVE_I_NEVERKNOWN,  1);
    add_prop(LIVE_I_SEE_DARK,  100);
    add_prop(LIVE_I_NO_CORPSE,   1);
    add_prop(CONT_I_HEIGHT,      5);
    add_prop(OBJ_I_VOLUME,      15);
    add_prop(OBJ_I_WEIGHT,      15);
    add_prop(OBJ_M_NO_TELEPORT,  1);
    add_prop(RANGER_I_NOT_BRAWL, 1);

    set_mm_in("buzzes around your head.");
    set_mm_out("buzzes out of ear-shot.");
    set_m_in("buzzes into ear-shot");
    set_m_out("buzzes away");

    set_alarm(10.0, 0.0, sting_sequence);
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

    FIX_EUID;

    sting = clone_object(MOSQUITO_POISON);
    sting->set_body_part(body_part);
    sting->move(victim, 1);
    sting->start_poison();

    tell_object(victim, BSN("The buzzing noise comes closer and you feel an " +
	"itch in your " + body_part + " and you think you have been stung " +
	"by " + query_art_name(victim) + "."));
    TELL_ROOM(ENV(), victim, (" grabs at " + POSSESSIVE(victim) +
	" " + body_part + " and you suspect that " + PRONOUN(victim) +
	" has just been stung there as you hear the buzzing noise of " +
	query_art_name(victim) + ".\n"), ({ TO, victim }) );
}

/*
 * From time to time the mosquito will try to sting someone.
 */
void
sting_sequence()
{
    object *targets = FILTER_PLAYERS(all_inventory(ENV()));

    if (sizeof(targets))
    {
	try_sting(ONE_OF_LIST(targets));
    }

    set_alarm(itof(COMPUTE_ALARM_TIME), 0.0, sting_sequence);
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
 * Each combat round you try to splash it. There is no such things as
 * arm-wrestling with mosquitos.
 */
void
spell_attack(object attacker, object target)
{
    int dark_attack = 100;
    int dex;

    if (target != TO)
    {
	return;
    }

    /* In the darkness, you will need SS_BLIND_COMBAT or SS_HEARING.
     */
    if (!CAN_SEE(attacker, target))
    {
	dark_attack = attacker->query_skill(SS_BLIND_COMBAT) +
	    attacker->query_skill(SS_HEARING);

	/* dark_attack should be in [40..100] */
	dark_attack = ((dark_attack <  40) ?  40 :
	    ((dark_attack > 100) ? 100 : dark_attack));
    }

    dex = (attacker->query_stat(SS_DEX) * dark_attack) / 100;
    dex = BASE_DEX + SQUARE_ROOT(dex);

    /* Hit is partially based on dexterity and 50 percent on chance.
     */
    if ((random(dex) < DEX_LIMIT) &&
	(random(2)))
    {
	attacker->tell_watcher(QCTNAME(attacker) + " manages to " +
	    ONE_OF_LIST(hit_verbs) + " " + QTNAME(TO) + ".\n", TO);
	tell_object(attacker, BSN("You manage to " + ONE_OF_LIST(hit_verbs) +
	    " " + query_the_name(attacker) + "!"));

	/* We need to calculate the current HP since we want to reset the
	 * delay value since that is queried in the do_die() function.
	 */
	calculate_hp();
	set_hp(0);
	do_die(attacker);

	return;
    }

    attacker->tell_watcher(QCTNAME(attacker) + " tries to " +
	ONE_OF_LIST(hit_verbs) + " " + QNAME(TO) +
	", but fails to hit it.\n", TO);
    tell_object(attacker, BSN("You try to " + ONE_OF_LIST(hit_verbs) + " " +
	query_the_name(attacker) + ", but fail to hit it!"));

    /* This needs to be called directly after heart-beat has called this
     * function in order to re-add the property. */
    set_alarm(0.1, 0.0, &attacker->add_prop(LIVE_O_SPELL_ATTACK, TO));
}
