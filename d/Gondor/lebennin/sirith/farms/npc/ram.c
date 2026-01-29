/* 
 * /d/Gondor/lebennin/sirith/farms/npc/ram.c  
 *
 * based on /d/Gondor/common/npc/deer, but tuned down
 * since this is for a low-level area.
 *
 */

#pragma strict_types
 
inherit "/d/Gondor/lebennin/sirith/farms/npc/livestock";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>		/* for W_IMPALE, etc		*/
#include <ss_types.h>		/* for SS_UNARMED, etc		*/
#include <macros.h>		/* for IS_CLONE			*/
#include <const.h>		/* for G_MALE			*/
#include <stdproperties.h>	/* for LIVE_I_NEVERKNOWN, etc	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"

#define	MYBARN	SIRITH_FARMS_DIR+"farm2/barn"

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_HORNS  0
#define A_CHARGE 1
#define A_FHOOVES 2
#define A_RHOOVES 3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2


public void	create_sirith_livestock();
public void	cr_configure();
public string	cr_attack_desc(int aid);
public mixed	oke_to_move(string exit);

/*
 * Function name:	create_sirith_livestock
 * Description	:	set up the ram
 */
public void
create_sirith_livestock()
{
    if (!IS_CLONE)
    {
	return;
    }

    set_name( ({ "ram", "animal", "creature", "beast" }) );
    set_race_name("sheep");
    set_alignment(0);
    set_gender(G_MALE);
    set_short("shaggy ram");
    add_adj("shaggy");
    set_long(BSN("The ram has a shaggy fleece and short curled horns."));

		/* str, dex, con, int, wis, dis */
    set_stats( ({  8 + random( 8), 10 + random( 6), 8 + random( 5),
		   2 + random( 5), 1, 1 }));
    set_skill(SS_UNARM_COMBAT, 10 + random(11));
    set_skill(SS_DEFENCE,      15 + random(11)); 
    set_skill(SS_SWIM,50+random(20));
    set_skill(SS_CLIMB,50+random(20));

    add_prop(CONT_I_WEIGHT, 54432);	/* 120 lbs */
    /* 4' at  shoulder x 4' long x 2' wide */
    add_prop(CONT_I_WEIGHT, 121);	/* 48 inches */
    add_prop(CONT_I_VOLUME, 906194);	/* 55296 cubic inches */

    set_act_time(15+random(15));
    add_act("emote stares angrily at you.");
    add_act("emote snorts loudly.");
    add_act("emote stamps his right hoof.");

    set_alarm(0.0, 0.0, &set_m_in("trots into view"));
    set_alarm(0.0, 0.0, &set_m_out("trots"));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(NPC_I_NO_LOOKS, 1);
} /* create_sirith_livestock */


/*
 * Function name:	cr_configure
 * Description	:	add attacks and hitlocations:
 */
public void
cr_configure()
{
    /*
     * add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
     * add_hitloc(int *ac, int prchit, string desc, int id)
     *
     * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
     */
    add_attack(5+random(5),10+random(2),W_IMPALE,10,A_HORNS);
    add_attack(5+random(5),5+random(2),W_BLUDGEON,10,A_CHARGE);
    add_attack(5+random(5),10+random(2),W_SLASH,20,A_FHOOVES);
    add_attack(5+random(5),10+random(2),W_SLASH,20,A_RHOOVES);
 
    add_hitloc(({15+random(15),10+random(10),5+random(5)}),10,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),10+random(10)}),50,"body",H_BODY);
    add_hitloc(({15+random(15),5+random(5),10+random(10)}),40,"legs",H_LEGS);
} /* cr_configure */


/*
 * Function name:	cr_attack_desc
 * Description	:	Give description of each attack.
 * Arguments	:	int aid -- the attack id
 *
 * We could also redefine the entire hitdescription by redefining 'cr_did_hit'
 */
public string
cr_attack_desc(int aid)
{
    switch (aid)
    {
    case A_HORNS:	return "sharp horns";
    case A_CHARGE:	return "butting head";
    case A_FHOOVES:	return "front hooves";
    case A_RHOOVES:	return "rear hooves";
    default:		return "mind"; /* should never occur */
    }
}


/*
 * Function name: oke_to_move
 * Description:   Overlay the default routine to check if we're fighting
 *		  OR if we're in the barn. Should not move in either case.
 * Arguments:     exit  : the exit that is generated for the monster to take.
 * Returns:       0     : if in combat or in barn
 *                string: the exit that the monster takes if not in combat.
 */
public mixed
oke_to_move(string exit)
{
    object env;

    if (TO->query_attack() ||
    	(objectp(env = ENV()) &&
	 file_name(env) == MYBARN))
    {
	return 0;
    }
    return exit;
} /* oke_to_move */
