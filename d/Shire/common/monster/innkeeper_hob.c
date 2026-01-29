/*
 * The innkeeper on the road to Grey Havens.
 * Cloned by ~Shire/common/greyhaven/inn
 */
inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "tobacco.h"

create_monster() {
  if (!IS_CLONE) return;
  set_name("dolin");
  set_title("Merryman the Tavernmaster of Michel Delving");
  set_adj(({"stout","pot-bellied"}));
  set_race_name("hobbit"); 
  set_long("Dolin runs the tavern here in Michel Delving. "+
    "He is always happy to serve his customers.\n");
  default_config_npc(30);
  set_base_stat(SS_CON, 45);

  set_skill(SS_UNARM_COMBAT,20);
  set_skill(SS_DEFENCE,30);
  set_pick_up(75);
  clone_tobacco();
  clone_tobacco(); /* He's well off, let's give him 2. */

  set_aggressive(0);
  set_attack_chance(0);

  add_prop(CONT_I_WEIGHT, 40000);   /* 40 Kg  */
  add_prop(CONT_I_VOLUME, 40000);   /* 80 Ltr */

  trig_new("%s 'smiles' %s", "react_smile");
  trig_new("%s 'sighs' %s", "react_sigh");
  trig_new("%s 'introduces' %s", "react_introduce");
}

init_living() {
  if (this_player() == this_interactive()) call_out("greet", 1, this_player());
  ::init_living();
}

greet(object ob) {
  command("say Hello there " + ob->query_nonmet_name() + ". What can I "
	  + "serve you?");
  command("introduce myself");
}


react_smile(who, tmp) {
  int r;

  if (!who) return 0;
  who = lower_case(who);
  r = random(3);
  if (r) call_out("return_smile", r, who);
  else return return_smile(who);
  return 1;
}

return_smile(who) {
  object ob;

  ob = present(who, environment());
  if (!ob) return 0;
  switch (random(4)) {
    case 0: command("smile"); return 1;
    case 1: command("smile " + who); return 1;
    case 2: if (notmet_me(ob)) {
              command("introduce myself to " + who);
              return 1; 
            }
            break;
  }
  return 0;
}

react_sigh(who, tmp) {
  if (!who) return 0;
  who = lower_case(who);
  if (random(3)) return 0;
  command("say Are you gonna order something or what?");
  return 1;
}

react_introduce(who, tmp) {
  object ob;
 
  if (!who) return 0;
  who = lower_case(who);
  ob = present(who, environment());
  if (!ob) return 0;
  if (!notmet_me(ob)) return 0;
  if (!random(20)) return 0;
  call_out("return_introduce", random(9));
  return 1;
}

return_introduce() {
  command("introduce myself");
}
