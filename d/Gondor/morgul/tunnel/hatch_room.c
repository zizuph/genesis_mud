/*
 * Jan 2000  -  Changed the awareness check to be 
 *                  3 * SS_AWARENESS from 2 * SS_AWARENESS
 *                   since the skill was moved from 50 to 30
 *            -- Morbeche --
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tunnel/std_tunnel";
#include <macros.h>
#include <ss_types.h>
#include "tunnel_door.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

#define AWARE_CHECK    (3 * TP->query_skill(SS_AWARENESS) + \
                            TP->query_skill(SS_TRACKING)  + \
                            TP->query_skill(SS_BLIND_COMBAT) )

/* hatch open: hatch_open = 1 */
int hatch_locked, hatch_open, hatch_broken;
object wheel_user;

void set_hatch()
{
    hatch_locked = 1;
    hatch_broken = 0;
    hatch_open = 0;
}

string query_key_name()
{
    if(MASTER == HATCH1_ROOM)
	return HATCH_KEY1;
    if(MASTER == HATCH2_ROOM)
	return HATCH_KEY2;
    write("There is a bug here: key name not found!\n");
    return "no_key";
}

int filter_player(object x) { return interactive(x); }

int can_see_hatch(object player)
{
    if(hatch_open)
	return 1;
    if(AWARE_CHECK > MIN_AWARE)
	return 1;
    return 0;
}

string examine_hatch(string str)
{
    string desc;

    if(hatch_open)
    {
	desc = "In the northern wall there is an open metal hatch. It is made of " +
	"a thick black metal plate. If the hatch were closed, you imagine it would " +
	"be hard to see it on the dark rock wall. Inside the hatch you can see " +
	"a large wooden wheel on a steel axle. You might be able to turn the wheel. ";
    }
    else if(can_see_hatch(TP))
    {
	desc = "The dark metal plate shows hardly against the dark rock wall. " +
	"There are two metal hinges on one side of the plate, and on the other side " +
	"there is a small keyhole. This metal plate might be a hatch hiding some " +
	"secret. ";
    }
    else
	desc = "You find no "+str+". ";

    return BSN(desc);
}

string exa_hatch() { return examine_hatch("hatch"); }
string exa_plate() { return examine_hatch("plate"); }
string exa_metal_plate() { return examine_hatch("metal plate"); }
string exa_black_metal_plate() { return examine_hatch("black metal plate"); }

string exa_walls()
{
    string desc;

    desc = "The walls are carved out of the living rock. They feel remarkably " +
    "smooth. The dark rock seems to swallow all light in the room. ";
    if(hatch_open)
    {
	desc += "In the northern wall you can see an open metal hatch. ";
    }
    else if(can_see_hatch(TP))
    {
	desc += "Looking closely, you can see a black metal plate in the midst of " +
	"the northern wall. ";
    }
    return BSN(desc);
}

void close_hatch()
{
    object *items;

    if(!sizeof(filter(all_inventory(TO),"filter_player",TO)))
    {
	hatch_open = 0;
	hatch_locked = 1;
	hatch_broken = 0;
    }
}

public void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!ob || !to)
	return;
    if(!interactive(ob)) 
	return;

    set_alarm(60.0, 0.0, close_hatch);
}

void reset_room()
{
    close_hatch();
}

void init()
{
    ::init();

    add_action("do_turn","turn");
    add_action("do_open","open");
    add_action("do_close","close");
    add_action("do_lock","lock");
    add_action("do_unlock","unlock");
    add_action("do_search", "search");
}

int do_turn(string str)
{
    object paralyze;

    if(!str || (str != "wheel"))
    {
	NF("Turn what?\n");
	return 0;
    }

    if(!hatch_open)
    {
	NF("You cannot see any wheel here!\n");
	return 0;
    }

    if(wheel_user && present(wheel_user, TO))
    {
	NF("You cannot turn the wheel.\n" + 
	  QCTNAME(wheel_user) + " is holding the wheel right now!\n");
	return 0;
    }

    if(TP->query_stat(SS_STR) < MIN_STR)
    {
	write("You try to turn the wheel, but you lack the strength necessary.\n");
	say(QCTNAME(TP) + " tries to turn the wheel, but he fails.\n");
	return 1;
    }

    wheel_user = TP;
    paralyze = clone_object("/std/paralyze");
    paralyze->set_stop_verb("release");
    paralyze->set_fail_message(BSN("You cannot do this since you are holding the wheel. "+
	"Release the wheel before you try to do anything else."));
    paralyze->set_stop_message("You stop holding the wheel.\n");
    paralyze->set_stop_fun("release_wheel");
    paralyze->set_stop_object(TO);
    paralyze->move( TP, 1 );

    if(DOOR_ROOM->query_f_door())
    {
	write("You turn the wheel for a few turns to the stop.\n");
	SAY(" turns the wheel.\n");
    }
    else
    {
	LSAY("Using all "+TP->query_possessive()+" strength, ", 
	  " just barely manages to turn the wheel.\n");
	write("Using all your strength, you just barely manage to turn the wheel.\n");
	DOOR_ROOM->set_f_door(-1);
    }
    return 1;
}

void close_door()
{
    DOOR_ROOM->set_f_door(0);
}

object query_wheel_user() { return wheel_user; }

int do_open(string str)
{
    if(!str || (str != "hatch"))
    {
	NF("Open what?\n");
	return 0;
    }

    if(hatch_open)
    {
	NF("But the hatch is already open!\n");
	return 0;
    }

    if(can_see_hatch(TP))
    {
	if(hatch_locked)
	{
	    if(TP->test_bit("Gondor",MORGUL_GROUP,MORGUL_ENTRY_BIT))
	    {
		write(BSN("The hatch is locked, but when you pull at the metal plate, " +
		    "the lock breaks, and you open the hatch. "));
		say(QCTNAME(TP) + " pulls at the metal plate. Suddenly, with a jerk, " +
		  "the hatch opens. \n");
		hatch_open = 1;
		hatch_locked = 0;
		hatch_broken = 1;
		return 1;
	    }
	    NF("The hatch is locked.\n");
	    return 0;
	}
	write("You open the hatch.\n");
	say(QCTNAME(TP) + " opens the hatch.\n");
	hatch_open = 1;
	return 1;
    }
    else
    {
	NF("Open what?\n");
	return 0;
    }
}

int do_close(string str)
{
    if(!str || (str != "hatch"))
    {
	NF("Close what?\n");
	return 0;
    }

    if(!hatch_open)
    {
	if(can_see_hatch(TP))
	{
	    NF("But the hatch is not open!\n");
	}
	else
	{
	    NF("Close what?\n");
	}
	return 0;
    }
    write("You close the hatch.\n");
    say(QCTNAME(TP) + " closes the hatch.\n");
    hatch_open = 0;
    return 1;
}

int do_lock(string str)
{
    object key;

    if(!str || (str != "hatch" && str != "hatch with key") )
    {
	NF("Lock what?\n");
	return 0;
    }

    if(!can_see_hatch(TP))
    {
	NF("You find no hatch.\n");
	return 0;
    }

    if(hatch_open)
    {
	NF("The hatch is open. Close it before you try to lock it!\n");
	return 0;
    }

    if(!(key = present(query_key_name(),TP)))
    {
	if(present("key",TP))
	{
	    write("Your key doesn't seem to fit.\n");
	    say(QCTNAME(TP) + " tries to lock the hatch.\n");
	    return 1;
	}
	NF("You need a key to lock the hatch.\n");
	return 0;
    }

    if(hatch_locked)
    {
	write("You try to lock the hatch, but it is already locked.\n");
	say(QCTNAME(TP) + " tries to lock the hatch.\n");
	return 1;
    }

    if(hatch_broken)
    {
	write(BSN("You try to lock the hatch, but the lock is broken, " +
	    "and there is no way to lock the hatch again.\n"));
	say(QCTNAME(TP) + " tries to lock the hatch.\n");
	return 1;
    }

    write("You lock the hatch with the "+key->short()+".\n");
    say(QCTNAME(TP) + " locks the hatch with a key.\n");
    hatch_locked = 1;
    return 1;
}

int do_unlock(string str)
{
    object key;

    if(!str || (str != "hatch" && str != "hatch with key" &&
	str != "plate" && str != "plate with key") )
    {
	NF("Unlock what?\n");
	return 0;
    }

    if(!can_see_hatch(TP))
    {
	NF("You find no hatch.\n");
	return 0;
    }

    if(hatch_open)
    {
	NF("The hatch is already open!\n");
	return 0;
    }

    if(!(key = present(query_key_name(),TP)))
    {
	if(present("key",TP))
	{
	    write("Your key doesn't seem to fit.\n");
	    say(QCTNAME(TP) + " tries to unlock the hatch.\n");
	    return 1;
	}
	NF("You need a key to unlock the hatch.\n");
	return 0;
    }

    if(!hatch_locked)
    {
	write("You try to unlock the hatch, but it is already unlocked.\n");
	say(QCTNAME(TP) + " tries to unlock the hatch.\n");
	return 1;
    }

    if(hatch_broken)
    {
	write(BSN("When you try to unlock the hatch, you notice that the lock is broken, " +
	    "so there is no need to unlock it!\n"));
	say(QCTNAME(TP) + " tries to unlock the hatch.\n");
	return 1;
    }

    write("You unlock the hatch with the "+key->short()+".\n");
    say(QCTNAME(TP) + " unlocks the hatch with a key.\n");
    if(TP->query_prop(MORGUL_ENTRY_HATCH) == 1)
	TP->change_prop(MORGUL_ENTRY_HATCH,2);
    hatch_locked = 0;
    return 1;
}

string exa_wheel()
{
    if(hatch_open)
	return BSN("Inside the hatch, you can see a large wooden wheel. You might " +
	  "try to turn it. ");
    return "You find no wheel.\n";
}

string exa_lock()
{
    if(!can_see_hatch(TP))
	return "You find no lock.\n";

    if(hatch_open)
    {
	if(hatch_broken)
	    return BSN("On the backside of the metal plate, you find a small lock " +
	      "that could be operated through the keyhole. But the bolt is broken, " +
	      "so it is impossible to lock the hatch again. ");
	return BSN("On the backside of the metal plate, you find a small lock " +
	  "that can be operated through the keyhole. ");
    }
    return BSN("You cannot see any lock, all you see is a small keyhole in the " +
      "metal plate. With the correct key, you might be able to operate a lock that " +
      "is probably fastened to the inner side of the metal plate. ");
}

int do_search(string str)
{
    if (str == "wheel" && !hatch_open)
    {
	write("You don't find any " + str + " to search.\n");
	return 1;
    }
    return 0;
}
