/* 
 * /Kalad/common/wild/pass/underdark/u6.c
 * Purpose    : Create a peril on the approach to Dark Dominion
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Aug'97: Adopted to dark_dom inherit
 */

# pragma strict_types
# include <macros.h>
# include <ss_types.h>
# include <stdproperties.h>
# include "dark_dom.h"

inherit DARK_DOM;

void
create_dark_dom()
{
    set_short("Inside the shaft");
    set_long("You are inside the shaft, suspended between the imposing "+
      "darkness above and below you.\n");
    add_item(({"imposing darkness","darkness"}),"The absence of light seems "+
      "unending.\n");
}
void
init()
{
    ::init();

    add_action("try_climb", "climb");
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

	    tell_room(DARK(u7), "Suddenly you hear a lot of "+
	      "noise from above and " + QTNAME(this_player()) + " falls " +
	      "down with a bone-crushing sound!\n");

	    this_player()->move_living("M", DARK(u7), 1);
	    return 1;
	}

	this_player()->move_living("climbing up the rock face", DARK(u5), 1);
	return 1;
    }

    if (str == "down")
    {
	set_dircmd("down");
	this_player()->move_living("climbing down", DARK(u7), 1);
	return 1;
    }

    return 0;
}
