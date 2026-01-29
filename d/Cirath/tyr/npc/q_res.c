/*
* Created by: Luther
* Date: August 2001 
*
* File: /d/Cirath/tyr/jail/q_res.c
* Comments: Dale's captain of the guard trying to rescue him
*           
*/

#pragma strict_types
#pragma save_binary
 
inherit "/d/Cirath/std/monster.c";
inherit "/d/Kalad/lib/special.c";

#include "/d/Cirath/common/defs.h"
#include "/sys/stdproperties.h"
#include <filter_funs.h>
#include "defs.h"
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <formulas.h>
#include <composite.h>
#include <options.h>
#include <std.h>
#include <filter_funs.h>
#include <money.h>
#define ZARTH_FIRST_PART "_zarth_first_part"
#define ZARTH_SECOND_PART "_zarth_second_part"
#define DALE_SPEAK_DONE "dale_speak_done"
#define DALE_QUEST_COMPLETE "dale_quest_complete"
#define THE_ROPE "the_rope"
#define DALE_KEY_GIVEN "dale_key_given"
#define _IS_KEY_ "_is_key_"
#define ROPE_WALL "rope_wall"
#include "/d/Cirath/quest_handler/quest_handler.h"

#define MAIN_ASK(x) ("@@askmost:"+file_name(TO)+"|"+x+"@@")

public int query_init_master() { return 1; }

object attacker;
int z;

void
create_monster ()
{
	set_name("zarth");
	set_title("Ex-Captain of the Merchant Guards");
	set_race_name("human");
	set_adj("aged");
	set_adj("battleworn");

	set_long("This is a shady human who seems to be looking for something. "
		+"He stands in the shadows hoping not to be seen by the nearby "
		+"guards. He is constantly looking up into the sky looking for "
		+"something.\n");

	set_stats(({ 160, 150, 160, 150, 140, 140}));

	set_skill(SS_DEFENCE, 90);
	set_skill(SS_PARRY, 90);
	set_skill(SS_WEP_SWORD, 90);
	set_skill(SS_AWARENESS, 60);	
	set_skill(SS_BLIND_COMBAT, 90);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop (LIVE_I_NEVERKNOWN, 1);
	add_prop(NPC_M_NO_ACCEPT_GIVE,0);
	add_prop(OBJ_M_HAS_MONEY, 25);
	set_alignment(0);
	z = 0;

	set_act_time(5);
	set_cact_time(3);

	add_act("emote starts to examine the jail walls.");
	add_act("emote gives you a grim look, that makes you shiver.");
	add_act("emote tries to climb the wall.");
	add_act("emote looks up at the building.");
	add_act("' Maybe you can help me?");
	add_act("' I have to climb this wall.");
	add_act("ponder i have to find some rope.");
	add_act("' I hate waiting here. If i only could climb this wall.");
	add_act("' If i only could climb this wall.");
	
	add_cact("emote looks for a way to escape.");
	add_cact("emote grins evilly.");
	add_cact("emote gasps in astonishment.");
	add_cact("' You should have helped me instead.");
	add_cact("' Well well, you gonna regret this.");
	add_cact("' I am going to have to hide your corpse now!");
	add_cact("' I have waited for a real fight for a very long time.");

	add_ask(({"weapon", "sword", "sunblade"}), 
         "A battleworn aged male human says: Oh yes, the sunblade. A ancient artifact made in the time of the psions. "
        +"In there hands its a deadly weapon, but not so deadly in our hands. "
        +"Mine was passed down almost thirty generations. It can be a nasty weapon "
        +"if i use it. Pray you never find out.\n");

	add_ask(({"task","about task","job","about job","help","about help",
	    "assignment","about assignment"}),VBFC_ME("asktask"));
	    
	add_ask(({"reward","about reward"}),VBFC_ME("reward"));    
	
	add_ask(({"wall", "climb", "sky", "up"}), 
	"A battleworn aged male human says: The wall is very hard to climb. "
	+"I will need something to help me climb up there if i am to help my " 
	+"friend.\n");
	
	add_ask(({"rope", "something"}),
	"A battleworn aged male human says: I can't find anything. Maybe you "
	+"can find soemthing for me? A rope possibly, but i doubt you can find "
	+"one. I haven't seen one in Athas in years.\n");
}

void
arm_me()
{	
   if(!random(3))
    { 
      clone_object(TYR_WEP+ "sun_swrd.c")->move(TO); 
    }
   else
    { 
     clone_object(TYR_WEP+ "edged_swrd.c")->move(TO);
    }   
	clone_object(TYR_ARM + "bone_shd.c")->move(TO);
	clone_object(TYR_ARM + "head_lth.c")->move(TO);	
	clone_object(TYR_ARM + "body_lth.c")->move(TO);
	clone_object(TYR_ARM + "legs_lth.c")->move(TO);
	command("wield all");
	command("wear all");
}

/* sets unarmed combat off, giving more attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}

/* ****************** THE QUEST ************************ */
string
asktask()
{
    if ((!QH_QUERY_QUEST_COMPLETED(TP, "jail_pris_quest")) && (TP->query_prop(DALE_SPEAK_DONE)))
    {
        command("say Yes i can use some help.");
        command("say A friend of mine is in the jail.");
        command("say The guards caught him a few nights ago.");
        command("say I warned him not to trade at night.");
        command("say But did he listen? Not likely.");
        command("say They accused him of illegal trading.");
        command("say The guards won't let me in there.");
        command("say They know i will try and break him out.");
        command("say Maybe you can find me some rope.");
        command("say Just give it to me once you find it.");
        command("say You will be rewarded very well.");
        TP->add_prop(ZARTH_FIRST_PART, 1);   
        return "";   
    }
    else
    {
    command("say Me need help?");
    command("say I think you have bigger problems.");
    command("say When those guards catch you.");
    command("say You will end up in a cell.");
       return "";
    }
}	

string
reward()
{
	string size;
	
	if (TP->query_prop(DALE_QUEST_COMPLETE))
	{
		command("say After all that trouble.");
		command("say He is being released.");
		command("say You have been a great help to me.");
		command("say Please accept this for your troubles.");
		command("say Coins are worth alot around here...");
		MONEY_MAKE_PC(random(10)+5)->move(TP,1);
		
        	QH_QUEST_COMPLETED(TP,"jail_pris_quest");
		
	
	size = "You feel enlightened.";
	if (TP->query_stat(SS_DIS) > 50) size = "You feel somewhat enlightened.";
	if (TP->query_stat(SS_DIS) > 100) size = "You feel slightly enlightened.";
	if (TP->query_stat(SS_DIS) > 130) size = "You feel a tinge enlightened.";
	if (TP->query_stat(SS_DIS) > 160) size = "You feel you gained something.";
	
	TP->catch_msg(size);
	TP->remove_prop(ZARTH_FIRST_PART);
	TP->remove_prop(ZARTH_SECOND_PART);
	TP->remove_prop(DALE_SPEAK_DONE);
	TP->remove_prop(DALE_QUEST_COMPLETE);
	TP->remove_prop(THE_ROPE);
	TP->remove_prop(DALE_KEY_GIVEN);
	TP->remove_prop(_IS_KEY_);
	TP->remove_prop(ROPE_WALL);
	return "";
	}
}		
		
public void
enter_inv(object ob, object from)
{      	
   	::enter_inv(ob,from);

    	if (!from) return;

    	if (ob->query_prop(THE_ROPE))    	
        	set_alarm(1.0, 0.0, "got_rope", ob, from);
   	else
        	set_alarm(1.0, 0.0, "got_else", ob, from);
}


void
got_rope(object ob, object from)                  
{   
    	if (!interactive(from))
        	return;
   
        set_this_player(from);
        
        if (TP->query_prop(ZARTH_FIRST_PART))
      	{
      		command("drop "+ob->query_name());
      		command("say Now here is the plan.");
      		command("say Take the rope and climb this wall.");
      		command("say Clear a path for Dale.");
      		command("say And bring him to me.");
      		command("say Just get him to 'follow' you.");
        	from->add_prop(ZARTH_SECOND_PART, 1);           	
    	}    	
    	else
	{
		set_alarm(1.0, 0.0, "got_else", ob, from);
	}      
}

void
got_else(object ob, object from)
{
    	command("say What is this?");
    	command("drop "+ob->query_name());
}

void
attacked_by(object ob)
{	
	::attacked_by(ob);
	
	if ((!can_see_in_room())&& TO->query_weapon(W_LEFT))
	{ 
		command("say What you think darkness will help you?");
		command("rub symbols");
		command("cackle");
    	}    
	else
	{
		command("say Attack me will you!");
	}	  
	command("' Guards attack!");	
	environment(this_object()) -> jalla_func();
	environment(this_object())-> jalla_func2(ob);	
	environment(this_object())-> jalla_func6(ob);	
}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc=-1)
{
	if ((query_hp()< 1600) && (!z) && TO->query_weapon(W_LEFT))
	{
		z = 1;
		command("' You think your tuff do you!");
		command("shout Lancers get in here!");	
		if ((!can_see_in_room()) && TO->query_weapon(W_LEFT))
		{ 
		command("shout Someone go get me a mind reaper!");
		command("rub symbols");
		set_alarm(10.0, 0.0, "get_reaper", attacker);	
    		} 
    		if (TO->query_weapon(W_LEFT))
		{
		environment(this_object())-> jalla_func3();
		environment(this_object())-> jalla_func4(attacker);
		}	
	}
		
	return ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
}

void
get_reaper(object attacker)
{
    	environment(this_object())-> jalla_func5();
	environment(this_object())-> jalla_func6(attacker);
}	