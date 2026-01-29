inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <money.h>
void
create_monster() {
   int i;
   set_name("rogue");
   set_adj("scruffy");
   set_adj("large");
   set_race_name("human");
   set_gender(0);
   set_alignment(-50);
   set_aggressive(1);
   set_stats(({ 40, 40, 40, 15, 30, 45 }));
   set_hp(300);
   set_skill(SS_DEFENCE, 35);
   set_skill(SS_BLIND_COMBAT, 25);
   set_skill(SS_PARRY, 15);
   set_skill(SS_WEP_POLEARM, 35);
   set_skill(SS_UNARM_COMBAT, 10);
   add_prop(CONT_I_WEIGHT, 90000);
   add_prop(CONT_I_HEIGHT, 1859);
   add_prop(CONT_I_VOLUME, 85000);
   set_act_time(1);
   add_act("say I hate you, and I hate having to guard here.");
   add_act("say I hate getting stuck in dungeons.");
   add_act("emote hits the other bandit with his pole axe.");
   add_act("shouts Oww, that hurt!");
   add_act("say Now you're really going to get it!");
   add_act(({"say I'm gonna rip your head off and rip all the skin off of it. " +
            "Then I'm gonna put it back on your shoulders...","giggle","...and then I'm gonna rip your head off and I'm gonna kick it!  Then I'll put it back!" }));
   add_act("emote laughs at your head!");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   clone_object("/d/Rhovanion/mute/dungeon1/banarmour1.c")->move(this_object());
   clone_object("/d/Rhovanion/mute/dungeon1/banpole.c")->move(this_object());
   clone_object("/d/Rhovanion/mute/dungeon1/bracelet.c")->move(this_object());
   ob1 = MONEY_MAKE(75,"copper")->move(TO);
   command("wield all");
   command("wear all");
}
