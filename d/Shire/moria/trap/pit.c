// pit.c
//
// Generic object for traps.
// -------------------------
// Plate Traps are modified versions of Khazad-dum's most
// common trap design, the Pit Trap. Dwarves built these
// pits of vatying lengths and widths, usually 1x1 m,
// 2x2 m, 4x4 m or 6x6 m. When unlocked and 84 or more
// pounds are applied to one of the gently counterweighted
// floor blocks, it rotates down into a housing in the wall
// or nearby floor area. The victim falls into a stone pit
// whose sloping walls merge toward a 1x1 m area 8 m below.
// There, seven 1 m iron spikes (arranged in a of six with
// a taller center one) awaits.
//
// Implementation.
// ---------------
// I will not create an extra room until the trap is released.
// I will take into concern skills like SS_FR_TRAPS, wisdom,
// race, awareness and etc. I will define the damage done by
// the fall. The weapon class of each spear. The acceleration
// is independant on the weight, so this will not affect. The
// trap is simply a hidden object (Very well hidden.) which
// does not show up in the room's description. The triggering
// of the action is simply done in init(). 

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/std/object";
inherit IM_TELL_FILE;

// Global variables.
static int alarm_id;
static object trap_room;	// The room to install as trap room.

mixed trap_room_file;		// Filename.
int trap_depth;		        // Depth in m.
int trap_size;			// Size in x*x m.
int trap_chance;		// Chance to step on it.
int trap_trigger_weight;	// Weight to release trap [grams.]
int trap_cover;		        // Chance in % to avoid being trapped.
int trap_is_triggered;		// Has it been released?

nomask void
create_object()
{
    trap_trigger_weight = 84000;
    trap_is_triggered = 0;
    trap_size = 2*2;		// Size: 2 by 2 meters.
    trap_cover = 0;
    trap_chance = 25;
    trap_depth = 4;
    trap_room_file = THIS_DIR + "pit_bottom";

    add_prop(OBJ_I_HIDE, 30+random(50));
    set_short("plate trap");
    add_adj("plate");
    set_name("trap");
    add_name("pit");
    set_long("@@pit_desc@@");
	     
    TO->create_pit();
    alarm_id = set_alarm(0.5, 1.0, "check_pit");
}

string
pit_desc()
{
    if (!trap_is_triggered)
	return ("You have discovered what seems to be a trap in the floor!\n" +
		"It seems to be cunningly made, a typical " +
		"version of the Khazad-dum Pit Trap design, often found " +
		"in Moria.\n");
    else if (!trap_room)
	return ("You are looking at an opened trap in the floor. It seems to " +
		"be cunningly made, a typical version of the Khazad-dum Pit " +
		"Trap design, often found in Moria.\n");
    else
	return ("You are looking at an opened trap in the floor. It seems to " +
		"be cunningly made, a typical version of the Khazad-dum Pit " +
		"Trap design, often found in Moria. You can't see what is down " +
		"in the pit.\n");
}

init()
{
    if (!ENV(TO))
	return;
    
    if (!trap_is_triggered)
    {
	if (!alarm_id)
	    alarm_id = set_alarm(0.5, 1.0, "check_pit");
	add_action("do_disarm", "disarm");
	add_action("do_place",  "place");
	add_action("do_push",   "push");
    }
    else
    {
	add_action("do_jump", "jump");
	add_action("do_enter", "enter");
	add_action("do_climb", "climb");
    }
}

/*
 * Check if we triggered the trap. If not, return.
 * Then send the poor lad down....
 */

void
check_pit()
{
    object *all  = INV(ETO) - ({TO});
    object *live = FILTER_LIVE(all);
    object *on_trap;
    int sum_weight = 0;
    int i;

    if (!sizeof(live))
	remove_alarm(alarm_id);

    on_trap = filter(all, "is_on_trap", TO);
    if (!sizeof(on_trap))
	return;
    for (i=0; i<sizeof(on_trap); i++)    
	sum_weight += on_trap[i]->query_prop(OBJ_I_WEIGHT);

    if (sum_weight >= trap_trigger_weight)
    {
	// Ok, we are a bit nice. We'll only drop one.
	i = random(sizeof(on_trap));
	TO->trap(on_trap[i]);
    }
}


int
is_on_trap(object who)
{
    int chance;

    if (trap_is_triggered)
	return 0;

    if (!living(who))
	return random(100) < trap_chance; // I.e.: chance is size*4 %
    
    if (CAN_SEE_IN_ROOM(who) && CAN_SEE(who, TO))
	return 0;

    chance = trap_chance;

    if (!CAN_SEE_IN_ROOM(who))
	chance *= 2;

    if (random(100) < chance)
	return 0;

    return 1;
}

/*
 * Now we actually trap the player. *grin*
 */
int
trap(object who)
{
    int bonus_wc; // Bonus for height.

    FIXEUID;
    if (!trap_room)
	trap_room = clone_object(trap_room_file);
	
    if (!living(who))
    {
	tell_room(TO,
		  "Suddenly, the " + QSHORT(who) + " falls down into a hidden trap!\n");
	who->move(trap_room);
    } 
    else
    {
	TellRoom(who, 0, "$Name $scream out as $_you $fall down a hidden trap!\n");
	who->move_living("M", trap_room);
    }
    ETO->add_exit(file_name(trap_room), "down", 2);
    trap_is_triggered = 1;
    TO->add_prop(OBJ_I_HIDE, 0);
    trap_room->recieve_victim(who, trap_depth);
    trap_room->add_exit(file_name(ETO), "up", 2);
}


