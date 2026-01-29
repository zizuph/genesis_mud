/*
 *	/d/Gondor/minas/npc/hmaster.c
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP1 "/d/Gondor/common/wep/lsword"
#define ARM1 "/d/Gondor/common/arm/studl"

#define RAT_PRICE 18

#define LOG_FILE "/d/Gondor/log/rats"

public void
create_gondor_monster()
{
    set_living_name("tarannon");
    set_title("the Harbour Master of the Harlond");
    set_name("tarannon");
    add_name(({"master","harbour master"}));
    set_race_name("human");
    set_adj("grey-haired");
    set_adj("lean");
    set_long(BSN(
         "You see a lean, grey-haired man of dunadan descent. He is Tarannon, "
         + "by order of the Steward Master of the Harlond. It is his duty to " 
         + "look after the piers and the warehouses here at the Harlond, " 
         + "ordering repairs to be made, and distributing the space to store goods "
         + "among the merchants and captains trading here. "
         + "He might be able to provide you with a task if you ask him. "));
    default_config_npc(55 + random(10));
    set_base_stat(SS_CON, 75 + random(10));
    set_skill(SS_WEP_SWORD,  65);
    set_skill(SS_2H_COMBAT,  35);
    set_skill(SS_PARRY,      45);
    set_skill(SS_DEFENCE,    55);
    set_skill(SS_SNEAK,      53);
    set_skill(SS_AWARENESS,  55);
    set_alignment(400);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_chat_time(7);
    add_chat("These rats are a curse!");
    add_chat("I'll pay cash for every dead rat!");
    add_chat("The merchants keep pestering me about the vermin in the warehouses.");
    add_chat("Those rats be damned!");
    add_chat("I want those rats exterminated!");
    add_chat("The sea port of Minas Tirith is Pelargir, not the Harlond.");
    add_chat("I need help, if you are interested in a job, then ask me!");
    add_cchat("Alarm!");
    add_cchat("Help! I'm being attacked by a maniac!");
    add_cchat("Ok, come on, bastard! I'll beat you up badly!");
    add_cchat("We won't give in to the enemy, killing me won't help!");
    add_cchat("You won't get away with this!");
    add_cchat("You will regret this when you are lying in chains in the prison!");
    set_default_answer("I do not know what you are talking about!\n");
    add_ask(({"help","task","quest","job"}), VBFC_ME("task_inform"));
    add_ask(({"about help","about task","about quest","about job"}), VBFC_ME("task_inform"));
    add_ask(({"for help","for task","for quest","for job"}), VBFC_ME("task_inform"));
    add_ask(({"about ithilien","ithilien"}), VBFC_ME("ask_ithilien"));
    add_ask(({"about anduin","anduin","about cross","cross"}), VBFC_ME("cross_anduin"));
    add_ask(({"about edoras","about rohan","rohan","edoras"}), VBFC_ME("ask_rohan"));
    add_ask(({"about pelargir","pelargir"}), VBFC_ME("ask_pelargir"));
    add_ask(({"rat","rats","vermin"}), VBFC_ME("ask_rats"));
    add_ask(({"lebennin","about lebennin"}), VBFC_ME("ask_lebennin"));
    add_ask(({"about rat","about rats","about vermin"}), VBFC_ME("ask_rats"));

    set_equipment( ({ WEP1, ARM1, }) );
}

public void
add_introduced(string who)
{
    if (objectp(find_player(who)))
	set_alarm(2.0, 0.0, &command("introduce myself to " + who));
}

string
task_inform()
{
    if (TP->query_exp_title() != "novice" &&
	TP->query_exp_title() != "greenhorne" &&
	TP->query_exp_title() != "beginner" &&
	TP->query_exp_title() != "apprentice")
    {
	command("peer " + TP->query_real_name());
	command("say I don't have any tasks for you, I'm afraid!");
	return "";
    }
    command("say I need help killing those rats at the Harlond!");
    command("say I will pay for every corpse of a rat that you can bring me.");
    command("say I pay good cash!");
    return "";
}

void
remove_rat(object rat)
{
   rat->remove_object();
}

void
reward_player(object rat, object player)
{
   int price;
   
   seteuid(getuid());
   set_alarm(5.0, 0.0, &remove_rat(rat));

   switch (player->query_exp_title())
   {
   case "novice": 
       price = RAT_PRICE*4; 
       break;
   case "greenhorne": 
       price = RAT_PRICE*2; 
       break;
   case "beginner": 
       price = RAT_PRICE; 
       break;
   case "apprentice": 
       price = RAT_PRICE/2; 
       break;
   case "wizard": 
   default:
       price = 0; 
       break;
   }
   if (!price)
   {
      command("hmm");
      command("say Thanks, but I must admit, I'm a bit surprised!");
      command("say Why does " + LANG_ADDART(player->query_exp_title()) +
         " go around killing rats?");
      command("say I usually offer this job to poor devils ");
      command("say so they can earn some cash. ");
      command("say I will not pay you for this!");
      return;
   }
   MONEY_MAKE_CC(price)->move(TO);
   command("thank " + player->query_real_name());
   command("say Thank you very much for your help!");
   command("say Here is the promised reward, "+price+" copper coins.");
   command("give " + price + " copper coins to " + player->query_real_name());
}

void
return_item(object ob, object from)
{
   command("say What am I supposed to do with this?");
   if( (!present(from,ENV(TO))) || (ob->move(from)) )
   {
       ob->move(ENV(TO));
       command("emote drops "+LANG_ADDART(ob->query_name())+".");
   }
   else
   {
       write(process_string(QCTNAME(TO),1) + " gives you "+LANG_ADDART(ob->short())+".\n");
       say(QCTNAME(TO) + " gives "+LANG_ADDART(ob->short())+" to "+QTNAME(from)+".\n");
   }
}
   
public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if (!objectp(from) || !objectp(ob))
       return;
   if ((ob->id("corpse of rat") && from == TP))
       set_alarm(1.0, 0.0, &reward_player(ob, from));
   else if(ob->id("coin"))
       set_alarm(1.0, 0.0, 
		 &command("say Why, thank you! I could always use a little tip!"));
   else
       set_alarm(2.0, 0.0, &return_item(ob, from));
}

string
ask_ithilien()
{
   command("say Ithilien once was the garden of Gondor.");
   command("say It lies east of the Anduin, between the river " );
   command("say and the Ephel Duath, the Mountains of Shadow.");
   command("say Since the armies of the Evil One reign in Ithilien");
   command("say no one may enter cross the Anduin, save by ");
   command("say leave of the Steward.");
   return "";
}

string
cross_anduin()
{
   command("say The Anduin is the mightiest river in Middle Earth.");
   command("say It divides Gondor into two parts, Ithilien on the ");
   command("say eastern bank, and Anorien and the coastlands to the ");
   command("say There might be some ferries running across the river.");
   command("say Go to Hunthor in Minas Tirith, he might be able to help you.");
   return "";
}

string
ask_rohan()
{
   command("say Edoras is the capital of Rohan, the land of the Rohirrim.");
   command("say Since the times of Eorl the Young there has been ");
   command("say friendship between Gondor and Rohan!");
   command("say Rohan lies north of the Ered Nimrais, the White Mountains.");
   command("say From Minas Tirith, follow the road northward through Anorien.");
   command("say You will come to Firien Forest and the Mering Stream.");
   command("say That is the border between Gondor and Rohan.");
   return "";
}

string
ask_pelargir()
{
   command("say Pelargir is the sea port of Minas Tirith!");
   command("say It lies close to the mouths of the Anduin. ");
   return "";
}

string ask_rats()
{
   command("say I'll pay cash for rat corpses.");
   command("grin");
   command("say But of course you must bring me one before I can pay.");
   return "";
}

string 
ask_lebennin()
{
  command("say Lebennin is the land south of the White Mountains and west of the Anduin.");
  command("say Pelargir at the mouths of the Anduin is its capital.");
  command("say It is a fair land full of wildlife and herbs.");
  command("say From the Harlond, there is an ancient road running through Lebennin to Pelargir.");
  return "";
}
