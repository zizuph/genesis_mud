/* File         : /d/Terel/silver_new/npc/bandit.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : Bandit Crew
 * Related Files: 
 * Comments     : 
 * Modifications: Cotillion, 2014-11-18
 *                Increased XP on kill, they're seriously annoying to kill
 */
#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"	

inherit STDMONSTER;

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <filter_funs.h>

void dress_me();

public string
random_weapon()
{
   switch (random(3))
   {
      case 0: return "cutlass";
      case 1: return "rapier";
      case 2: return "mace";
   }
}


query_m_in()
{ 
   return "sneaks in"; 
}

query_m_out()
{
   return "sneaks";
}

public void disappear();
public void set_recon();

int recon = 0;

public void 
create_monster()
{
    set_name("bandit");
	add_name("_silver_forest_bandit");
	set_assist("_silver_forest_bandit");
    set_adj(({"angry","lurking","upset","sneaky"})[random(4)]);
    set_race_name("halfling");
    set_long("This halfling seems to be a part of the band of bandits that make a " +
             "living off ambushing and plundering outgoing shipments from Calathin. " +
             "These types of bandits perform their deeds and operates in the " +
             "wilderness and oppose, attacks and disrupts anything passing them by. " +
             "The bandana that covers the bottom half of his face let you see into the " +
             "eyes of this devoted outlaw.\n");


    set_stats(({120 + random(10), 135 + random(10), 140, 110, 110, 120 + random(20)}));
    set_alignment(-100 - random(100));

    set_skill(SS_WEP_CLUB, 80 + random(10));
    set_skill(SS_WEP_KNIFE, 90 + random(10));
    set_skill(SS_WEP_SWORD, 70 + random(10));
    set_skill(SS_DEFENCE, 80 + random(10));
    set_skill(SS_PARRY, 70 + random(10));
    set_skill(SS_AWARENESS, 50 + random(5));
    set_skill(SS_BLIND_COMBAT, 75 + random(5));
    set_skill(SS_2H_COMBAT, 90 + random(5));
    heal_hp(query_max_hp());

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    dress_me();

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_UNARMED, 1);


    set_act_time(20 + random(5));
	add_act("assist halfling");
    add_act("emote yells: LOOTS LOOTS!!");
	add_act(({"say Now, where is that loot?", "peer", "ponder"}));
    add_act(({"say We plunder and massacre for pleasure and profit.", "laugh evil", "poke halfling"}));		
    add_act("whisper halfling When that wagon comes, I'm gonna get that loot!");
	add_act("say Mind your own business!");
    add_act("say A kind of transaction in which A plunders from B the " +
            "goods of C, and for compensation B picks the pocket of D " +
            "of money belonging to E.");
	add_act("chuckle");
	add_act("laugh sarc");
	add_act("whisper to halflings Lets find The Hand when we're done!");
	add_act(({"slap halfling", "whisper halfling Wake Up!", "laugh"}));
    add_act("grin");
	add_act(({"say Imagine if the animals in this forest would be wealthy enough " +
		    "to rob! I would snatch their coins right away!", "say Like.. Hey little " +
		    "bird, give me that gold", "laugh evil"}));
	add_act("whisper halflings Shall we end this loser's life?");


    set_cact_time(1);
	add_cact("assist halfling");
	
	add_ask(({"job", "task", "quest", "assignment"}), "@@tasking");
    set_default_answer(QCTNAME(this_object()) + " smirks and says: What? I don't understand your question.\n");

    /* Cotillion, 2016-02-18 */
    set_exp_factor(140);
}

string
tasking()
{
	TO->command("ponder");
	TO->command("say I do not trust you yet!");
	return "";
}

public void set_recon()
{
	recon = 1;
}

public void disappear()
{
	tell_room(E(TO), QCTNAME(TO) + " runs into the trees and quickly disappears.\n", TO);
	remove_object();
}

void
dress_me()
{
    seteuid(getuid(this_object()));     

    clone_object(WEAPON + random_weapon())->move(TO);
	clone_object(WEAPON + random_weapon())->move(TO);
	clone_object(ARMOUR + "bandit_padded")->move(TO);
	clone_object(ARMOUR + "bandit_pants")->move(TO);
    clone_object(ARMOUR + "bandit_boots")->move(TO);
    clone_object(ARMOUR + "bandit_bandana")->move(TO); 

  
    command("wield weapons");
    command("wear armours");
}



void
remove_berserk()
{
 say(QCTNAME(TP)+" calms down.\n");
 TO->remove_prop(LIVE_I_QUICKNESS, 100);
}

int
special_attack(object enemy)
{
    if (random(3)) return 0;
    if (TO->query_prop(LIVE_I_QUICKNESS) < 100)        
    {
       tell_room(ENV(TO), QCTPNAME(TO)+" veins almost explode as he turns quicker.\n");
       TO->add_prop(LIVE_I_QUICKNESS, 100);
       TO->add_mana(-200);
       set_alarm(60.0,0.0, remove_berserk);
       
       return 1;
    }
 
    return 0;
}

public void do_die(object killer)
{
	if(recon)
		disappear();
	else
		::do_die(killer);
}


void
notify_death(object killer)
{
	command("give weapons to halfling");
	command("give coins to halfling");
    command("emote pleads 'take these items, i don't want that " +
            "fool to have my valuable weapons and coins' before he dies.\n");
    ::notify_death(killer);
}

