// Konner Abair, Maighstir (Mayor) of Baile Ashlagh
//
// Zima, June 10, 1998
//
// Refactored Tapakah 08/2021

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
inherit BASE_ASHLAGH;

void
equip_me ()
{
  armours = ({ COM_ARM + "vest_leather",
               COM_ARM + "shirt_wool",
               COM_ARM + "belt",
               COM_KILTS + "kilt_lohrayn" });
}
 
void
create_khalakhor_human ()
{
   int     level=50+random(20);

   explicit_name = "konner";
   equip_me();
   ::create_khalakhor_human();
   add_name(({"mayor","maighstir","villager"}));
   set_adj(({"befuddled","balding"}));
   set_race_name("human");
   set_long("He is the maighstir, or mayor, of the village, a befuddled "+
            "balding human who is trying to look important and busy but "+
            "doing a poor job of it.\n");
 
   add_prop(ATTACK_TEAM,ATEAM);
   set_height_desc("short");
   set_width_desc("plump");
   
   set_default_answer("@@defans");
   add_ask(({"quest","tour","job","task","for job","for task"}),
      "say I don't have anything for you to do today, but I hear "+
      "Litreach is looking to hire someone.",1);
   add_ask(({"Litreach","litreach","who is litreach","where is litreach"}),
      "say Litreach is the Postmaighster of this village. He's usually "+
      "say at the post office.",1);
 
   //configure NPC level
   default_config_npc(level);
   set_skill(SS_UNARM_COMBAT, (level*8)/10);
   set_skill(SS_DEFENCE,      (level*7)/10);
   set_skill(SS_PARRY,        (level*6)/10);
   set_alignment(300+random(100));
 
   set_act_time(60);
   add_act("emote twidles his thumbs.");
   add_act("emote whistles boredly.");
   add_act("emote shuffles through some papers.");
   add_act("emote glances at you curiously.");
   add_act("emote looks down at his desk avoiding eye contact.");
   add_act("say The goblins won't dare come here again anytime soon.");
   add_act("say I've organized a fine band of men to defend the village.");
   add_act("say There'll be plenty of business in the village soon.");
   add_act("say Now where did I put those general orders...");
   add_act("say Peace and prosperity, that's my motto!");
   add_act("say Now where did I put that letter...");
   add_act("say Yes, yes, if you have business stranger, speak up!");
 
   set_cact_time(60);
   add_cact("say Now you don't really want to do this!");
   add_cact("say You'll never get past the guards you know!");
   add_cact("say Now lets sit down and talk about this rationally!");
   add_cact("say This village can't survive without me!");
   add_cact("say Think of the children! They need me!");
   add_cact("say Now just put down your weapon and surrender peaceably.");
   add_cact("emote tries to hide under his desk.");
   add_cact("emote runs around his desk with you in pursuit.");
   add_cact("emote puts his hands over his eyes for a moment.");
 
}
void
do_return_ob (object ob, object from)
{
   string obs=lower_case(ob->query_name());
   command("say Yes, yes, well...give this to my secretary please.");
   command("say She's on the other side of the town hall.");
   command("give "+obs+" to "+lower_case(from->query_name()));
   command("drop "+obs);
}
 
//
// defans
//
string
defans ()
{
   command("say Hmm, I'll make a point to find that out for you...tomorrow.");
   return "";
}
 
void
hook_return_intro_new (string str)
{
   command("say Greetings "+capitalize(str)+"! Welcome to Baile Ashlagh!");
   command("say I'm " + query_name() + " " + query_title() + "!");
   command("bow deeply");
   command("say Enjoy your stay in our village, and be sure to "+
           "patronize the local businesses!");
}
 
