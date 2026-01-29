// Village Guard
//
// Zima, June 10, 1998
//
// Refactored Tapakah 08/2021

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "adj.h"
#include "defs.h"

inherit BASE_ASHLAGH;
 
void
equip_me ()
{
 
  weapons = ({ WEP+"gclaymore" });
  armours = ({ ARM+"gshirt",
               COM_ARM+"belt",
               COM_KILTS+"kilt_lohrayn" });
}
 
//
// create_monster()
//
void
create_khalakhor_human ()
{
  int     level=50+random(20);
  string  adj=MALE_ADJ[(random(sizeof(MALE_ADJ)))];
  
  equip_me();
  ::create_khalakhor_human();
   
  set_name("guard");
  add_name("villager");
  set_adj(adj);
  set_race_name("human");
  set_random_size_descs();
  set_short(adj + " village guard");
  set_long("He is a member of the village guard, proudly called "+
           "The Freiceadanan de Baile Ashlagh. A volunteer, he is "+
           "highly respected for the service he offers his fellow "+
           "villagers. Colorfully outfitted in the village color of "+
           "purple, he looks ready to take on any enemy.\n");
 
  add_prop(ATTACK_TEAM,ATEAM);
 
  //configure NPC level
  default_config_npc(level);
  set_skill(SS_WEP_SWORD,        (level*8)/10);
  set_skill(SS_DEFENCE,      (level*7)/10);
  set_skill(SS_PARRY,        (level*6)/10);
  set_alignment(300+random(100));
 
  set_act_time(90);
  add_act("emote eyes you suspiciously.");
  add_act("emote scans the street for trouble.");
  add_act("emote stands at attention.");
  add_act("emote swings his claymore around in practice.");
  add_act("emote nods at you carefully.");
  add_act("emote pulls his kilt higher on his hips.");
  add_act("emote shades his eyes with his hand and looks around.");
  set_cact_time(60);
  add_cact("emote swings his claymore with an evil grin.");
  add_cact("emote dodges a blow and smiles confidently.");
  add_cact("shout You'll never leave here alive stranger!");
  add_cact("shout The Freiceadanan de Baile Ashlagh are invincible!");
  add_cact("emote yells out a heroic battle cry!");
  add_cact("shout Yer head will hang from me belt, curr!");
  add_cact("shout Ye'll never see daylight again, ye snake!");
}
 
void
hook_return_intro_new (string str)
{
  command("emote nods hospitably.");
}
