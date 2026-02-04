inherit "/std/monster";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/valley/city/"

create_monster(){
   
   set_living_name("mendalah");
   set_race_name("human");
   set_name("mendalah");
   set_adj("muscular");
   add_name("guild_master");
   set_stats(({ 101, 121, 143, 75, 80, 99 }));
   
   set_skill(SS_DEFENCE, 70);
   set_skill(SS_CLIMB, 100);
   set_skill(SS_WEP_SWORD, 70);
   set_skill(SS_SWIM, 70);
   set_all_attack_unarmed(100);
   set_all_hitloc_unarmed(60);
   
}


