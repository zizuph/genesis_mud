#pragma  strict_types

#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "../sys/defs.h"

inherit  (MORDOR_NPC + "soldier");

public void
reset_uruk() {}

public nomask void
reset_soldier() {
  reset_uruk();
}

public void
create_uruk() {}

public nomask void
create_soldier() {
  string adj = ({ "grim", "grumpy", "cruel", "angry",
                  "beastly", "mean", "foul", "dirty",
                  "brutal", "battered", "sinister", "scarred",
                  "wicked", "evil", "savage", "ugly",
                  "fierce", "dangerous", "yellow-eyed",
                  "red-eyed", "black-eyed", })[random(21)];
  int r = random(31);

  set_name("uruk");
  set_pname("uruk-hai");
  add_pname("uruks");
  set_race_name("uruk");
  set_adj(adj);
  add_adj("black-skinned");
  set_short(adj + " black-skinned uruk-hai");
  set_pshort(adj + " black-skinned uruk-hai");
  set_long("This is a " + adj + " black-skinned orc of large size, " +
           "bred by the Shadow of the East for increased strength, " +
           "intelligence, and resistance to the sun.  He is the " +
           "staple soldier of the Dark Lord's armies and often " +
           "appears in large numbers.\n");

  set_alignment(-300 - (r * 10));
  set_appearance_offset(25 + random(26));

  set_base_stat(SS_STR, 70 + r);
  set_base_stat(SS_DEX, 50 + r);
  set_base_stat(SS_CON, 70 + r);
  set_base_stat(SS_INT, 30 + r);
  set_base_stat(SS_WIS, 20 + r);
  set_base_stat(SS_DIS, 60 + r);

  switch (random(6)) {
    case 0 :
      set_skill(SS_WEP_SWORD, 40 + r);
      add_weapon(WEAP + "scimitar");
      add_armour(ARM + "shield");
      break;
    case 1 :
      set_skill(SS_WEP_CLUB, 40 + r);
      add_weapon(WEAP + "mace");
      add_armour(ARM + "shield");
      break;
    case 2 :
      set_skill(SS_WEP_AXE, 40 + r);
      add_weapon(WEAP + "battle_axe");
      add_armour(ARM + "shield");
      break;
    case 3 :
      set_skill(SS_WEP_POLEARM, 40 + r);
      add_weapon(WEAP + "spear");
      add_armour(ARM + "shield");
      break;
    case 4 :
      set_skill(SS_WEP_CLUB, 50 + r);
      add_weapon(WEAP + "morning_star");
      break;
    case 5 :
      set_skill(SS_WEP_POLEARM, 50 + r);
      add_weapon(WEAP + "halberd");
      break;
  }
  add_armour(ARM + "cap");
  add_armour(ARM + "shirt");
  add_armour(ARM + "skirt");
  set_skill(SS_PARRY, 40 + r);
  set_skill(SS_DEFENCE, 40 + r);

  add_prop(LIVE_I_SEE_DARK, 5);

  set_chat_time(15 + random(15));
  add_chat("We are the fighting Uruk-hai!");
  add_chat("Stop squeaking, you dunghill rat!");
  add_chat("Lugburz wants it, we do it!");
  add_chat("Curse you!");

  set_cchat_time(15 + random(15));
  add_cchat("Finish it!");
  add_cchat("Curse you, you little maggot!");
  add_cchat("Come here, and I'll squeeze your eyes out!");
  add_cchat("Let's string it up!");

  set_act_time(15 + random(15));
  add_act("burp");
  add_act("get all from corpse");
  add_act("hiss");
  add_act("grin");
  add_act("fart");

  set_cact_time(2 + random(2));
  add_cact("scream");
  add_cact("kick enemy");
  add_cact("snarl enemy");
  add_cact("glare enemy");

  MONEY_MAKE(random(3), "gold")->move(TO, 1);

  create_uruk();
}
