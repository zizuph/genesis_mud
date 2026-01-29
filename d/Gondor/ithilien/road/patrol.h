#include <ss_types.h>
#include "/d/Gondor/defs.h"

int move_patrol_alarm;

void move_patrol(object ob);

public void
enter_inv(object ob, object from)
{
  string npc_name;
  npc_name = ob->query_real_name();
  ::enter_inv(ob, from);
  if (TO->query_lookout_message()) {
    if(living(ob))
      "/d/Gondor/ithilien/nforest/lookout"->enter_road(ob,from);
  }
  if(npc_name == "haradrim captain")
  {
    move_patrol_alarm = set_alarm(40.0, 0.0, &move_patrol(ob));
  }
}

void
move_patrol(object ob)
{
  if (!TO->move_other_dir(ob))
    ob->command("north"); 
}

void
stand_to_fight()
{
    if (move_patrol_alarm)
        remove_alarm(move_patrol_alarm);
    move_patrol_alarm = 0;
}

void
continue_patrol(object ob)
{
  if (!move_patrol_alarm)
  {
    move_patrol_alarm = set_alarm(40.0, 0.0, &move_patrol(ob));
  }
}

int
test_exit()
{
  int stopped;
  object attacker;
  attacker = TP->query_attack();
  if(attacker)
  {
    stopped = TP->query_stat(SS_DEX) - attacker->query_stat(SS_DEX) + 85;
    if(stopped < 0) stopped = 0;
    stopped = 12 - stopped / 10;
    if (stopped < 1) stopped = 1;
    if (stopped > 10) stopped = 10;
    if(random(stopped)) 
    {
      write("The " + attacker->query_nonmet_name() + " stops you!\n");
     return 1;
    }
  }
  return 0;
}
