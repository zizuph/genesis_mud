/*
 *      message_server.c
 *
 *      Gives messages to a certain area
 *
 *      Fysix@Genesis, November 1996
 *
 * Example code:
 *
 *      inherit "/blah/blah/msg_server";
 *
 *      void create_msg_server()
 *      {
 *          set_messages( ({
 *              "Lightning strikes down from the heavens above.\n",
 *              "A loud thunder rolls through the sky.\n",
 *              }) );
 *          set_msg_time(60);   // Send a message each minute
 *      }
 *
 * Every room that wants messages from this message server
 * should mask the enter_inv() function:
 *
 *      public void enter_inv(object o, object from)
 *      {
 *          ::enter_inv(o, from);
 *          if (interactive(o))
 *              "/your/dir/your_server"->add_room(this_object());
 *      }
 *
 * If random messages are not desired, just mask the query_msg() function.
 *
 */
#pragma strict_types
#pragma save_binary

#include <macros.h>
#include <filter_funs.h>

// process a number of rooms at the same time
#define N_TELLS 5

inherit "/std/room";

// --- Global variables ---
static string *messages = ({ });
static object *rooms = ({ });
static float  msg_time = 40.0;      // the time between messages in seconds
static int    active = 0,           // is the server active?
running_alarm = 0,    // the alarm id
busy = 0;             // is the server busy telling?

/* Function name: stop_alarm
 * Description:   stop the alarm for giving message to the rooms
 */
void
stop_alarm()
{
    if (!running_alarm)
	return;

    remove_alarm(running_alarm);
    running_alarm = 0;
}

/* Function name: update_alarm
 * Description:   Stop alarm if there is no need to give messages.
 */
public void
update_alarm()
{
    if (!sizeof(rooms) || !sizeof(messages))
	stop_alarm();
}

/* Function name: query_messages
 * Description:   What messages are in the server to give to the rooms?
 * Returns:       string * - array of messages
 */
string *
query_messages()
{
    return messages + ({ });
}

/* Function name: set_messages
 * Description:   set the messages to give to the rooms periodically
 * Arguments:     mixed - a message or an array of messages
 * Returns:       1 - if the messages were set, 0 - illegal type
 */
int
set_messages(mixed s)
{
    if (s && stringp(s))
	s = ({s});

    if (s && pointerp(s))
    {
	messages = s;
	return 1;
    }
    return 0;
}

/* Function name: add_messages
 * Description:   add messages to give to the rooms periodically
 * Arguments:     mixed - a messages or an array of messages
 * Returns:       1 - if the messages were added, 0 - illegal type
 */
int
add_messages(mixed s)
{
    if (stringp(s))
	s = ({ s });

    if (pointerp(s))
    {
	messages += s;
	return 1;
    }
    return 0;
}

/* Function name: do_tell_room
 * Description:   Do a tell to a single room.
 * Arguments:     object the room object
 *                string the message
 */
void
do_tell_room(object room, string s)
{
    object *players;

    // If there are players in the room, do the tell, otherwise remove
    // the room from the list
    if (sizeof(players = FILTER_PLAYERS(all_inventory(room))))
	players->catch_tell(s);
    else
	rooms -= ({ room });
}

/* Function name: do_tell
 * Description:   do the actual tell_room to all the rooms of a
 *                certain message. Calls do_tell_room,
 *                Called by send_messages via an alarm.
 * Arguments:     object* - the array of rooms
 *                string - the message
 */
void
do_tell(object *r, string s)
{
    if (!sizeof(r) || !s)
    {
	busy = 0;
	update_alarm();
	return;
    }

    // Do some tells at once
    map(r[0..N_TELLS - 1], &do_tell_room(, s));

    // Do the other tells later    
    set_alarm(0.5, 0.0, &do_tell(r[N_TELLS..], s));
}

/* Function name: query_msg()
 * Description:   Pick a random message from the message list
 *                Mask this function if other behaviour is wanted
 * Returns:       string - a message
 */
string
query_msg()
{
    return messages[random(sizeof(messages))];
}

/* Function name: send_messages
 * Description:   Sends a message as returned by query_msg() to
 *                all rooms currently in memory of the server
 *                (see also query_rooms). Nothing happens if the
 *                server is already sending tells at the moment.
 */
void
send_messages()
{
    if (busy)
	return;

    busy = 1;  // busy telling for a little while
    do_tell(rooms + ({ }), query_msg());
}

/* Function name: start_alarm
 * Description:   start the alarm for giving messages to the rooms
 */
void
start_alarm()
{
    if (running_alarm || !active)
	return;
    running_alarm = set_alarm(msg_time * itof(random(100)) / 100.0,
      msg_time, send_messages);
}

/* Function name: query_running_alarm_id
 * Description:   query the running alarm id if running
 * Returns:       int - 0 if not running
 */
int
query_running_alarm_id()
{
    return running_alarm;
}

/* Function name: set_msg_time
 * Description:   set the time between two subsequent messages
 * Args:          mixed - the time in seconds, either int or float
 */
void
set_msg_time(mixed t)
{
    if (!intp(t) || !floatp(t))
	return;

    if (intp(t))
    {
	msg_time = (float) t;
    }
    else if (floatp(t))
    {
	msg_time = t;
    }

    if (running_alarm)
    {
	stop_alarm();
	start_alarm();
    }
}

/* Function name: query_msg_time
 * Description:   query the time between to subsequent messages
 * Returns:       float - the time in seconds
 */
float
query_msg_time()
{
    return msg_time;
}

/* Function name: query_rooms
 * Description:   What rooms are in the server to give messages to?
 * Returns:       object * - array of the room objects
 */
object *
query_rooms()
{
    return rooms + ({ });
}

/* Function name: add_room
 * Description:   Add a room to give messages to.
 * Args:          object - the room object
 */
void
add_room(object r)
{
    if (member_array(r, rooms) >= 0)
	return;

    rooms += ({ r });

    if (active)
	start_alarm();
}

/* Function name: remove_room
 * Description:   Remove a room object from the array that was used
 *                for sending messages to.
 * Arguments:     object - the room object
 */
void
remove_room(object r)
{
    rooms -= ({ r });
    if (!sizeof(rooms))
	stop_alarm();
}

/* Function name: query_active
 * Description:   is the server running?
 * Returns:       int - 0 if not running, the alarm ID if running
 */
int
query_active()
{
    return active;
}

/* Function name: set_active
 * Description:   Activate/deactivate the message server.
 * Arguments:     int new active state, 1/0
 */
void
set_active(int i)
{
    active = i;
    if (active)
	start_alarm();
    else
	stop_alarm();
}

/* Function name: create_msg_server
 * Description:   Message server creation function.
 */
public void
create_msg_server()
{
}

nomask void
create_room()
{
    set_short("message server");
    set_long("This is a message server.\n" +
      "For seeing the messages:\n" +
      "\tCall here query_messages\n" +
      "For seeing the loaded rooms:\n" +
      "\tCall here query_rooms\n" +
      "For checking the message_time:\n" +
      "\tCall here query_msg_time\n" +
      "Is it running?\n" +
      "\tCall here query_active\n" +
      "Start messages / stop messages:\n" +
      "\tCall here set_activate 1\tCall here set_active 0\n" +
      "");

    set_active(1);

    create_msg_server();
}
