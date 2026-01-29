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
   
   set_name("faelund");
   add_adj(({"wide","big-eared"}));
   set_long("This wide, big-eared man seems to be rather busy running the inn. He would " +
      "probably be happy to serve you something if you wanted to order food or drink.\n");
   set_race_name("human");
   set_gender(0);
   
   add_act("smile all");
   add_act("emote bustles around the inn, serving drinks and food.");
   add_act("greet all");
   add_act("say Running an inn is hard work, but it is enjoyable work at that.");
   add_act("emote begins to clean some tables.");
   add_act("emote takes out a rag and polishes up the bar surface.");
   add_act("cough silently");
   add_act("stretch");

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

   hat = clone_object(WOODSMEN_DIR + "arm/faelund_hat.c");
   shirt = clone_object(WOODSMEN_DIR + "arm/faelund_shirt.c");
   pants = clone_object(WOODSMEN_DIR + "arm/faelund_pants.c");

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
