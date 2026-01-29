inherit "/std/monster";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <money.h>
void
create_monster() {
   set_name("guard");
   set_race_name("wyrmman");
   set_adj("reptilian");
   set_adj("strapping");
   set_gender(2);
   set_alignment(-100);
   set_aggressive(0);
   set_stats(({ 70, 60, 80, 30, 50, 40 }));
   set_hp(500);
   set_skill(SS_2H_COMBAT, 40);
   set_skill(SS_WEP_KNIFE, 40);
   set_skill(SS_BLIND_COMBAT, 75);
   set_skill(SS_PARRY, 45);
   add_prop(CONT_I_WEIGHT, 99000);
   add_prop(CONT_I_HEIGHT, 2200);
   add_prop(CONT_I_VOLUME, 85000);
   set_act_time(5);
   add_act("emote rummages through your belongings...");
   add_act("emote takes one of your gold coins from you.");
   add_act("emote takes one of your platinum coins from you.");
   add_act("emote goes: Dost no have you all else?");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   ob1 = MONEY_MAKE(25, "silver")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wdagger.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wdagger.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/warmour2.c")->move(TO);
   command("wear all");
   command("wield all");
   return 1;
}
