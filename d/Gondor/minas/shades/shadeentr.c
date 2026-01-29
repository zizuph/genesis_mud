/*
 *	/d/Gondor/minas/shades/shadeentr.c
 *
 *	Modification log:
 *	20-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static int     check_for_herb();
static int     keep_back(string dir);
public string  long_func();

static object  Guard;

public void
create_gondor()
{
    set_short("in the entryhall of the Shades quarters");
    set_long(long_func);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  1);
    add_exit(MINAS_DIR + "rooms/oldcellar", "south", 0);
    add_exit(SHADES_DIR + "office",   "north", check_for_herb);
    add_exit(SHADES_DIR + "corr1",    "west",  &keep_back("west")); 
    reset_room();
}

static int
check_for_herb()
{
    if (!objectp(Guard) || !objectp(present(Guard, TO)))
	return 0;

    if (TP->query_prop("_gondor_quest_is_smuggler"))
    {
	write("The guard says: You have been expected, " +
	      TP->query_name() + ".\n");
	return 0;
    }
    return keep_back("north");
}

static int
keep_back(string dir)
{
    if (!objectp(Guard) || !objectp(present(Guard, TO)))
	return 0;

    if (!CAN_SEE(Guard, TP)) 
	return 0;
    write("The guard says: You are not allowed in that room, " + 
	  TP->query_race_name()+".\n");
    say("The guard stops " + QTNAME(TP) +
	" from entering the "+dir+" door.\n");
  return 1;
}

public string
long_func()
{
    string longstr = "This is the gloomy entrancehall of the Shades quarters. "+
        "Two torches are hanging on the south wall, on each side of the door. "+
        "The walls are covered with dark, heavy panels. There's another door "+
        "leading north, and a passageway leads west. ";
    if (objectp(Guard) && objectp(present(Guard, TO)))
	longstr += "A man is standing here, guarding the doors.";
    return BSN(longstr);
}

public void
reset_room()
{ 
    Guard = clone_npc(Guard, SHADES_DIR + "shadeguard");
}
