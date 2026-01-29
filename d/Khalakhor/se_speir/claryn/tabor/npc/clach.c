/*
 *
 * Clach Neese - just a villager; recipient of a letter in postman tour
 *
 * Zima, June 13, 1998
 * Refactored
 * Tapakah, 07/2021
 */

#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/random.h"
#include "npc.h"
 
inherit BASE_NPC;

void
arm_me()
{
  armours = ({ "/d/Khalakhor/common/arm/dress",
               "/d/Khalakhor/common/arm/bonnet",
               "/d/Khalakhor/common/arm/apron" });
  ::arm_me();
}
 
void
create_khalakhor_human()
{
  ::create_khalakhor_human();

  int     level=10+random(50);
  string* adj;
 
  add_name(({"lass","woman","villager"}));
 
  set_gender(G_FEMALE);
  set_adj(RANDOM_DETAILED_ADJS(TO));
  adj=query_adj(1);
  add_adj("bonnie");
  set_long("This bonnie lass is a "+adj[0]+" "+adj[1]+" villager, "+
           "dressed modestly with her apron and bonnet, the traditional "+
           "garb of the local women.\n");
 
  set_random_size_descs();
  default_config_npc(level);
  set_skill(SS_UNARM_COMBAT, level);
  set_skill(SS_DEFENCE, level);
  set_alignment(0);
  set_exp_factor(50);
 
  set_act_time(60);
  add_act("emote breaths in the sea air deeply.");
  add_act("emote glances out over the sea vigilantly.");
  add_act("say 'Tis a beautiful day, truly tis!");
  add_act("say There's the smell 'o a storm brewing, I say.");
  add_act("say Top 'o the mornin' to ya, stranger.");
  add_act("emote reties her bonnet beneath her chin.");
  add_act("emote wipes her hands on her apron.");
  add_act("emote nods her head to you politely.");
  add_act("emote smooths the wrinkles of her dress.");
 
  set_restrain_path("/d/Khalakhor/se_speir/claryn/tabor/room");
  set_monster_home("/d/Khalakhor/se_speir/claryn/tabor/room/road_1_5");
  set_random_move(60);
  set_default_answer("I'm afraid I can't answer that.");
  add_ask(({"gebann","Gebann","prior","Prior"}),
          "say Prior Gebann is usually in his priory, the house just "+
          "south of the kirk.",1);
  add_ask("kirk",
          "say We've a wee kirk, but it serves us well. It's on the north "+
          "side of the village.",1);
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

int
hook_return_intro_new (string str)
{
  command("say Goo' day to ya, "+capitalize(str)+"!");
  command("say I'm "+query_name()+" "+query_title()+", and pleased to "+
          "make yer acquaintance.");
  command("curtsey politely");
  (find_player(lower_case(str)))->add_introduced(lower_case(query_name()));
}
