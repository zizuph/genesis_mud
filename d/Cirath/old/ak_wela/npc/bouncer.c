/* 
 */

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "/d/Cirath/common/defs.h"

object *troublemakers; // Which players are fighting.

void create_monster()
{
    seteuid(getuid());

    set_name("bouncer");
    set_race_name("dwarf");
    set_adj("large");
    add_adj("cautious");

    set_short("large cautious dwarf");

    set_long("This dwarf guards the stairs to the upper level, to keep " +
             "out the riff-raff and protect the welfare of the ladies.  " +
             "He watches the room very carefully, and nothing seems to " +
             "escape his notice.\n" +
             "Currently, he is making sure no one goes upstairs, as the " +
             "brothel has been shut down by the owner.\n");

    add_prop(CONT_I_WEIGHT, 45000);     /* 80 Kg */
    add_prop(CONT_I_HEIGHT, 100);     /* 130 cm */

             /* STR DEX CON INT WIS DIS */
    set_stats(({ 75, 50, 75, 33, 66, 80}));
    set_skill(SS_UNARMED, 80);

    set_pick_up(0);
    set_aggressive(0);
    set_attack_chance(0);
    set_hp(query_max_hp()); /* Heal fully */

    /* Actions */
    set_act_time(45);
    add_act("growl");
    add_act("glare");

    /* Triggers */
    trig_new("%w 'introduces' %s", "react_introduce");
    trig_new("%w 'died.' %s", "remove_victim");
}


string *query_troublemakers()
{
    return troublemakers;
}


void intro_chat()
{
  tell_room(environment(TO),
            break_string("His voice dripping with sarcasm, the robber says, " +
            "\"Pleased to meet you.  Now gimme your money!!\"\n", 70));
}


void react_introduce(string dummy1, string dummy2)
{
  call_out("intro_chat", 1);
}


void remove_victim(string old_victim, string dummy1)
{
  old_victim = lower_case(old_victim);
  if (member_array(old_victim, customers) != -1)
  {
    command("wink " + old_victim);
    customers -= ({ old_victim });
    if (!sizeof(customers))
      call_out("destruct_bandit", 1);
  }
}


void no_go_chat()
{
  int chat_num;

  chat_num = random(3);
  switch (chat_num)
  {
    case 0:
        tell_room(environment(TO),
                  "The bandit yells, \"You're not going anywhere, chump!\"\n");
        return;
    case 1:
        tell_room(environment(TO),
                  "The bandit says, \"Where do ya think you're going?\"\n");
        return;
    case 2:
        tell_room(environment(TO),
                  "The bandit growls, \"Ya gotta pay the toll-keeper, and dat's me!\"\n");
        return;
  }
}


void init_living()
{
  int exit_arrays_counter;

  ::init_living();
  grab_newcomer();
  exit_cmds = environment(TO)->query_exit_cmds();
}


int query_knight_prestige() { return -5; }
