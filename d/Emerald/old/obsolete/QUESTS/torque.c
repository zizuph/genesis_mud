/* torque.c originally done by Phase, redone by Mayhem then Shiva
 * This is the quest item for the Crystal Tower quest
 */
 
inherit "/std/object";
 
#pragma save_binary
 
#include "/d/Emerald/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <language.h>
#include <composite.h>
#include <filter_funs.h>
#include <living_desc.h>
 
#define TORQUE_SUBLOC   "_torque_subloc"
#define MANA_COST       80
#define MIN_INTERVAL    120
#define BIT_GROUP       2
 
static int last_time;
 
void
create_object()
{
  set_name("torque");
  add_name("phase_torque");
  add_adj("crystal");
  set_long("This beautifully crafted torque is made entirely "+
      "of\ncrystal that swirls with every colour in the spectrum.\n");
   
  add_prop(OBJ_M_NO_DROP, "You can't drop that!\n");
  add_prop(OBJ_M_NO_STEAL, "That item is not stealable!\n");
  add_prop(OBJ_M_NO_SELL, "It is too priceless to sell!\n");
  add_prop(OBJ_M_NO_BUY, "It is not for sale!\n");
  add_prop(OBJ_I_WEIGHT, 300);
  add_prop(OBJ_I_VOLUME, 300);
  add_prop(OBJ_I_VALUE, 0);
  add_prop(MAGIC_AM_MAGIC, ({ 10, "divination" }));
  add_prop(MAGIC_AM_ID_INFO, ({
      "The torque is enchanted with divine power.\n", 1,
      "It can be used to look at the surroundings of other " +
          "people\nanywhere in the world using the trigger 'scry "+
          "<name>'.\n", 15 }) );
}
 
string
query_auto_load()
{
  return MASTER;
}
 
void
get_lost()
{
  write("Oops! You fumble with the torque and drop it.\nThe crystal " +
      "torque shatters into myriad pieces as it strikes the ground.\n");
  say(QCTNAME(this_player()) + " fumbles with the torque and drops it.\n" +
      "The crystal torque shatters into myriad pieces as it strikes "+
      "the ground.\n");
 
  remove_object();
}
 
void
leave_env(object env, object to)
{
  ::leave_env(env, to);
 
  if (living(env))
  {
    env->remove_subloc(TORQUE_SUBLOC);
  }
}
 
string
show_subloc(string subloc, object carrier, object for_obj)
{
  if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
  {
    return "";
  }
 
  if (for_obj == carrier)
  {
    return "You are wearing " + LANG_ADDART(short()) +
        " around your neck.\n";
  }
 
  return capitalize(carrier->query_pronoun()) + " is wearing "+
      LANG_ADDART(short()) + " around " + carrier->query_possessive() + 
      " neck.\n";
}
 
int
scry(string arg)
{
  object env, who, *items, *dead, *live;
  object *ctants1, *ctants2, enemy;
  string who_str, tmp;
  int    i, size, index, success;
  mixed  *attackers;
 
  notify_fail("Scry on whom?\n");
  if (!strlen(arg))
  {
    return 0;
  }
 
  if (this_player()->query_mana() < MANA_COST)
  {
    notify_fail("You are too exhausted to do that.\n");
    return 0;
  }
 
  who = find_player(lower_case(arg));
 
  if (!who)
  {
    if (sscanf(arg, "on %s", who_str) == 1 && 
        !(who = find_player(lower_case(who_str))))
    {
      return 0;
    }
  }
 
  if (!this_player()->query_met(who))
  {
    return 0;
  }
 
  if (SECURITY->query_wiz_level(who->query_real_name()) > 
      SECURITY->query_wiz_level(this_player()->query_name()))
  {
    return 0;
  }
 
  if (!(env = environment(who)))
  {
    return 0;
  }
 
  if (who->query_prop("protected"))
  {
    write("A strange power seems to flood your mind, making you uneasy.\n");
    return 1;
  }
 
  if ((time() - last_time) >= MIN_INTERVAL) 
  {
    if (!env->query_no_snoop() &&
        !env->query_prevent_snoop() &&
        !env->query_prop(ROOM_M_NO_MAGIC) &&
        !who->query_prop(OBJ_M_NO_MAGIC))
    {
      if (this_player()->query_prop(LIVE_I_SEE_INVIS) >=
          who->query_prop(OBJ_I_INVIS))
      {  
        success = this_player()->resolve_task(TASK_ROUTINE,
            ({ TS_INT,          SKILL_WEIGHT, 50, 
               SS_SPELLCRAFT,   SKILL_WEIGHT, 25, 
               SS_ELEMENT_LIFE, SKILL_WEIGHT, 25, 
               SS_FORM_DIVINATION
            }),
            who, ({ TS_INT, SS_ELEMENT_DEATH }));
      }
    }
  }
 
#ifndef DEBUG_ON
  if (success < 1)
  {
    write("For some reason, you were unable to do that.\n");
    this_player()->add_mana(-MANA_COST / 2);
    return 1;
  }
 
  who->catch_msg("You have a sense of being watched.\n");
  who->add_prop("_scried_by", this_player()->query_real_name());
 
  this_player()->add_mana(-MANA_COST);
  last_time = time();
#endif
 
  write("You can see the following:\n");
 
  if (env->query_prop(OBJ_I_LIGHT) < 1)
  {
    if (!stringp(tmp = env->query_prop(ROOM_S_DARK_LONG)))
    {
      write(LD_DARK_LONG);
      return 1;
    }
     
    write(tmp);
    return 1;
  }
 
  write(env->long());
 
  items = FILTER_CAN_SEE(all_inventory(env), this_player());
  if (sizeof(items))
  {
    if (sizeof(dead = FILTER_DEAD(items)))
    {
      write(capitalize(COMPOSITE_DEAD(dead)) + ".\n");
    }
    
    if (sizeof(live = FILTER_LIVE(items)))
    {
      write(capitalize(COMPOSITE_LIVE(live)) + ".\n");
    }
  }
 
  ctants1 = ({ });
  ctants2 = ({ });
  attackers = ({ });
  i = -1;
  size = sizeof(live);
  while (++i < size)
  {
    if (enemy = live[i]->query_attack())
    {
      if (member_array(live[i], ctants1) >= 0)
      {
        // already taken care of!
        continue;
      }
 
      if (enemy->query_attack() == live[i])
      {
        // describe two livings attacking each other
        write(live[i]->query_The_name(this_player()) +
            " and " + enemy->query_the_name(this_player()) +
            " are fighting each other.\n");       
        ctants1 += ({ enemy });
        continue;
      }
 
      if (sizeof(ctants2) &&
          (index = member_array(enemy, ctants2)) >= 0)
      {
        // group all the attackers who are attacking the same living
        attackers[index] += ({ live[i] });
        continue;
      }
   
      attackers += ({ ({ live[i] }) });
      ctants2 += ({ enemy });
    }
  }
 
  i = -1;
  size = sizeof(attackers);
  while (++i < size)
  {
    write(COMPOSITE_LIVE(attackers[i]) + 
        (sizeof(attackers[i]) == 1 ? " is" : " are") + " fighting " + 
        ctants2[i]->query_the_name(this_player()) + ".\n");
  }
 
  return 1;
}
    
void
init()
{
  ::init();
 
  if (this_player() != environment())
  {
    return;
  }
 
  if (!this_player()->test_bit(DOMAIN_NAME, BIT_GROUP, 1) &&
      !this_player()->test_bit(DOMAIN_NAME, BIT_GROUP, 2))
  {
    set_alarm(1.0, 0.0, get_lost);
    return;
  }
 
  this_player()->add_subloc(TORQUE_SUBLOC, this_object());
 
  add_action(scry, "scry");
}
