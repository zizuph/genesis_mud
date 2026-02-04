inherit "/std/monster";
#include <macros.h>
#include <stdproperties.h>

object it;

#define TO this_object()
#define PATH "/d/Terel/mecien/valley/guild/spells/"
#define ENV environment

query_mm_in(){ return "descends from a dark cloud that has formed above."; }

query_mm_out(){ return "disperse into the dark regions."; }


set_plagued(object target){
it = target;
}

query_plagued(){ return it; }

create_monster(){
   
   set_race_name("locusts");
   set_name("locusts");
   add_adj("swarm of");
   add_name("swarm");
   add_name("locust");
   set_long(
      "Shadowy locusts that form a swarm of thousands upon thousands. " +
      "They make horrible noises and flutter all about, chewing and clicking.\n"
   );
   add_prop(LIVE_O_ENEMY_CLING, 1);
   add_prop(OBJ_M_NO_ATTACK, "There are thousands upon thousands! You can kill them forever!\n");
   
   set_act_time(1);
   add_act("emote makes horrible noises and flutter all about.\n");
   
}

make_crazy(object who){
   int n;
   n = random(4);
   if(n == 0) who->catch_msg("A locust slips into your mouth and you accidentally swallow it!\n");
   if(n == 1) who->catch_msg("The sounds of the locust grow stronger and stronger!\n");
   if(n == 2) who->catch_msg("Some of the locusts get into your clothes.\n");
   if(n == 3) who->catch_msg("A locust flies in your face.\n");
   
   set_alarm(1.0, -1.0, "plague");
}

plague(){
  object who, after;

after = query_plagued();
   
  who=find_living(after->query_real_name());
   if(who){
      if(!present(who, ENV(TO))){
         TO->move_living("X", ENV(who));
      }
      set_alarm(3.0, -1.0, "make_crazy", who);
   }
}

