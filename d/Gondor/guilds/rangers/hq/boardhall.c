/*
 *  /d/Gondor/guilds/rangers/hq/boardhall.c
 *
 *  Public bulletin board room of Ranger Central Headquarters
 *
 *  Coded by Elessar
 *  Modification log:
 *     Alto, 7 July 2001 to fit CH theme
 *     Gwyneth, 3 May 2004 to tidy it up
 *     Tigerlily, Dec. 31, 2004--removed deleted players from list
 *                         of outlaws and notorious outlaws
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
#include "/d/Gondor/defs.h"

#include <macros.h>
#include <std.h>
#include <stdproperties.h>

inherit RANGERS_HQ_DIR + "ch_funcs.c";

#define RANGER_I_WAS_STEALTHY "_ranger_was_stealthy"

public int     leave_hall();
public int     check_ranger();
public string  long_func();
public string  read_list();
public string  read_poster();
public string  read_reports();

public void
create_gondor()
{
    object  board;

    set_short("the board room of Ranger Central Headquarters");
    set_long(long_func);

    hideout_add_items();

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  1);

    add_exit(RANGERS_HQ_DIR + "join",                 "north", 0, 0);
    add_exit(RANGERS_HQ_DIR + "dcorridor1",           "west",  0, 0);
    add_exit(RANGERS_HQ_DIR + "herb_shop",            "south", 0, 0);
    add_exit(ANO_DIR        + "druedain/rangerfield", "east",  leave_hall, 0);
    add_exit(RANGERS_HQ_DIR + "uphall",               "up",    check_ranger, 0);

    add_item("poster", read_poster);
    add_cmd_item("poster", "read", read_poster);

    add_item("list", read_list);
    add_cmd_item("list", "read", read_list);

    add_item(({"reports","report","scout reports"}), read_reports);
    add_cmd_item(({"reports","report","scout reports"}), "read", read_reports);

    add_item(({"north wall"}), "On the north wall you see a poster and "
        + "a list.\n");
    add_item(({"corner", "northeast corner"}), "In the northeast corner you "
        + "see a stairwell curving up to the second floor.\n");
    add_item(({"second floor"}), "Not much of it can be seen from down "
        + "here.\n");
    add_item(({"stairwell", "stairs", "stair"}), "The stairs curve up to the "
        + "second floor.\n");

    if (!objectp(present("board", TO)))
    {
       board = clone_object(BOARD_DIR + "rog_pub_board");
       board->move(TO);
    }
}

public string
read_poster()
{
    return "\n --------------------------------------------------------- \n"
        + "|o                                                       o|\n"
        + "|                                                         |\n"
        + "|                                                         |\n"
        + "|      See Amaron the Master Ranger in the hall to        |\n"
        + "|      the north. He may have a task for you, if you      |\n"
        + "|      ask him.                                           |\n"
        + "|                          The Council of Rangers         |\n"
        + "|                                                         |\n"
        + "|o                                                       o|\n"
        + " --------------------------------------------------------- \n\n";

}

public string
long_func()
{
    object clock = find_object(CLOCK);
    string time = clock->query_time_of_day(),
           longtxt = "This is the central headquarters of the Rangers of "
               + "the Westlands. Rangers gather here from the four corners "
               + "of the realms to share and gather information about recent "
               + "events. There is a bulletin board here, the only formal "
               + "conduit of communication between the secretive rangers "
               + "and the outside world. Strong oak beams support the "
               + "ceiling, and oak panels make up the walls of the hall. A "
               + "poster hangs on the north wall, and a list hangs beside "
               + "it. Near the board you see some reports pinned up by ranger "
               + "scouts. In the northeast corner a stairwell leads up to the "
               + "second floor."; 

    switch (time)
    {
    case "night":
        longtxt += " Through the east door you see only darkness as it is "
            + "night.";
        break;
    case "early morning":
        longtxt += " Through the east doorway you see long shadows cast "
            + "by the rising sun.";
        break;
    case "morning":
    case "noon":
    case "afternoon":
        longtxt += " Through the east door daylight enters the hall.";
        break;
    case "evening":
        longtxt += " Through the east door you see the sky is colored "
            + "golden red.";
        break;
    }

    return (longtxt + "\n");
}

public string
read_reports()
{
    write("You read the reports:\n\n");
    TP->more(read_file(RANGERS_HQ_DIR + "lib/scoutreports.txt", 2), 0);
    return "";
}

/*
 * Function name: read_list
 * Description  : Lists outlaws and NOs
 * Returns      : The list
 */
public string
read_list()
{
    string text;
    string *outlaw_list, *not_outlaw_list;
    int    i = -1, j = -1;

    outlaw_list = MANAGER->query_outlaw_members();
    not_outlaw_list = MANAGER->query_notorious_members();

    text = "These scoundrels are presently outlaws of the Westlands:\n\n";

    seteuid(getuid());
    
    while (++i < sizeof(outlaw_list))
    {
        if (SECURITY->exist_player(outlaw_list[i]))
            text += "- " + CAP(outlaw_list[i]) + ", Outlaw.\n";
    }

    while (++j < sizeof(not_outlaw_list))
    {
        if (SECURITY->exist_player(not_outlaw_list[j]))
            text += "- " + CAP(not_outlaw_list[j]) + ", Notorious Outlaw.\n";
    }

    return text + "\n";
}

/*
 * Function name: leave_hall
 * Description  : Resets stealth if the Ranger was stealthy upon entering.
 * Returns      : 0
 */
public int
leave_hall()
{
    object tp = this_player();

    if (tp->query_npc()) 
        return 0;

    write("You walk through the open doorway out of the house.\n");
    if (tp->query_prop(RANGER_I_WAS_STEALTHY))
    {
        tp->remove_prop(RANGER_I_WAS_STEALTHY);
        if (tp->query_autosneak() || sizeof(tp->query_team()))
            return 0;
        tp->set_autosneak(1);
        write("You prepare to move stealthily again as you were "
            + "when entering the hideout.\n");
    }

    return 0;
}

/*
 * Function name: check_ranger
 * Description  : Checks if the player is allowed
 * Returns      : 0 if allowed, 1 if not
 */
public int
check_ranger()
{
    object tp = this_player();

    if (RANGERS_MEMBER(tp))
    {
        write("Welcome, Ranger of the Westlands!\n");
        return 0;
    }

    if (tp->query_wiz_level())
    {
        write("Welcome, Wizard!\n");
        return 0;
    }

    write("As you obviously have no business up there, you decide "
        + "to remain downstairs and respect the privacy of the "
        + "Rangers of the Westlands.\n");
    return 1;
}
