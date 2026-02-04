inherit "/std/monster";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

object it;

#define TO this_object()
#define PATH "/d/Terel/mecien/valley/guild/spells/"
#define EN environment

query_mm_in(){ return "descends from the sky."; }
query_mm_out(){ return "fly off into the sky."; }





create_monster(){
   
   set_race_name("bees");
   set_name("bees");
   add_adj("swarm of");
   add_name("swarm");
   add_name("bee");
   set_long(
   "A magnificent swarm of bees. They are very unusual, being large and " +
"a bright crimson in colour. They make an unusual buzzing sound that " +
"sounds almost like a song.\n"
   );
   add_prop(LIVE_O_ENEMY_CLING, 1);
   add_prop(OBJ_M_NO_ATTACK, "It would be unwise to disturb such a swarm!\n");
   
   set_gender(2);
   add_prop(NPC_I_NO_LOOKS, 1);
   set_act_time(1);
  add_act("@@enter_hive");
  add_act("@@fly_off");
  add_act("emote buzz very loudly.");
  add_act("@@arrive_from");
  set_alignment(127);
   
}

enter_hive(){
  tell_room(EN(TO), "A bee flies into the hive.\n");
}
fly_off(){
   tell_room(EN(TO), "A group of bees fly off into the distant sky.\n");
}
arrive_from(){
  tell_room(EN(TO), "A bee arrives from the distant sky and enters the swarm.\n");
}

