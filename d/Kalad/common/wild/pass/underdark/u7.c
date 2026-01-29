/*
 * /d/Kalad/common/wild/pass/underdark/u7.c
 * Purpose    : Entry to the Dark Dominion, bottom of shaft
 * Located    : Beneath the Hespyre Mountains
 * Created By : Antharanos
 * Modified By: Nikklaus, Aug'97: Consolidated inheritance.
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "dark_dom.h"

inherit DARK_DOM;

#define HARD_TO_CLIMB 30
#define DAMAGE 150

public void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+"You find yourself at the bottom of an apparently endless "+
      "shaft. There is no ceiling here, at least none that you can see for "+
      "yawning above you like some horrible mouth is a gigantic hole. A dark "+
      "passage heads east from here.\n");
    add_item(({"shaft","gigantic hole","hole"}),"All you can see is "+
      "impenetrable and seemingly infinite darkness.\n");
    add_exit(DARK(u6), "up", "@@climb", 3, 3);
    add_exit(DARK(u8), "east", 0, 1, 1);
}

int
climb()
{
    if(this_player()->query_skill(SS_CLIMB) < random(HARD_TO_CLIMB))
    {
	write("You slip while climbing the sheer rock face and fall down.\n");
	write("You slam into a group of stalagmites!\n");
	this_player()->heal_hp(-DAMAGE);
	say(QCTNAME(this_player()) + " fell down while trying to climb the rock face and slammed into some stalagmites.\n");
	if(this_player()->query_hp() < 1)
	    this_player()->do_die(this_object());
	return 1;
    }
    write("You manage to scale the rock face.\n");
    say(QCTNAME(this_player()) + " manages to scale the rock face.\n");
    return 0;
}
