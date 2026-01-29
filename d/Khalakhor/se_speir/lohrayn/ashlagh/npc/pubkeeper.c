//
// pubtender - of the Taigh Leann (House of Beer)
//
// Zima  - June 10/98
// Refactored Tapakah 08/2021

#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit "/d/Khalakhor/se_speir/common/landlord";
inherit BASE_ASHLAGH;

void
arm_me ()
{
  armours = ({ COM_ARM+"shirt_wool",
               COM_ARM+"apron",
               COM_ARM+"breeches" });
  ::arm_me();
}

void
create_khalakhor_human ()
{
  explicit_name = "bedwyn";
  ::create_khalakhor_human();
  set_race_name("dwarf");
  add_name(({"pubtender","bartender"}));
  set_adj(({"lean","red-haired"}));
  set_long("The lean red-haired dwarf seems to be the bartender, as "+
           "he is wearing an apron.\n");
 
  default_config_npc(40);
  set_skill(SS_AWARENESS, 75);
  set_skill(SS_UNARM_COMBAT, 30);
  set_skill(SS_DEFENCE, 30);
  set_skill(SS_WEP_SWORD, 35);
  
  set_alignment(400);
  add_prop(ATTACK_TEAM,ATEAM);
 
  set_act_time(15);
  add_act("emote chuckles softly to himself.");
  add_act("say All these visitors from different lands have been " +
          "great for business!");
  add_act("say No scufflin' in me tavern! Too much broke last time!");
  add_act("say Rumour has it the Clans will attack the goblins "+
          "soon, I wonder which ones.");
  add_act("say The gobbo's been bad for business these days.");
  add_act("emote cleans a glass with his apron.");
  add_act("emote cleans a glass with his apron.");
  add_act("emote cleans a glass with his apron.");
  add_act("emote cleans a glass with his apron.");
  add_act("ponder");
 
  add_cact("say Oh, so it's a fight you want, is it?");
  add_cact("say Ye'll not get a penny of me money, varmit!");
  add_cact("say The guards'll rip yer head off!");
  add_cact("emote growls.");
 
  set_size_descs("tall", "lean");
}
 
void
hook_return_intro_new (string str)
{
  command("say Hello thar  " + capitalize(str) + "!");
  command("say I'm " + query_name() + " " + query_title() + "!");
  command("say What can I get fer ye?");
}

void
hook_return_intro_good (string str)
{
  command("say Aye, we met earlier " + capitalize(str) + ".");
  command("say Can I get ye a leann or some mutton?");
}
 
void
hook_return_intro_bad (string str)
{
  hook_return_intro_good(str);
}

