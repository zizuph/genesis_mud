/* squirrel that steals chicken.
created for Icewall by Stevenson */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
inherit C_FILE
inherit "/std/act/domove";
inherit "/std/act/action";

create_creature() {
   int i;
   set_short("white squirrel");
   set_race_name("squirrel");
   set_name("squirrel");
   set_adj("white");
   set_long("This is a white squirrel which is common to these parts. "
      + "It has a fondness for food, so watch yer step."
      + "\n");
   
   
   set_alarm(1.0,0.0,"set_m_in","scampers in.");
   set_alarm(1.0,0.0,"set_m_out","scampers");
   for (i=0;i<6;i++)
   set_base_stat(i, 15+random(5));
   
   set_skill(SS_DEFENCE, 15);
   set_knight_prestige(-1);
   set_alignment(1);
   
   set_hp(query_max_hp());
   set_monster_home(ICE_FOREST+"forest_5.c");
   set_restrain_path(ICE_FOREST);
   set_random_move(30);
   
   set_act_time(1);
   add_act("emote sniffs the air hungrily.");
   add_act("emote chitters noisily.");
   add_act("emote approaches you cautiously.");
   add_act("@@steal_something");
   add_act("@@steal_something");
   add_act("@@steal_something");
   add_act("@@steal_something");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_NO_CORPSE,1);
   add_prop(CONT_I_VOLUME,250);
   add_prop(CONT_I_WEIGHT,500);
   
   set_attack_unarmed(0, 10, 10, W_IMPALE, 60, "bite");
   set_attack_unarmed(1, 10, 10, W_SLASH, 40, "claw");
   
   set_hitloc_unarmed(0, 5, 30, "head");
   set_hitloc_unarmed(1, 5, 30, "tail");
   set_hitloc_unarmed(2, 7, 40, "back");
}

string steal_something() {
   int i;
   object * ob = all_inventory(E(TO));
   object what;
   ob = FILTER_PLAYERS(ob);
   if (ob && sizeof(ob))
      for (i=0;i<sizeof(ob);i++)
   if (what = P("icechicken",ob[i])) {
      what->remove_object();
      ob[i]->catch_msg(QCTNAME(TO)+" steals a piece of "
         + "chicken from you.\n");
      tell_room(E(TO),QCTNAME(TO)+" devours a piece of chicken.\n");
      return "";
   }
   return "";
}

do_die(object killer) {
   tell_room(E(killer),"\nAn angel descends from the squirrel "
      + "heavens to reclaim the body of the one that "
      + QCTNAME(killer) + " just butchered.\n\n");
   ::do_die(killer);
}
