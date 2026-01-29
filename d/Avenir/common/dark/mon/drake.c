/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 * Lilith Nov 2021: Fixed up the hit/pen of attacks after the white hits and 
 *                      updated actions and loot.
 * Lilith Dec 2021: Don't want it wandering anymore.
 * Lilith Feb 2022: Remvoed res magic since the combat system autocalcs
 *                   it based on AC now.
 */
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "/d/Avenir/smis/sys/statserv.h"
#include "../dark.h"
/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE	0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3
#define A_HORN  4

#define H_HEAD  0
#define H_BODY  1


void add_attacks()
{
    query_combat_object()->cb_set_attackuse(110);
}

public void
create_creature(void)
{
    setuid();
    seteuid(getuid());

    set_adj(({"somnolent", "cave" }));
    set_short("somnolent cave drake");
    set_race_name("drake");
    set_long("This is a cave drake. These smaller dragons inhabit "+
      "dark caverns, seeking refuge from light. They devour beings "+
      "very quickly with their massive jaws. They are wicked creatures "+
      "and possess great intelligence.\n");

    default_config_creature(150);

    set_skill(SS_DEFENCE,       80);
    set_skill(SS_BLIND_COMBAT,  75);
    set_skill(SS_UNARM_COMBAT,  90);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 1);

    set_restrain_path(L1);
    //    set_random_move(8);  Stay put for now. 
    set_attack_chance(20);
    set_alignment(0);

    set_attack_unarmed(A_BITE,  60, 30, W_IMPALE,   20, "jaws");
    set_attack_unarmed(A_LCLAW, 30, 50, W_SLASH,    20, "left claw");
    set_attack_unarmed(A_RCLAW, 30, 50, W_SLASH,    20, "right claw");
    set_attack_unarmed(A_TAIL,  80, 30, W_BLUDGEON, 20, "tail");
    set_attack_unarmed(A_HORN,  40, 60, W_IMPALE,   20, "horn");

    set_hitloc_unarmed(H_HEAD, ({ 60 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 70 }), 80, "body");
 
    set_alarm(0.1, 0.0, add_attacks);
    clone_object("/d/Genesis/gems/obj/agate_fire")->move(TO);
}

/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 */
void
attacked_by(object ob)
{
    int s, t;

    ::attacked_by(ob);

    set_short("enraged cave drake");
}


void
do_die(object killer)
{
    object treasure;

    if (query_hp() > 0)
	return;

    treasure = clone_object("/d/Genesis/gems/obj/agate_fire");
    treasure->set_heap_size(4 + random(5));
    treasure->move(TO);
    STATSERV_LOG_EVENT("Utterdark", "Drake killed");	

    ::do_die(killer);

}
