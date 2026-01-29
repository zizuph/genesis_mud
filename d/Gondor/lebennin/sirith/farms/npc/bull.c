/* 
 * /d/Gondor/lebennin/sirith/farms/npc/cow.c
 *
 * basically, /d/Gondor/common/npc/buck.c with different description
 */

#pragma strict_types
 
inherit "/d/Gondor/lebennin/sirith/farms/npc/livestock";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>		/* for W_SLASH, etc		*/
#include <ss_types.h>		/* for SS_DEFENCE, etc		*/
#include <macros.h>		/* for IS_CLONE			*/
#include <const.h>		/* for G_MALE			*/
#include <stdproperties.h>	/* for LIVE_I_NEVERKNOWN, etc	*/

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
#define A_TRAMPLE  0
#define A_CHARGE 1
#define A_FHOOVES 2
#define A_RHOOVES 3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2


/*
 * Function name:	create_sirith_livestock
 * Description	:	set up the bull
 */
public void
create_sirith_livestock()
{
    if (!IS_CLONE)
    {
	return;
    }

    set_name( ({ "bull", "animal", "creature", "beast" }) );
    set_race_name("cattle");
    set_gender(G_MALE);

    set_short("large, white-spotted bull");
    add_adj( ({ "white-spotted", "large" }) );
    set_long(BSN("The bull is quite large and has a glossy black hide "+
	"with white spots. He looks as if he could be dangerous "+
	"when annoyed."));
  
		/* str, dex, con, int, wis, dis */
    set_stats(({random(40)+40,random(45)+50,random(40)+50,
		random(7)+7,random(10)+5,random(25)+25}));
    set_gender(G_MALE);
    set_skill(SS_UNARM_COMBAT,random(40)+20);
    set_skill(SS_CLIMB,random(25)+25);
    set_skill(SS_SWIM,random(20)+25);
    set_skill(SS_DEFENCE,random(20)+30);
    set_skill(SS_PARRY,random(30)+30);

    add_prop(CONT_I_WEIGHT, 725760);	/* 1600 lbs */
    /* ooooh, make it 5.5 feet at the shoulder x 7 feet long x 2 feet wide */
    add_prop(CONT_I_HEIGHT, 167);	/* 66 inches */
    add_prop(CONT_I_VOLUME, 2180531);	/* 133056 cubic inches */

    /* random_move and restrain_path set when cloned */

    set_act_time(15+random(15));
    add_act("emote stares suspiciously at you.");
    add_act("emote tosses his head angrily.");
    add_act("emote snorts loudly.");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alarm(0.0, 0.0, &set_m_in("ambles into view"));
    set_alarm(0.0, 0.0, &set_m_out("ambles"));
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
    add_attack(random(10)+5,random(10)+15,W_BLUDGEON,10,A_TRAMPLE);
    add_attack(random(20)+10,random(20)+10,W_IMPALE,30,A_CHARGE);
    add_attack(random(20)+15,random(15)+5,W_SLASH,20,A_FHOOVES);
    add_attack(random(20)+10,random(30)+10,W_SLASH,20,A_RHOOVES);
 
    add_hitloc(({random(5)+15,random(2)+5,random(2)+6}),10,"head",H_HEAD);
    add_hitloc(({random(3)+8,random(2)+11,random(2)+10}),50,"body",H_BODY);
    add_hitloc(({random(10)+15,random(2)+4,random(2)+5}),40,"legs",H_LEGS);
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
} /* cr_attack_desc


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
