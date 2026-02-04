/*
 * bigwolf.c
 *
 * This white wolf is larger than the grey wolves and gets a special
 * attack.
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */
#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/lib/unique";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>

#define HUNT_SHADOW     "/d/Terel/std/follow.c"

#define A_BITE   0
#define A_LCLAW  1
#define A_RCLAW  2

#define H_HEAD   0
#define H_BODY   1


static object prey = 0;
static int    shadowed = 0, hunt_alarm = 0;

mixed benice();
void start_hunting();

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    FIX_EUID;
    ::create_creature();
    set_name(({"animal"}));
    set_short("enormous white wolf");
    set_pshort("enormous white wolves");
    set_long("An enormous white vicious-looking wolf.\n");
    set_adj(({"enormous", "white", "vicious"}));
    set_race_name("wolf");
    set_alignment(-80 - random(20));
    set_exp_factor(150);

    set_stats(({random(30)+70, random(12)+100, 140, 30, 33, 90}));

    set_attack_unarmed(A_BITE,  15, 12, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 20, 10, W_SLASH,  30, "left claw");
    set_attack_unarmed(A_RCLAW, 20, 10, W_IMPALE, 30, "right claw");

    set_hitloc_unarmed(H_HEAD, ({ -15, -25, -20, -20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  10,  15,  30,  20 }), 80, "body");

    set_aggressive("@@benice");
    SET_MAX_HP;
    set_gender(NEUTER);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE, 80);
    BRAVE;
    add_prop(LIVE_I_SEE_DARK,10); 
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_SEE_INVIS,100);            /* I smell you, I know you are there */
    add_leftover(MOUNTAIN_DIR + "goblincave/armour/whitepelt","pelt", 1, "", 0, 1);

    set_restrain_path(MOUNTAIN_DIR + "goblincave");
    set_random_move(6);

    set_act_time(20);
    add_act("emote growls ferociously.");
    add_act("emote bares its teeth at you.");
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me = TO;
    int hurt;
    int fire_resist;

    if (random(10) < 4)
    {
	hurt = F_PENMOD(60, 70 + random(10));

	hitresult = enemy->hit_me(hurt, MAGIC_DT, me, -1);

	how = "unharmed";
	if (hitresult[0] > 0)
	    how = "slightly hurt";
	if (hitresult[0] > 20)
	    how = "rather hurt";
	if (hitresult[0] > 50)
	    how = "crushed";
	if (hitresult[0] > 100)
	    how = "devastated";

	tell_watcher(QCTNAME(me) + " mauls " + QTNAME(enemy) + ".\n", enemy); 
	enemy->catch_msg(QCTNAME(me) + " mauls you!\n");
	enemy->catch_msg("You feel " + how + ".\n");

	start_hunting();
	return 1;
    }

    return 0;
}

mixed
benice()
{
    if (TP->query_race_name() == "goblin")
	return 0;

    /* Dont bite the hand that feeds me */
    if (TP->query_wiz_level())
	return 0;

    /* Invisible players doesn't mean they dont smell */
    if (TP->query_prop(OBJ_I_INVIS))
    {
	write("The wolf raises his snout high in the air " +
            "sniffing in your direction.\n");
	say("The wolf raises his snout as if smelling something.\n", TP);
	return 1;
    }

    /* Too small, throw em back!  */
    if (TP->query_average_stat() <= 90)
	return 0;

    return 1; 
}

//  Here are the hunting functions :)
public void
attack_object(object ob)
{
    ::attack_object(ob);
    if (!prey && !shadowed && !hunt_alarm)
	hunt_alarm = set_alarm(itof(10 + random(8)),0.0,&start_hunting());
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (!prey && !shadowed && !hunt_alarm)
	hunt_alarm = set_alarm(itof(8 + random(8)),0.0,&start_hunting());
}

void
start_hunting()
{
    if (hunt_alarm)
    {
	remove_alarm(hunt_alarm);
	hunt_alarm = 0;
    }

    //  Can't hunt if we aren't killing somene ;)
    if (!objectp(query_attack()))
	return;

    //  We already got our prey in our hunting sights
    if (objectp(prey) && shadowed)
	return;

    object *enemies = query_enemy(-1) & all_inventory(environment());
    //  Make sure there are no npcs in the array.
    enemies = FILTER_PLAYERS(enemies);
    if (!sizeof(enemies))
	return;

    prey = one_of_list(enemies);
    clone_object(HUNT_SHADOW)->follow(prey, TO);
    shadowed = 1;
}

//  Called from the follow shadow
void
notify_stopped_hunt()
{
    prey = 0;
    shadowed = 0;
}

string
query_hunting()
{
    return prey->query_real_name();
}

int
query_shadowed()
{
    return shadowed;
}
