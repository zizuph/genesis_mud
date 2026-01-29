/*
 *    /d/Avenir/inherit/npc
 * Inheritable file with some useful
 * npc functions, like delayed actions and
 * guard functions.
 *   Lord Cirion, 041196
 *
 * Modified: Cirion, March 1, 1998: Fixed a bug where
 *   passing in a function pointer to delay_action would
 *   not get called properly.
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Avenir/inherit/monster";
#include <macros.h>
#include <stdproperties.h>

static int      action_alarm_id,
                action_alarm_counter,
                npc_guard_enabled;
static mixed   *action_alarm_actions;
static string  *guard_these_exits;


/* ********* Delayed actions ********** */
/*
 *  Example of use:
 *   delay_action(1.7, ({"open door", "south", "smile all",
 *         "say Hello everyone!", do_search, "wave", "north",
 *         "close door", "lock door"}));
 */

/*
 * Function name: do_my_actions
 * Description:   Does the next action in the sequence,
 *                or ends the actions if the end of
 *                the sequence has been reached.      
 */
private void 
do_my_actions()
{
  function f;

  if(action_alarm_counter + 1 > sizeof(action_alarm_actions))
  {
    remove_alarm(action_alarm_id);
    action_alarm_counter = 0;
    return;
  }

  if(stringp(action_alarm_actions[action_alarm_counter]))
  {
    command(action_alarm_actions[action_alarm_counter]);
    action_alarm_counter++;
    return;
  }

  if(functionp(action_alarm_actions[action_alarm_counter]))
  {
    f = action_alarm_actions[action_alarm_counter];

    f();

    action_alarm_counter++;
    return;
  }

  action_alarm_counter++;
  return;
}

/*
 * Function name: delay_action
 * Description:   sets up a repeating alarm of actions that
 *                the npc should perform.
 * Arguments:	  delay      - the float delay of the alarm
 *                my_actions - an array containing either
 *                             a string for an action that
 *                             should be executed, or a
 *                             function that should be called.
 *                priority   - set it to 1 if you want these
 *                             actions to take priority over
 *                             any others. If it is called, any
 *                             other action alarm will be removed.
 * Returns:       1 if the alarm has been set, 0 otherwise.
 */
public varargs int 
delay_action(float delay, mixed *my_actions, int priority)
{
  if(get_alarm(action_alarm_id))
  {
    if(!priority)
      return 0;
    else
      remove_alarm(action_alarm_id);
  }
  
  if(query_attack() && !priority)
    return 0;

  action_alarm_counter = 0;
  if(!sizeof(my_actions))
    return 0;
  action_alarm_actions = my_actions;
  action_alarm_id = set_alarm(delay, delay, do_my_actions);
  return 1;
}

/*
 * Function name: remove_delay_actions
 * Description:   Will end any sequence of actions an npc
 *                might be performing at the time. Typical
 *                use would be to end all actions if the npc
 *                is attacked, etc.
 * Returns:       1 if the action alarm was removed
 *                0 if no actions were being executed at the time
 */
public int
remove_delay_actions()
{
  if(!get_alarm(action_alarm_id))
   return 0;

  action_alarm_counter = 0;
  remove_alarm(action_alarm_id);
  return 1;
}

/* ******** Guard Functions *********** */

/*
 * Function name: guard_enable
 * Description:   sets up an npc to guard a number of exits.              
 * Arguments:	  what  - setting it to 1 enables to guard
 *                        to block exits, 0 disabled the guarding.
 *                exits - a string array of exits to block. If this
 *                        is not included, the guard will automatically
 *                        block all exits in the room.      
 */
public varargs void
guard_enable(int what, string *exits)
{
  npc_guard_enabled = what;
  if(sizeof(exits))
   guard_these_exits = exits;
}

/*
 * Function name: query_guarding
 * Description:   decide if you want to guard against a
 *                certain living.
 * Arguments:	  who - the living to check against.
 * Returns:       1 if the player is stopped, 0 if he
 *                can pass.
 * Nota Bene:     This should be redefined in the guard
 *                with a more intelligent routine.
 */
public int
query_guarding(object who)
{
  if(!CAN_SEE(this_object(), who) || !CAN_SEE_IN_ROOM(this_object()))
    return 0;

  who->catch_msg(QCTNAME(this_object())+" stops you from going "
        +"in that direction.\n");
  say(QCTNAME(this_object())+" stops "+QTNAME(who)+" from passing.\n");
  return 1;
}

public void
init_living()
{
  int       jj;
  string   *cmds;

  ::init_living();

  if(!npc_guard_enabled)
   return;

  cmds = environment(this_object())->query_exit_cmds();

  if(!sizeof(cmds))
   return;

  if(sizeof(guard_these_exits))
  {
    for(jj = 0; jj < sizeof(guard_these_exits); jj++)
    {
      if(member_array(guard_these_exits[jj], cmds) != -1)
        add_action("npc_try_to_stop", guard_these_exits[jj], 2);
    }
    return;
  }

  for(jj = 0; jj < sizeof(cmds); jj++)
    add_action("npc_try_to_stop", cmds[jj], 2);
}

static int
npc_try_to_stop(string str)
{
  return query_guarding(this_player());
}
