#pragma save_binary

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_room()
{
    set_short("The temple of Tulkas");
    set_long(BS("The temple of Tulkas, also called Astaldo, the brave. "+
    "This room is spartanly furnished. A simple but beautiful altar is at "+
    "the east wall.\n"));
    add_item("altar","This altar is dedicated to the worship of Tulkas.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR+"t_corridor","west",0);
}

init()
{
    ::init();
    add_action("pray","pray");
    add_action("pray","worship");
}

int
pray()
{
    TP->catch_msg(BS("You kneel and start to pray to Tulkas. You feel "+
    "yourself filled with new hope, and rise.\n")); 
    say(QCTNAME(TP) + " closes "+POSSESSIVE(TP)+" eyes and kneels briefly.\n");
    return 1;
}