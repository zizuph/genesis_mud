// file name: s_shore.c
// creator(s): Ilyian, April 1995
// last update: Lilith Sep 2021: Changed the way the gate works so it is
//              less dependent on the gatekeeper for people leaving the Holm.
//              His add_acts etc were getting out of sync. The gate here now
//              acts like the Third Gate--players can let themselves out. But.
//              They won't be able to let themselves out if they are still full
//              of "adrenaline".
// purpose: Entrance to bridge between bazaar and park islands.
/*
 * Revisions:
 * 	Lucius, Jun 2017: Lowered gate opening delay. Misc cleanups.
 *
 */
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "../bazaar.h"
#include "/d/Avenir/common/herbs/herbsearch.h"
#include "/d/Avenir/smis/sys/statserv.h"

#define OTHER_SIDE ("/d/Avenir/common/bazaar/green/green17")
// Temp for union accepted to do entrance quest.
#define LIST       ("/d/Avenir/union/list")

#define CLOSE_DELAY	 15.0

int door_closed = 1, door_locked = 1;

void
create_room()
{
    set_short("South shore");
    set_long("You stand upon the south shore of the bazaar island. To the "
      +"south, a massive stone bridge rises up, crossing over the distance "
      +"to an overgrown island. North is a tall, thick stone wall, which is "
      +"parted by a silver gate. Through the gate you can see a pleasant garden "
      +"area, and in the distance you hear the shouts of merchants and "
      +"hawkers selling their wares.\nA silver garden gate blocks the "
      +"way north.\n");

    add_exit(GREEN +"green17", "north", "@@try_north");
    add_exit(BAZAAR+"green/n_bridge", "south", "@@try_south");

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(OBJ_I_CONTAIN_WATER, 1);     //water is available here
    add_prop(ROOM_I_LIGHT,1);
    IN

    AI(({"bridge","stone"}), "The bridge to the south is made from a rough "
      +"grey stone that has blackened to a sooty colour over the years. It "
      +"arches high over the sea, and ends at an island you can see to the "
      +"distant south. In the middle of the bridge, you can make out two "
      +"large statues on either side.\n");
    AI(({"water","sea","ocean"}),"The water of surrounding the island is "
      +"completely lightless, so you have no indication of either how "
      +"deep it is, or what hides beneath the surface. It gives you an "
      +"uncomfortable feel, and strange eddies swirl in eerie patterns.\n");
    AI(("shore"),"The shore goes around the island, but you cannot follow along "
      +"it because your way is blocked by hedges on either side.\n");
    AI(({"hedge","hedges"}),"Massive hedges have grown up on either side "
      +"of this path, both preventing you from going along the shore and "
      +"stopping you from seeing over them. They are thick with thorns.\n");
    AI(({"wall","walls"}),"The wall to the north extends past the hedges to "
      +"either side of you, so there is no chance of getting around it. "
      +"Directly to your north is a large silver gate in the wall with a "
      +"small latch.\n");

    add_cmd_item(({"gate", "silver gate", "gates", "on gate"}), 
      ({"knock", "bang"}), "@@knock_gate");
    ACI(({"gate", "silver gate", "garden gate", "silver garden gate"}),
      ({"pick"}), 
      "As you approach it, an uncomfortable current of energy pulses "+
      "through you, pressing you backwards.\n"); 
    AI(({"gate", "silver gate", "garden gate", "silver garden gate"}),
      "This silver gate gleams from the light. It is high, and from both "+
      "sides of it extend a wall. It has a small latch in the middle, "+
      "with a lock beneath it. Through the gate, you can see the "+
      "beginning of a path through a strange garden, and next to the "+
      "gate, on the other side, sits a stone bench.\n");
    AI(({"lock", "latch"}), "The latch and the lock, both, are oddly shaped "+
      "and inscribed with magical symbols of unknown provenance. It looks "+
	  "like you can probably unlock and open the gate from this side.\n");
    AI(({"symbols", "magical symbols"}), "They appear magical in nature.\n");
	add_prop(OBJ_S_WIZINFO, "As of Sept 2021, the gatekeeper no longer "+
	    "opens the gate for people returning from the Holm--they can now "+
		"do it for themselves. This reduces movement time and the out-of-"+
		"sync issues with the gatekeepers add_acts and the gate. However, "+
		"players who aren't relaxed from combat yet can't open the gate "+
		"until the adrenaline is gone--their hands are too shaky.\n");


    set_search_places(({"shore","edge","water","beach"}));
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(HERB+"nethra");
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    reset_room();
}

void 
reset_room()
{
    set_searched(0);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob) &&
      (file_name(from) == "/d/Avenir/common/bazaar/green/green17"))
	STATSERV_LOG_EVENT("holm", "Entered via garden gate");
}

void
open_door()
{
    tell_room(TO,"The silver garden gate swings open on silent hinges.\n");
    door_closed = 0;
    return;
}

void
close_door()
{
    if (door_closed)
	return;

    tell_room(TO,"The silver garden gate swings closed.\n");
    tell_room(OTHER_SIDE, "The silver garden gate swings closed.\n");
    door_closed = 1;
    door_locked = 1;
    return;
}

int
knock_gate()
{
    if (!door_closed)
    {
	notify_fail("The silver garden gate is already open.\n");
	return 0;
    }

    write("You knock on the silver garden gate.\n");
    return 1;
}

void
do_shout()
{
    if (!door_closed)
    {
	notify_fail("Why are you shouting? The silver garden gate is "+
	  "already open.\n");
	return;
    }

    tell_room(BAZAAR+"green/green17", "Shouts can be heard from the "+
	"other side of the gate.\n");
	
}    

/* Is gate open, or closed ? */    
int
try_north()
{   
    if (!interactive(TP))
	return 0;

    if (door_closed)
    {
	write("The silver gate is closed.\n");
	return 1;
    }

    write("You walk past the open gate.\n");
    return 0;
}

/* Final 'newbie' check. GA and below are not able to go. */
int
try_south()
{   
    if (!interactive(TP))
	return 0;

    if (LIST->query_accepted(TP->query_real_name()))
    {
	write("Despite your small stature, your interest in "+
	  "Unity gives you the courage to step onto the Holm.\n");
	return 0;
    }

    if (TP->query_average_stat() < 87)
    {
	write("A sudden terror freezes your blood, preventing you "+
	  "from moving south.\n");   
	return 1;
    }
    return 0;
}

void try_latch()
{
  if (!door_locked && door_closed)
  {
      door_locked = 1;
      tell_room(this_object(), "The latch on the silver gate closes again.\n");
  }
}

int do_unlock(string str)
{
    notify_fail("Unlock what?\n");
    if (!str)
    {
        return 0;
    }
    if (str != "gate" && str != "silver gate")
    {
        return 0;
    }
    if (!door_locked)
    {
        write("The silver gate is already unlocked.\n");
        return 1;
    }
	// If player is too recently from combat, they can't open the gate just yet.
    if (!TP->query_relaxed_from_combat())
    {
        write("You try to unlock the gate, but your hands are too shaky with "
            + "adrenaline to manage it. Calm down and then try again.\n");
        return 1;
    }
    door_locked = 0;
    set_alarm(CLOSE_DELAY, 0.0, try_latch);
    write("Ok.\n");
    say(QCTNAME(TP) + " unlocks the silver gate.\n");
    return 1;    
    
}


int do_open(string str)
{
    notify_fail("Open what?\n");
    
    if (!str)
    {
        return 0;
    }
    
    if (str != "gate" && str != "silver gate")
    {
        return 0;
    }
    
    if (!door_closed)
    {
        write("The silver gate is already open.\n");
        return 1;
    }
    if (door_locked)
    {
        write("The silver gate is locked.\n");
        return 1;
    }
    if (!TP->query_relaxed_from_combat())
    {
        write("You try to open the gate, but your hands are too shaky with "
            + "adrenaline to do so. Take a few moments to calm down and "
			+"then try again.\n");
        return 1;
    }
    door_closed = 0;
    set_alarm(CLOSE_DELAY, 0.0, close_door);
    write("Ok.\n");
    say(QCTNAME(TP) + " opens the silver gate.\n");
    return 1;    
}


void
init()
{
    ::init();
    add_action(do_shout, "shout");
    add_action(do_unlock, "unlock");
    add_action(do_open, "open");
}
