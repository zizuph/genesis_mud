// Goblin digger, hired and cloned :) by dark/mon/rogue
// Made by Boriska, Feb 28 1995

inherit "/std/monster";

#include "/d/Avenir/common/dark/dark.h"

void
create_monster()
{
  set_name ("digger");
  set_short("goblin digger");
  set_long(
	   "This short goblin was persuaded by Barmaley to do some digging " +
	   "and carving work deep underground. Now there is a regretful " +
	   "expression on his wrinkled face, the assignment turned to be " +
	   "much more difficult than he expected.\n");
  set_race_name("goblin");
  set_stats( ({70,40,40,1,1,5}) );
  set_alignment(0);
  
  set_skill(SS_WEP_AXE, 50);
  set_skill(SS_WEP_CLUB, 50);
  set_skill(SS_2H_COMBAT, 50);
  
  set_act_time(5);
  add_act("emote pretends he is busy working.");
  add_act("emote moves a small rock out of his way.");
  add_act("duh");
  add_act("scream");
}

void
equip_me()
{
  seteuid(getuid());
  clone_object(OBJ + "t_rope")->move(this_object());
  clone_object(OBJ + "t_hammer")->move(this_object());
  clone_object(OBJ + "t_torch")->move(this_object());
  clone_object(OBJ + "t_pickaxe")->move(this_object());
  command("wield all");
}

// called from master rogue when he dies
void
flee() { set_alarm(3.0, 0.0, "do_flee"); }

private void
do_flee()
{
  command("say Gee, that stinker's dead!");
  command("cheer");
  command("say Time to go...");
  command("emote runs away.");
  remove_object();
}
