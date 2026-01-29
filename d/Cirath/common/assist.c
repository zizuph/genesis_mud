/*
   /d/Kalad/lib/assist.c

   Inherit this module to make your npc assist certain npcs when
   they are attacked.
   Includes optional attack on sight and active watching of the
   environment for friends in distress. Since active watching
   needs an alarm this only works when interactives are present.

   For guards that wander around you can call watch_friends
   from enter_env when you don't want active watching of the 
   environment.

   Fysix@Genesis, Nov 1997

   Example:

      inherit "/std/monster";
      inherit "/d/Kalad/lib/assist";

      #include "/d/Kalad/sys/npc_types.h"

      void create_monster()
      {
	 set_name("guard");

	 // Assist all kabal citizens and some other type of npcs
	 add_friend(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN | SOME_TYPE);
	 // I am a kabal citizen mysel
	 add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

	 // Watch actively for friends (optional)
	 // If you only need attack on sight and not an active watch
	 // you might want to use watch_friends from enter_env
	 set_watch_friends(1);
      }

 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>

// The time between two watches in seconds.
#define WATCH_INTERVAL 10.0

// --- Global variables ---

static string  *Property = ({ });   // Property for friend identification
static int     *Value = ({ }),      // Property value
Going_to_assist,     // About to assist
Watch,               // Watch the environment?
Watch_alarm_id;      // id for the alarm that watches
static float   Assist_delay = 1.0;

/* Function name: query_assist
 * Description:   Assist the attacked living? Mask this function
 *                if you have special wishes for assisting livings.
 * Arguments:     object living
 * Returns:       int 1 if I should assist
 */
public int
query_assist(object living)
{
    int i;

    i = sizeof(Property);
    while (i--)
	if (living->query_prop(Property[i]) & Value[i])
	    return 1;

    return 0;
}

/* Function name: assist_hook
 * Description:   Called when the npc is about to assist.
 *                Redefine this when you want to give extra
 *                assist messages for example.
 * Arguments:     object friend, object enemy
 */
public void
assist_hook(object friend, object enemy)
{
}

/* Function name: assist
 * Description:   Assist a friend and attack the enemy.
 *                Mask this function if you need extra functionality.
 * Arguments:     object friend, object enemy
 * Returns:       int 1 if I attacked, 0 if I failed somehow
 */
public int
assist(object friend, object enemy)
{
    if (!friend || !enemy)
	return 0;

    if (!CAN_SEE_IN_ROOM(this_object()) ||
      !CAN_SEE(this_object(), enemy) ||
      environment()->query_prop(ROOM_M_NO_ATTACK) ||
      enemy->query_prop(OBJ_M_NO_ATTACK) ||
      environment() != environment(enemy) ||
      this_object()->query_attack() == enemy)
	return 0;

    this_object()->reveal_me();

    if (!F_DARE_ATTACK(this_object(), enemy))
	return 0;

    // Call this hook when we actually assist
    assist_hook(friend, enemy);

    enemy->catch_tell(this_object()->query_The_name(enemy) +
      " assists " + friend->query_the_name(enemy) + " and attacks you!\n");
    tell_room(environment(),
      QCTNAME(this_object()) + " assists " + QTNAME(friend) +
      " and attacks " + QTNAME(enemy) + ".\n",
      ({this_object(), friend, enemy}));

    this_object()->attack_object(enemy);
    this_object()->add_prop(LIVE_O_LAST_KILL, enemy);

    return 1;
}

// Clear the Going_to_assist flag just before calling assist
public nomask void
going_to_assist(object friend, object enemy)
{
    // Clear flag again
    Going_to_assist = 0;

    assist(friend, enemy);
}

/* Function name: assist_with_delay
 * Description:   Calls assist with the specified delay.
 *                If the delay was 0, assist is called immediately.
 * Arguments:     object friend, object enemy
 */
public void
assist_with_delay(object friend, object enemy)
{
    if (Going_to_assist)
	return;

    if (Assist_delay >= 0.0)
    {
	Going_to_assist = 1;
	set_alarm(Assist_delay, 0.0, &going_to_assist(friend, enemy));
    }
    else
	assist(friend, enemy);
}

/* Function name: notify_ob_attacked_me
 * Description:   This function is called when a Kalad npc is attacked.
 *                Calls query_assist to decide if we assist or not.
 * Arguments:     object victim, object attacker
 */
public void
notify_ob_attacked_me(object victim, object attacker)
{
    // Don't attack if I am already fighting
    if (this_object()->query_attack())
	return;

    if (query_assist(victim))
	assist_with_delay(victim, attacker);
}

/* Function name: watch_friends
 * Description:   This functions sees if anybody in the environment
 *                is fighting with one of my friends.
 *                Calls assist (with an optional delay).
 */
public void
watch_friends()
{
    object   *livings;
    int      i;

    if (this_object()->query_attack())
	return;

    // Find all livings who are fighting   
    livings = filter(FILTER_LIVE(all_inventory(environment())),
      &objectp() @ &->query_attack());

    // See if there are any friends who are under attack
    i = sizeof(livings);
    while (i--)
	if (query_assist(livings[i]))
	{
	    assist_with_delay(livings[i], livings[i]->query_attack());
	    return;
	}
}

/* Function name: add_friend
 * Description:   Add a friend to this npc
 * Arguments:     string property - the property to check
 *                int value - an int containing all the bits that
 *                            the property should have.
 */
public void
add_friend(string property, int value)
{
    int i;

    if ((i = member_array(property, Property)) >= 0)
    {
	Value[i] |= value;   // Do a bitwise or on the existing value
    }
    else
    {
	Property += ({ property });
	Value += ({ value });
    }
}

/* Function name: set_assist_delay
 * Description:   Set the delay before we assist in seconds.
 * Arguments:     mixed the delay in seconds (int/float),
 *                   use a negative value if no delay is wanted.
 */
public void
set_assist_delay(mixed delay)
{
    if (intp(delay))
	Assist_delay = (float) delay;
    else if (floatp(delay))
	Assist_delay = delay;
}

/* Function name: query_assist_delay
 * Description:   What is the delay before we assist?
 * Returns:       float the time in seconds
 */
public float
query_assist_delay()
{
    return Assist_delay;
}

/* Function name: stop_watch
 * Description:   Stop actively watching the environment, See also watch,
 *                start_watch.
 */
public void
stop_watch()
{
    if (Watch_alarm_id)
    {
	remove_alarm(Watch_alarm_id);
	Watch_alarm_id = 0;
    }
}

/* Function name: watch
 * Description:   Actively watches the environment to see if we
 *                should assist friends right now.
 *                Aborts the watch alarm if
 *                there are no interactives left.
 */
public void
watch()
{
    if (!sizeof(FILTER_PLAYERS(all_inventory(environment()))))
	stop_watch();
    else
	watch_friends();
}

/* Function name: start_watch
 * Description:   Starts to actively watch the environment to see if any
 *                friends need assistance.
 */
public void
start_watch()
{
    if (Watch_alarm_id)
	return;
    Watch_alarm_id = set_alarm(WATCH_INTERVAL, WATCH_INTERVAL, &watch());
    watch_friends();
}

/* Function name: interactive_meets_me
 * Description:   Is used to start actively watching the environment
 *                for fights.
 *                See also set_watch_friends.
 */
public void
interactive_meets_me()
{
    start_watch();
}

/* Function name: set_watch_friends
 * Description:   Actively watch the environment for friends
 *                if they need assistance.
 * Arguments:     int 1/0
 */
public void
set_watch_friends(int watch)
{
    if (!Watch && watch)
    {
	this_object()->add_notify_meet_interactive("interactive_meets_me");
    }
    else if (Watch && !watch)
    {
	this_object()->remove_notify_meet_interactive("interactive_meets_me");
	stop_watch();
    }

    Watch = watch;
}
