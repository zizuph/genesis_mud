// Teaghe Foclair, School Marm
//
// Zima, June 10, 1998
//
// Refactored, Tapakah 08/2021

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
inherit BASE_ASHLAGH;

void
arm_me ()
{
  armours = ({ COM_ARM+"dress",
               COM_ARM+"belt", });
  ::arm_me();
}

void
create_khalakhor_human ()
{
   int     level=10+random(20);
   explicit_name = "teaghe";
   ::create_khalakhor_human();
   add_name(({"teacher","marm","villager"}));
   set_adj(({"old","bun-headed"}));
   set_gender(1); // female
   set_long("She is a tall skinny human who works as the school marm "+
            "of the village. Mostly a baby sitter for the smaller "+
            "children, she looks like she's been run raggerd. Her gray "+
            "hair is wound into a bun on her head.\n");
 
   add_prop(ATTACK_TEAM,ATEAM);
   set_size_descs("tall","very thin");
 
   set_default_answer(defans);
 
   //configure NPC level
   default_config_npc(level);
   set_skill(SS_UNARM_COMBAT, (level*8)/10);
   set_skill(SS_DEFENCE,      (level*7)/10);
   set_skill(SS_PARRY,        (level*6)/10);
   set_alignment(300+random(100));
 
   set_act_time(60);
   add_act("emote files some papers away.");
   add_act("emote dusts her desk.");
   add_act("emote stares at you annoyingly.");
   add_act("emote arranges some books on a shelf.");
   add_act("emote looks up at you questioningly.");
   add_act("say Those kids are gonna drive me nuts!");
   add_act("say Discipline! That's what those kids need!");
   add_act("say Quittin' school at such a young age! What a waste!");
   add_act("say Who can read this handwriting!");
   add_act("emote grumbles annoyedly.");
   add_act("emote scribbles a note hurriedly.");
 
   set_cact_time(60);
   add_cact("say Now you don't really want to do this!");
   add_cact("say You'll never get past the guards you know!");
   add_cact("say Now lets sit down and talk about this rationally!");
   add_cact("say This village can't survive without me!");
   add_cact("say Think of the children! They need me!");
   add_cact("say Now just put down your weapon and surrender peaceably.");
   add_cact("emote tries to hide under her desk.");
   add_cact("emote runs around her desk with you in pursuit.");
   add_cact("emote puts her hands over her eyes for a moment.");
   add_cact("emote screams loudly!");
   add_cact("emote screams loudly!");
   add_cact("emote screams loudly!");
   add_cact("emote screams loudly!");
 
}
 
string
defans ()
{
   command("say You better ask the maighstir that.");
   return "";
}
 
void
hook_return_intro_new (string str)
{
   command("say Hello there.");
   command("say I'm "+query_name()+" "+query_title()+".");
   command("say How can I help you?");

}
