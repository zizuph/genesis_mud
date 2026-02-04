// modified by Lilith May 2022: got the add_acts working.
// cloning to the playhouse in Calathin.
inherit "/std/monster.c";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h";

void
create_monster() 
{
  set_name("irilyan");
  set_race_name("elf");
  add_name(({"boy", "lad", "musician"})); 
  set_adj(one_of_list(({"smiling","happy", "entertaining","charming","engaging",
      "delightful", "cheerful", "enthusiastic", "sunny", "joyful", "blue-eyed", 
      "hazel-eyed", "black-eyed", "brown-eyed", "green-eyed","olive-skinned",
      "brown-skinned","tanned","dark-skinned","light-skinned","grey-eyed",
      "muscular"})));
  add_adj("young");
  set_gender(0);
  default_config_npc(30);
  set_long("The young lad is playing on his new recorder.\n");

  // add acts never worked they weren't set up correctly or the functionality changed. 
  // add_act(({"smile","play recorder","sing","say Boy this recorder is the best I've ever made",
  // "bounce","dance","say this recorder is great!"}));
  set_act_time(5);
  add_act("play recorder", 1);
  add_act("sing");
  add_act("smile");
  add_act("say Boy, this recorder is the best I've made ever made!");
  add_act(({"say Clap along now, everyone.", "play recorder"}));
  add_act("dance");
  add_act("emote plays a lively tune on his recorder and dances along to it.");
  add_act("bow");
   
  add_prop(LIVE_I_NEVERKNOWN,1);
// set_random_move(60);
  clone_object("/d/Terel/calathin/obj/recorder")->move(this_object());
}

