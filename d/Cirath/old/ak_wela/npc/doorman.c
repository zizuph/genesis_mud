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

    set_name("doorman");
    set_race_name("elf");
    set_adj("tall");
    add_adj("handsome");
    set_living_name("altair");

    set_short("tall handsome elf");

    set_long("");

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(CONT_I_WEIGHT, 45000);     /* 60 Kg */
    add_prop(CONT_I_HEIGHT, 100);     /* 200 cm */

             /* STR DEX CON INT WIS DIS */
    set_stats(({ 40, 80, 42, 69, 75, 70}));
    set_skill(SS_WEP_KNIFE, 75);

    set_pick_up(0);
    set_aggressive(0);
    set_attack_chance(0);
    set_hp(query_max_hp()); /* Heal fully */

    /* Actions */
    set_act_time(5);
    add_act("smile");

    /* Triggers */
    trig_new("%w 'introduces' %s", "react_introduce");
    trig_new("%w 'died.' %s", "remove_victim");
}


object *query_customers()
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


void init_living()
{
  int exit_arrays_counter;

  ::init_living();
  grab_newcomer();
  exit_cmds = environment(TO)->query_exit_cmds();
}


int query_knight_prestige() { return -5; }
