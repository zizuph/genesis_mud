/*
Cleric of the Citadel.
MADE BY: Korat
DATE: Feb 14 1995

Updated by Mirandus 2018/01/19 to fit in with the return of Thanar
Made him more in line with the Priests/Clerics of Thanar
Also, as a quest master, made him unattackable.
*/

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"

create_monster()
{
   ::create_monster();
   set_name("hamer");
   add_name("cleric");
   set_race_name("human");
   set_adj("wise");
   set_long("This man is the main cleric of the Citadel. He is responsible "+
      "for the daily work and functioning of this place, making him a "+
      "very busy and important man.\n");
   set_stats(({50,80,70,110,100,60}));
   set_alignment(300);
   set_skill(SS_UNARM_COMBAT,90);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_BLIND_COMBAT,80);
   set_skill(SS_AWARENESS,90);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
  
   /* Quest master */
   add_prop(OBJ_M_NO_ATTACK,"Umm... no, You " +
   "do not have the self-discipline to dare!\n");
  
   set_act_time(3);
   add_act(({"say Welcome to the Citadel. Can I help you?","smile ."}));
   add_act("emote shuffles around some papers on his desk.");
   add_act(({"say Thanar grant me strength.", "emote crosses himself."}));
   add_act("say It was wise of the High Lord to allow us to return to the city.");
   add_act("say While the Highlord may fear our power, we help him keep his.");
   add_act("emote peers around to check that none of his helpers are napping.");
   add_act("hmm");
   add_act("emote studies some of the papers on his desk.");
   set_cact_time(1);
   add_cact("spit");
   add_cact("I will punish you for this!");
   add_cact("say Why this senseless act?");
   add_cact("My God! Help me now!!.");
   add_cact("gasp");
   set_title("the Master cleric of the Citadel");
   add_speak("Maybe you can be of help to me...\n");
   set_default_answer("The cleric says: What was that?\n");
   add_ask(({"job","quest","help","task"}),"The cleric goes "+
      "Hmmm, and says: Well, maybe you could help. All I know is that "+
      "something is going on inside the political structure in Kabal. "+
      "Of course, this is frowned upon by the High Lord, since it might "+
      "affect him! So if you could help out here, and find out what "+
      "is going on, I would be immensly appreciative.\n");
   add_ask(({"lord","high lord"}),"Well, he is busy man! And if you want "+
      "to meet him, you must get my permission first.\n");
   add_ask("permission","And why should I give you a permission? "+
      "What entitles you to be rewarded a grant for audience?\n");
   set_knight_prestige(-5);
   trig_new("%w 'shows' 'you' 'a' 'handwritten' 'note.\n' %s","react_show");
   trig_new("%w 'shows' 'you' 'a' 'strange' 'message.\n' %s","react_show");
   trig_new("%w 'gives' 'you' 'a' 'strange' 'message.\n' %s","react_message");
   trig_new("%w 'gives' 'you' 'a' 'handwritten' 'note.\n' %s","react_note");
   
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   object arm, neck;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/guilds/new_thanar/arm/probe");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/cit_human_sandal");
   arm -> move(TO);
   neck = clone_object("/d/Kalad/common/guilds/new_thanar/arm/pnecklace");
   neck -> move(TO);
   command("wear all");
}

void
react_show(string who,string dummy)
{
   command("say You better give me that.");
   command("emote stretches out his hand.");
}

void
react_message(string who, string dummy)
{
   if (who)
   {
      who = lower_case(who);
      set_alarm(3.0,0.0,"reward1",who);
   }
}

void
reward1(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj->test_bit("Kalad",1,10))
         {
         command("say What is this! You have brought me this before.");
         TP->catch_msg("You do not feel more experienced at all!\n");
         set_alarm(1.0,0.0,"kill_notes");
      }
      else
         {
         command("say This is important! But ... I need more information. "+
            "Who is behind it? Find out!");
         command("point south");
         command("hmm");
         command("say Just to make you more eager to help me...");
         MONEY_MAKE_PC(1)->move(TP,1);
         command("emote slips you a platinum coin.");
         obj->add_exp(500);
         obj->set_bit(1,10);
         obj->catch_msg("You feel a bit more experienced!\n");
         command("wink");
         command("say Be careful! And don't get caught!");
         command("I expect they would kill you if they found you snooping " +
                 "around in their secrets.");
         set_alarm(1.0,0.0,"kill_notes");
      }
   }
}

void
react_note(string who,string dummy)
{
   if (who)
      {
      who = lower_case(who);
      set_alarm(3.0,0.0,"react_code",who);
   }
}

void
react_code(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj->test_bit("Kalad",1,12))
         {
         command("But I have stopped this treason before! And "+
            "that with your help!?!");
         obj->catch_msg("You really don't feel any more experienced, just abit "+
            "embarrased.\n");
         set_alarm(1.0,0.0,"kill_notes");
         return;
      }
      if (!obj->test_bit("Kalad",1,11))
         {
         command("say I have a feeling you are hiding something! "+
            "Did you maybe kill someone for it!?!");
         command("shout GUAARRDDSS!!! Imprison this assassin!");
         say("Several guards comes running to the room and drags "+
            QTNAME(obj)+" away screaming.\n");
         obj->move_living("towards jail accompanied by several guardsmen","/d/Kalad/common/trade/jail");
         set_alarm(1.0,0.0,"kill_notes");
         return;
      }
      if (!obj->test_bit("Kalad",1,10))
         {
         command("say Hmm, I do not understand this at all...why "+
            "are you bringing me this?");
         command("say but still...");
      }
      command("say It must be some code. Translate it for me, will you?");
      command("say If you think you know the solution, then tell me the _exact_ "+
         "translation of the note.");
      command("emote grins merrily.");
      command("drop note");
   }
}

void
speech_hook(string verb, object actor, string adverb,
    object *oblist, string text, int target)
{
    if (target != 1)
	return;

    if (actor->test_bit("Kalad",1,12))
    {
	command("say Why are you telling me this??");
	return;
    }
    if (actor->test_bit("Kalad",1,11))
    {
	command("say Ahh, you think you know the answer... "+
	    "Lets see.");
	if(lower_case(text)=="as arranged i will pay you the "+
	    "platinums after the death of the lord. "+
	    "bocca, lord of the city council.")
	{
	    command("say Yes!! Its him!!!");
	    command("fume");
	    command("I will take care of this from here...");
	    actor->set_bit(1,12);
	    actor->add_exp(2500);
	    actor->catch_msg("You feel more experienced.\n");
	    command("say Thank you! You have been a great help.");
	}
	else
	{
	    command("say no, that cannot be right.");
	    actor->catch_msg("You don't feel more experienced.\n");
	}
    }
}

kill_notes()
{
   int i;
   object *ob;
   ob=all_inventory(TO);
   for (i=0;i<sizeof(ob);i++)
   {
      if (ob[i]->query_name()=="note") ob[i]->remove_object();
      if (ob[i]->query_name()=="message") ob[i]->remove_object();
   }
}
