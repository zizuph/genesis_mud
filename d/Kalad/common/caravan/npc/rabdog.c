/*
 * Turned into a non-humnanoid, Cotillion - 2010-03-15
 */


#include "default.h"
inherit "/d/Kalad/std/creature";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include <files.h>
#include <poison_types.h>

#define A_BITE 0
#define A_LPAW 1
#define A_RPAW 2
#define H_BODY 0

void
create_kalad_creature()
{
    if (!IS_CLONE)
	return;
    set_name("dog");
    set_race_name("dog");
    set_adj("rabid");
    set_long("The animal has white froth foaming from its jaws, it stares "+
      "at you in an unsettling manner.\n");
    set_gender(G_NEUTER);
    set_stats(({50, 50, 50, 25, 25, 75}));
    set_skill(SS_DEFENCE, 30);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_M_NO_INS, 1);
    set_aggressive(1);
    set_random_move(10);
    set_act_time(3);
    add_act("snarl all");
    add_act("growl all");
    set_attack_unarmed(A_BITE, 40, 20, W_IMPALE, 10, "jaws");
    set_attack_unarmed(A_LPAW, 45, 15, W_SLASH, 45, "left paw");
    set_attack_unarmed(A_RPAW, 45, 15, W_SLASH, 45, "right paw");
    set_hitloc_unarmed(H_BODY, ({  15, 15, 10 }), 100, "body");
}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;
    if(aid==A_BITE)
    {
	tell_object(enemy, "The dog's jaws clamp into your torso!\n");
	poison = clone_object(POISON_OBJECT);

	if(poison)
	{
	  poison->move(enemy , 1);
	    poison->set_time(1000);
	    poison->set_interval(100);
	    poison->set_strength(40);
	    poison->set_damage(({POISON_FATIGUE, 100, POISON_STAT, SS_CON}));
	    poison->set_poison_type("rabies");
	    poison->start_poison();
	}

    }
    return 0;
}
