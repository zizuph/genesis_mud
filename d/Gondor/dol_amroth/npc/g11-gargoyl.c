/* -*- Mode: C -*-
 *
 * npc/g11-gargoyl
 *
 * By Skippern 20(c)02
 *
 * This is a gargoyl. It is summoned when any of the magicians
 * servants are attacked.
 */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";

#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "../defs.h"

#define A_BITE      0
#define A_HORN      1
#define A_L_WING    2
#define A_R_WING    3
#define A_L_CLAW    4
#define A_R_CLAW    5
#define A_TAIL      6

#define H_L_FOOT    0
#define H_R_FOOT    1
#define H_BODY      2
#define H_HEAD      3
#define H_L_WING    4
#define H_R_WING    5
#define H_L_ARM     6
#define H_R_ARM     7
#define H_TAIL      8

/* GLobal variables */
static object     Mage, tower;

/* Prototypes */
void return_me();

void set_Mage(object o)     { Mage = o; }
void set_Tower(object o)    { tower = o; }


void
create_creature()
{
    set_name("gargoyl");
    set_gender(G_NEUTER);
    set_short("massive gargoyl");
    set_long("This deamon like statue is a living creature, summoned " +
	     "to protect the magician in the tower.\n");

    set_stats( ({ 100, 85, 85, 50, 50, 100 }) );

    set_skill(SS_DEFENCE,         80);
    set_skill(SS_PARRY,           80);
    set_skill(SS_UNARM_COMBAT,   100);
    set_skill(SS_BLIND_COMBAT,    50);

    //set_attack_unarmed(   aid,wchit, wcpen,         dt, %use, adesc);
    set_attack_unarmed(  A_BITE,   20,    20, W_BLUDGEON,    5, "bite");
    set_attack_unarmed(  A_HORN,   50,    20, W_IMPALE,     20, "horn");
    set_attack_unarmed(A_L_WING,   25,    20, W_SLASH,      20, "left wing");
    set_attack_unarmed(A_R_WING,   25,    20, W_SLASH,      20, "right wing");
    set_attack_unarmed(A_L_CLAW,   30,    20, W_SLASH,      15, "left claw");
    set_attack_unarmed(A_R_CLAW,   30,    20, W_SLASH,      15, "right claw");
    set_attack_unarmed(  A_TAIL,   15,    20, W_BLUDGEON,    5, "tail");

    //set_hitloc_unarmed(   hid,                  *ac, %hit, hdesc);
    set_hitloc_unarmed(H_L_FOOT, ({  6,  8, 15, 35 }),   15, "left foot");
    set_hitloc_unarmed(H_R_FOOT, ({  6,  8, 15, 35 }),   15, "right foot");
    set_hitloc_unarmed(  H_BODY, ({  3, 10, 15, 35 }),    8, "body");
    set_hitloc_unarmed(  H_HEAD, ({  3, 10, 15, 35 }),   10, "head");
    set_hitloc_unarmed(H_L_WING, ({  1,  1, 15, 35 }),   15, "left wing");
    set_hitloc_unarmed(H_R_WING, ({  1,  1, 15, 35 }),   15, "right wing");
    set_hitloc_unarmed( H_L_ARM, ({  3,  8, 15, 35 }),   10, "left arm");
    set_hitloc_unarmed( H_R_ARM, ({  3,  8, 15, 35 }),   10, "right arm");
    set_hitloc_unarmed(  H_TAIL, ({ 10, 10, 15, 35 }),    2, "tail");


    set_alarm(720.0, 0.0, &return_me());
}

void
return_me()
{
    tell_room(tower, "The gargoyl flaps its wings and returns to its " +
	      "pedistall on the wall.\n", this_object());
    tower->add_g();
    remove_object();
}

void
do_assist()
{
    command("assist " + Mage->query_name());
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr, o;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
}

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 */
public int
do_die(object killer)
{
    object o;

    if (query_hp() > 0)
	return 0;

    if (!objectp(killer))
	killer = previous_object();

    Mage->Gargoyl_Death();
    tower->add_g();

    this_object()->notify_death(killer);

    if (living(killer))
    {
        combat_reward(killer, 0, 1);
    }

    /*
    add_leftover(DOL_LEFTOVER + "g_horn", "horn", random(3), 0, 1, 1);
    add_leftover(DOL_LEFTOVER + "g_wing", "wing", random(3), 0, 1, 1);
    if (random(10)<2)
	add_leftover(DOL_LEFTOVER + "w_tail", "tail", 1, 0, 1, 1);
    */
    if (random(10) > 6)
    {
	o->clone_object(DOL_LEFTOVER + "g_horn");
	o->move(this_object());
    }
    if (random(10) > 8)
    {
	o->clone_object(DOL_LEFTOVER + "g_wing");
	o->move(this_object());
    }
    if (random(10) > 5)
    {
	o->clone_object(DOL_LEFTOVER + "w_tail");
	o->move(this_object());
    }

    killer->notify_you_killed_me(this_object());

    move_all_to(environment(this_object()));
    this_object()->remove_object();
  
    return 1;
}

int
special_attack(object victim)
{
    int dam;
    object o;

    if (victim != query_attack() || random(150) > 10)
	return 0;

    if (environment(victim) != environment(this_object()))
	return 0;

    switch(random(25))
    {
    case 0..5:
	victim->catch_msg(QCTNAME(this_object())+" lashes a wing at you and hurts your left sholder. You are in " +
			  "severe pain.\n");
	victim->tell_watcher(QCTNAME(this_object())+" lashes a wing at "+QTNAME(victim)+", and hurts " +
			     victim->query_possessive()+" left sholder.\n");
	victim->heal_hp(-(10+random(15)));
	victim->add_attack_delay(1);
	break;
    case 6..10:
	victim->catch_msg(QCTNAME(this_object())+" rushes at you and rams you with its horn.\n");
	victim->tell_watcher(QCTNAME(this_object())+" rushes at "+QTNAME(victim)+" and rams " +
			     victim->query_objective()+" with its horn.\n");
	victim->heal_hp(-(20+random(10)+random(25)));
	victim->add_attack_delay(5+random(15));
	break;
    case 11..15:
	dam = random(50)+25;
	if (dam > victim->query_hp())
	{
	    victim->catch_msg("All you see as the world dims for your eyes is that "+QTNAME(this_object())+
			      " drives one of its claws deep into you throat.\n");
	    victim->tell_watcher(QCTNAME(this_object())+" drives one of its claws deep into "+
				 QTPNAME(victim)+" throat and rips it open. "+QCTPNAME(victim)+
				 " soul leaves "+victim->query_possessive()+" body.\n");
	}
	else
	{
	    victim->catch_msg(QCTNAME(this_object())+" drives one of its claws deep at your throut and hits. " +
			      "Blood flows out of the deep wound.\n");
	    victim->tell_watcher(QCTNAME(this_object())+" drives one of its claws deep into "+QTPNAME(victim)+
				 " throat. Blood flows from "+QTPNAME(victim)+" throat.\n");
	}
	victim->heal_hp(-dam);
	break;
    case 16..20:
	victim->catch_msg(QCTNAME(this_object())+" flies up and rushes at you from the air with its " +
			  "feet first.\n");
	victim->tell_watcher(QCTNAME(this_object())+" flies up and rushes at "+QTNAME(victim)+" with " +
			     "its feet first.\n");
	victim->add_stun();
	o = clone_object(DOL_OBJ + "stun");
	o->set_victim(victim);
	o->set_delay(10);
	o->move(victim, 1);
	break;
    default:
	victim->catch_msg("WHACK!\nWhat happened? Your head feels terrible.\n");
	victim->tell_watcher(QCTNAME(this_object())+" tunrs suddenly round and smashes its tail in " +
			     QCTPNAME(victim)+" face. "+QCTNAME(victim)+" looks confused.\n");
	victim->add_attack_delay(5+random(10));
	return 0;
    }

    if (victim->query_hp() < 1)
	victim->do_die(this_object());

    return 1;
}

