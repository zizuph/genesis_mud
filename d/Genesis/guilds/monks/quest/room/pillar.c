#include "defs.h"
inherit QUESTROOM;

public void reset_room ();

public void
create_room ()
{
    set_short ("marble hallway");
    set_long ("Flickering torchlight reflects of the white marble "
	+ "walls and casts long, eerie shadows from the three "
	+ "tall pillars at the north end of the hall. The pillars "
	+ "rest on a short, three stepped half-dais against the "
	+ "north wall. Resting upon each pillar is an hourglass "
	+ "containing water.\n");

    reset_room ();
}

public void
reset_room ()
{
    while (sizeof (filter (all_inventory 
	(this_object ()), &->id (QUEST_PILLAR))) < 3)
    {
	clone_object (QUEST_PILLAR)->init_pillar (this_object ());
    }
}

