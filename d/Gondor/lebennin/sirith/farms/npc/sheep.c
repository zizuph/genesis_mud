/* 
 * /d/Gondor/lebennin/sirith/farms/npc/sheep.c  
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

#include <wa_types.h>		/* for W_SLASH, etc		*/
#include <ss_types.h>		/* for SS_DEFENCE, etc		*/
#include <macros.h>		/* for IS_CLONE			*/
#include <const.h>		/* for G_FEMALE			*/
#include <stdproperties.h>	/* for OBJ_I_WEIGHT, etc	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"

#define	MYBARN	SIRITH_FARMS_DIR+"farm2/barn"

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_CHARGE 1
#define A_FHOOVES 2
#define A_RHOOVES 3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
create_sirith_livestock()
{

    if (!IS_CLONE)
    {
	return;
    }
    set_name( ({ "sheep", "sheep", "animal", "creature", "beast", "ewe" }) );
    set_race_name("sheep");
    set_alignment(0);
    set_gender(G_FEMALE);

    switch (random(3))
    {

    case 0:
    	set_short("dusty sheep");
    	set_pshort("dusty sheep");
    	set_long(BSN("The sheep is dusty, and there are twigs in "+
	    "her fleece."));
    	add_adj("dusty");
	break;

    case 1:
	set_short("shaggy sheep");
	set_pshort("shaggy sheep");
	set_long(BSN("The sheep has a very shaggy fleece."));
	add_adj("shaggy");
	break;

    case 2:
	set_short("fat sheep");
	set_pshort("fat sheep");
	set_long(BSN("The sheep is quite plump."));
	add_adj( ({"plump", "fat"}) );
	break;
    }

		/* str, dex, con, int, wis, dis */
    set_stats( ({  8 + random( 8), 10 + random( 6), 8 + random( 5),
		   2 + random( 5), 1, 1 }));
    set_skill(SS_UNARM_COMBAT, 10 + random(11));
    set_skill(SS_DEFENCE,      15 + random(11)); 
    set_skill(SS_SWIM,50+random(20));
    set_skill(SS_CLIMB,50+random(20));

    set_act_time(15+random(15));
    add_act("emote stares blankly at you.");
    add_act("emote bleats mournfully.");
    add_act("emote looks around nervously.");

    add_prop(CONT_I_WEIGHT, 54432);	/* 120 lbs */
    /* 4' at  shoulder x 4' long x 2' wide */
    add_prop(CONT_I_WEIGHT, 121);	/* 48 inches */
    add_prop(CONT_I_VOLUME, 906194);	/* 55296 cubic inches */

    set_alarm(0.0, 0.0, &set_m_in("trots into view"));
    set_alarm(0.0, 0.0, &set_m_out("trots"));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(NPC_I_NO_LOOKS, 1);
}

/*
 * Here we add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */
public void
cr_configure()
{
    add_attack(5+random(5),5+random(2),W_BLUDGEON,20,A_CHARGE);
    add_attack(5+random(5),10+random(2),W_SLASH,20,A_FHOOVES);
    add_attack(5+random(5),10+random(2),W_SLASH,20,A_RHOOVES);
 
    add_hitloc(({15+random(15),10+random(10),5+random(5)}),10,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),10+random(10)}),50,"body",H_BODY);
    add_hitloc(({15+random(15),5+random(5),10+random(10)}),40,"legs",H_LEGS);
}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */
public string
cr_attack_desc(int aid)
{
    switch (aid)
    {
    case A_CHARGE:	return "butting head";
    case A_FHOOVES:	return "front hooves";
    case A_RHOOVES:	return "rear hooves";
    }
    return "mind"; /* should never occur */
}

public string	query_combat_file() { return "/std/combat/cplain"; }


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
}
