/*
 * /d/Avenir/common/dark/mon/bat.cabs
 *
 * Created:   Lilith Nov 2021
 * Revisions:
 * Purpose:   Ambiance for the Utterdark
 *
 */
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "../dark.h"
/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE	 0
#define A_LCLAW  1
#define A_RCLAW  2
#define A_LWING  3
#define A_RWING  4

#define H_HEAD   0
#define H_BODY   1
#define H_LWING  2
#define H_RWING  3


void add_attacks()
{
    query_combat_object()->cb_set_attackuse(150);
}


public void
create_creature(void)
{
	setuid();
    seteuid(getuid());
	
    set_race_name("bat");
    set_short("alert bat");
    set_adj(({"black", "cave", "little", "small" }));
    set_long("A small creature, with an oval body and "+
	"larger, paper-thin wings. It has oversized ears "+
	"and big round eyes. It is alert and watching you.\n");
    set_gender(G_NEUTER);
	default_config_creature(10);
    set_stat_extra(SS_DEX, 200);
    /* Little flying things are hard to hit */
    set_skill(SS_ACROBAT,       100);
    set_skill_extra(SS_ACROBAT, 150);
    set_skill(SS_DEFENCE,       100);
    set_skill(SS_BLIND_COMBAT,  100);
	set_skill(SS_UNARM_COMBAT,  100);

    add_prop(LIVE_I_SEE_DARK, 1);
	remove_prop(OBJ_M_NO_GET);
	add_prop(OBJ_I_WEIGHT, 500);
	add_prop(OBJ_I_VOLUME, 750);
	add_prop(CONT_I_VOLUME, 750);
	add_prop(CONT_I_WEIGHT, 500);
    add_prop(NPC_I_NO_LOOKS, 1);	
	
    set_restrain_path("/d/Avenir/common/dark/");
    set_random_move(3);
    set_alignment(0);

    set_attack_unarmed(A_BITE,  10, 10, W_IMPALE,   20, "fangs");
    set_attack_unarmed(A_LCLAW, 10, 10, W_SLASH,    20, "left claw");
    set_attack_unarmed(A_RCLAW, 10, 10, W_SLASH,    20, "right claw");
    set_attack_unarmed(A_LWING,  5,  5, W_BLUDGEON, 20, "left wing");
    set_attack_unarmed(A_RWING,  5,  5, W_BLUDGEON, 20, "right wing");
    
	/* giving high AC to make them hard to kill because they are so small */
    set_hitloc_unarmed(H_HEAD, ({ 90 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 90 }), 20, "body");
    set_hitloc_unarmed(H_LWING,({ 90 }), 30, "left wing");
    set_hitloc_unarmed(H_RWING,({ 90 }), 30, "right wing");
	add_prop(OBJ_I_RES_MAGIC, 20); 
	
	set_m_in("flies in");
	set_m_out("flies");
	
	set_act_time(4);
    add_act("emote rustles its wings.");
	add_act("emote squeaks loudly.");
	add_act("emote twitches its ears.");

    set_alarm(0.1, 0.0, add_attacks);	
	
	if (random(5) == 0)
		add_object("/d/Avenir/common/obj/guano", 1);
}
