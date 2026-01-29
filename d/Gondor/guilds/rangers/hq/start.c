/*
 *  /d/Gondor/guilds/rangers/hq/start.c
 *
 *  The bunkroom of Central Headquarters
 *
 *  Coded by Elessar
 *    Modified by Alto & Gwyneth, 07 July 2001, changed to fit CH theme
 *    Modified by Gwyneth, 25 March 2002, added logbook writing and viewing.
 *
 *  Modifications:
 *    Tigerlily, 02 January 2004, removed torches.
 *    Toby, 29-mar-2007: Fixed with 'view_log', it now gives
 *                       a message if no log entry is made for 
 *                       the requested apprentice.
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_HQ_DIR + "ch_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define LOGBOOK RANGERS_OBJ + "logbook.c"

public string      long_desc();

print_member_list()
{
    string text, *apprentice_list, *trusted_list;
    int i, j;

    text = "Below are the Ranger apprentices.\n\nYou may 'write log for <apprentice>' or 'view log for <apprentice>':\n\n";

    trusted_list = MANAGER->query_company_members(APPROVED_APP_LEVEL);
    apprentice_list = MANAGER->query_company_members(APPRENTICE_LEVEL);
    
    text += "Trusted Ranger Apprentices\n--------------------------\n";
    i = -1;
    while (++i < sizeof(trusted_list))
    {
        /* Don't want a jr's name on the guildlist */
        if ((extract(trusted_list[i], -2) == "jr") &&
          !(TP->query_wiz_level()))
        {
            continue;
        }

        text += "- " + capitalize(trusted_list[i]) + "\n";
    }
    
    text += "\nRanger Apprentices\n------------------\n";
    j = -1;
    while (++j < sizeof(apprentice_list))
    {
        /* Don't want a jr's name on the guildlist */
        if ((extract(apprentice_list[j], -2) == "jr") &&
          !(TP->query_wiz_level()))
        {
            continue;
        }

        text += "- " + CAP(apprentice_list[j]) + "\n"; 
    }

    return text + "\n";
}


static string 
exa_poster()
{
    write("On the poster you read:\n\n");
    write(print_member_list());
    return "";
}


string
long_desc()
{
    return "This is where rangers stationed at Central Headquarters sleep. "
        + "The room is narrow, but long, with rows of bunks along the "
        + "north and south walls. The light is kept dim, even during the "
        + "day, so that those rangers who pull the night watch can sleep. "
        + "The wooden floor creaks beneath your feet, "
        + "not as a result of poor carpentry, but rather because the hideout "
        + "stands partially in the trees and was built by clever hands "
        + "to shift in the wind. To the east lies the main passage of the "
        + "second floor. There is a poster on the wall.\n";
}

public void
create_gondor()
{
    set_short("the bunkroom of Central Headquarters");
    set_long(&long_desc());

    hideout_add_items();
    
    add_item(({"room"}), &long_desc());
    add_item(({"passage", "main passage"}), "To the east there is a passage "
        + "that appears to lead to other rooms. Where it leads, however "
        + "cannot be seen from here.\n");
    add_item(({"wall", "walls"}), "There are three walls here: a north "
        + "wall, a south wall and an west wall.\n");
    add_item(({"north wall"}), "Rows of bunks line the north wall.\n");
    add_item(({"south wall"}), "Rows of bunks line the south wall.\n");
    add_item(({"west wall"}), "A torch stand is mounted in the center of "
        + "the west wall.\n");
    add_item(({"logbooks", "logbook", "books", "book", "log books","log book"}),
        "Attached to each apprentice's bunk is a logbook. You may write a "
        + "short entry in it or view the entries already there.\n");
    add_item(({"bunk", "bunks", "rows", "row"}), "There are enough bunks here "
        + "to accomodate a company of rangers. Most of them are neatly made "
        + "up such that a copper coin would bounce if dropped on the bunk. "
        + "Attached to each apprentice's bunk is a logbook. You may write "
        + "a short entry in it or view the entries already there. "
        + "A few bunks are being used at the moment, so please be quiet as "
        + "you move about the room.\n");


    add_item(({"rangers","members","poster"}), exa_poster);
    add_cmd_item(({"rangers","members","poster"}), "read", exa_poster);
    
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(RANGERS_HQ_DIR + "ucorridor1", "east", 0, 1);
}

int
start(string str)
{
    if (!strlen(str) || lower_case(str) != "here")
    {
        notify_fail("Start here?\n");
        return 0;
    }

    if (!RANGERS_MEMBER(this_player()))
    {
        notify_fail("Only Rangers may sleep here!\n");
        return 0;
    }
    else if (this_player()->set_default_start_location(RANGERS_HQ_START))
    {
        write("You decide to start your day out here.\n");
        return 1;
    }
    else
    {
        notify_fail("Some problem prevents you from starting here.\n" +
            "Please make a bug report.\n");
        return 0;
    }
}

public int
write_log(string str)
{
    object logbook;
    string name;

    if (!strlen(str))
    {
        notify_fail("Write log for <apprentice>?\n");
        return 0;
    }

    if (!parse_command(str, ({}), " 'entry' / 'log' [for] %w", name))
    {
        notify_fail("Write log for <apprentice>?\n");
        return 0;
    }

    logbook = clone_object(LOGBOOK);
    logbook->move(this_player(), 1);
    logbook->begin_entry(name, this_player());
    return 1;
}

public int
view_log(string str)
{
    string name, log_text;

    if (!strlen(str))
    {
        notify_fail("View log of <apprentice>?\n");
        return 0;
    }

    if (!parse_command(str, ({}), " 'entry' / 'log' [of] / [for] %w", name))
    {
        notify_fail("View log for <apprentice>?\n");
        return 0;
    }    

/*    if (MANAGER->query_ranger_level(this_player()->query_real_name()) 
      > APPROVED_APP_LEVEL)
        write(MANAGER->query_apprentice_log(name, 1));
    else
        write(MANAGER->query_apprentice_log(name, 0));
*/
    if (MANAGER->query_ranger_level(this_player()->query_real_name()) 
      > APPROVED_APP_LEVEL)
        log_text = MANAGER->query_apprentice_log(name, 1);
    else
        log_text = MANAGER->query_apprentice_log(name, 0);

    if(strlen(log_text))
       write(log_text);
    else
       write("No log entry for " + capitalize(name) + ".\n");
 
    return 1;
}

void
init()
{
    ::init();

    add_action(start, "start");
    add_action(write_log, "write");
    add_action(view_log, "view");
}


