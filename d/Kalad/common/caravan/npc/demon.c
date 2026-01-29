#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed.c";

#include <poison_types.h>

#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_BODY 0
#define H_HEAD 1
#define H_LARM 2
#define H_RARM 3
#define H_LEGS 4

/* The demons that appear when Thanar's avatar is slain */

void go_away();

void
create_kalad_monster()
{
    set_name("demon");
    set_race_name("demon");
    set_adj("horrific");
    add_adj("ghastly");
    set_long("A terrifying creature from the nether planes, its twisted and "+
      "contorted body only vaguely resembles that of a human, for it is "+
      "ugly and misshapen, covered with a skin of oozing black maggots and a "+
      "face that is pocked with disease and decay.\n");
    set_alignment(-1000);
    set_knight_prestige(1000);
    set_gender(G_NEUTER);
    set_stats(({75, 100, 125, 75, 75, 100}));
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(OBJ_M_NO_INS, 1);
    set_random_move(10);
    set_act_time(3);
    add_act("get weapons");
    add_act("snarl all");
    add_act("growl all");
    add_act("glare evil all");
    add_act("cackle dem");
    add_act(({"kill human", "kill elf", "kill dwarf", "kill gnome", "kill hobbit", "kill goblin"}));
    set_cact_time(3);
    add_cact(({"kill human", "kill elf", "kill dwarf", "kill gnome", "kill hobbit", "kill goblin"}));
    set_attack_unarmed(A_BITE, 50, 50, W_IMPALE, 10, "gnarly fangs");
    set_attack_unarmed(A_LCLAW, 40, 40, W_SLASH, 45, "left claw");
    set_attack_unarmed(A_RCLAW, 40, 40, W_SLASH, 45, "right claw");
    set_hitloc_unarmed(H_BODY, ({60, 60, 60}), 40, "tortured body");
    set_hitloc_unarmed(H_HEAD, ({50, 50, 50}), 10, "twisted head");
    set_hitloc_unarmed(H_LARM, ({40, 40, 40}), 15, "distorted left arm");
    set_hitloc_unarmed(H_RARM, ({40, 40, 40}), 15, "distorted right arm");
    set_hitloc_unarmed(H_LEGS, ({45, 45, 45}), 20, "atrophic legs");
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_SEE_INVIS, 10);

    set_alarm(1800.0 + (1800.0 * rnd()), 0.0, &go_away());
}

void
go_away()
{
    tell_room(environment(), 
	      QCTNAME(this_object()) + " fades away.\n");
    remove_object();
}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;

    if (aid==A_BITE)
    {
	tell_object(enemy, "The demon's gnarly fangs impale you with their horrible bite!\n");
	poison = clone_object("/std/poison_effect");
	if(poison)
	{
	    poison->move(enemy, 1);
	    poison->set_time(1000);
	    poison->set_interval(100);
	    poison->set_strength(200);
	    poison->set_damage(({POISON_FATIGUE, 200, POISON_STAT, SS_CON}));
	    poison->set_damage_type("demonic");
	    poison->start_poison();
	}

    }
    return 0;
}
