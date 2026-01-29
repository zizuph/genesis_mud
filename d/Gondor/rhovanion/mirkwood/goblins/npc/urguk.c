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
   
   set_name("urguk");
   set_title("Silvertongue, Merchant Extraordinaire");
   add_adj(({"narrow-faced","sharp-eyed"}));
   set_long("This goblin is very well dressed and probably quite wealthy! " +
      "Judging by appearances, this goblin is a very successful merchant.\n");
   set_race_name("goblin");
   set_gender(0);
   
   add_act("smile brightly");
   add_act("emote straightens up some goods on the shelves.");
   add_act("emote picks up a broom and begins to sweep the floor.");
   add_act("say Would you like to buy something? I sell only the finest " + 
      "goods here!");
   add_act("emote ducks through the opening in the west wall for a moment " +
      "before returning with some goods to restock the shelves.");
   add_act("emote carefully cleans the surface of his sales counter.");
   add_act("greet all");
   add_act("say It is a long trip to the Misty Mountains, but if you know " +
      "what you are doing, there is good profit to be made!");

   set_act_time(10);
   
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE, 100);

   set_stats(({ 100, 100, 100, 110, 110, 100}), 10);
   
   set_alignment(-500);
   
   
   intro_id = 0;
   set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
   object shirt, pants;

   FIXEUID;

   shirt = clone_object(GOBLINS_DIR + "arm/urguk_shirt.c");
   pants = clone_object(GOBLINS_DIR + "arm/urguk_pants.c");

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
