inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <money.h>
void
create_monster() {
   int i;
   set_name("bandit leader");
   add_name("bandit");
   set_race_name("human");
   set_adj("unshaven");
   set_adj("dashing");
   set_gender(0);
   set_alignment(-150);
   set_aggressive(0);
   set_stats(({ 45, 65, 35, 30, 50, 75 }));
   set_hp(450);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_BLIND_COMBAT, 45);
   set_skill(SS_PARRY, 55);
   set_skill(SS_UNARM_COMBAT, 31);
   add_prop(CONT_I_WEIGHT, 89000);
   add_prop(CONT_I_HEIGHT, 1900);
   add_prop(CONT_I_VOLUME, 81000);
   set_act_time(10);
   add_act("say I am the best swordsman ever lived.!");
   add_act("emote slices his long sword through the air and parries a couple of times in boredom.");
   add_act("say I could cleave you in two should I choose to do so.");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   clone_object("/d/Rhovanion/mute/dungeon1/banshirt.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/banpants.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/banboots.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/bansword.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/ring.c")->move(TO);
   ob1 = MONEY_MAKE(100,"silver")->move(TO);
   command("wield all");
   command("wear all");
   command("invite kow");
   set_act_time(1);
   add_act("invite thief");
}
void
attacked_by(object ob) {
   object *arr;
   int i;
   ::attacked_by(ob);
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
   arr[i]->notify_ob_attacked_me(this_object(), ob);
}
void
notify_ob_attacked_me(object friend, object attacker) {
   if (query_attack())
      return;
   if (random(10))
      call_out("help_friend", 1, attacker);
}
void
help_friend(object ob) {
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("say Why don't you try your hand at this!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
