
/*
*A fisher (quest vital)
*Joshua 95-02-04
*
*bugcheck: Napture
* Ckrik 9/2003 Changed to Earthsea intro lib
*/

inherit "/std/monster";
inherit "/d/Earthsea/lib/intro";
inherit "/d/Earthsea/lib/width_height";

#include "defs.h"
#include "/sys/macros.h"
#include <money.h>

#pragma strict_types      /* To make Quetzl happy! */
object solver;

void
create_monster()
{
   set_name(({"negel"}));
   add_name("fisher");
   set_short("tall old human");
   set_title("the Fisherman");
   set_race_name("human");
   set_adj(({"tall", "old"}));
   set_height("tall");
   set_width("skinny");
   set_gender(G_MALE);
   set_long("It seems that he contemplates his " +
      "younger years. Time hasn't been gentle to him. " +
      "You notice that the poor man has only one leg. \n");
   default_config_creature(50);
   set_alignment(100);
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   set_random_move(10);
   set_act_time(5);
   add_act("emote contemplates the gods whereabouts.");
   add_act("emote jumps around you with his one leg.");
   add_act("emote mutters: I am too old, too old... ");
   add_act("emote sighs.");
/* waiting for shark quest
   add_act("emote says: The shark took it...");
   add_act("emote says: Please, can you help me?");
*/
   
   add_ask(({"quest", "task", "help", "shark"}),VBFC_ME("shark"));
   add_ask(({"boat", "key"}), "I have lost my keys to the "+
      "boat...I don't remember...\n");   
}

string
shark()
{
  /*
   command("say The horrible white shark took my leg, and nearly " +
      "my life too.");
   set_alarm(3.0, 0.0, "shark1");
  */
  command("say I do not have a task for you right now, but I may shortly " +
	  "in the future.\n");

   return "";
}

string
shark1()
{
   command("say I have fought him " +
	   "all my life, but now I am too old... \n");
   command("say It's generally believed that the white shark is " +
	   "a wizard that transformed himself into "+
	   "animals too many times..."+
	   "until he forgot who he was and finally became " +
	   "one...\n");
   set_alarm(4.0, 0.0, "shark2");
}

string
shark2()
{
   command("moan");
   command("say To find the cursed shark, you must first somehow " +
	   "draw him to you. To ensure that he stays interested, " +
	   "you must sacrifice a magical item while you have " +
	   "his attention, else he will elude you.\n");
   tell_room(environment(TO), QCTNAME(TO) + " says: My soul will have " +
      "no rest until I know that the white shark is dead. \n");
   set_alarm(3.0, 0.0, "shark3");
}

string
shark3()
{
   tell_room(environment(TO), QCTNAME(TO) + " mutters: Ohh " +
      "please, if someone just could bring proof back that he is dead. \n");
   tell_room(environment(TO), QCTNAME(TO) + " says: Then " +
      "I could find comfort in my heart. \n");
   set_alarm(3.0, 0.0, "shark4");
}

void
shark4()
{
   tell_room(environment(TO), QCTNAME(TO) + " says: My wealth is small, " +
      "but if you would do this for me I will give you all I have. \n");
}


void
quest(object tp)
{
   solver = tp;
   tell_room(environment(TO), QCTNAME(TO) + " says: Praise the Lord! " +
      "\n");
   set_alarm(3.0, 0.0, "quest1", tp);
}

void
quest1(object tp)
{
   tell_room(environment(TO), QCTNAME(TO) + " says: My fortune " +
      "amounts to 100 silver coins, just say how many you want....\n");
   trig_new("%w 'says:' %s", "quest2");
}

void
quest2(string who, string amount_str)
{
   object tp = find_player(who);
   int amount = atoi(amount_str);
   
   if (amount>0 && amount<101)
      {
      command("say Thanks for your help, the money is yours. \n");
      tell_room(environment(TO), QCTNAME(TO) + " gives " + amount +
         " silver coins to " + QCTNAME(TP) + ". \n");
      MONEY_MAKE_SC(amount)->move(TP);
   }
   else
      command("say I thank you for your genorosity...");
   
   if (who)
      {
      who = lower_case(who);
      tp = find_player(who);
      set_this_player(tp);
#if 0
      if(!QDONE(GROUP1,SHARKQUEST))
         {
         tp->catch_msg("You feel much more experienced!\n");
         tp->add_exp(15000, 0);
         ADDEXP(TP,15000,0);
         QSET(GROUP1, SHARKQUEST); /*  grupp1, bit 8 */
         QLOG("Sharkquest");
       }
      call_out("remove_object", 1);
#endif
      tell_room(environment(TO), QCTNAME(TO) + " bounces " +
         "gratefully away, finally at peace with himself. \n");
   }
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   if (ob->query_name() == "skin")
      set_alarm(2.0,0.0,"check", ({ob, from}));
}


void
check(object *obs)
{         
   object ob = obs[0];
   object from = obs[1];
   
   if (ob->query_namn() == from->query_real_name())
      set_alarm(1.0,0.0,"quest",from);
   else
      command("say This is not of your doing " + QCTNAME(TP) +
      ". Please convey my gratitude to the one that gave you " +
      "the skin. ");
}


