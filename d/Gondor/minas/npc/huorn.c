/* 
 * /d/Gondor/minas/npc/huorn.c  
 *
 * A huorn of Fangorn - part of oat quest
 *
 * Alto, 14 May 2001
 *
 */

#pragma strict_types

inherit "/std/monster";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>

#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <money.h>




#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/lib/porter_defs.h"


/* Define some attack and hitloc id's */

#define A_L_FIST   0
#define A_R_FIST   1
#define A_L_ROOT   2
#define A_R_ROOT   3

#define H_HEAD    0
#define H_TRUNK   1
#define H_RARM    2
#define H_LARM    3
#define H_RLEG    4
#define H_LLEG    5

#define INNER_MINAS "/d/Gondor/minas"
#define FANGORN_DIR "/d/Gondor/fangorn/"

int try_attack();
static  object  Victim;
public int  remove_huorn();


public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj("gigantic");
    add_adj("angry");
    set_pname("huorns");
    set_name("huorn");
    add_name("ent");

    set_race_name("huorn");

    set_long("A gigantic huorn of Fangorn Forest. He looks very angry.\n");

    rnd = random(60);
    default_config_npc(150+rnd/2);
    set_base_stat(SS_DIS, 150 + rnd);
    set_alignment(50+rnd*10);

    set_gender(0);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_LOC_SENSE, 100);
    set_skill(SS_TRACKING, 100);

    add_prop(LIVE_I_SEE_DARK, 200);

    set_aggressive(&try_attack());
    set_attack_chance(100);

    set_m_out("tramples");
    set_m_in("tramples in");

    set_act_time(5);
    add_act("emote trumpets a deep woodwind note.");
    add_act("emote says: Hrum!");
    add_act("emote says: Hroom!");
    add_act("emote says: Hoom!");
    add_act("growl");
    add_act("grumble");

    set_cact_time(2);
    add_cact("emote trumpets a painful high-pitched note.");
    add_cact("emote thunders: How dare you harm my trees! Hroom!");
    add_cact("emote thunders: Fangorn is not a place for tree-killers! Hrum!");
    add_cact("emote growls: Unfortunately for you, I am a hasty ent.");
    add_cact("emote grumbles: Do not touch the trees in my forest.");

    setuid();
    seteuid(getuid());
    clone_object(INNER_MINAS + "/obj/huorn_torch.c")->move(TO);

    set_restrain_path(FANGORN_DIR);
    set_monster_home(FANGORN_DIR + "marsh_oak_room");


    set_alarm(900.0, 0.0, &remove_huorn());

    refresh_mobile();

}



/*
 * Add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */

public void
cr_configure()
{
    add_attack(40+random(5),30+random(5),W_BLUDGEON,10,A_L_FIST);
    add_attack(40+random(5),30+random(5),W_BLUDGEON,30,A_R_FIST);
    add_attack(40+random(5),30+random(5),W_BLUDGEON,20,A_L_ROOT);
    add_attack(40+random(5),30+random(5),W_BLUDGEON,40,A_R_ROOT);

    add_hitloc(({25+random(15),20+random(10),15+random(5)}),10,
        "massive head",H_HEAD);
    add_hitloc(({25+random(5),15+random(5),20+random(10)}),50,
        "thick trunk",H_TRUNK);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "knotted left arm",H_RARM);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "knotted right arm",H_LARM);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "huge root-like left leg",H_RLEG);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "huge root-like right leg",H_LLEG);

}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_L_FIST:return "hammer-shaped left fist";
    case A_R_FIST:return "hammer-shaped right fist";
    case A_L_ROOT:return "gnarled left foot";
    case A_R_ROOT:return "gnarled right foot";
    }
    return "mind"; /* should never occur */
}

public string
query_combat_file()
{
    return "/std/combat/cplain";
}



/*
 * Function name:   start_follow
 * Description:     Start following the enemy.
 * Arguments:       The object to follow.
 */
public void
start_follow(object ob)
{
    object *follower,
            shadow;

    if (!objectp(ob) || !objectp(present(ob, ENV(TO))) || 
	(ob != query_attack()) || (Victim == ob))
	return;

    if (pointerp(follower = ob->query_follower()))
    {
	if (member_array(TO, follower) < 0)
	    ob->add_follower(TO);
    }
    else
    {
	shadow = clone_object(GONDOR_FOLLOW_SHADOW);
	shadow->follow(ob, TO);
    }
    Victim = ob;
}

public varargs void
remove_victim(object victim)
{
    if (objectp(victim) && (Victim != victim))
	return;
    Victim = 0;
}



/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    ::attack_object(ob);
    start_follow(ob);
}

public int
remove_huorn()
{
    say("The gigantic angry male huorn fades into the trees and is gone.\n");
    TO->remove_object();
    return 1;
}



int
try_attack()
{ 
    if (TP->query_prop(I_CUT_TREE))
    {
        set_alarm(1.0, 0.0, &command("light torch"));
        return 1;
    }
    command("assist ent");
    set_alarm(10.0, 0.0, &command("light torch"));
    return 0;
}

int
notify_you_killed_me(object player)
{
    set_alarm(2.0, 0.0, &remove_huorn());
   	return 1;
}



public int
do_die(object killer)
{
    if (query_hp() > 0) 
     return 0;
    if (!objectp(killer))
     killer = previous_object();
    tell_room(ENV(TO), "The Huorn shrieks so loudly that your ears hurt. "
        + "As it dies, it crumbles into the dust from which it was born.\n");
    combat_extern->cb_death_occured(killer);

    this_object()->notify_death(killer);

    if (living(killer))
    {
        combat_reward(killer, 0, 1);
    }

    killer->notify_you_killed_me(TO);
    TO->remove_object();
    return 1;
}

