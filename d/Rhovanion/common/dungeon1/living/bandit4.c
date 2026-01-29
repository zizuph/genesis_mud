inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <money.h>
#include <macros.h>
void
create_monster() {
   int i;
   set_name("digger");
   add_name("kow");
   set_race_name("human");
   set_adj("dirty");
   set_adj("short");
   set_gender(0);
   set_alignment(-75);
   set_aggressive(0);
   set_stats(({ 35, 30, 35, 10, 19, 35 }));
   set_hp(100);
   set_skill(SS_DEFENCE, 20);
   set_skill(SS_BLIND_COMBAT, 20);
   set_skill(SS_PARRY, 11);
   set_skill(SS_WEP_KNIFE, 29);
   add_prop(CONT_I_WEIGHT, 93000);
   add_prop(CONT_I_HEIGHT, 2000);
   add_prop(CONT_I_VOLUME, 85000);
   set_act_time(10);
   add_act("emote digs out more dirt with his shovel.");
   add_act(({"emote pulls out a handkerchief and wipes his brow.",
            "say Further?" }));
   set_alarm(1.0,0.0,"get_stuff");
   set_alarm(2.0,0.0,"join_leader");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   clone_object("/d/Rhovanion/common/dungeon1/gear/shovel.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/banarmour2.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/bandag2.c")
   ->move(TO);
   ob1 = MONEY_MAKE(55,"copper")->move(TO);
   command("wear all");
}
void
attacked_by(object ob) {
   object *arr;
   int i;
   ::attacked_by(ob);
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
   arr[i]->notify_ob_attacked_me(this_object(), ob);
   command("drop shovel");
   command("wield all");
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
      command("shout NOooooo!!!");
      command("drop shovel");
      command("wield all");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
join_leader() {
   command("join bandit");
}
