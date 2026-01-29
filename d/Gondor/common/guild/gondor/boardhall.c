#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/common/guild/gondor/no_theft";

#include <macros.h>
#include <stdproperties.h>
#include <std.h>

#include "/d/Gondor/defs.h"

public int     leave_hall();
public string  long_func();
public string  read_list();
public string  read_poster();
public string  read_reports();

public void
create_room()
{
    object  board;

    set_short("the Gondorian Rangers Boardroom");
    set_long(long_func);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_STEAL, no_theft);

    add_exit(RANGER_DIR + "recruithall",       "north", 0, 0);
    add_exit(RANGER_GON_DIR + "wcorr",         "west",  0, 0);
    add_exit(RANGER_GON_DIR + "gondor_train",  "south", 0, 0);
    add_exit(ANO_DIR + "druedain/rangerfield", "east",  leave_hall, 0);
    add_exit(RANGER_GON_DIR + "uphall",        "up",    0, 0);
    add_item("poster", read_poster);
    add_cmd_item("poster", "read", read_poster);
    add_item("list", read_list);
    add_cmd_item("list", "read", read_list);
    add_item(({"reports","report","scout reports"}), read_reports);
    add_cmd_item(({"reports","report","scout reports"}), "read", read_reports);

    if (!objectp(present("board", TO)))
    {
       board = clone_object(BOARD_DIR + "rog_pub_board");
        board->move(TO);
    }
}

public string
read_poster()
{
    return "See Amaron the Master Ranger in the hall to the north.\n"+
        "He may have a task for you, if you ask him.\n"+
        "    The Council of Rangers.\n";
}

public string
long_func()
{
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day(),
            longtxt = 
        "This is the entryhall of the Rangers of Gondor, where the Rangers "+
        "can get information about the recent events. There is a bulletin "+
        "board here, where announcements will be posted "+
        "or young travellers may ask for membership. Strong oak "+
        "beams support the ceiling, and oak panels make up the "+
        "walls of the hall. A poster hangs on the north wall, and a list hangs "+
        "beside it. Near the board you see some scout reports. "+
        "In the northeast corner a stair leads up to the second floor.";

    switch (time)
    {
    case "night":
        longtxt += " Through the east door you see only darkness as it is night.";
        break;
    case "early morning":
        longtxt += " Through the east doorway you see long shadows cast by the rising sun.";
        break;
    case "morning":
    case "noon":
    case "afternoon":
        longtxt += " Through the east door daylight enters the hall.";
        break;
    case "evening":
        longtxt += " Through the east door you see the sky is colored golden red.";
        break;
    }
    return BSN(longtxt);
}

public string
read_reports()
{
    write("You read the reports:\n\n");
    TP->more(read_file(RANGER_DIR + "txt/scoutreports.txt", 2), 0);
    return "";
}

public string
read_list()
{
    string *ol;
    int     i;

    FIX_EUID
    ol = (R_OUTLAW)->query_outlaw() + ({ });
    if (!sizeof(ol))
    {
        write("There are no names on the outlaw list right now.\n");
        return "";
    }
    i = 0;
    while (i < sizeof(ol))
    {
        write("  * " + CAP(ol[i]) + ", " + ol[i+1] + "\n");
        i += 2;
    }
    return "";
}

public int
leave_hall()
{
    if (TP->query_npc()) 
        return 0;
    write("You walk through the open doorway out of the house.\n");
    if (TP->query_prop("_ranger_was_stealthy"))
    {
        TP->remove_prop("_ranger_was_stealthy");
        if (TP->query_autosneak() || sizeof(TP->query_team()))
            return 0;
        TP->set_autosneak(1);
        TP->catch_msg("You prepare to move stealthily again as you were "
            + "when entering the hideout.\n");
    }
    return 0;
}

