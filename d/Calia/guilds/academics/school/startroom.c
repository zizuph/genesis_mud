/*
 * Start Room for the Academy of Elemental Arts in Gelan
 * 
 * Every member of the Elemental Academy Guild has the option of starting
 * here in this room. It is part of the Elemental Academy of Gelan.
 *
 * Created by Petros, August 2009
 */

#pragma strict_types

#include "defs.h"

inherit SCHOOL_ROOM_BASE;

public void
create_school_room()
{
    set_short("Dormitory");
    set_long("You have entered a rather bare room with barely any furnishings "
        + "besides the long rows of bunks. These are very clearly the "
        + "dormitories of the students of the Academy. Students come here to "
        + "rest after a long day of classes, studies, and experiments - failed "
        + "and otherwise! As you are a student of the Academy, you "
        + "can choose to <start here> if you wish to make this your nightly "
        + "residence.\n\n");
                   
    add_exit(ACADEMIC_SCHOOL + "boardroom", "west");
}

public void
init()
{
    ::init();
    
    add_action("start_here", "start");
}

public int
start_here(string str)
{
    if (!strlen(str) || str != "here")
    {
        notify_fail("Did you wish to <start here>?\n");
        return 0;
    }
    
    this_player()->set_default_start_location(ACADEMIC_SCHOOL + "startroom");
    write("Ok!\n");
    return 1;
}
