/* File         : /d/Terel/silver_new/npc/bandit_leader.c
 * Creator      : Udana
 * Date         : March 2006         
 * Purpose      : Bandit Crew Leader Rommenus
 * Related Files: 
 * Comments     : 
 * Modifications: Modified by Pasqua
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>
#include "../include/defs.h"

#define PLAYER_I_ATTACKED_CARAVAN "_player_i_attacked_caravan"
#define PLAYER_I_DESTROYED_CARAVAN "_player_i_destroyed_caravan"
#define CARAVAN_START (ROAD + "road02")

inherit "/lib/unique";

inherit STDMONSTER;

int gave_whistle = 0;
object quiver;
string my_long();
/* sets his secondary weapon to spear */
void set_melee();
public void wield_melee();
void arm_me();

void
create_terel_monster()
{
    
    set_name("rommenus");
    add_name("bandit");
	add_name("_silver_forest_bandit");
	set_assist("_silver_forest_bandit");
    set_living_name("rommenus");
    set_race_name("halfling");
    set_adj("commanding");
    add_adj("mean");
    set_title("the Banditleader");
    set_long("@@my_long");
    
    set_gender(0);
    set_alignment(-600);
    
    set_stats(({ 140 +random(20), 190 +random(10), 170 +random(30), 80 +random(20), 90 +random(20), 160 +random(20) }));

    set_skill(SS_WEP_MISSILE, 100 +random(50));
    set_skill(SS_WEP_POLEARM, 100 +random(50));
    set_skill(SS_UNARM_COMBAT, 90 +random(10));
    set_skill(SS_PARRY, 100 +random(20));
    set_skill(SS_DEFENCE, 100 +random(25));
    set_skill(SS_AWARENESS, 50 +random(30));
    set_skill(SS_BLIND_COMBAT, 100);
     
   
    add_prop(CONT_I_WEIGHT, 30000 +random(5000));
    add_prop(CONT_I_HEIGHT, 110 +random(10));
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 1);   
    add_prop(NPC_I_NO_UNARMED, 1);

    set_hp(query_max_hp());

     set_act_time(10 + random(2));
    add_act(({"say Give me that loot or I'll cut out your liver!", "laugh viol", "lick spear blood", 
		"say The caravan will soon arrive at the forest.", "say I need more men."}));
    add_act("emote hums something.");
    add_act("emote makes sure the spear is in his reach.");
    
    set_cact_time(1);   

    add_cact("emote looks at you without fear.");
    add_cact("say That was a mistake!");
    add_cact("take arrows");
    set_default_answer("say I've got a job to do, I have no time for silly questions.", 1);
    enable_intro();
    add_ask(({"caravan", "caravan ambush", "more men", "task", "quest"}), "@@caravan_answer");
	add_ask("reward", "@@reward_quest");
    
    arm_me();
    
    MONEY_MAKE_GC(random(10) + 5)->move(TO);
    MONEY_MAKE_SC(random(20) + 20)->move(TO);
    
    set_melee();
}

string reward_quest()
{
	if(!TP->query_prop(PLAYER_I_DESTROYED_CARAVAN))
	{
		command("say I'll reward you when you do what I asked you to do.");
		return "";
	}
	TP->remove_prop(PLAYER_I_DESTROYED_CARAVAN);
	command("say Yes, I heard you've done well. What you looted there, " +
		"is yours.");
	if(!TP->test_bit("Terel", QUEST_CARAV_GROUP, QUEST_CARAV_BIT))
	{
		if(TP->query_exp() <= QUEST_CARAV_REWARD ) 
			TP->add_exp_quest(TP->query_exp());
		else
			TP->add_exp_quest(QUEST_CARAV_REWARD);
		write("You feel more experienced.\n");
		TP->set_bit(QUEST_CARAV_GROUP, QUEST_CARAV_BIT);
		write_file(QUEST_LOG, capitalize(TP->query_real_name()) +
			" destroyed the caravan (" + ctime(time()) + ")\n");
	}
	return "";
}	

string caravan_answer()
{
	FIX_EUID;
	if(TP->test_bit("Terel", QUEST_CARAV_GROUP, QUEST_CARAV_BIT))
	{
		command("say We don't need any more of your help.");
		return "";
	}
	if(TP->query_alignment() > 0)
	{
		command("say You seem more like a guard then a bandit to me. Be gone!");
		return "";
	}
	command("say Yes, I could use a good leader for the ambush.. ");
	if(!CARAVAN_START->create_caravan(TP, 0))
	{
		command("say But the caravan is on it's way already, "+
			"maybe you can help us with next one.");
		return "";
	}
	command("say The caravan is currently assembling just north of the Calathin "+
		"gates. Make it never reach the Last.");
	if(!gave_whistle)
	{
		clone_object(OBJ + "bandit_whistle")->move(TP);
		TP->catch_msg(QCTNAME(TO) + " hands you a long black whistle.\n");
		command("say Take this, use it to signal my men in the forest. They'll come "+
			"and assist you on whoever you're fighting.\n");
		gave_whistle = 1;
	}
	TP->add_prop(PLAYER_I_ATTACKED_CARAVAN, 1);
	return "";
}

void arm_me()
{
	FIX_EUID;     
	/* weapons */
	clone_object(WEAPON + "black_bow")->move(TO);
	clone_object(WEAPON + "spear")->move(TO);
	/*armours */
	clone_object(ARMOUR + "bandit_bandana")->move(TO);
	clone_object(ARMOUR + "leggings")->move(TO);
	clone_object(ARMOUR + "ringmail_bracers")->move(TO);
	clone_object(ARMOUR + "worn_cloak")->move(TO);
	clone_object(ARMOUR + "ringmail")->move(TO); 
	/*quiver and arrows*/
	quiver = clone_object(OBJ + "quiver");
	quiver->move(TO);
	clone_object(WEAPON + "black_arrow")->move(quiver);
	clone_unique(WEAPON + "burr_arrow", 3, WEAPON + "black_arrow")->move(quiver);
	quiver->wear_me();
	/*treasure password*/
	clone_object(OBJ + "password")->move(TO);
	/*commands*/
	command("wield bow");
	command("wear all");
}


string my_long()
{
    string weapon_desc;
    object *wielded = query_weapon(-1);
    if(!sizeof(wielded) || query_prop(LIVE_S_EXTRA_SHORT))
       weapon_desc = "He's has an quiver with arrows and bow strapped to "+
             "his back. A spear is logged in the ground just few feets behind "+
             "him.";
    else
    {
     if(wielded[0]->query_short() == "black shortbow")
       weapon_desc = "A spear is lodged in the ground just few feets behind "+
             "him.";
     else
       weapon_desc = "He's has an quiver with arrows and bow strapped to "+
             "his back.";
    }
    return "The short halfling standing before you seems to be an experienced "+
             "hunter. " + weapon_desc + " You wonder what is he doing here. \n";
}


public void wield_melee()
{
	
	tell_room(E(TO), QCTNAME(TO) + " straps bow on his back and reaches for his "+
                   "spear.\n");
	command("unwield all");
	command("wield spear");
}

void set_melee()
{
	command("wield bow");
	command("secondary wield spear");
}
