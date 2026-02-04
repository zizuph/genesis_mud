/*
  A generic walking monster that only travels in a certain directory (MY_PATH)
  and will go home when stuck (MY_HOME).
  /Nosferatu   May 29th '92
*/

inherit "std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

#define SEQ_RWALK "_mon_ranwalk"

static
string MY_HOME, MY_PATH;

create_monster() {
  if (!IS_CLONE) return;
  create_walk_monster();
  set_random_move(1);  /* only a trigger!! Look below!!! */
}

create_walk_monster() { }

mixed *my_filter(mixed *exits) {
  string tmp;
  int i;

  if (!exits || !sizeof(exits)) return 0;
  while (i < sizeof(exits)) {
    if (!sscanf(exits[i], MY_PATH + "%s", tmp)) {
      exits = exclude_array(exits, i, i+2);
    }
    else i += 3;
  }
  if (!sizeof(exits)) return 0;
  return exits;
}

void monster_ranwalk() {
  mixed *exits;
  int il;
  string ex, tmp;

  if (!environment()) return;
  if (monster_follow && present(monster_follow, environment())) return;
  exits = my_filter(environment()->query_exit());
  if (!exits) {
    this_object()->move_living("home", MY_HOME);
    ex = 0;
    il = 0;
  }
  else {
    il = random(sizeof(exits)) / 3;
    ex = exits[il*3+1];
    il = 4 + random(10);
  }
  this_object()->seq_clear(SEQ_RWALK);
  this_object()->seq_addfirst(SEQ_RWALK, ({ex, il, "@@monster_ranwalk"}));
}

set_my_home(str) { MY_HOME = str; }
set_my_path(str) { MY_PATH = str; }
query_my_home() { return MY_HOME; }
query_my_path() { return MY_PATH; }

