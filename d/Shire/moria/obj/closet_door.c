inherit "/std/door";
#include "defs.h"

create_door()
{
    set_door_id("Gwindor's door");
    set_door_name(({"wooden oak door", "wooden door", "oak door", "door"}));
    set_other_room(MINES_DIR + "alch_home");
    set_lock_desc("The lock seems to be of dwarven origin. You would " +
		  "bet that it would be hard, if not impossible, to " +
		  "try to pick this lock.");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_door_name(({"door","heavy door"}));
    set_pick(101);
    set_key(77660334); // My phone number actually. :-)

    set_no_show_composite(1);

    add_prop(DOOR_I_HEIGHT, 150);
}

init_north()
{
    set_pass_command(({"s","south"}));
    set_door_desc("This is a heavy wooden oak door in the south.\n"+
		  "On the wall there is inscribed in runes the name:\n" +
		  "\tGwindor.\n");
    set_open_desc("an opened heavy oak door leading into a spartan room.\n");
//    set_closed_desc("a heavy oak door which seems to be firmly closed.\n");
    set_closed_desc("The heavy oak door is firmly closed.\n");
}

init_south()
{
    set_pass_command(({"n", "north"}));
    set_door_desc("This is the heavy wooden oak door which leads "+
		  "out north into the dangerous Mines of Moria.");
    set_open_desc("In the north you notice a heavy oak door which " +
		  "is open. It leads north into the tunnels of the " +
		  "Mines of Moria.\n");
    set_closed_desc("The heavy oak door is closed.\n");
}

