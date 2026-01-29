inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>

create_room()
{
    set_short("Meeting hall");
    set_long("This is where the citizens of Esgaroth gather to discuss " +
        "things of importance to the city, and leave notes about the " +
        "discussion for those who were not able to attend.  There is a " +
        "bulletin board here.\n");

    add_exit("/d/Rhovanion/common/esgaroth/es-3-12", "east");
    add_prop(ROOM_I_INSIDE, 1);
    load_it_up();
}

void load_it_up()
{
    object bb;

    bb = clone_object("/std/board");
    bb->set_board_name("/d/Rhovanion/common/esgaroth/board");
    bb->set_num_notes(20);
    bb->set_silent(0);
    bb->set_err_log("/d/Rhovanion/log/boarderrs");
    bb->set_show_lvl(0);
    bb->set_remove_level(30);
    bb->set_remove_str("Sorry, you can't do that.\n");
    bb->move(this_object());
}
