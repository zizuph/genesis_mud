inherit "/std/monster";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/valley/city/"
#define TO this_object()
#define EN environment

create_monster(){
   set_living_name("wentis");
   set_race_name("human");
   set_adj("wizened");
   add_adj("white-haired");
   set_short("elderly monk");
   add_name("monk");
   set_name("wentis");
   set_alignment(856);
   set_stats(({ 50, 44, 68, 78, 74, 67 }));
   set_all_attack_unarmed(30);
   set_all_hitloc_unarmed(70);
   set_skill(SS_DEFENCE, 50);
   
   set_alarm(1.0, -1.0, "stuff");
   
}

stuff(){
   clone_object(PATH + "plain_cloak")->move(TO);
   command("wear cloak");
}

