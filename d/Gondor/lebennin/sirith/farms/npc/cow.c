/* 
 * /d/Gondor/lebennin/sirith/farms/npc/cow.c
 *
 * basically, /d/Gondor/common/npc/deer.c with different description
 *
 * XXX respond to attempts to milk cow
 */

#pragma strict_types
 
inherit "/d/Gondor/lebennin/sirith/farms/npc/livestock";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>		/* for W_IMPALE, etc		*/
#include <ss_types.h>		/* for SS_DEFENCE, etc		*/
#include <macros.h>		/* for IS_CLONE			*/
#include <stdproperties.h>	/* for NPC_I_NO_LOOKS, etc	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"

#define	MYBARN	(SIRITH_FARMS_DIR+"farm1/barn2")

public void	create_sirith_livestock();
public void	cr_configure();
public string	cr_attack_desc(int aid);
public mixed	oke_to_move(string exit);


/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_TRAMPLE  0	/* was BITE, but i can't see a cow biting :-) */
#define A_CHARGE 1
#define A_FHOOVES 2
#define A_RHOOVES 3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

/*
 * Function name:	create_sirith_livestock
 * Description	:	set up the cow
 */
public void
create_sirith_livestock()
{
    if (!IS_CLONE)
    {
	return;
    }

    set_name( ({ "cow", "animal", "creature", "beast" }) );
    set_race_name("cattle");
    set_gender(G_FEMALE);

    switch (random(3))
    {
    case 0:
    	set_short("placid cow");
	add_adj( ({ "placid", "tame", "mild" }) );
    	set_long(BSN("The cow appears to be quite tame. She regards you "+
	    "with only mild interest."));
	break;
    case 1:
	set_short("spotted cow");
	add_adj("spotted");
	set_long(BSN("The cow's coat is white with scattered black spots."));
	break;
    case 2:
	set_short("black cow");
	add_adj("black");
	set_long(BSN("The cow's coat is solid black, except for a "+
	    "white star on her forehead."));
	break;
    }

    set_alignment(0);
		/* str, dex, con, int, wis, dis */
    set_stats(({15+random(10),15+random(10),10+random(15),
		5+random(5),5+random(10),5+random(5)}));
    set_skill(SS_UNARM_COMBAT,30+random(10));
    set_skill(SS_DEFENCE,30+random(10));
    set_skill(SS_PARRY,30+random(10));
    set_skill(SS_SWIM,50+random(20));
    set_skill(SS_CLIMB,50+random(20));
    /* random_move and restrain_path set when cloned */


    add_prop(CONT_I_WEIGHT, 725760);	/* 1600 lbs */
    /* ooooh, make it 5.5 feet at the shoulder x 7 feet long x 2 feet wide */
    add_prop(CONT_I_HEIGHT, 167);	/* 66 inches */
    add_prop(CONT_I_VOLUME, 2180531);	/* 133056 cubic inches */

    set_act_time(15+random(15));
    add_act("emote stares calmly at you.");
    add_act("emote lows mournfully.");
    add_act("emote placidly chews her cud.");

    set_alarm(0.0, 0.0, &set_m_in("ambles into view"));
    set_alarm(0.0, 0.0, &set_m_out("ambles"));
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
    add_attack(5+random(5),15+random(5),W_IMPALE,10,A_TRAMPLE);
    add_attack(15+random(15),5+random(5),W_BLUDGEON,30,A_CHARGE);
    add_attack(15+random(5),15+random(5),W_SLASH,20,A_FHOOVES);
    add_attack(15+random(10),15+random(5),W_SLASH,40,A_RHOOVES);
 
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
    case A_TRAMPLE:	return "trample";
    case A_CHARGE:	return "charge";
    case A_FHOOVES:	return "front hooves";
    case A_RHOOVES:	return "rear hooves";
    default:		return "mind"; /* should never occur */
    }
} /* cr_attack_desc */


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
