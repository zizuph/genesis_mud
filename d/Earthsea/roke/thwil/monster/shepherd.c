
/* A shepherd
Joshua 95-01-28

Many thanks to Napture
for the filter function

Tis okay...Napture.

Thanks for the rest
as well! /josh
*/

#include "defs.h"
inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/intro";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"

#pragma strict_types      /* To make Quetzl happy! */

string sheep();
void sheep1();
void sheep2();
void sheep3();
void sheep4();
void squest();
void quest(object tp);
void quest1(object tp);
void quest2(object tp);
void count_sheep(object who);

void
create_earthsea_monster()
{
   int i;
   object sheep_room;

   set_name(({"takwa"}));
   add_name("shepherd");
   set_short("adolescent sad boy");
   add_name("boy");
   set_title("3rd Sheepfarmer of Thwil");
   set_race_name("human");
   set_adj(({"sad","adolescent"}));
   set_gender(G_MALE);
   set_long("He looks at you pleadingly. " +
      "Some tears are coming down his cheek. \n");   
   set_gender(0);
   default_config_creature(40);   
   set_alignment(100);
   
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   
   set_act_time(5);
   add_act("emote sobs sadly.");
   add_act("emote wipes off some tears from his face.");
   add_act("emote says: My sheep just ran away!");
   add_act("emote says: I will get beaten if my father " +
      "discovers. ");
   add_act("emote says: Please, can you help me?");
   
   add_ask(({"task", "help", "sheep"}),VBFC_ME("sheep"));
   
   trig_new("%w 'pushes' 'the' 'sheep' %s", "trig_push");
   trig_new("%s 'sheep' 'leaves' 'north.'", "trig_sheep");

   setuid();
   seteuid(geteuid(this_object()));

   /* Make sure the sheep get loaded */
   sheep_room = find_object(THWIL + "p1");
   sheep_room->reset_room();
   sheep_room = find_object(THWIL + "t3");
   sheep_room->reset_room();
}

string
sheep()
{
#if 0
      tell_room(environment(TO), QCTNAME(TO) + " says: Some of my " +
      "sheep just ran away. \n");
#endif
      command("say Some of my sheep just ran away!");
   set_alarm(3.0, 0.0, &sheep1());
   return "";
}

void
sheep1()
{
   tell_room(environment(TO), QCTNAME(TO) + " says: If I don't " +
      "get them back soon my father will discover... \n");
   set_alarm(3.0, 0.0, &sheep2());
}

void
sheep2()
{
   tell_room(environment(TO), QCTNAME(TO) + " says: But if I " +
      "go out and search for them the others will " +
      "escape too! \n");
   set_alarm(3.0, 0.0, &sheep3());
}

void
sheep3()
{
   tell_room(environment(TO), QCTNAME(TO) + " says: Ohh " +
      "please, Cant you get them for me? \n");
   tell_room(environment(TO), QCTNAME(TO) + " says: They " +
      "are so stupid that you can push them even!  \n");
   set_alarm(3.0, 0.0, &sheep4());
}

void
sheep4()
{
   tell_room(environment(TO), QCTNAME(TO) + " says: Just " +
      "push them into the paddock north of here. \n");
   tell_room(environment(TO), QCTNAME(TO) + " looks " +
      "pleadingly at you with his big brown eyes.  \n");
}

int
trig_push(string who, string where)
{
   object plr;
   
   if (who)  {
      who = lower_case(who);
      plr = find_player(who);
      set_alarm(3.0, 0.0, &count_sheep(plr));
      return 1;
   }
}

int
trig_sheep(string who)
{ 
   int sheep, i;
   setuid();
   seteuid(geteuid(this_object()));
   for (i = 0, sheep = 0; i < 6; i++)
     {
       sheep += (THWIL + "p" + (i+1))->count_sheep();
     }   
   tell_room(environment(TO), QCTNAME(TO) + " says: Right, " +
      "now I have " + LANG_WNUM(sheep) + " sheep in the paddock. \n");
   if ((9-sheep) > 1)
      tell_room(environment(TO), QCTNAME(TO) + " says: " + 
      LANG_WNUM(9 - sheep) +" more sheep to go! \n");
   if ((7-sheep) == 1)
      command("say Now where did that last one go?");
   command("bounce");
   if (sheep > 8)
      set_alarm(3.0, 0.0, &squest());
   return 1;
}


int
parse_sheep(object sheep)
{
   if (living(sheep) && sheep->id("sheep"))
      return 1;
   return 0;
}

void
remove_sheep(object sheep)
{
   if (living(sheep) && sheep->id("sheep"))
      sheep->remove_object();
}

void
count_sheep(object who)
{
   int sheep, i;

   if (!present(who, environment(this_object())))
     {
       return;
     }
   setuid();
   seteuid(geteuid(this_object()));
   for (i = 0, sheep = 0; i < 6; i++)
     {
       sheep += (THWIL + "p" + (i+1))->count_sheep();
     }
   tell_room(environment(TO), QCTNAME(TO) + " says: Right " +
      "now I have " + LANG_WNUM(sheep) + " sheep in the paddock. \n");
   if ((9-sheep) > 1)
      tell_room(environment(TO), QCTNAME(TO) + " says: " + 
      LANG_WNUM(9 - sheep) +" more sheep to go!! \n");
   if ((9-sheep) == 1)
      command("say Now where did that last one go?");
   command("bounce");
   if (sheep > 8)
      set_alarm(3.0, 0.0, &quest(who));
}

void
quest(object tp)
{
   tell_room(environment(TO), QCTNAME(TO) + " says: YES! " +
      "Thanks a lot!!  \n");
   set_alarm(3.0, 0.0, &quest1(tp));
}

void
quest1(object tp)
{
  int i;
  tell_room(environment(TO), QCTNAME(TO) + " closes " +
	    "the gate to the paddock and happily runs away.\n");
  for (i = 1; i < 7; i++)
    {
      filter(all_inventory(find_object(THWIL + "p" + i)),"remove_sheep",
	     this_object());
    }
  set_alarm(3.0, 0.0, &quest2(tp));
}


void
quest2(object tp)
{  
  if (!present(tp, environment(this_object())))
    {
      command("say Oh, they've gone already!");
      return;
    }
  if(!QH_QUERY_QUEST_COMPLETED(tp, "sheep_quest"))
    {
      this_object()->command("cheer");
      QH_QUEST_COMPLETED(tp, "sheep_quest");
      tp->catch_msg("You feel slightly more experienced!\n");
    }
  else  
    {
      this_object()->command("cheer");
      tp->catch_msg("Hmm...that was fun!\n");
    }
  tell_room(environment(this_object()),
	    QCTNAME(this_object()) + " happily hops away.\n");
  remove_object();
}

void
squest()
{
   tell_room(environment(TO), QCTNAME(TO) + " says: Geee " +
      "the sheep walk in by themselves...  \n");
   tell_room(environment(TO), QCTNAME(TO) + " closes " +
      "the gate to the paddock and happily runs away.\n");
   remove_object();
}
