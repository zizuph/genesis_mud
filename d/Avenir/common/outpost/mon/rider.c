// -*-C++-*-
// file name: ~Avenir/common/outpost/mon/riderr.c
// creator(s): Boriska, Sep 1995
// last update:
// purpose:    NPC for outpost area, carries spurs.
// note:       
// bug(s):
// to-do:     

#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include "/d/Avenir/common/common.h"

inherit "/std/monster";

void
create_monster() {
  if (!IS_CLONE)
    return;
  set_name("rider");
  set_adj("confused");
  set_race_name("rider");
  set_long("Judging the shape of this man's legs you conclude that he " +
	   "spent more time of his life sitting on horse's back than " +
	   "walking. Sharp spurs worn on his feet give him a nasty look.\n");
	   
  set_stats(({100, 100, 100, 70, 70, 70}));
  set_alignment(0);

  set_chat_time(3);
  add_chat("Have you seen my horse???");
  add_chat("I hate walking on foot!");
  add_chat("Somebody stole my horse while I was drinking in the pub!");
  add_chat("Oh, how my feet hurt!");

  add_act("puzzled");
  add_act("confused");

  set_random_move(3);
  
  set_skill( SS_DEFENSE, 100 );
  set_skill( SS_UNARM_COMBAT, 100 );
  set_skill( SS_AWARENESS, 50 );
}

void
equip_me() {
  object spur;
  
  seteuid(getuid());
  
  MONEY_MAKE_SC(random(50))->move(this_object(), 1);
  
  clone_object(OUTPOST + "obj/r_boots")->move(this_object(), 1);
  clone_object(OUTPOST + "obj/r_hat"  )->move(this_object(), 1);
  clone_object(OUTPOST + "obj/r_cloak")->move(this_object(), 1);
  
  spur = clone_object(OUTPOST + "obj/spur");
  spur->configure_me(A_R_FOOT);
  spur->move(this_object(), 1);
  
  spur = clone_object(OUTPOST + "obj/spur");
  spur->configure_me(A_L_FOOT);
  spur->move(this_object(), 1);
  
  command("wear all");
}
