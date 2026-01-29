/* 
 * /d/Gondor/sirith/farms/obj/gartersnake.c
 *
 * /d/Gondor/common/npc/snake.c and /d/Gondor/common/npc/rabbit.c
 * combined to make a little, non-venomous gartersnake suitable
 * for gardens in newbie areas.
 */

#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <const.h>		/* for G_NEUTER			*/
#include <ss_types.h>		/* for SS_DEFENCE, etc		*/
#include <wa_types.h>		/* for W_IMPALE			*/
#include <stdproperties.h>	/* for NPC_I_NO_LOOKS, etc	*/

#include "/d/Gondor/defs.h"

#define A_BITE 0
#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

public void	create_creature();
public int	query_knight_prestige();

/*
 * Function name:	create_creature
 * Description	:	set up the snake
 */
public void
create_creature() 
{
    ::create_creature();
    set_name( ({ "snake", "reptile", "gartersnake" }) );
    set_pname("snakes");
    set_adj( ({"smooth","green"}) );
    set_pshort(implode(query_adjs(), ", ") + " snakes");
    set_race_name("snake"); 
    set_long(BSN("The snake is pale green with a light yellow belly. "+
       "It is only a couple of feet long."));
    set_gender(G_NEUTER);
    set_alignment(0); // neutral alignment for animals
    add_prop(CONT_I_WEIGHT,500);	/* 1.1 lbs */
    add_prop(CONT_I_HEIGHT,10);		/* 4 inches */
    add_prop(CONT_I_VOLUME,1573);	/* 96 cubic inches */
    add_leftover(NPC_DIR + "snake_meat", "snake meat", 3, 0, 0, 0);
    add_leftover(NPC_DIR + "snake_skin", "snake skin", 1, 0, 0, 0);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(NPC_I_NO_LOOKS, 1);

    set_stats( ({  3 + random( 8),	/* str */
		  10 + random( 6),	/* dex */
		   5 + random( 5),	/* con */
		   5 + random( 5),	/* int */
		   1,			/* wis */
		   1 }));		/* dis */
    set_skill(SS_UNARM_COMBAT, 10 + random(11));
    set_skill(SS_DEFENCE,      10 + random(11)); 
    set_attack_unarmed( A_BITE,
	5+random(5), 5+random(5), W_IMPALE, 50, "bite");
    set_hitloc_unarmed( H_HEAD, ({ 20, 15, 1}), 10, "head");
    set_hitloc_unarmed( H_BODY, ({ 30, 25, 1}), 80, "body");
    set_hitloc_unarmed( H_TAIL, ({ 20, 15, 1}), 10, "tail");

} /* create_creature */

public int	query_knight_prestige() { return 1; }
