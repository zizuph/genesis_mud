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
   
   set_name("palandur");
   add_adj(({"strong","black-haired"}));
   set_long("This strong, black-haired human appears to be the local blacksmith for the " +
      "village of Gairent.\n");
   set_race_name("human");
   set_gender(0);
   
   add_act("smile all");
   add_act("emote hammers away in the forge.");
   add_act("emote wipes some sweat from his brow.");
   add_act("emote washes some grime from his face.");
   add_act("emote stretches his tired muscles.");
   
   set_act_time(4);
   
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_WEP_CLUB,100);
   set_skill(SS_DEFENCE, 100);

   set_stats(({ 200, 100, 160, 70, 70, 120}), 10);
   
   set_alignment(270);
   
   
   intro_id = 0;
   set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
   object hammer, apron;

   FIXEUID;

   hammer = clone_object(WOODSMEN_DIR + "/wep/hammer.c");
   apron = clone_object(WOODSMEN_DIR + "arm/apron.c");

   hammer->move(TO);
   apron->move(TO);
   
   command("wear all");
   command("wield all");
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
