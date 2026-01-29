inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include "/sys/macros.h"
#include <money.h>
void
create_monster() {
   int i;
   set_name("thief");
   set_living_name("thief");
   set_adj("shadowy");
   set_adj("short");
   set_race_name("elf");
   set_gender(0);
   set_alignment(-75);
   set_aggressive(0);
   set_stats(({ 30, 50, 35, 30, 40, 50 }));
   set_hp(250);
   set_skill(SS_DEFENCE, 45);
   set_skill(SS_BLIND_COMBAT, 30);
   set_skill(SS_PARRY, 25);
   set_skill(SS_UNARM_COMBAT, 15);
   set_skill(SS_WEP_KNIFE, 40);
   set_skill(SS_SNEAK, 45);
   set_skill(SS_HIDE, 40);
   add_prop(CONT_I_WEIGHT, 88000);
   add_prop(CONT_I_HEIGHT, 1800);
   add_prop(CONT_I_VOLUME, 80000);
   set_act_time(0);
   add_act("join bandit");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   clone_object("/d/Rhovanion/common/dungeon1/gear/banarmour1.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/bandag.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/coral.c")
   ->move(TO);
   ob1 = MONEY_MAKE(100,"copper")->move(TO);
   command("wield all");
   command("wear all");
}
init_living() {
   ::init_living();
   if (interactive(this_player())) {
      part_sneak();
   }
}
part_sneak() {
   object ob;
   ob = present(this_player(), environment());
   if (!ob) return 0;
   if (!CAN_SEE(this_object(), this_player())) {
      write("Is there someone sneaking here?\n");
      return 0;
   }
   command("hole");
   command("sneak north");
   command("hide");
   set_alarm(2.0,0.0,"join_leader");
}
join_leader() {
   command("join bandit");
   command("join bandit");
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
      write("A shadowy figure leaps out from behind a pile " +
         "of dirt and backstabs you!\n");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
