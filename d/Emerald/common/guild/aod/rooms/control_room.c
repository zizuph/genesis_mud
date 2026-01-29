/*
 *  /d/Emerald/common/guild/aod/control_room.c
 *
 *  This is a room to control certain features of the Army of Darkness.
 *  It is for official use by the Guild Master only.
 *
 *  Created June 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/room";

#include <language.h>
#include <stdproperties.h>
#include <time.h>
#include "../aod_titles.h"

public string      List_Options =
           "Ogres cannot read, but the Darklings allow them to know:\n\n"
         + "\t  Collecting information is given as follows:\n\n"
         + "\t  <know readerboard>  - Show comprehensive collection"
         + " information\n"
         + "\t* <know [racename]>   - Show top collectors for a"
         + " particular race\n"
         + "\t* <know total>        - Show top total collectors\n"
         + "\t* <know hourly>       - Show top collection rates\n"
         + "\t  <know [playername]> - Show information for"
         + " a particular person\n"
         + "\t  <know roster>       - Show a full Duty Roster\n"
         + "\t  <know slackers>     - Show a know of unproductive"
         + " members\n"
         + "\t  <know rate>         - Show your collection rate\n"
         + "\t  <know shortcuts>    - Show a list of command shortcuts\n"
         + "\t  <know milestones>   - Show a list of Army"
         + " Milestones\n\n"
         + "\t  Items with an asterisk display the top 5 by default.\n"
         + "\t  You may specify a number or 'all' to see entire list.\n";

public void
create_room()
{
    set_short("the Army of Darkness control room");
    set_long("The Army of Darkness control room.\n");

    add_exit("forge", "forge");
    add_exit("bbroom", "board");
    add_exit("aod_shop", "shop");
    add_exit("start", "start");
    add_exit("joinroom", "join");
    setuid();
    seteuid(getuid());
}


public int
dark1(string arg)
{
    find_living(arg)->catch_tell("A sudden, strange feeling comes"
      + " over you ... confusion ... your mind begins racing for no"
      + " apparent reason!\n");

    return 1;
}

public int
dark2(string arg)
{
    set_this_player(find_living(arg));

    DARKLING_TELL("Be still mortal, for Val-Shoreil, the God of all"
      + " that is blessed has seen your dreams. I serve His purposes"
      + " in the Lands of Emerald.");
}


public int
dark3(string arg)
{
    set_this_player(find_living(arg));

    DARKLING_TELL("The time is come. If you would deal death in the"
      + " name of the God of Darkness, seek for the Tower along the"
      + " north shores of Lake Telberin. You shall be among the first"
      + " in the Great Harvest!");
}


/*
 * Function name:        do_know
 * Description  :        Allow the player to access particular
 *                       statistics on the skull collecting
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_know(string arg)
{
    string  *races = ({ "human", "elf", "hobbit", "dwarf", "gnome",
                        "other", "total", "hourly", "elves", "dwarves",
                        "humans", "hobbits", "gnomes", "goblin",
                        "goblins", "normal", "magic" });
    mixed    accounts;
    mixed    length = "5";
    int      i,
             n = 7;

    notify_fail("Know what? You may <exa sign> for help here.\n");

    if (!strlen(arg))
    {
        notify_fail(List_Options);
        return 0;
    }

    /*
     * This is a way to force the election process to take place
     * immediately so you don't have to wait 10 days.
     */
    if (arg == "update")
    {
        if (this_player()->query_real_name() != "gorboth")
        {
            write("You do not have permission to do that.\n");
            return 1;
        }

        AOD_MASTER->check_leader_update(1);
        return 1;
    }

    if (arg == "rate")
    {
        if (!this_player()->query_guild_member(GUILD_NAME))
        {
            if (!this_player()->query_wiz_level())
            {
                write("Only Army members may check their collection"
                    + " rate.\n");
                return 1;
            }
        }

        write("\t" + sprintf("%-20s", "Membership:")
          + CONVTIME(AOD_MASTER->membership_duration(
            this_player()->query_real_name())) + "\n");
        write("\t" + sprintf("%-20s", "Collection:") + sprintf("%,d",
            AOD_MASTER->query_skull_total(this_player(), 0))
          + " Skulls\n");
        write("\t" + sprintf("%-20s", "Skulls Per Hour:") + sprintf("%,d",
            AOD_MASTER->skulls_per_hour(this_player())) + "\n");
        return 1;
    }

    if (arg == "shortcut" || arg == "shortcuts")
    {
        if (!this_player()->query_guild_member(GUILD_NAME))
        {
            if (!this_player()->query_wiz_level())
            {
                write("Only Army members may know such things!\n");
                return 1;
            }
        }

        write(read_file(AOD_DIR + "shortcuts.txt", 0));
        return 1;
    }

    if (arg == "milestone" || arg == "milestones")
    {
        if (!strlen(read_file(MILESTONE_FILE, 0)))
        {
            this_player()->catch_tell("There have been no milestones"
              + " achieved thus far.\n");
            return 1;
        }

        this_player()->catch_tell(read_file(MILESTONE_FILE, 0));
        return 1;
    }

    if (arg == "roster")
    {
        if (!this_player()->query_guild_member(GUILD_NAME))
        {
            if (!this_player()->query_wiz_level())
            {
                write("Only Army members may know such things!\n");
                return 1;
            }
        }

        AOD_MASTER->print_member_list(this_player());
        return 1;
    }

    if (arg == "readerboard" || arg == "board")
    {
        AOD_MASTER->print_big_list(this_player());
        return 1;
    }

    if (arg == "slackers")
    {
        if (!this_player()->query_guild_member(GUILD_NAME))
        {
            if (!this_player()->query_wiz_level())
            {
                write("Only Army members may know such things!\n");
                return 1;
            }
        }

        AOD_MASTER->display_worthless(this_player());
        return 1;
    }

    if (parse_command(arg, ({}),
        "%p [skull] [skulls] [collections]", races) ||
        parse_command(arg, ({}),
        "%p %s", races, length))
    {
        switch (races[0])
        {
            case "humans":
            {
                races[0] = "human";
                break;
            }
            case "dwarves":
            {
                races[0] = "dwarf";
                break;
            }
            case "elves":
            {
                races[0] = "elf";
                break;
            }
            case "hobbits":
            {
                races[0] = "hobbit";
                break;
            }
            case "gnomes":
            {
                races[0] = "gnome";
                break;
            }
            case "normal":
            {
                races[0] = "normal";
                break;
            }
            case "magic":
            {
                races[0] = "magic";
                break;
            }
            case "goblin":
            case "goblins":
                write("Ogres find goblins too cute and loveable to"
                  + " even think of collecting their skulls!\n");
                return 1;
            default:
            {
                break;
            }
        }

        if (length == "all")
        {
            length = "0";
        }

        length = LANG_WORD2NUM(length);

        AOD_MASTER->print_particular_list(races[0], this_player(),
                                          length, 0);

        if (races[0] != "hourly")
        {
            this_player()->catch_tell("\n"
          + sprintf("%|80s", capitalize(races[0]) + " Skulls Collected: "
          + sprintf("%,d", AOD_MASTER->query_guild_total(races[0]))
          + "\n"));
        }

        if (length == 5)
        {
            write("\n"
              + sprintf("%|80s", "To show more than just the top five"
              + " collectors for\n")
              + sprintf("%|80s", "any list, you may specify a range, or"
              + " use 'all'.\n"));
        }

        return 1;
    }

    accounts = AOD_MASTER->scan_accounts();

    if (!parse_command(arg, ({}), "%p", accounts))
    {
        return 0;
    }

    write("\n" + sprintf("%|80s",
            "Collection information for "
          + capitalize(accounts[0]) + ":\n"));
    write(sprintf("%|80s",
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"));

    write("\t\t\t" + sprintf("%-16s    %-14s", "Skulls Per Hour:",
        sprintf("%,d", AOD_MASTER->skulls_per_hour(accounts[0]))
      + "\n\n"));

    for (i = 0; i < n; i++)
    {
        write("\t\t\t" + sprintf("%-14s      %-14s", capitalize(races[i])
          + " Skulls:", sprintf("%,d", AOD_MASTER->get_info(
            accounts[0], capitalize(races[i]))) + "\n"));

        if (races[i] == "other")
        {
            write("\n");
        }
    }

    return 1;
} /* do_know */


public int
sack_list(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("List the skulls in the sack of what Ogre?\n");
        return 0;
    }

    AOD_MASTER->print_skull_list(arg);
    return 1;
}


/*
 * Function name:        duty_roster
 * Description  :        print the who list for the guild
 * Arguments    :        string arg - if the player typed something
 *                                    after the verb.
 * Returns      :        int 1
 */
public int
duty_roster(string arg)
{
    setuid();
    seteuid(getuid());

    AOD_MASTER->aod_who_list(this_player());
    return 1;
} /* duty_roster */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(duty_roster, "dr");
    add_action(do_know, "know");
    add_action("dark1", "dark1");
    add_action("dark2", "dark2");
    add_action("dark3", "dark3");
    add_action(sack_list, "skulls");
} /* init */
