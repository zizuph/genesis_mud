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
   
   set_name("gruk");
   add_adj(({"muscular","grey-skinned"}));
   set_long("This goblin looks extremely strong and muscular! His skin is a " +
      "pale grey colour, and his arms appear to be covered in scars. He " +
      "appears to be the trainer in this hall.\n");
   set_race_name("goblin");
   set_gender(0);
   
   add_act("scowl");
   add_act("emote grabs a sword from the racks and practices his forms.");
   add_act("flex");
   add_act("say You don't look so tough to me, perhaps you need some lessons?");
   add_act("emote stretches out his body in a series of complex movements.");
   add_act("emote eyes you suspiciously, grunting in dissatisfaction.");
   add_act("cough silently");
   add_act("emote rubs his eyes wearily.");

   set_act_time(10);
   
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE, 100);

   set_stats(({ 300, 300, 350, 110, 110, 300}), 10);
   
   set_alignment(-500);
   
   
   intro_id = 0;
   set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
   object shirt, pants;

   FIXEUID;

   shirt = clone_object(GOBLINS_DIR + "arm/gruk_shirt.c");
   pants = clone_object(GOBLINS_DIR + "arm/gruk_pants.c");

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
