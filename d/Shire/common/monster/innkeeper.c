/*
 * The keeper of the Prancing Pony Inn in Bree.
 * Cloned by ~Shire/common/bree/inn
 *
 * I have made some changes to this file and not all of them are too
 * good I expect but I couldn't make the change to set_alarm work
 *
 *                                           Morinir June 1996
 */
inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "tobacco.h"
#include "/d/Shire/common/defs.h";

/// Prototypes
void do_greet(object ob);

create_monster() {
  if (!IS_CLONE) return;
  set_name(({"human", "barliman"}));
  set_race_name("innkeeper"); 
  set_long("@@my_long");
  default_config_npc(30);
  set_base_stat(SS_CON, 30);

  set_skill(SS_UNARM_COMBAT,20);
  set_skill(SS_DEFENCE,30);
  set_pick_up(75);
  clone_tobacco();

  set_aggressive(0);
  set_attack_chance(0);

  add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
  add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */

  trig_new("%s 'smiles' %s", "react_smile");
  trig_new("%s 'sighs' %s", "react_sigh");
  trig_new("%s 'introduces' %s", "react_introduce");
}

void
do_greet(object ob) {
  command("say Hi there "+ob->query_nonmet_name()+
          ". What can I serve you?");
}

init_living() {
  if (TP==TI) set_alarm(1.0, 0.0, &do_greet(TP));
  ::init_living();
}

my_long() {
  if (notmet_me(this_player())) this_player()->add_introduced("barliman");
  return break_string("Meet Barliman Butterbur the innkeeper. Barliman "+
                      "Butterbur will serve you anything on the "+
                      "menu. Barliman Butterbur is human and you wonder "+
                      "what he is doing here in the land of the Hobbits. "+
                      "He is currently holding a tiny mirror in his right "+
                      "hand.\n", 70);
}

return_smile(string who) {
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

react_smile(string who, string tmp) {
  float r;

  if (!who) return 0;
  who = lower_case(who);
  r = random(3.0);
  if (r) set_alarm(r, 0.0, &return_smile(), who);
  else return return_smile(who);
  return 1;
}

react_sigh(string who, string tmp) {
  if (!who) return 0;
  who = lower_case(who);
  if (random(3)) return 0;
  command("say Are you gonna order something or what?");
  return 1;
}

return_introduce() {
  command("introduce myself");
}

react_introduce(string who, string tmp) {
  object ob;
  float wait;
 
  if (!who) return 0;
  who = lower_case(who);
  ob = present(who, environment());
  if (!ob) return 0;
  if (!notmet_me(ob)) return 0;
  if (!random(20)) return 0;

  wait=random(9.0);

  set_alarm(wait, 0.0, &return_introduce());
  return 1;
}
