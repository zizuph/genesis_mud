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
   set_adj("muscular");
   set_gender(2);
   set_alignment(-100);
   set_aggressive(1);
   set_stats(({ 80, 40, 80, 30, 40, 40 }));
   set_hp(300);
   set_skill(SS_2H_COMBAT, 40);
   set_skill(SS_WEP_SWORD, 40);
   set_skill(SS_BLIND_COMBAT, 75);
   set_skill(SS_PARRY, 55);
   set_skill(SS_DEFENCE, 20);
   add_prop(CONT_I_WEIGHT, 99000);
   add_prop(CONT_I_HEIGHT, 2200);
   add_prop(CONT_I_VOLUME, 85000);
   set_cchat_time(4);
   add_cchat("say Tear ung head frrrom yore body!");
   add_cchat("emote clangs its shortswords together in front of " +
      "itself and fights with renewed vigor and ferocity!");
   add_cchat("emote slices through your gut, cackling " +
      "evilly as your blood pours upon the floor!");
   set_act_time(3);
   add_act("emote swings its shortswords through the air " +
      "in a tremendous display of skill and prowess.");
   add_act("emote chuckles at your approach.");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   ob1 = MONEY_MAKE(36, "silver")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wsword1.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wsword1.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wgauntlets.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wbuckler.c")->move(TO);
   command("wear all");
   command("wield all");
   return 1;
}
