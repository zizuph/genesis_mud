/*
 * The owner of the Stock Tailor Shop.
 */
inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"

//  Prototypes
void return_introduce();
void greet(object player);
void return_smile(string who);

void
create_monster() {
  if (!IS_CLONE) return;
   set_name("robin");
   add_name(({"","tailor"}));
   set_living_name("_robin_");
  set_title("the Tailor");
  set_race_name("hobbit"); 
  set_adj(({"merry","helpful"}));
  set_long("@@my_long");
  default_config_npc(30);
  set_base_stat(SS_CON, 65);
  set_base_stat(SS_STR,40);
  set_base_stat(SS_DEX,60);
  set_base_stat(SS_DIS,70);
  set_base_stat(SS_INT,30);
  set_base_stat(SS_WIS,30);
   set_gender(0);
  set_skill(SS_PARRY,60);
  set_skill(SS_UNARM_COMBAT,50);
  set_skill(SS_DEFENCE,50);
  set_pick_up(75);
  set_alignment(400 + random(200));

  set_aggressive(0);
  set_attack_chance(0);

  add_prop(CONT_I_WEIGHT, 60000);   /* 60 Kg  */
  add_prop(CONT_I_VOLUME, 60000);   /* 60 Ltr */
   add_prop(LIVE_I_NEVERKNOWN, 1);

  trig_new("%s 'smiles' %s", "react_");

   set_act_time(3);
   add_act("emote sticks his sewing needle in his finger and starts to suck on it.");
   add_act("emote grins as he watches you look around.");
   add_act("emote hums to himself as he works.");
   add_act("emote riffles through his stacks of fabric.");
   add_act("emote finishes a garment, displaying it proudly.");
   add_act("giggle");
  trig_new("%s 'introduces' %s", "react_introduce");
}

init_living() {
  if (this_player() == this_interactive()) set_alarm(1.0,0.0,&greet(this_player()));
  ::init_living();
}

greet(object ob) {
  if (!CAN_SEE(ob,this_object())) return;
  command("say Greetings " + ob->query_nonmet_name() + ". Can I interest you in some new clothes" +
    "?");
}

my_long() {
  if (notmet_me(this_player())) this_player()->add_introduced("robin");
  return break_string("This is Robin the tailor."+
         " He will try persuading you into buying some of his clothes. "+
         "He is wearing a brightly coloured hand stiched vest "+
                      "and dark green short pants.\n", 70);
}

react_smile(who, tmp) {
  int r;

  if (!who) return 0;
  who = lower_case(who);
  r = random(3);
  if (r) set_alarm(itof(r),0.0,&return_smile(who));
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


react_introduce(who, tmp) {
  object ob;
 
  if (!who) return 0;
  who = lower_case(who);
  ob = present(who, environment());
  if (!ob) return 0;
  if (!notmet_me(ob)) return 0;
  if (!random(20)) return 0;
  set_alarm(itof(random(9)),0.0,&return_introduce());
  return 1;
}

return_introduce() {
  command("introduce myself");
}
