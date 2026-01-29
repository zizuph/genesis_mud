/*
* Created by: Luther
* Date: 13 August 2001
*
* File: /d/Cirath/tyr/npc/q_pris.c
* Comments: Slave prisoner in the Jail of Tyr part of Jail quest
*           used lyden.c as a template to making 
*/
 
#pragma strict_types
#pragma save_binary
 
inherit "/d/Cirath/std/monster.c";
#include "/d/Cirath/quest_handler/quest_handler.h"
#include <wa_types.h>
#include "defs.h"
#define DALE_SPEAK_DONE "dale_speak_done"
#define DALE_KEY_GIVEN "dale_key_given"
#define DALE_QUEST_COMPLETE "dale_quest_complete"
#define ZARTH_SECOND_PART "_zarth_second_part"
#define _IS_KEY_ "_is_key_"
#define ROPE_WALL "rope_wall"
#include "/d/Cirath/common/introfnc.h"
#include "/sys/filter_funs.h"

#define MAIN_ASK(x) ("@@askmost:"+file_name(TO)+"|"+x+"@@")
 
void
create_monster ()
{
    	set_living_name("dale");
    	set_name("dale");
    	set_title("Poor merchant of Tyr");
    	set_race_name("human");
    	set_adj("skinny");
    	add_adj("bonny");
    	set_long("Once a wealthy merchant in Tyr, this bonny prisoner looks "
            +"ragged and worn down. By the looks of his clothes he must "
            +"have been here for quite some time. His arms and legs are "
            +"chained to the wall, giving him little movement. He still "
            +"looks like he can fight being chained up to the wall. You "
            +"should probably leave him alone.\n");
   
    	set_stats(({75,75,75,100,100,75}));
    	set_all_hitloc_unarmed(50);
    	set_skill(SS_BLIND_COMBAT, 50);
    	set_skill(SS_DEFENCE, 60);
    	set_skill(SS_PARRY, 40);
    	set_skill(SS_UNARM_COMBAT,80);
    	set_alignment(-250);
    	add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   
    	set_act_time(3);
    	add_act("emote glares at you wishing he was free.");
    	add_act("emote tries to break his chains.");
	add_act("emote rattles his chains.");
	add_act("emote mumbles painfully.");
	add_act("emote ponders when the leftovers will arrive.");
	add_act("' I don't like being a prisoner.");
    	add_act("emote stares at the dead body against the wall.");
    	add_act("shout let me out of here!");
    	add_act("' No one can help me.");
    	
    	set_cact_time(3);
    	add_cact("shout Guards, Help me!");
    	add_cact("' But i dont know where it is! I swear!");
    	add_cact("' These chains hinder me or you would die alot faster.");
    	add_cact("emote tries to break the chains.");
    	add_cact("emote almost breaks his chains.");  
    	
    	add_ask(({"rope","about rope"}), MAIN_ASK("rope"));
  	add_ask(({"trading","about trading"}), MAIN_ASK("trading"));
  	add_ask(({"key","about key"}), MAIN_ASK("key"));
    	add_ask(({"task","about task","job","about job","help","about help"}), 
    		VBFC_ME("asktask"));
}
 
void
arm_me()
{
    clone_object(TYR_ARM+"d_gloves")->move(TO);
    clone_object(TYR_ARM+"d_shirt")->move(TO);
    command("wear all");
}
 
int
follow()
{
   	notify_fail("Follow who?\n");
   	        
        if ((TP->query_prop(ZARTH_SECOND_PART)) && (TP->query_prop(ROPE_WALL)))
      	{
      		command("say What a day!");
        	command("say A guard just visisted me.");
        	command("say He claimed i would be set free tomorrow.");    
        	command("say No need to escape now.");    
        	command("say I appreciated all the help you've given me.");   
      		command("say Go tell my friend about my release.");
      		command("say He will reward you well for all your help.");
      		TP->add_prop(DALE_QUEST_COMPLETE, 1);    
      		return 1;
   	}
   	else
   	return 0;
}

void
init_living()
{
::init_living();
add_action("follow","follow");
}
 
void
attacked_by(object ob)
{
    ::attacked_by(ob);
}
 
void
do_die(object killer)
{
    ::do_die(killer);
}
 
/* **************** DALES CHAIN WHIPPING ******************** */
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
 
    me=this_object();
 
    if(random(8)) return 0;
 
    hitresult = enemy->hit_me(200 + random(200), W_BLUDGEON, me, -1);
    how = "ankle";
    if (hitresult[0] > 0) how = "hand";
    if (hitresult[0] > 15) how = "leg";
    if (hitresult[0] > 30) how = "arm";
    if (hitresult[0] > 50) how = "body";
    if (hitresult[0] > 75) how = "neck";
 
    enemy->catch_msg(QCTNAME(me) + " wraps a chain around your " +
                     how + " making you feel pain.\n");
    
    tell_watcher(QCTNAME(me)+" wraps a chain around "+ QCTNAME(enemy)+
                 " causing pain to " + HIS_HER(me) + " " + how + ".\n",
                 enemy);
     
     if(enemy->query_hp() <= 0) enemy->do_die(me);
 
    return 1;
}

string
askmost(string subject)
{
   object who;
   who=PO;
  
   switch(subject)
   {     
      case "rope":
         command("' Rope? Hmm i don't recall ever seeing any.");
         return "";
      case "trading":
         command("' Ya i like to trade...");
         command("' You better have something worth my while!");
         return "";
      case "key":         
         command("' Maybe you could find me something to unlock these chains with.");
         return "";
      default: return "";
   }
}

/* ****************** THE QUEST ************************ */
string
asktask()
{
    if ((!QH_QUERY_QUEST_COMPLETED(TP, "jail_pris_quest")) && (!TP->query_prop(DALE_KEY_GIVEN)))
    {
        command("say A friend of mine is in the alley.");
        command("say He plans on rescuing me from this place.");
        command("say However i will first need some help.");    
        command("say I need to remove these chains.");    
        command("say Go find me something to pick the locks.");    
        TP->add_prop(DALE_KEY_GIVEN, 1);    
        return "";
    }
    else
    {
    	command("say Go kill all the guards.");
    	command("say They will deserve it!");
    	command("grin");
    	return "";
    }
}

public void
enter_inv(object ob, object from)
{      	
   	::enter_inv(ob,from);

    	if (!from) return;

    	if (ob->query_prop(_IS_KEY_))
        	set_alarm(1.0, 0.0, "got_key", ob, from);
   	else
        	set_alarm(1.0, 0.0, "got_else", ob, from);
}


void
got_key(object ob, object from)                  
{   
    	if (!interactive(from))
        	return;
   
        set_this_player(from);
        
        if ((!QH_QUERY_QUEST_COMPLETED(from, "jail_pris_quest")) && (from->query_prop(DALE_KEY_GIVEN)))
      	{      		      		
      		command("say Now here is the plan.");
      		command("say I said a friend of mine is in the alley.");
		command("say Go speak with him and he will tell you what to do.");         		
      		ob->remove_object();
        	from->add_prop(DALE_SPEAK_DONE, 1);           	
    	}    	
    	else
    		set_alarm(1.0, 0.0, "got_else", ob, from);
}      

void
got_else(object ob, object from)
{
    	command("say What is this?");
    	command("drop "+ob->query_name());
}
