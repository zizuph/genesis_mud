#include "../defs.h"
inherit STD + "room.c";
#include <macros.h>

int check_exit();
int leave();

void
create_room()
{
    set_short("in a dark basement.");
    set_long("In a dark forgotten basement in Altaruk." +
        " New buildings has been build over the remains" +
        " of the old ones destroyed by raiding giants." +
        " A stone pillar leans against the wall.\n");

    add_item(({"pillar","stone pillar"}),"A stone pillar" +
        " has fallen against the wall leaving a hole in" +
        " the ceiling where it hit.\n");

    add_item("hole","There is a hole in the ceiling.\n");
    
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, 0);
    add_exit(ALT_MAN + "temp.c", "up", &check_exit(),3 ,1);
    add_exit("07.c", "north", 0, 1, 1);
}

int
check_exit()
{
    write("You climb onto the fallen pillar.\n");
    say(QCTNAME(this_player()) + " climbs onto a fallen pillar.\n");
    set_alarm(1.0, 0.0, &write("You start to ascend towards the hole in the ceiling.\n"));
    set_alarm(4.0, 0.0, &write("Your about halfway on the pillar.\n"));
    set_alarm(8.0, 0.0, &write("Your getting close to the hole.\n"));
    set_alarm(12.0, 0.0, &leave());
    return 1;
}

int
leave()
{
    write("You reach the top and climb through the hole.\n");
    say(QCTNAME(this_player()) + " climbs through a hole in the ceiling.\n");
    this_player()->move_living("M", ALT_MAN + "temp.c", 1, 0);
    say(QCTNAME(this_player()) + " climbs out of a hole in the ground.\n");
    return 1;
}