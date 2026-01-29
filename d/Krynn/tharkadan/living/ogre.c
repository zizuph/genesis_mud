/*
 * Coded by Arman Mar 2017
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE
inherit "/lib/unique";


string *gAdj1 = ({"gigantic","massive","huge",
  "ferocious","black-haired","yellow-skinned"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

#define TRINKET  ARMOUR + "ogre_trinkets"
#define ARM1     ARMOUR + "ogre_leather"
#define ARM2     ARMOUR + "ogre_fur"

#define WEP1     WEP + "ogre_2hsword"
#define WEP2     WEP + "ogre_2haxe"
#define WEP3     WEP + "ogre_2hhalberd"
#define WEP4     WEP + "ogre_2hhammer"
#define MAG_AXE  WEP + "magic_2haxe"
#define MAG_CLUB  WEP + "magic_2hhammer"
#define MAG_SWORD  WEP + "magic_2hsword"
#define MAG_POLE  WEP + "magic_2hhalberd"

int st_bonus = random(50);
object trinket1, trinket2;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("ogre");
    add_name("barbarian");
    set_adj(ONE_OF(gAdj1));
    add_adj("barbarian");
    add_adj(ONE_OF(gAdj1));
    set_race_name("ogre");
    set_short(ONE_OF(gAdj1)+ " ogre barbarian");
    set_long("Before you stands an ogre of massive proportions, one " +
       "from the feared Tharkadan mountain barbarian tribes! Standing " +
       "taller than your average ogre at almost 11 feet tall, this " +
       "ogre also does not have the hunched posture of their lesser " +
       "brethren, making them look all the more daunting. His yellow " +
       "skin is heavily tattooed and covered in ritual scarification.\n");

    set_appearance(-75);

    set_stats(({300 + st_bonus, 200 + st_bonus, 300 + st_bonus, 
                100 + st_bonus, 150 + st_bonus, 200 + st_bonus}));
    set_intoxicated(1000);
    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(CONT_I_HEIGHT, 300 + random(100));
    add_prop(CONT_I_WEIGHT, 400000 + random(300000));
    add_prop(CONT_I_VOLUME, 420000 + random(300000));
  
    add_prop(LIVE_I_SEE_DARK, 5);

    // resistance to cold 
    add_prop(OBJ_I_RES_COLD, 25);

    set_alignment(-850);
    set_knight_prestige(100);

    set_skill(SS_WEP_CLUB, 70 + random(30));
    set_skill(SS_WEP_SWORD, 70 + random(30));
    set_skill(SS_WEP_POLEARM, 70 + random(30));
    set_skill(SS_WEP_AXE, 70 + random(30));
    set_skill(SS_UNARM_COMBAT, 70 + random(30));
    set_skill(SS_DEFENSE, 70 + random(30));
    set_skill(SS_PARRY, 40 + random(60));
    set_skill(SS_AWARENESS, 70 + random(30));
    set_skill(SS_BLIND_COMBAT, 30 + random(70));

    set_all_hitloc_unarmed(80);

    // Good natural armour and powerful special attack
    set_exp_factor(120);

    set_act_time(10);
    add_act("emote stares at you as if thinking whether " +
       "you would be better suited dead or as a slave.");
    add_act("emote grumbles about being hungry.");
    add_act("say Dragonmen walk da forests. Turn to stone when " +
       "smashed!");
    add_act("emote flexes his massive arm muscles.");

    set_cact_time(10);
    add_cact("emote roars gleefully.");
    add_cact("say I smash you tiny one!");


}

void 
arm_me()
{
    seteuid(getuid(this_object()));

    int weapon_type = random(100);

    switch(weapon_type)
    {
       case 0..24:
       {
          clone_unique(MAG_POLE, 15, WEP3)->move(this_object(),1);
          break;
       }
       case 25..50:
       {
          clone_unique(MAG_AXE, 15, WEP2)->move(this_object(),1);
          break;
       }
       case 51..74:
       {
          clone_unique(MAG_CLUB, 15, WEP4)->move(this_object(),1);
          break;
       }
       default:
       {
          clone_unique(MAG_SWORD, 15, WEP1)->move(this_object(),1);
          break;
       }
    }      

    command("wield all");

    trinket1 = clone_object(TRINKET);
    trinket1->make_the_trinket();
    trinket1->move(TO, 1);
    trinket2 = clone_object(TRINKET);
    trinket2->make_the_trinket();
    trinket2->move(TO, 1);

    clone_object(ARM1)->move(TO, 1);
    clone_object(ARM2)->move(TO, 1);
    command("wear all");
}


int
special_attack(object enemy)
{

    int attacktype, pen, wloc;
    mixed hitres;

    string *hitloc, how;

    attacktype = random(4);
    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    int ogre_str = TO->query_stat(SS_STR);

    if(attacktype == 1)
    {
    // Make sure that we can actually attack the target
    if (enemy->query_not_attack_me(TO, -1))
    {
        return 1; // round is ended so return 1.
    }
        
	pen = (ogre_str * 3) + random(800);
	hitres = enemy->hit_me(pen, 50, TO, -1);
	wloc = random(5);

	if(hitres[0] <= 0)
	    how = "his fist just missing";
	if(hitres[0] > 0)
	    how = "his fist grazing the skin of";
	if(hitres[0] > 10)
	    how = "his fist bruising";
	if(hitres[0] > 20)
	    how = "his fist bludgeoning";
	if(hitres[0] > 40)
	    how = "smashing his fist into";
	if(hitres[0] > 60)
	    how = "his fist crushing";
	enemy->catch_msg(QCTNAME(TO)+ " swings at you " +
	  "in a rage, " +how+ " your " +
	  hitloc[wloc]+ ".\n");
	tell_room(E(TO), QCTNAME(TO)+
	  " swings at " +QTNAME(enemy)+ " in a rage, " +
	  how+ " " +QTPNAME(enemy)+
	  " " +hitloc[wloc] + ".\n", ({enemy,TO}));

	if(enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}
	return 1;
    }
    return 0;
}

void
attack_func(object enemy, string race)
{
    if(!CAN_SEE(TO, enemy))
    {
	enemy->catch_msg(QCTNAME(TO)+ " is oblivious to your presence.\n");
	return;
    }

    command("say Ah! Me smash you " +race+ "!");
    command("kill " +enemy->query_real_name());
    return;
}

void
attack_weird_race(object enemy, string race)
{
    if(!CAN_SEE(TO, enemy))
    {
	enemy->catch_msg(QCTNAME(TO)+ " is oblivious to your presence.\n");
	return;
    }

    command("think");
    command("say What is this strange creature? What it taste like?");
    command("kill " +enemy->query_real_name());
    return;
}

void
greet_race(object enemy, string race)
{
    if(!CAN_SEE(TO, enemy))
    {
	enemy->catch_msg(QCTNAME(TO)+ " is oblivious to your presence.\n");
	return;
    }

    command("acknowledge " +enemy->query_real_name());
    command("flex");
    command("smile challenging " +enemy->query_real_name());

    return;
}

void 
init_living() 
{
    string race_name = TP->query_race_name();

    switch(race_name)
    {
       case "kender":
       case "elf":
       case "dwarf":
       case "half-elf":
       case "gnome":
        set_alarm(1.0, 0.0, &attack_func(TP, race_name));
        break;
       case "hobbit":
        set_alarm(1.0, 0.0, &attack_weird_race(TP, race_name));
        break;
       case "drow":
       case "minotaur":
       case "ogre":
       case "goblin":
       case "hobgoblin":
        set_alarm(1.0, 0.0, &greet_race(TP, race_name));
        break;
       default:
        set_alarm(1.0, 0.0, &attack_func(TP, race_name));
        break;
     }
 
    ::init_living(); 
}