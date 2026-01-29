#pragma save_binary

inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_monster() {
   set_name(({"go_player","player", "go player"}));
   set_adj("Go");
   set_race_name("player");
   set_living_name("go_player");

   set_long(break_string(
      "This is a Go player sitting and thinking about the problem on the board "
    + "before him. He looks like he could use some help! Why don't you take a "
    + "look at the problem on the board and say what to play?\n",70));

   set_stats(({30,30,30,30,30,30}));

   add_prop(CONT_I_WEIGHT,100000);
   add_prop(CONT_I_HEIGHT,90);
   add_prop(LIVE_I_NEVERKNOWN,1);
   
   set_act_time(1);
   add_act("emote is thinking very hard.");
   add_act("emote ponders his next move.");
   add_act("say I don't understand this one...");
   add_act("say Hmmm...");
}

/* Called from the go_board.c */
make_noise(str) {
   tell_room(environment(),str);
}

