// Captain of the Guard - Priomh Feach
//
// Zima, June 10, 1998
//
// Bug fix: removed set_short() and string adj
// Damaris January 8, 2001
//
// Refactored
// Tapakah, 08/2021
//

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit BASE_ASHLAGH;
 
void
equip_me()
{
  weapons = ({ WEP+"gclaymore" });
  armours = ({ ARM+"gshirt",
               COM_ARM+"belt",
               COM_KILTS+"kilt_lohrayn" });
  ::arm_me();
}
 
void
create_khalakhor_human ()
{
  int level = 80;
  explicit_name = "feach";
  equip_me();
  ::create_khalakhor_human();
  add_name(({"guard","captain","priomh","villager"}));
  set_adj("decorated village guard");
  set_long("He is a member of the village guard, proudly called "+
           "The Freiceadanan de Baile Ashlagh. A volunteer, he is "+
           "highly respected for the service he offers his fellow "+
           "villagers. Colorfully outfitted in the village color of "+
           "purple, he looks ready to take on any enemy. He seems to "+
           "be highly decorated and so may be of some rank.\n");
 
  add_prop(ATTACK_TEAM,ATEAM);
 
  set_default_answer(defans);
  add_ask(({"guard","village guard","the freiceadanan","freiceadanan"}),
          "say The Freiceadanan is the village guard, a volunteer force.",1);
  add_ask(({"gates","western gates"}),
          "say The western gates are closed due to recent goblin attacks.",1);
  add_ask(({"goblins","attacks"}),
          "say The goblins from the clans of the north have raided in the "+
          "area recently.",1);
  add_ask(({"ardmaugh","Ardmaugh"}),
          "say Ardmaugh is the Holy City just west of the village in the "+
          "mountains.",1);
  add_ask(({"tour","quest","job","task","help","for job","for task"}),
          "say Sorry, I don't have anything for you to do.",1);
  
  //configure NPC level
  default_config_npc(level);
  set_skill(SS_WEP_SWORD,    (level*8)/10);
  set_skill(SS_DEFENCE,      (level*7)/10);
  set_skill(SS_PARRY,        (level*6)/10);
  set_skill(SS_ACROBAT,      (level*5)/10);
  set_skill(SS_BLIND_COMBAT, (level*5)/10);
  
  set_alignment(300+random(100));
  
  set_act_time(60);
  add_act("emote studies the map on the wall.");
  add_act("emote searches through the books on the shelf.");
  add_act("emote admires his medals proudly.");
  add_act("emote glances at you impatiently.");
  add_act("emote studies you carefully.");
  add_act("say The goblins won't dare come here again anytime soon.");
  add_act("say It should be safe to open the western gate soon.");
  add_act("say I haven't heard from my scouts in a few days.");
  add_act("say I think we have enough guards now to protect the village.");
  add_act("say I'm expecting a letter from Ardmaugh any day.");
  add_act("emote coughs impatiently.");
  add_act("emote barks out an order to a guard standing outside.");
  add_act("emote inspects his claymore.");
  add_act("say We'll need a troop review tomorrow.");
  
  set_cact_time(60);
  add_cact("emote swings his claymore with an evil grin.");
  add_cact("emote dodges a blow and smiles confidently.");
  add_cact("shout You'll never leave here alive stranger!");
  add_cact("shout The Freiceadanan de Baile Ashlagh are invincible!");
  add_cact("emote yells out a heroic battle cry!");
  add_cact("shout Yer head will hang from me belt, curr!");
  add_cact("shout Ye'll never see daylight again, ye snake!");
  
}

string
defans ()
{
  command("say I'm afraid I don't know the answer to that.");
  return "";
}
 
//
// my_intro
//
void
hook_return_intro_new (string str)
{
  command("say Greetings " + capitalize(str) + ".");
  command("say I'm " + query_name() + " " + query_title() + "!");
  present(str, environment(TO))->add_introduced("feach");
}
 
