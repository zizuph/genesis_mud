/*
 * The keeper of the Perfumery Inn in Bree.
 * Cloned by ~Shire/common/bree/perfumery
 */
inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

//   Prototypes
void return_introduce();
void return_smile(string who);
void greet(object player);

void
create_monster() {
  if (!IS_CLONE) return;
   set_name("gudran");
   add_name(({"","shopkeeper"}));
   set_living_name("gudran");
  set_title("Shopkeeper of the Bree Perfumery");
  set_race_name("human"); 
  set_adj(({"short","thin"}));
  set_long("@@my_long");
  default_config_npc(30);
  set_base_stat(SS_CON, 39);
   set_gender(1);

  set_skill(SS_UNARM_COMBAT,20);
  set_skill(SS_DEFENCE,30);
  set_pick_up(75);

  set_aggressive(0);
  set_attack_chance(0);

  add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
  add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   add_prop(LIVE_I_NEVERKNOWN, 1);

  trig_new("%s 'smiles' %s", "react_smile");

   set_act_time(3);
   add_act("emote cleans the counter deliberately.");
   add_act("emote smells the air carefully.");
   add_act("emote washes some old perfume bottles.");
   add_act("emote grinds up some rose petals.");
   add_act("emote wonders when someone will buy from her.");
   add_act("chuckle");
  trig_new("%s 'introduces' %s", "react_introduce");
}

init_living() {
  if (this_player() == this_interactive()) set_alarm(1.0,0.0,&greet(this_player()));
  ::init_living();
}

greet(object ob)
{
    string str;

    if(random(2))
	str = (". What can I interest you in?");
    else
	str = (". What can I do for you?");

  /* can this object() see ob ? - fixed by Elwing */
  if (!CAN_SEE(this_object(),ob)) return;
  command("say Hello " + ob->query_nonmet_name() + str);
}

my_long() {
  if (notmet_me(this_player())) this_player()->add_introduced("gudran");
  return break_string("Meet Gudran the perfume-maker."+
         " She will sell you any one of her fine perfumes. "+
         "She seems to be grinding rosebuds in her "+
                      "hand.\n", 70);
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
