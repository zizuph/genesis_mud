/* 
 * 
 * The Innkeeper at The Foaming Mug, in Waymeet.
 * Cloned by /d/Shire/eastroad/foam_mug.c
 *
 * Barrowed for the Upstairs Bar at the Foaming mug
 * /d/Shire/eastroad/foam_mug_up.cab
 *
 *  Questmaster for /d/Shire/private/QUESTS/fix_still.txt
 * Raymundo, 2020
 */


#include "/d/Shire/sys/defs.h"
#include "/d/Shire/waymeet/defs.h"
#include "/d/Shire/eastroad/western/local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/std/monster";

//All of the defines here are for the quest.
#define QBIT	"_i_have_test_qbit"
#define PIPE_1	"_i_delivered_pipe_1"
#define PIPE_2	"_i_delivered_pipe_2"
#define PIPE_3	"_i_delivered_pipe_3"
#define CONE	"_i_delivered_cone"
#define NOZZLE	"_i_delivered_nozzle"


void return_introduce();
void greet(object ob);



create_monster()
{
	if (!IS_CLONE)
		return;

	set_name("imbert");
	add_name(({"bartender", "_foaming_mug_bartender_"}));
	set_title("Bartender of the Foaming Mug Private Lounge");
	set_race_name("hobbit");
	set_adj(({"dapper", "mustachioed"}));
	set_long(
		"This dapper hobbit has quite an impressive mustache. He stands "
		+ "ready to mix drinks or hand out menus as needed.\n");
	default_config_npc(30);
	set_base_stat(SS_DIS, 40);
	set_base_stat(SS_DEX, 40);
	set_base_stat(SS_CON, 120);

	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_DEFENCE, 30);
	set_skill(SS_AWARENESS, 20);
	set_alignment(200 + random(50));

	add_prop(CONT_I_WEIGHT, 60*1000); //100 Kg's.
	add_prop(CONT_I_HEIGHT, 100);		//170 cm tall.
	remove_prop(NPC_M_NO_ACCEPT_GIVE);
	
	set_act_time(100);
	add_act("smile");
	add_act("emote twists his mustahce.");
	add_act("emote straightens the menus.");
	add_act("emote carefully arranges the bottles behind the bar.");
	add_act("emote smiles at you.");
	add_act("say What can I get you to drink?");
	add_act("say You know, I could use a favor.");
	add_act("emote looks at the still and sniffles.");
	add_act("emote worries about his still.");
	add_act("mstroke");
	add_act("mtwist");
	

	add_ask(({"favor", "task", "quest"}), "@@ask_quest@@");
	add_ask( ({"still", "pot still"}), "@@ask_still@@");
	add_ask( ({"cone", "metal cone"}), "@@ask_cone@@");
	add_ask( ({"pipe", "pipes"}), "@@ask_pipe@@");
	add_ask( "ogee", "@@ask_ogee@@");
	add_ask( ({"arm", "lyne", "lyne arm"}), "@@ask_lyne_arm@@");
	add_ask( "nozzle", "@@ask_nozzle@@");
	add_ask("joint", "@@ask_joint@@");
    add_ask( ({"parts", "pieces", "parts left", "pieces left", "turned in", "progress"}),
        "@@ask_progress@@");
	
	add_ask( ({"menu", "pricelist", "for a menu", "for a pricelist"}),
		"@@ask_menu@@");
		
		
	add_ask( ({"moustache", "mustache"}), "@@ask_moustache@@");
	add_ask("beard", "@@ask_beard@@");
	add_ask( ({"martini", "gin"}), "@@ask_martini@@");
	add_ask("liquor", "@@ask_liquor@@");
	
	set_default_answer("@@ask_default@@");
	
	equip(EAST_R_DIR + "arm/fake_moustache.c");
	
}

init_living() 
{
   ::init_living();
   if (interactive(this_player()))
   {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}

//If you've returned everything, you get a reward.
void
check_reward()
{
	if(CHECK_QUEST(TP, "fix_still"))
	{
		command("say You've already fixed the still, though!");
		return;
	}
	if(TP->query_prop(CONE) && TP->query_prop(PIPE_1) && TP->query_prop(PIPE_2) && TP->query_prop(PIPE_3) && TP->query_prop(NOZZLE))
	{
		command("say Thanks for all the help!\n");
		command("say I can distill a proper bit of liquor now.");
		command("say You know, I can make you some more drinks now if you'd like a menu.");
		TP->remove_prop(CONE);
		TP->remove_prop(PIPE_1);
		TP->remove_prop(PIPE_2);
		TP->remove_prop(PIPE_3);
		TP->remove_prop(NOZZLE);
		TP->add_prop(QBIT, 1);
		REWARD_QUEST(TP, "fix_still");
		write("You feel more experienced!\n");
		say(QCTNAME(TP) + " looks more experienced!\n");
		return;
	}
	else //Lets you know you're not done yet.
	{
		command("say I do need a few more pieces to the still though.");
		return;
	}
}

//returning the object
public void
enter_inv(object obj, object from)
{
	::enter_inv(obj, from);
	if(CHECK_QUEST(TP, "fix_still"))
	{
		//Making sure the other emotes work. Don't want this messing up other functions.
		if(obj->id("moustache") | obj->id("martini") | obj->id("menu") | obj->id("toothpick") | obj->id("olives") | obj->id("olive"))
		{
	
			return;
		}
		else
		{
			command("say You've already helped me! Just ask for a menu.");
			command("wink drunk");
			command("drop " + obj->query_short());
			return;
		}
	}
	if(obj->id("_still_quest_1"))
	{
		if(TP->query_prop(CONE))
		{
			command("say Thanks, but you've already given me the "
				+ obj->query_short() + ".");
			command("say But there are more parts to the still...");
			command("drop " + obj->query_short());
			return ;
		}
		else
		{
			command("say Thank you so much!");
			command("say I really needed this " + obj->query_short()+ ".");
			command("smile");

			TP->add_prop(CONE, 1);
			check_reward();
			obj->remove_object();
		
			return;
		}
	}
	if(obj->id("_still_quest_2"))
	{
		if(TP->query_prop(PIPE_1))
		{
			command("say Thanks, but you've already given me the "
				+ obj->query_short() + ".");
			command("say But there are more parts to the still...");
			command("drop " + obj->query_short());
			return ;
		}
		else
		{
			command("say Thank you so much!");
			command("say I really needed this " + obj->query_short()+ ".");
			command("smile");

			TP->add_prop(PIPE_1, 1);
			check_reward();
			obj->remove_object();
			return;
		}
	}
	if(obj->id("_still_quest_3"))
	{
		if(TP->query_prop(PIPE_2))
		{
			command("say Thanks, but you've already given me the "
				+ obj->query_short() + ".");
			command("say But there are more parts to the still...");
			command("drop " + obj->query_short());
			return ;
		}
		else
		{
			command("say Thank you so much!");
			command("say I really needed this " + obj->query_short()+ ".");
			command("smile");

			TP->add_prop(PIPE_2, 1);
			check_reward();
			obj->remove_object();
			return;
		}
	}
	if(obj->id("_still_quest_4"))
	{
		if(TP->query_prop(PIPE_3))
		{
			command("say Thanks, but you've already given me the "
				+ obj->query_short() + ".");
			command("say But there are more parts to the still...");
			command("drop " + obj->query_short());
			return ;
		}
		else
		{
			command("say Thank you so much!");
			command("say I really needed this " + obj->query_short()+ ".");
			command("smile");

			TP->add_prop(PIPE_3, 1);
			check_reward();
			obj->remove_object();
			return;
		}
	}
	if(obj->id("_still_quest_5"))
	{
		if(TP->query_prop(NOZZLE))
		{
			command("say Thanks, but you've already given me the "
				+ obj->query_short() + ".");
			command("say But there are more parts to the still...");
			command("drop " + obj->query_short());
			return ;
		}
		else
		{
			command("say Thank you so much!");
			command("say I really needed this " + obj->query_short()+ ".");
			command("smile");

			TP->add_prop(NOZZLE, 1);
			check_reward();
			obj->remove_object();
			return;
		}
	}
	//Again, This is here so as to preserve other functions. 
	if(obj->id("moustache") | obj->id("martini") | obj->id("menu") | obj->id("toothpick") | obj->id("olives") | obj->id("olive"))
	{
	
		return;
	}
	else
	{
		command("say I'm not sure what this is! I dont need it though.");
		command("say Thanks though!");
		command("drop " + obj->query_short());
	}
	
}
// Making sure the hobbit introduces itself like a nice boy.
void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say to " + ob->query_real_name() + 
   " Welcome to the upstairs bar! Please ask if you'd like to "
   + "see a menu.");
}

int
add_introduced(string who)
{
   object ob;
   
   if (!who) return 0;
   who = lower_case(who);
   ob = present(who, environment());
   if (!ob) return 0;
   if (!CAN_SEE(this_object(), ob)) return 0;
   if (!notmet_me(ob))
   {
	   command("say to " + TP->query_real_name() 
		+ " So nice to see you again!");
	   return 0;
   }
   
   set_alarm(itof(random(9)),0.0,&return_introduce());
   return 1;
}

void
return_introduce()
{
   command("introduce myself");
}

//Questions and Answers
void
ask_default()
{
	if(CHECK_QUEST(TP, "fix_still"))
	{
		command("say Oh, I'm not sure about that, but I do have a menu "
			+ "if you'd like to order a drink!");
		command("smile .");
		return;
	}
	else
	{
		command("say I could use some help with a favor, if you're not "
			+ "too busy. Of course, this is a bar, and I'd be happy to "
			+ "get you a menu if you're thirsty. We make a great "
			+ "martini!");
		command("smile help");
		return;
	}
}

//He whispers because you get a different answer depending on whether or
//not you've done the quest.
void
ask_liquor()
{
	if(CHECK_QUEST(TP, "fix_still"))
	{
		command("whisper to " + TP->query_real_name() 
			+ " We have many kinds of liquor. Ask for a "
			+ "menu and order whatever you'd like!");
		return;
	}
	else
	{
		command("whisper to " + TP->query_real_name() 
			+ " Once the still is fixed, we'll be able "
			+ "to distill some liquors.");
		return;
	}
}

//Showing off the toothpick in the martini for the observant.
void
ask_martini()
{
	object martini;
	object toothpick;
	martini = clone_object(EAST_R_DIR + "supplies/martini");
	martini->move(TO);
	command("say The trick to a good martini is good gin.");
	command("lick");
	command("say That's why the juniper berries we gather are so "
		+ "important.");
	command("show martini");
	command("get olives from martini");
	command("eat olives");
	command("say Of course, olives are important too.");
	command("discard toothpick");
	command("drink martini");
	command("say Damn, that's good!");
	return;
}

void
ask_beard()
{
	command("say Hobbits can't grow beards. We're not dwarves!");
	return ;
}
//I love the mustache. It's sexy.
void
ask_moustache()
{
	command("say Look.. I know...");
	command("mtwist");
	command("say Hobbits don't normally grow moustaches.");
	command("remove moustache");
	command("show full mustache");
	command("wear moustache");
	command("say But it drives the girls wild!");
	command("wink sugges");
	return;
}


//gives the player a menu

void
ask_menu()
{	
	if(TP->query_prop(OBJ_I_HIDE) || TP->query_prop(OBJ_I_INVIS) || TP->query_invis() || (!CAN_SEE(TO, TP)))
	{
		command("say Who's there? I can't see a thing!\n");
		command("peer");
		return;
	}
	if(CHECK_QUEST(TP, "fix_still"))
	{
		command("say Oh, wecome back!");
		command("bow to" + TP->query_real_name());
		object special_menu;
		special_menu = clone_object(EAST_R_DIR + "supplies/special_menu");
		special_menu->move(TO);
		command("say Here is a menu for you!");
		command("give menu to " + TP->query_real_name());
		return;
	}
	if(TP->query_wiz_level())
	{
		command("say Oh, your majesty, your most esteemed greatness and "
			+ "creator of all life on the Donut.");
		command("govel " + TP->query_real_name());
		command("say Please accept my oh so very most humble (humblest!) "
			+ "skills as a bartender. Order anything I pray you and I shall "
			+ "do my utmost to please!");
		object special_menu;
		special_menu = clone_object(EAST_R_DIR + "supplies/special_menu");
		special_menu->move(TO);
		command("say Here is a menu for you!");
		command("give menu to " + TP->query_real_name());
		command("grovel " + TP->query_real_name());
		return;
	}
	else
	{
		command("say Welcome! Welcome!");
		command("say We are, as you can see, a very small establishment.");
		command("bow " + TP->query_real_name());
		command("say At the moment, I have a limited drink menu for you...");
		command("peer caref");
		command("say But... if you could maybe do me a favor...");
		command("gesture .");
		object reg_menu;
		reg_menu = clone_object(EAST_R_DIR + "supplies/reg_menu");
		reg_menu->move(TO);
		command("say I may have something... more for you.");
		command("give menu to " + TP->query_real_name());
		command("say Please don't hesitate to order anything on the menu. "
			+ "Anything at all!\n");
		command("emote fidgets with his mustache.");
		return;
	}
}

//begins quest chain
void
ask_quest()
{
	if(CHECK_QUEST(TP, "fix_still"))
	{
		command("say Thank you so much for your help. We wouldn't be "
			+ "in business without you!");
		command("hug " + TP->query_real_name());
		return;
	}
	else
	{
		command("point still");
		command("cry");
		command("wail");
		command("emote cries even more!");
		command("say My poor still... You can ask me about it if you really want to help.");
	}
		
}

//condition of the still & quest
void
ask_still()
{
		if(TP->query_prop(OBJ_I_HIDE) || TP->query_prop(OBJ_I_INVIS) || TP->query_invis() || (!CAN_SEE(TO, TP)))
	{
		command("say Who's there? I can't see a thing!\n");
		command("peer");
		return;
	}
	if(CHECK_QUEST(TP, "fix_still"))
	{
		command("whisper to " + TP->query_real_name() + " Thank you so much "
			+ "for fixing the still! We can make our premium liquors now! ");
		command("applaud " + TP->query_real_name());
		command("whisper to " + TP->query_real_name() + " Please grab a "
			+ "menu and order something.");
		command("smile at " + TP->query_real_name());
		return;
	}
	else
	{
		command("whisper to " + TP->query_real_name() + " We bought this "
			+ "inn thinking we could make a good living selling liquor. We "
			+ "knew there was a still upstairs. But when we got here, it was "
			+ "broken!");
		command("cry");
		command("whisper to " + TP->query_real_name() + " We're missing "
			+ "the metal cone for the top of the still, three copper pipes and "
			+ "a copper nozzle. If you could find them for us, it "
			+ "would mean the world!");
		command("smile hope");
		return;
	}
}
	
//Each of the following gives a hint as to where you can find the 
//missing object. 
void
ask_cone()
{
	command("say I don't know where it could have gone! Actually, that was "
		+ "here when we bought the place.");
	command("sigh");
	command("say But then elves came in and got WAY too drunk on the "
		+ "elven ice wine downstairs...");
	command("emote shakes his head.");
	command("say And in the morning, it was gone! They took the cone! Of course, "
		+ "they also puked all over the floor downstairs, so who knows what "
		+ "they ended up doing.");
	command("grumble");
	command("say Anyway, the bottom should be big enough to fit on a pot, and "
		+ "the top small enough for a pipe. It's copper. If you find it, please "
		+ "bring it back!");
}

void
ask_pipe()
{
	command("say Oh, it's dreadful. Simply dreadful! I'm not sure how much "
		+ "it'll cost to have them replaced.");
	command("say We lost an ogee, a lyne arm, and a joint.");
	command("say And we can't distill anything new until we get them back!");
	command("worry");
	return;
}

void
ask_ogee()
{
	command("say The ogee?");
	command("think");
	command("say It looks like a big onion, kindof. But copper. And shiny.");
	command("say It's all very complicated, but it helps with distillation.");
	command("say The worst part of it is, whoever took it probably doesn't know "
		+ "what it is! They probably just stuck it away in a cellar or "
		+ "drawer or closet or something.");
	command("grumble");
	return;
}

void
ask_nozzle()
{
	command("emote screams in frustration.");
	command("say I'm so frustrated with this! Some idiot hobbit probably "
		+ "took my nice copper nozzle and used it to stop up their sink "
		+ "or something! Why can't they use a drain plug like everyone "
		+ "else?");
	command("frown");
	return;
}

void
ask_lyne_arm()
{
	command("emote looks depressed.");
	command("say Why take the lyne arm? What're you going to do with it?");
	command("boggle");
	command("say The idiots probably stashed it in an attic somewhere "
		+ "or used it for a weathervane or something.");
	command("grumble");
	return;
}

void
ask_joint()
{
	command("say It's not much to look at really.");
	command("emote holds his fingers about 3 inches apart.");
	command("say Some idiot probably took it and then didn't realize what "
		+ "it's for.");
	command("say I bet it's just sitting around in someone's cellar.");
}

void
ask_progress()
{

    if(CHECK_QUEST(TP, "fix_still"))
    {
        command("say You don't have anything left to find. The still is "
            + "working now! Thanks!");
        command("bounce");
        return;
    }
    if(!TP->query_prop(PIPE_1))
    {
        command("say I still need an ogee to fix the still.");
        return;
    }
    if(!TP->query_prop(PIPE_2))
    {
        command("say I still need a lyne arm to fix the still.");
        return;
    }
    if(!TP->query_prop(PIPE_3))
    {
        command("emote thinks for a moment.");
        command("say I really need a pipe joint for the still.");
        return;
    }
    if(!TP->query_prop(CONE))
    {
        command("say We need the cone back. Who steals a cone?");
        command("emote goes ugh!");
        return;
    }
    if(!TP->query_prop(NOZZLE))
    {
        command("say You know what? I need a nozzle.");
        command("say Otherwise all the liquid will run out of the still and "
            + "onto the floor! That's a mess!");
            return;
    }
    else
    {
        command("say You've given me everything already. Thanks!");
    return;
    }
}
   
   