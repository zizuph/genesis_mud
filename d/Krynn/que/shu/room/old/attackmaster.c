/* created by Aridor 06/28/94 */

inherit "/std/room";

#include "../local.h"
#define SAVE_FILE   ROOM + "attack_state"

static int *state_time = ({0, 100, 100, 100});
/*test values above, these are the normal values:({0, 3000, 3000, 5000});*/

int state_of_attack = 0;

/*list of rooms who need to be changed when this master changes*/
static object *room_list = ({});

/*prototypes*/
void start_attack();

public nomask void
create_room() 
{ 
    set_short("Attackmaster room");
    set_long("You are in the master room which handles the attack on " +
	     "Que Kiri. This room just keeps track on the state of " +
	     "the attack and it is also this room all the other rooms " +
	     "query to know what is happening.\n");
    restore_object(SAVE_FILE);
    if (state_of_attack != 0)
      set_alarm(itof(state_time[state_of_attack]),0.0,"next_period");
}

/* Call this function to start a drac attack on Que Kiri.
 * This is automatically done by Verminaard when he nears the village
 * It shouldn't be called at any other time right now, maybe there
 * will be more callers coming sometime later...
 */
public nomask int
start_attack()
{
    int i = -1, ok_to_start = 1, size = sizeof(room_list);

    if (state_of_attack != 0)
      return 0;

    while (++i < size)
      ok_to_start = ok_to_start && room_list[i]->hook_change_room(0);
    if (!ok_to_start)
      return 0;
    
    i = -1;
    while(++i < size)
      room_list[i]->start_change_this_room();
    state_of_attack++;
    save_object(SAVE_FILE);
    set_alarm(itof(state_time[state_of_attack]),0.0,"next_period");
    return 1;
}

public nomask int
next_period()
{
    int i = -1, ok_to_start = 1, size = sizeof(room_list);

    while (++i < size)
      ok_to_start = ok_to_start &&
	room_list[i]->hook_change_room(state_of_attack);
    if (!ok_to_start)
      {
	  set_alarm(itof(TRY_AGAIN),0.0,"next_period");
	  return 0;
      }
    
    i = -1;
    while(++i < size)
      room_list[i]->change_state_of_room(state_of_attack);
    state_of_attack++;
    if (state_of_attack >= sizeof(state_time))
      state_of_attack = 0;
    else
      set_alarm(itof(state_time[state_of_attack]),0.0,"next_period");
    save_object(SAVE_FILE);
    return 1;
}

public nomask int
attack_ends_prematurely()
{
    mixed alrms = get_all_alarms();
    int i = -1, size = sizeof(alrms);

    if (state_of_attack != 1)
      return 0;

    while(++i < size)
      remove_alarm(alrms[i][0]);
    next_period();
    return 1;
}

public nomask int
query_attack_state()
{ 
    return state_of_attack; 
}

public nomask void
add_room(object room)
{
    if (room && file_name(room) != ATTACKROOM)
      room_list += ({ room });
    room_list -= ({ 0 });
}

