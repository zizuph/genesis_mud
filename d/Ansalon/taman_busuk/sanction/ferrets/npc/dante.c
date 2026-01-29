/*
 * dante.c
 * Young boy in the ferret shack in the city of Sanction. 
 * Has a quest to find seven names of long dead ferrets.
 * 
 * Ares, July 2004
 *
 */

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/ferrets/defs.h"
#pragma strict_types


inherit "/d/Krynn/std/monster";
inherit "/d/Ansalon/common/cheater";
inherit "/d/Krynn/std/act/gift";
inherit "/d/Krynn/std/equip.c";

#define GOT_QUEST_ROCK "_i_found_rock"  
#define GOT_QUEST_COFFIN "_i_found_coffin"
#define GOT_QUEST_PAPER1 "_i_found_paper1"
#define GOT_QUEST_PAPER2 "_i_found_paper2"
#define GOT_QUEST_SHINY_OBJECT "_i_found_shinyobject"
#define GOT_QUEST_TAG "_i_found_tag"
#define GOT_QUEST_OLD_PAPER "_i_found_oldpaper"
#define GOT_A_TAG "_i_got_tag"
#define XP_VALUE 5000

void calculate_experience(object who);
void remove_quest_props(object who);
int got_rock(object what, object who);
int got_coffin(object what, object who);
int got_oldpaper(object what, object who);
int got_paper1(object what, object who);
int got_shinyobject(object what, object who);
int got_ferrettag(object what, object who);
int calculate_experience(object who);
int remove_quest_props(object who);

public void
 enter_inv(object ob, object from)
 {
    ::enter_inv(ob, from);
    recieve_gift(ob, from);
 }





void
create_krynn_monster()
{
    set_name("dante");
    set_race_name("human");
    set_living_name("dante");
    set_adj("young");
    add_adj("scraggly");
    set_gender(G_MALE);
    set_long("A young boy in Sanction? Must have a very protective relative. \n");
    set_stats(({22,22,22,22,22,22}));
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_all_hitloc_unarmed(10);
    set_act_time(9);
    add_act("say I wish my grandpa would stop yelling at me.");
    add_act("say I can't wait until I get to play with the ferrets again!");
    add_act("emote sweeps the room with an old broom.");
    add_act("emote stares at the weapons on the walls for a moment, lost in thought.");
    add_act("say Scabbers got lost the other day but I found him in the pile of wood "+
        "in the kitchen.");
    add_act("emote takes a break from cleaning and lays down on the ground "+
        "to draw pictures on a pad of paper.");
    
    add_ask(({" [about] 'quest'","quest", "quests", "task", "tasks"}), "say A quest? "
	+"I wish I could go on a quest some day! One where I could climb tall mountains "
	+"and fight on top of dragons! I do think I have one thing you could help. Ferrets.",1);
    add_ask(({" [about] 'ferrets'", "ferrets", "ferret"}), "say Oh I love them! My grandpa "
	+"loves them too!",1);
    add_ask(" [about] 'grandpa'", "say He yells at me a lot, but he loves me. "+
       "He's very forgetful. His birthday is coming up and I'm going to draw him "+
       "a picture of all his favourite ferrets! I just need their names...",1);
    add_ask(" [about] 'names'", "say The names of his favourite ferrets!  He can't "+
       "remember all of them. He yells at me when I ask about them. It'd be so nice "
	   +"to be able to draw him those pictures. Maybe you can find their names for me?",1);
    add_ask(" [about] 'birthday'", "say Grandpa's birthday is next week! "+
       "I'm drawing him pictures of his lost ferrets! But I need to "+
       "know what to name them. Can you find out what their names are "+
       "for me?",1);
    
    add_gift("_quest_rock_", got_rock);
    add_gift("_quest_old_paper_", got_oldpaper);
    add_gift("_quest_coffin_", got_coffin);
    add_gift("_quest_paper_", got_paper1);
    add_gift("_quest_shiny_object_", got_shinyobject);
    add_gift("_silver_ferret_tag_", got_ferrettag);
    
    set_introduce(1);

}

int
got_rock(object what, object from)
{
    
    if (TP->query_prop(GOT_QUEST_OLD_PAPER)&& TP->query_prop(GOT_QUEST_COFFIN) 
	&& TP->query_prop(GOT_QUEST_PAPER1) && TP->query_prop(GOT_QUEST_PAPER2)
	&& TP->query_prop(GOT_QUEST_SHINY_OBJECT) && TP->query_prop(GOT_QUEST_TAG))
	{
		command("emote looks at the gravestone and reads the name on it.");
		command("say George! I cannot believe he could forget the name George! "+
        "Thank you for showing this to me, I'll make sure to tell him!");
		TP->add_prop(GOT_QUEST_ROCK, 1);
		what->remove_object();
		calculate_experience(TP);
		remove_quest_props(TP);
		return 1;
	}
	else
		command("emote looks at the gravestone and reads the name on it.");
		command("say George! I cannot believe he could forget the name George! "+
        "Thank you for showing this to me, I'll make sure to tell him!");
        TP->add_prop(GOT_QUEST_ROCK, 1);
		what->remove_object();
		return 1;
}

int
got_oldpaper(object what, object from)
{
    
    if (TP->query_prop(GOT_QUEST_ROCK) && TP->query_prop(GOT_QUEST_TAG) 
    && TP->query_prop(GOT_QUEST_COFFIN) && TP->query_prop(GOT_QUEST_PAPER1) 
    && TP->query_prop(GOT_QUEST_PAPER2) && TP->query_prop(GOT_QUEST_SHINY_OBJECT))
    {
		command("emote takes the paper and reads the name.");
		command("say Skedar! He used to have a dog named Skedar Two! It all makes sense!");
		what->remove_object();
		TP->add_prop(GOT_QUEST_OLD_PAPER, 1);
		calculate_experience(TP);
		remove_quest_props(TP);
		return 1;
	}
	else
		command("emote takes the paper and reads the name.");
		command("say Skedar! He used to have a dog named Skedar Two! It all makes sense!");
       
		TP->add_prop(GOT_QUEST_OLD_PAPER, 1);
		what->remove_object();
		return 1;
}

int
got_coffin(object what, object from)
{
    if (TP->query_prop(GOT_QUEST_ROCK) && TP->query_prop(GOT_QUEST_OLD_PAPER) 
    && TP->query_prop(GOT_QUEST_PAPER1) && TP->query_prop(GOT_QUEST_PAPER2)
    && TP->query_prop(GOT_QUEST_SHINY_OBJECT) && TP->query_prop(GOT_QUEST_TAG))
	{
		command("emote reluctantly opens the coffin.");
		command("say Ick, it smells aweful!");
		command("emote reads the name on the coffin.");
		command("say Ixi.");
		command("frown");
		command("drop coffin");
		TP->add_prop(GOT_QUEST_COFFIN, 1);
		calculate_experience(TP);
		remove_quest_props(TP);
		return 1;
	}
	else
		command("emote reluctantly opens the coffin.");
		command("say Ick, it smells aweful!");
		command("emote reads the name on the coffin.");
		command("say Ixi.");
		command("frown");
		command("drop coffin");
    
		TP->add_prop(GOT_QUEST_COFFIN, 1);
		return 1;
}

int
got_paper1(object what, object from)
{
      if (what->query_ferret_name() == "LILLY")

    {
        if (TP->query_prop(GOT_QUEST_ROCK) && TP->query_prop(GOT_QUEST_OLD_PAPER) 
		&& TP->query_prop(GOT_QUEST_COFFIN) && TP->query_prop(GOT_QUEST_PAPER2) 
	    && TP->query_prop(GOT_QUEST_SHINY_OBJECT) && TP->query_prop(GOT_QUEST_TAG))
	{
		command("emote reads the name on the paper.");
        command("say Lilly, I think I remember Grandpa talking about Lilly "+
        "a long time ago! Thank you!");
		what->remove_object();
		TP->add_prop(GOT_QUEST_PAPER1, 1);
		calculate_experience(TP);
		remove_quest_props(TP);
		return 1;
	}
	else
		command("emote reads the name on the paper.");
        command("say Lilly, I think I remember Grandpa talking about Lilly "+
        "a long time ago! Thank you!");
        
        TP->add_prop(GOT_QUEST_PAPER1, 1);
        what->remove_object();
		return 1;
    }
    
    if (what->query_ferret_name() == "ELMANTIA")
    {
        
        if (TP->query_prop(GOT_QUEST_ROCK) && TP->query_prop(GOT_QUEST_OLD_PAPER) 
		&& TP->query_prop(GOT_QUEST_COFFIN) && TP->query_prop(GOT_QUEST_PAPER1) 
		&& TP->query_prop(GOT_QUEST_SHINY_OBJECT) && TP->query_prop(GOT_QUEST_TAG))
	{
		command("emote reads the name on the paper.");
        command("say Elmantia, that sure is a girly name. Thank you so much! "+
        "I wonder where did my Grandpa came up with such a name?");
        command("smile curious");
		what->remove_object();
		TP->add_prop(GOT_QUEST_PAPER2, 1);
		calculate_experience(TP);
		remove_quest_props(TP);
		return 1;
	}
	else
		command("emote reads the name on the paper.");
        command("say Elmantia, that sure is a girly name. Thank you so much! "+
        "I wonder where did my Grandpa came up with such a name?");
        command("smile curious");
       
        TP->add_prop(GOT_QUEST_PAPER2, 1);
        what->remove_object();
		return 1;
    }
    
        command("emote reads the name on the paper.");
        command("say He talks about that ferret all the time!");
        command("say I better keep these, Grandpa might need them.");
        what->remove_object();
    return 1;      
}

int
got_shinyobject(object what, object from)
{
    if (TP->query_prop(GOT_QUEST_ROCK) && TP->query_prop(GOT_QUEST_OLD_PAPER) 
    && TP->query_prop(GOT_QUEST_COFFIN) && TP->query_prop(GOT_QUEST_PAPER1) 
    && TP->query_prop(GOT_QUEST_PAPER2) && TP->query_prop(GOT_QUEST_TAG))
	{
		command("emote flips the ferret tag over and reads the name.");
		command("say Trilob? That's a strange name. Where did you find this? "+
		"Oh well, he'll be happy you were able to get it.");
		what->remove_object();
		TP->add_prop(GOT_QUEST_SHINY_OBJECT, 1);
		calculate_experience(TP);
		remove_quest_props(TP);
		return 1;
	}
	else
		command("emote flips the ferret tag over and reads the name.");
		command("say Trilob? That's a strange name. Where did you find this? "+
		"Oh well, he'll be happy you were able to get it.");
  
		TP->add_prop(GOT_QUEST_SHINY_OBJECT, 1);
		what->remove_object();
		return 1;
}

int
got_ferrettag(object what, object from)
{
    if (TP->query_prop(GOT_QUEST_ROCK) && TP->query_prop(GOT_QUEST_OLD_PAPER) 
    && TP->query_prop(GOT_QUEST_COFFIN) && TP->query_prop(GOT_QUEST_PAPER1) 
    && TP->query_prop(GOT_QUEST_PAPER2) && TP->query_prop(GOT_QUEST_SHINY_OBJECT))
	{
		command("emote reads the name on the tag.");
		command("say A ferret named Trouble? Well they sure are a lot of "+
		"trouble when they're loose! They get lost so easily! Thank you for "+
		"finding this!");
		what->remove_object();
		TP->add_prop(GOT_QUEST_TAG, 1);
		calculate_experience(TP);
		remove_quest_props(TP);
		return 1;
	}
	else
    command("emote reads the name on the tag.");
	command("say A ferret named Trouble? Well they sure are a lot of "+
    "trouble when they're loose! They get lost so easily! Thank you for "+
    "finding this!");
    TP->add_prop(GOT_QUEST_TAG, 1);
    what->remove_object();
		return 1;
}

void
calculate_experience(object who)
{
   int xp_base = 2500;

   if(who->test_bit("ansalon", 0, 5))
   {
      who->catch_msg("\nThere is no experience the second time you " +
                     "solve this quest.\n");
      return;
   }
   
    if (TP->query_prop(GOT_QUEST_ROCK) && TP->query_prop(GOT_QUEST_OLD_PAPER) 
    && TP->query_prop(GOT_QUEST_COFFIN) && TP->query_prop(GOT_QUEST_PAPER1) 
    && TP->query_prop(GOT_QUEST_PAPER2) && TP->query_prop(GOT_QUEST_SHINY_OBJECT)
    && TP->query_prop(GOT_QUEST_TAG))
	{
   
    command ("emote cheers loudly!");
	command ("say You are awesome! This will make the best birthday present ever");
	who->catch_msg("\nYou feel more experienced.\n");
    tell_room(E(who), QCTNAME(who) + " looks more experienced.\n", who);

   
    who->add_exp_quest(xp_base);
    who->set_bit(0, 5);                               

    A_QUEST_LOG("quest", "Ferret Name Quest", who, xp_base);
    }
}


void
remove_quest_props(object who)
{
   if(who->query_prop(GOT_QUEST_ROCK))
      who->remove_prop(GOT_QUEST_ROCK);
      
   if(who->query_prop(GOT_QUEST_OLD_PAPER))
      who->remove_prop(GOT_QUEST_OLD_PAPER);

   if(who->query_prop(GOT_QUEST_COFFIN))
      who->remove_prop(GOT_QUEST_COFFIN);

   if(who->query_prop(GOT_QUEST_PAPER1))
      who->remove_prop(GOT_QUEST_PAPER1);
      
   if(who->query_prop(GOT_QUEST_PAPER2))
      who->remove_prop(GOT_QUEST_PAPER2);

   if(who->query_prop(GOT_QUEST_SHINY_OBJECT))
      who->remove_prop(GOT_QUEST_SHINY_OBJECT);

   if(who->query_prop(GOT_QUEST_TAG))
       who->remove_prop(GOT_QUEST_TAG);
   
   if(who->query_prop(GOT_A_TAG))
       who->remove_prop(GOT_A_TAG);
}



