/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

void
create_tunnel()
{
    add_std_herbs("underground");

    set_short("Inside the shaft");
    set_long("You are inside the shaft, suspended between the imposing "+
      "darkness above and below you.\n");
    add_item(({"imposing darkness","darkness"}),"The absence of light seems "+
      "unending.\n");

    reset_room();

    add_exit(TUN_DIR + "tu18", "down");
    add_exit(TUN_DIR + "cv05", "up");
}
void
init()
{
    ::init();

//    add_action("try_climb", "climb");
}
int
try_climb(string str)
{
    notify_fail("Climb up or down?\n");

    if (!str)
	return 0;

    if (str == "up")
    {

	if((this_player()->query_skill(SS_CLIMB) + this_player()->query_stat(SS_DEX) +
	    random(100) / 3) + this_player()->query_encumberance_weight()
	  < 40)
	{
	    write("You start to climb but slip and fall all the way down "+
	      "and hurt yourself.\n");
	    say(QCTNAME(this_player()) + " starts to climb the rock face but "+
	      "slips and falls all the way down.\n");
	    this_player()->heal_hp(-250);

	    tell_room(TUN_DIR + "tu18", "Suddenly you hear a lot of "+
	      "noise from above and " + QTNAME(this_player()) + " falls " +
	      "down with a bone-crushing sound!\n");

	    this_player()->move_living("M",TUN_DIR + "tu18", 1);
	    return 1;
	}

	this_player()->move_living("climbing up the rock face", TUN_DIR + "cv05", 1);
	return 1;
    }

    if (str == "down")
    {
	set_dircmd("down");
	this_player()->move_living("climbing down", TUN_DIR + "tu18", 1);
	return 1;
    }

    return 0;
}

void
reset_room()
{
    set_searched(0);
}