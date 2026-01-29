/*
 * The owner of the Stock Bakery.
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
   set_name("togo");
   add_name(({"","baker"}));
   set_living_name("_togo_");
  set_title("the Baker");
  set_race_name("hobbit"); 
  set_adj(({"short","friendly"}));
  set_long("@@my_long");
  default_config_npc(30);
  set_base_stat(SS_CON, 65);
  set_base_stat(SS_STR,60);
  set_base_stat(SS_DEX,80);
  set_base_stat(SS_DIS,95);
  set_base_stat(SS_INT,50);
  set_base_stat(SS_WIS,50);
   set_gender(0);
  set_skill(SS_PARRY,70);
  set_skill(SS_UNARM_COMBAT,60);
  set_skill(SS_DEFENCE,70);
  set_pick_up(75);
  set_alignment(400 + random(200));

  set_aggressive(0);
  set_attack_chance(0);

  add_prop(CONT_I_WEIGHT, 50000);   /* 50 Kg  */
  add_prop(CONT_I_VOLUME, 50000);   /* 50 Ltr */
   add_prop(LIVE_I_NEVERKNOWN, 1);

  trig_new("%s 'smiles' %s", "react_smile");

   set_act_time(3);
   add_act("emote rubs his hands together, wiping flour from them.");
   add_act("emote smiles happily at you.");
   add_act("emote whistles a jaunty tune.");
   add_act("emote pulls on the corner of his apron.");
   add_act("emote breathes deeply, inhaling the aromas of the bakery.");
   add_act("giggle");
  trig_new("%s 'introduces' %s", "react_introduce");
}

init_living() {
  if (this_player() == this_interactive()) set_alarm(1.0,0.0,&greet(this_player()));
  ::init_living();
}

greet(object ob) {
  if (!CAN_SEE(ob,this_object())) return;
  command("say Greetings " + ob->query_nonmet_name() + ". What can I do for you today" +
    "?");
}

my_long() {
  if (notmet_me(this_player())) this_player()->add_introduced("togo");
  return break_string("This is Togo the baker."+
         " He will tempt you with his delicious treats. "+
         "He is wearing a dirty apron, tied around "+
                      "his waist.\n", 70);
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
