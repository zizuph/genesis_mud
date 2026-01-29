/* 
 * /d/Kalad/common/wild/pass/underdark/u39.c
 * Purpose    : Shadowgloom's entry foyer
 * Located    : Dark Dominion southwest of Undraeth.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"
# include <macros.h>

inherit DARK_DOM;

object ob1;

void
create_dark_dom()
{
    set_short("Circular Chamber");
    set_long("You are within a roughly circular chamber. The stone walls "+
      "are colored an unusual reddish-yellowish color, most likely sulphur. "+
      "The strong odor of sulphur lingers in the air, mixing with another, "+
      "far more sinister smell. This area is also clear of the usual debris "+
      "that clutter most natural caverns, since there are no visible "+
      "stalagmites or stalactites. Dark passages lead to the north and west.\n");
    add_item(({"stone walls","stone wall","walls","wall"}),
      "The characteristically dark rock of the region has been "+
      "tainted an unusual red-yellow color due to the presence of sulphur "+
      "in the environment.\n");
    add_item(({"chamber"}),"Its what you are standing in.\n");
    add_item(({"dark passages","dark passage","passages","passage"}),
      "The exits leading out of this rock chamber.\n");
    add_exit(DARK(u32), "north");
    add_exit(DARK(u37), "west", "@@query_move");
    set_alarm(1.0, 0.0, "reset_room");
}

void
reset_room()
{
    if(!ob1)
	(ob1 = clone_object("/d/Kalad/common/wild/pass/npc/iron_golem"))->move_living("xxx", 
	  this_object());
}

int
query_move()
{
    if (present(ob1))
    {
	write("You cannot go that way! The iron golem is in the way!\n");
	write("The iron golem intones: Show the proper respect due Shadowgloom "+
	  "and you may pass.\n");
	say(QCTNAME(this_player()) + " tries to go west but runs into the iron golem.\n");
	say("The iron golem intones: Show the proper respect due Shadowgloom "+
	  "and you may pass.\n");
	return 1;
    }
    return 0;
}
