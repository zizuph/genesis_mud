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
   
   set_name("rukh");
   set_title("Krignuk, owner of the Chipped Mug");
   add_adj(({"grey","bald"}));
   set_long("This goblin looks a little more friendly and out-going than " +
      "most goblins you have met. Perhaps he just wants you to buy " +
      "something from his tavern?\n");
   set_race_name("goblin");
   set_gender(0);
   
   add_act("chuckle grimly");
   add_act("emote bustles around the tavern, serving drinks and food.");
   add_act("greet all");
   add_act("say Maggots yesterday, maggots today and blimey if it " +
      "don't look like maggots tomorrer! Why can't you lazy tomnoddies " +
      "get me some clean meat for once!");
   add_act("emote makes a half-hearted attempt to clean up a little.");
   add_act("emote absentmindedly scrapes away at a chunk of dried " +
      "food on the bar.");
   add_act("emote coughs out a chunk of blackish phlegm and spits it " +
      "on the ground.");
   add_act("stretch");

   set_act_time(10);
   
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE, 100);

   set_stats(({ 100, 100, 100, 110, 110, 100}), 10);
   
   set_alignment(-300);
   
   
   intro_id = 0;
   set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
   object shirt, pants;

   FIXEUID;

   shirt = clone_object(GOBLINS_DIR + "arm/rukh_shirt.c");
   pants = clone_object(GOBLINS_DIR + "arm/rukh_pants.c");

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
