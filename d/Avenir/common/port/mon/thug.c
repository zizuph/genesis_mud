// -*-C++-*-
// file name: ~Avenir/common/port/mon/thug.c
// creator(s): Boriska, Aug 1995
// last update: Boriska, Nov 95.
// purpose:    NPC for port area, carries brass knuckles for left hand.
// note:       Wimpy routines used to clone several more thugs to help
//             us in combat if we're losing it. 
// bug(s):
// to-do:     


#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <state_desc.h>
#include "/d/Avenir/common/common.h"

#define HEALTH_DROP 25
// call for help each time out health goes down by this value (in %%)

#define HELPER_LIMIT 2
// how many times we call for help

#define D(x) (find_player("boriska")->catch_msg((x)))

inherit "/std/monster";

void wear_knuckles();
static void remove_knuckles();

private int last_health; // stores previous health value 
private int count;       // counts # of NPCs we called for help
private int alarm_id;    
private string *sd_health = SD_HEALTH;

void
create_monster() {
  if (!IS_CLONE)
    return;
  set_name("thug");
  set_adj("skulking");
  set_race_name("port thug");
  set_long("This is a nondescript man in hanging grey clothes you hardly " +
	   "notice till he gets very close to you and saves you the " +
	   "trouble of carrying heavy money purse around.\n");
  
  set_stats(({90, 100, 100, 60, 60, 90}));
  set_alignment(-1000);

  set_chat_time(3);
  add_chat("Burn you!");
  add_chat("Hey ya, gimme all your money!");
  add_chat("My distant relative Barmaley went to the caves looking for " +
	   "an immense treasure.");
  
  set_act_time(5);
  add_act("hide");
  add_act("peek all");
  
  set_skill( SS_DEFENSE, 100 );
  set_skill( SS_UNARM_COMBAT, 100 );
  set_skill( SS_AWARENESS, 70 );
  set_skill( SS_HIDE, 80 );
  set_skill( SS_PICK_POCKET, 30);
  set_whimpy(100 - HEALTH_DROP);
  last_health = query_max_hp();
}


void
equip_me() {
  object knuckles;
  int i;
  
  seteuid(getuid());
  
  MONEY_MAKE_SC(random(50))->move(this_object(), 1);

  clone_object(PORT + "obj/jacket")->move(this_object(), 1);
  command("wear all");
  
  knuckles = clone_object(PORT + "obj/knuckles");
  knuckles->configure_me(A_L_HAND);
  knuckles->move(this_object(), 1);

  for (i = 0; i < 6; i++)
    clone_object(PORT + "obj/rum")->move(this_object(),1);
  // we can drink 5 flasks of rum at once when sober
}

void
attacked_by(object ob) {
  ::attacked_by(ob);
  set_alarm(1.0, 0.0, wear_knuckles);
}

void
wear_knuckles() {
  command("wear knuckles");
  command("drink all");
  if (!alarm_id)
    // check whether we're fighting once for a while and remove knuckles
    // if we are not.
    alarm_id = set_alarm(60.0, 60.0, remove_knuckles);
}

// This is called to check whether to run when our health goes lower than
// whimpy level. We use it to check out health periodically
// and clone a couple more of tough guys if we're getting hurt.
// Helping guys have their whimpy set to 0 so run_away() is never
// called in them. This avoids exponential cloning of helpers.
void
run_away() {
  int health;
  object another_thug;
  object room;
  string hd;
  
  // do not clone thugs in unlimited quantities
  if (count > HELPER_LIMIT) 
    return;
  
  health = 100 * query_hp() / query_max_hp();
  if (last_health - health > HEALTH_DROP) {
    hd = sd_health[health * sizeof(sd_health) / 100];
    command("shout Help me pals! I am " + hd + "!");
    another_thug = clone_object(PORT + "mon/thug");
    another_thug->equip_me();
    another_thug->set_helper(); // this one will not call for help
    team_join(another_thug);
    room = environment();
    another_thug->move_living("M", room);
    tell_room(room, "A port thug arrives running!\n");
    another_thug->command("kill " + query_attack()->query_real_name());
    another_thug->wear_knuckles();
    last_health = health;
    count++;
  }
}

void
set_helper(object ob) {
  set_whimpy(0);
}

void
remove_knuckles() {
  if (objectp(query_attack())) {
    command("drink all"); //keep drunk while fighting
    return;
  }
  command("remove knuckles");
  remove_alarm(alarm_id);
  alarm_id = 0;
}

void
do_die(object killer) {
  command ("shout Run! Run for your lives!");
  query_team_others()->run();
  ::do_die(killer);
}

private void
do_run() {
  command ("say Time to get outta here!");
  command ("emote sneaks away.");
  remove_object();
}

void
run() { set_alarm(itof(random(10)), 0.0, do_run); }





