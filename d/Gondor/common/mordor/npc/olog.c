#pragma  strict_types

#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <money.h>
#include "../sys/defs.h"

inherit  (MORDOR_NPC + "soldier");

public void
reset_olog() {}

public nomask void
reset_soldier() {
  reset_olog();
}

public void
create_olog() {}

public nomask void
create_soldier() {
  string adj = ({ "grim", "grumpy", "cruel", "angry",
                  "beastly", "mean", "foul", "dirty",
                  "brutal", "battered", "sinister", "scarred",
                  "wicked", "evil", "savage", "ugly",
                  "fierce", "dangerous", "yellow-eyed",
                  "red-eyed", "black-eyed", })[random(21)];
  int r = random(41);

  set_name("olog");
  add_name("troll");
  set_pname("olog-hai");
  add_pname("ologs");
  set_race_name("olog");
  set_adj(adj);
  add_adj("powerful");
  set_short(adj + " powerful olog-hai");
  set_pshort(adj + " powerful olog-hai");
  set_long(capitalize(LANG_ADDART(implode(query_adjs()," "))) +
           " troll, one of the Olog-hai, the troll-race bred by the " +
           "Dark Lord in the mountains of Mordor.  They are larger, " +
           "fiercer, and more cunning than normal trolls, but like " +
           "them are as hard as stone.\n");

  set_alignment(-300 - (r * 10));
  set_appearance_offset(25 + random(26));

  set_base_stat(SS_STR, 200 + r);
  set_base_stat(SS_DEX, 150 + (r / 2));
  set_base_stat(SS_CON, 250 + (r * 2));
  set_base_stat(SS_INT, 55 + (r / 2));
  set_base_stat(SS_WIS, 25 + (r / 2));
  set_base_stat(SS_DIS, 80 + (r / 2));

  switch (random(2)) {
    case 0 :
      set_skill(SS_WEP_CLUB, 70 + r);
      add_weapon(MORDOR_WEAP + "morning_star");
      break;
    case 1 :
      set_skill(SS_WEP_POLEARM, 70 + r);
      add_weapon(MORDOR_WEAP + "halberd");
      break;
  }
  add_armour(MORDOR_ARM + "cap");
  add_armour(MORDOR_ARM + "platemail");
  add_armour(MORDOR_ARM + "skirt");
  set_skill(SS_PARRY, 70 + r);
  set_skill(SS_DEFENCE, 70 + r);

  add_prop(LIVE_I_SEE_DARK, 5);

  set_chat_time(15 + random(15));
  add_chat("We are the mighty Olog-hai!");
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

  MONEY_MAKE(random(6), "gold")->move(TO, 1);
  MONEY_MAKE(random(4), "platinum")->move(TO, 1);

  create_olog();
}
