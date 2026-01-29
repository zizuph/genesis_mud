/*
 * Upper corridor in Elrond's house
 * By Finwe, December 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;

void
create_house_room()
{
    set_short("An upstairs corridor in the house of Elrond");
    set_long("You stand in a corridor outside of Elrond's " +
        "private quarters and the library. The corridor is " +
        "plainly decorated except for a large window on the " +
        "west wall. The window fills the room with gentle " +
        "@@daylight_desc@@.\n");
    add_item("door",
        "The door is simple in design. No special decorations " +
        "adorn it. The door is locked.\n");
    add_item(({"west window", "western window"}),
        "@@west_up@@ The mountains loom in the distance.\n");
    set_extra_window("@@window_position@@ set into the " +
        "west wall.");
 
    num_of_windows=1;

    add_exit("/d/Shire/rivendell/library/library", "north");
    add_exit(VALLEY_DIR + "elrond_study", "south");
    add_exit(VALLEY_DIR + "u_cor04", "east");
}
 

int
block_exit()
{
    if (this_player()->query_wiz_level()) 
    {
        write("\n\nYou enter an area that is not open to mortals.\n\n\n");
        return 0;
    }
    
    write("The door to the library is locked.\n");
    say(QCTNAME(TP) + " rattles the door of the library " +
        "but discovers it is locked.\n");
    return 1;
}
