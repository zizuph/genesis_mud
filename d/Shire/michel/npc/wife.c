/* Patched by Tapakah for quest reset - June 2011 */

inherit "/std/monster";
#include "/d/Shire/common/make_money.h"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/common/defs.h"

#define HUBBY_DESTS (({"/d/Shire/bree/rooms/town/innfront", \
		  "/d/Genesis/start/hobbit/farm/barn1",							\
		  "/d/Shire/gsl_ships/gh-sparkle/ship/crewroom",				\
		  "/d/Shire/eastroad/western/lpath1",							\
		  "/d/Shire/eastroad/western/er22",								\
		  "/d/Shire/eastroad/western/er8"}))

object dondel;

void
create_monster()
{
   if (!IS_CLONE)
      return;
   set_name("amanda");
   add_name(({"wife","woman"}));
   set_living_name("_amanda_");
   set_race_name("hobbit");
   add_adj(({"tall","blonde"}));
   set_long("This tall blonde woman seems to be stressed by large amount of house work. " +
            "Perhaps she could use a hand.\n");
   
   set_gender(1);
   set_appearance(95);
   set_alignment(200 + random(100));
   set_stats(({50,60,70,80,90,100}));
   
   set_skill(SS_DEFENCE, 67);
   set_skill(SS_UNARM_COMBAT, 53);
   
   set_act_time(5);
   add_act("emote mutters silently about something she has forgotten.");
   add_act("sigh sadl");
   add_act("emote stops to catch her breath.");
   
   set_chat_time(4);
   add_chat("Curse that husband of mine. Ran off without his lunch again!");
   add_chat("I suppose he thinks it's my fault!");
   
   set_whimpy(75);
   set_cact_time(3);
   add_cact("scream");
   MAKE_MONEY;
   
   add_ask(({"task", "quest", "job", "husband","lunch","about husband","about lunch"}),
             VBFC_ME("ask_lunch"));
}

string
ask_lunch()
{

  string hubby_dest;
  object lunch;

  if (TP->query_prop("_amanda_gave_me_lunch_")) {
	command("say I gave you my husbands lunch already!");
	return "";
  }

  seteuid(getuid(this_object()));
  command("say Oh my silly husband ran off without his lunch.");
  command("hmm");
  command("say Say, you look like a respectable person.");
  command("think");
  command("say I'm sure you'd deliver it for me, wouldn't you? He'd be most pleased.");
  
  lunch = clone_object(MICH_DIR + "obj/lunch");
  lunch->move(TO);
  
  if (!objectp(dondel))	{
	dondel = clone_object("/d/Shire/michel/npc/dondel");
	hubby_dest = ONE_OF_LIST(HUBBY_DESTS);
	hubby_dest->teleledningsanka();
	while(dondel->move(hubby_dest)) {
	  hubby_dest = ONE_OF_LIST(HUBBY_DESTS);
	  hubby_dest->teleledningsanka();
	}
  }
  
  TP->add_prop("_amanda_gave_me_lunch_",1);
  command("drop lunch");
  
  command("say Thank you, toodles!");
  command("say Oh, by the way, my husband's name is Dondel!");
  
  return "";
}
