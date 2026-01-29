/*
 *    A hobbit that rewards players for solving a small quest
 *    Cloned by /d/Shire/common/hobbiton/er2
 */

inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/monster/tobacco.h"

//   Prototypes
void arm_me();
void return_introduce(string who);
void reset_intr();

int intro;

/*
 * Function name:create_monster
 * Description  :The standard create_monster
 */
create_monster() {

  if (!IS_CLONE) return;
  set_name("tobold");
  add_name("shirriffe");
  set_living_name("_tobold_");
  set_adj("wary");
  set_race_name("hobbit");
  set_long("This is a member of the local police force. He looks like "
      + "he is quite capable of looking after himself.\n");

  set_short("shirriffe");
  default_config_npc(95);      
  set_hp(50000);

  add_cmdsoul("/d/Shire/bounders/soul/bounder_soul"); update_hooks();

  set_skill(SS_WEP_POLEARM, 100);
  set_skill(SS_DEFENCE, 90);
  set_skill(SS_PARRY, 90);
  set_skill(SS_WEP_MISSILE, 90);
  set_skill(SS_AWARENESS, 90);
/*  set_skill(SS_DECK, 100);
  set_skill(SS_NAIL, 100); */
  set_skill(SS_WEP_KNIFE, 100);

  add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
  add_act("bstance");
  set_act_time(15);
/* add_ask(({"help", "quest", "for help", "for quest", "about quest"}), VBFC_ME("try_to_tell"));
  set_default_answer("The hobbit says: I don't know what you mean.\n");
*/
  trig_new("%s 'introduces' %s", "react_introduce");

  intro = 1;

  set_alarm(0.1,0.0,&arm_me());
  clone_tobacco();

}

arm_me() {

  object staff;

  staff = clone_object(HOBBIT_DIR + "wep/bstaff");
  staff->move(this_object());
  command("wield staff");

}

return_introduce(string who) {
  if (random(4) && present(who, environment())) {
    command("introduce myself to " + who);
   }
  else {
    command("introduce myself");
   }
}

/*
 * Function name:react_introduce
 * Description  :Introduce myself when someone else does it.
 */
react_introduce(who, tmp) {
  if (!intro) return 0;
  intro = 0;
  set_alarm(30.0,0.0,&reset_intr());
/*  set_alarm(itof(random(3) + 2),0.0,&return_introduce(who)); */
  return 1;
}


/*
* Function name:query_knight_prestige
* Description  :returns a value for the knights.
*/
query_knight_prestige() { return (-5); }

reset_intr() {

  intro = 1;

}
