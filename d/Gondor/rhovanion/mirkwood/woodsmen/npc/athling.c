inherit "/std/monster.c";

#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"


void

introduce_me();
arm_me();

int intro_id;

void
create_monster()
{
   
   set_name("athling");
   add_adj(({"short","red-haired"}));
   set_long("This appears to be the shopkeeper. He appears to be rather interesting in " +
      "doing business with you.\n");
   set_race_name("human");
   set_gender(0);
   
   add_act("greet all");
   add_act("emote wanders brifely into the storeroom before coming back with a smile.");
   add_act("say Would you like to buy something? Or do you have something you would like to sell?");
   add_act("say Mirkwood is a dangerous place if you don't know your way around.");
   add_act("emote straights up some of his goods on the shelves.");
   add_act("emote waits patiently behind the counter.");
   add_act("scratch nose");
   add_act("emote rubs his eyes wearing.");

   set_act_time(10);
   
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE, 100);

   set_stats(({ 100, 100, 100, 110, 110, 100}), 10);
   
   set_alignment(150);
   
   
   intro_id = 0;
   set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
   object hat, shirt, pants;

   FIXEUID;

   hat = clone_object(WOODSMEN_DIR + "arm/athling_hat.c");
   shirt = clone_object(WOODSMEN_DIR + "arm/athling_shirt.c");
   pants = clone_object(WOODSMEN_DIR + "arm/athling_pants.c");

   hat->move(TO);
   shirt->move(TO);
   pants->move(TO);   

   command("wear all");
}

void
add_introduced(string person)
{
   if (intro_id == 0) {
      intro_id = set_alarm(4.0,0.0, introduce_me);
   }
}

void
allow_introductions() 
{
   intro_id = 0;
}

void
introduce_me()
{
   command("introduce me");

   set_alarm(15.0, 0.0, allow_introductions);
}
