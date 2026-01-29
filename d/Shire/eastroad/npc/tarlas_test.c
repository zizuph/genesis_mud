/*
 * The Innkeeper at The Foaming Mug, in Waymeet.
 * Cloned by /d/Shire/eastroad/foam_mug.c
 *
 * There is a "pre-quest" here, where you have to pick
 * Juniper berries and give them to Tarlas. No qxp is
 * given. However, if you complete this task, you can
 * go up to /d/Shire/eastroad/western/foam_mug_up.c .
 *
 * Upstairs is a nicer bar and a chance at a real quest
 * that gives qxp. IF the quest upstairs has been
 * completed, the player can go upstairs without picking
 * Juniper Berries.
 *
 * --Raymundo, winter of 2020
 *
 * Cleaned up some of the dialogue to make things
 * flow a little easier
 *
 * Varian - July, 2020
 *
 * Made him introduce himself. Created an error message
 * if the player gives an herb directly to him instead
 * of using the jar.
 *
 * Raymundo, July 2020
 */

inherit "/std/monster";
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/waymeet/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define JUNIPER "_i_picked_juniper_berries"
#define NO_SERVE "_waymeet_no_serve_alcohol"

void return_introduce();
void greet(object ob);

object *inv;

create_monster()
{
	if (!IS_CLONE)
		return;

	set_name("tarlas");
	add_name(({"innkeeper", "_foaming_mug_innkeeper_"}));
	set_title("Innkeeper of the Foaming Mug");
	set_race_name("hobbit");
	set_adj(({"fat", "happy"}));
	set_long(
		"This merry hobbit stands behind the bar in the inn, "+
		"serving all the thirsty travellers.  He is wearing a dirty "+
		"apron, that he occasionally uses to polish glasses with.\n");
	default_config_npc(30);
	set_base_stat(SS_DIS, 40);
	set_base_stat(SS_DEX, 40);

	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_DEFENCE, 30);
	set_skill(SS_AWARENESS, 20);
	set_alignment(200 + random(50));

	add_prop(CONT_I_WEIGHT, 60*1000); //100 Kg's.
	add_prop(CONT_I_HEIGHT, 100);		//170 cm tall.
	remove_prop(NPC_M_NO_ACCEPT_GIVE);

	set_act_time(20);
	add_act("smile");
	add_act("emote polishes a glass with his apron.");
	add_act("laugh");
	add_act("emote carefully arranges the bottles behind the bar.");
	add_act("emote smiles at you.");
	add_act("say What can I get you to drink?");

	set_default_answer("@@ask_default@@");
	add_ask( ({"special", "specials"}), "@@ask_special@@");
	add_ask( ({"stairs", "upstairs"}), "@@query_upstairs@@");
	add_ask( "favor", "@@ask_favor@@");
	add_ask( "reward", "@@ask_reward");
	add_ask( "quest", "@@ask_quest");
    add_ask( ({"juniper", "juniper berry", "juniper berries", "berries", "berry"}),
        "@@ask_juniper@@");
}

/* Player interaction for introductions*/
init_living()
{
   ::init_living();
   if (interactive(this_player()))
   {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}

void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say to " + ob->query_real_name() +
   " Welcome to the Foaming Mug! Have you tried the special?");
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
		+ " Welcome back!");
	   return 0;
   }

   set_alarm(itof(random(9)),0.0,&return_introduce());
   return 1;
}

void
return_introduce()
{
   command("introduce myself");
   command("bow");
   command("say At your service!");
}
/* End introduction section*/

void
ask_quest()
{
	if(TP->query_prop(JUNIPER) | CHECK_QUEST(TP, "fix_still"))
	{
		command("say You've already helped me more than enough!");
		command("hug " + TP->query_real_name());
		command("thank " + TP->query_real_name());
		return;
	}
	else
	{
		command("say I don't have any quests...");
		command("say But I could use your help with a favor!");
		return;
	}
}

void
ask_juniper()
{
    command("say Juniper berries are what we use to make our gin.");
    command("emote sparkles his eyes brightly.");
    command("say The best ones grow near Waymeet, honestly.");
    command("say If you would do me a favor, I'd appreciate it.");
}

void
ask_reward()
{
    if(TP->query_prop(JUNIPER) | CHECK_QUEST(TP, "fix_still"))
    {
        command("say Reward? Well, you've done me a favor.");
        command("smile");
        command("say So your reward is getting to upstairs for a "
            + "drink!");
        return;
    }
    else
    {
        command("say If you're doing me that favor, you can just "
            + "give me the herb jar.");
        command("smile help");
        command("say If you're not doing me a favor, would you "
            + "consider please helping me out?");
        return;
    }
}

//What item is coming in?
public void
enter_inv(object obj, object from)
{
	::enter_inv(obj, from);


	if(obj->id("_still_herb_jar")) //this is the item.
	{
		if(TP->query_prop(JUNIPER) | CHECK_QUEST(TP, "fix_still"))
            //if you've already done the quest, we don't need it.
		{
		command("say Oh, you've already helped me! I don't need "
			+ "any more help from you. Head on upstairs and order a "
			+ "drink!");
		obj->move(TP);
		command("emote gives you back your jar.");
		return;
		}
		if(obj->query_jar_full() < 5) //uh oh, it's not full.
		{
			command("say There's not quite enough juniper berries in here yet.");
			if(obj->query_jar_full() == 0)
			{
				command("say You don't have any juniper berries in this jar!");
			}
			else if(obj->query_jar_full() == 1)
			{
				command("say You only have one juniper berry in here.");
			}
			else
			{
			command("say You only have " + obj->query_jar_full() + " juniper "
				+ "berries in here.");
			}
			obj->move(from);
			write("Tarlas gives you back your jar.\n");
            say("Tarlas gives the herb jar back to " + QCTNAME(TP) + ".\n");
			return;
		}
		if(obj->query_jar_full() >= 5) //success!
		{
			command("say Oh, thanks for the help!");
			TP->add_prop(JUNIPER, 1);
			command("say Why don't you head on up and check out the upstairs "
				+ "bar.\n");
			return;
		}
	}

	if(obj->id("juniper_berry"))
	{
		command("emote takes the berry from you but notices it is squished!");
		command("say Oh no! This always happens when juniper barries are " +
			"not kept in a jar! Please put them in the jar I gave you and " +
			"then just give me the jar itself.");
		obj->remove_object();
        return;
	}
	else
	{
		command("say I don't need this.");
		obj->move(environment(TO));
		command("emote drops the " + obj->query_short() + ".\n");
		return;
	}
}
//The favor you can do.
void
ask_favor()
{
	if(TP->query_prop(OBJ_I_HIDE) || TP->query_prop(OBJ_I_INVIS) || TP->query_invis() || (!CAN_SEE(TO, TP)))
	{
		command("say Who's there? I can't see a thing!\n");
		command("peer");
		return;
	}
	if(TP->query_prop(JUNIPER) | CHECK_QUEST(TP, "fix_still"))
	{
		command("say You've already helped me so much. Please, "
			+ "head on upstairs! Have one for me!");
		command("bow " + OB_NAME(TP));
		return;
	}
	else
	{
		object pouch;
		command("say Well, as you can see, we've been remodeling.");
		command("smile proud");
		command("say And I think I've found a real money-maker for "
			+ "the inn...");
		command("gesture .");
		command("say GIN! Have you had it? It's wonderful. The only problem "
			+ "is that you need juniper berries or it won't taste quite "
			+ "right.");
		command("say And.. umm...");
		command("blush");
		command("say I'm out.");
		command("say If you could go out and pick me some juniper berries, "
			+ "I'd be really thankful. I need five in order to have enough "
			+ "for the next batch.");
		command("emote writes your name on top of an empty herb jar.");

		pouch = clone_object(WAYM_OBJ_DIR + "still_herb_jar");
		pouch->move(TP);

		command("say Here, I put your name on this herb jar so you " +
			"don't lose it! Just fill it with five juniper berries and " +
			"return it to me. Thanks!\n");
			return;
	}
}

//Default answer to any question.
void
ask_default()
{
	command("say Oh, I don't know about that. But if you "
		+ "want, I can get you a drink. Otherwise, you could see "
		+ "about doing me a little favor.");
	command("twinkle");
}


//Can the player go upstairs?
void
query_upstairs()
{
	if(TP->query_prop(OBJ_I_HIDE) || TP->query_prop(OBJ_I_INVIS) || TP->query_invis() || (!CAN_SEE(TO, TP)))
	{
		command("say Who's there? I can't see a thing!\n");
		command("peer");
		return;
	}
	if(TP->query_prop(NO_SERVE))
	{
		command("say to " + TP->query_real_name() +
			" You puked all over down here. I don't think I'm going to "
			+ "let you go upstairs.");
		command("glare at " + TP->query_real_name());
		return;
	}
	if(TP->query_prop(JUNIPER) | CHECK_QUEST(TP, "fix_still"))
	{
		command("say Oh, you're so silly. Of course you can go upstairs. "
			+ "You were very helpful earlier!");
		return;
	}
	else
	{
		command("say The upstairs is only for people who have done me "
			+ "a bit of a favor.");
		command("smile slight");
		return ;
	}
}

//returns the daily specials.
void
ask_special()
{
	if(TP->query_prop(OBJ_I_HIDE) || TP->query_prop(OBJ_I_INVIS) || TP->query_invis() || (!CAN_SEE(TO, TP)))
	{
		command("say Who's there? I can't see a thing!\n");
		command("peer");
		return;
	}

	if(TP->query_race_name() == "dwarf")
	{
		command("say Well, right now what we have for special...");
		command("emote looks down at a piece of paper behind the bar.");
		command("say is a drink. You people seem to like this one, "
			+ "because it's strong. Lots of liquor in it.");
		command("wink .");
		command("say If you'd like it, you can always order the special.");
		return;
	}
	if(TP->query_race_name() == "human")
	{
		command("say We have a special right now. It's more for dwarves "
			+ "than humans, but you lot tend to drink yourselves blind "
			+ "often as not.");
		command("frown");
		command("whisper to " + (TP->query_real_name()) +
		" If you want it, you can order the special.\n");
		return;
	}
	else
	{
		command("whisper to " + (TP->query_real_name()) + " Look. Umm...");
		command("peer nervous");
		command("whisper to " + (TP->query_real_name()) +
			" This drink is... umm.. it's gross.");
		command("whisper to " + (TP->query_real_name()) +
			" We basically dump all the stuff behind "
			+ "the bar into a cup and stir it with a dirty spoon. It's "
			+ "really not good.");
		command("emote wrinkles his nose up in disgust.");
		command("whisper to " + (TP->query_real_name()) + " Its for dwarves. They don't care "
			+ "what it tasted like.");
		command("gesture expla");
		command("whisper to " + (TP->query_real_name()) +
			" If you want it, order the special. But "
			+ "really, you should order the elven wine. It's much nicer.\n");
		return;
	}
}
