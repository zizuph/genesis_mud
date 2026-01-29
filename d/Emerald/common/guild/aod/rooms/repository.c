/*
 *  /d/Emerald/common/guild/aod/rooms/repository.c
 *
 *  This room is the heart and soul of the Army of Darkness guild. Here,
 *  players can deposit their skulls, and see statistics on all of the
 *  skull collection that has taken place. Through skull deposits a
 *  a player raises their status in the guild.
 *
 *  Copyright (c) April 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/d/Emerald/std/room";

#include "../aod_titles.h"

#include <language.h>
#include <stdproperties.h>
#include <time.h>

/* Prototypes */
public void        create_emerald_room();
public string      exa_readerboard();
public string      exa_vault();
public int         do_read(string arg);
public int         do_climb(string arg);
public int         do_drink(string arg);
public int         deposit_fail(string arg);
public void        init();
public void        enter_inv(object ob, object from);
public void        do_tutorial(object player);
public void        do_tutorial_sack(object player);

/* Global Variables */
public int         Tell_Alarm;
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


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    add_name("_aod_repository");

    set_short("the Repository of Skulls");
    set_em_long("This is the Repository of Skulls for the Army of"
      + " Darkness. Though carved from the very rock of the Blackwall"
      + " Mountains, this vast chamber is framed by walls which are"
      + " utterly black, and smooth as glass. Dwarfing all it surrounds,"
      + " a great rendering vat rises from the chamber floor where a"
      + " steep set of stone steps grants access to its gaping maw. A"
      + " large opening in the north wall looks out into the vault"
      + " of the repository, where the Darklings store their grim"
      + " harvest. The west wall appears to be dedicated entirely"
      + " to record keeping. Ogres cannot read, but the Darklings have"
      + " filled the area with a strange purple mist which somehow"
      + " helps people to <know> things here. Members of the Army may"
      + " <claim> a harvesting sack here.\n");

    add_item( ({ "repository", "repository of skulls", "here",
                 "area", "chamber", "room" }), long);
    add_item( ({ "rock", "wall", "walls", "black walls", "black wall",
                 "darkness", "dark" }),
        "The walls of this chamber actually appear to radiate darkness."
      + " Their smooth glassy surfaces are so black that the eye"
      + " becomes confused when gazing at them for any length of"
      + " time. An opening rests in the north wall, and the west wall"
      + " is dominated by many knows.\n");
    add_item( ({ "mountain", "mountains", "blackwall mountains" }),
        "Though this chamber has been hewn from the Blackwall Mountains,"
      + " they themselves are not visible here from within.\n");
    add_item( ({ "sky" }),
        "The sky is not visible from within this chamber.\n");
    add_item( ({ "up", "roof", "ceiling" }),
        "Though there is clearly a ceiling high above, the blackness"
      + " and glassy surface of the rock makes it difficult to judge"
      + " the height.\n");
    add_item( ({ "floor", "ground", "down", "dirt", "dust" }),
        "The floor is much like the walls, glassy and black. Only the"
      + " dirt and dust that has been tracked in gives any indication"
      + " of dimension.\n");
    add_item( ({ "vat", "renderer", "rendering vat", "great vat",
                 "great rendering vat", "vase", "metal vase" }),
        "The rendering vat of the repository is somewhat awe-inspiring."
      + " Shaped like a great metal vase, its more than fifty-foot"
      + " bulk yawns open at the top, allowing members of the Army"
      + " to pour the contents of their harvesting sacks into its"
      + " large rounded hollow. The vat tapers dramatically at its"
      + " bottom, narrowing to a thin tube which is poised directly"
      + " above a large stone bowl which rests on a pedestal. The entire"
      + " structure is supported by a framework of thick iron bars.\n");
    add_item( ({ "top of the vat", "maw", "great maw", "vat opening",
                 "lip", "lip of the vat", "gaping maw" }),
        "The opening at the top of the rendering vat has a wide lip"
      + " which extends out to catch skulls as they are poured from"
      + " harvesting sacks.\n");
    add_item( ({ "hollow", "rounded hollow", "large hollow",
                 "large rounded hollow" }),
        "The vat is quite wide at its mid-section. This is perhaps"
      + " where the rendering takes place. It is hard to know exactly"
      + " what goes on in that thing, but it is certainly foul-"
      + "smelling!\n");
    add_item( ({ "bottom of the vat", "tube", "thin tube" }),
        "The bottom of the vat has been designed to spew out the essence"
      + " of the rendered brain material from harvested skulls into a"
      + " bowl which rests beneath it.\n");
    add_item( ({ "bowl", "stone bowl", "large bowl",
                 "large stone bowl" }),
        "The stone which comprises the large bowl which rests beneath"
      + " the rendering vat has been stained a dark and unsavory hue."
      + " It is into this bowl that the mind essence which has been"
      + " rendered from harvested skulls is released for the"
      + " responsible ogre to drink.\n");
    add_item( ({ "pedestal" }),
        "The pedestal houses a large stone bowl, and keeps it in"
      + " the proper position beneath the rendering vat.\n");
    add_item( ({ "steps", "stair", "stairs", "step", "stone step",
                 "stone steps", "stone stair", "stone stairs",
                 "stone stairway" }),
        "Stone steps rise beside the rendering vat to allow a member"
      + " of the Army to climb up to the opening at the top and pour"
      + " in the contents of their harvesting sack.\n");
    add_item( ({ "framework", "iron", "thick iron", "bar", "bars",
                 "iron bar", "iron bars", "thick iron bar",
                 "thick iron bars", "thick bar", "thick bars",
                 "framework of thick iron bars" }),
        "The iron bars are extremely thick, which is almost certainly"
      + " necessary to prevent the rendering vat from tipping one way"
      + " or the other as it shudders and shakes in the rendering"
      + " process.\n");
    add_item( ({ "north wall", "north", "opening", "large opening",
                 "opening in the north wall",
                 "large opening in the north wall",
                 "northern wall", "vault",
                 "vault of the repository",
                 "repository vault", "harvest",
                 "grim harvest" }), exa_vault);
    add_item( ({ "know", "knows", "scores of knows", "records",
                 "record", "record keeping" }), List_Options);
    add_item( ({ "archway", "high archway", "south", "southern wall",
                 "south wall", "block", "blocks", "stone block",
                 "great stone block", "great stone blocks", "arch" }),
        "The archway is framed by great grey stone blocks which were"
      + " almost certainly hewn from the very rock of the mountains.\n");
    add_item( ({ "outside", "outdoors" }),
        "The outside is not clearly visible from here. You would need"
      + " to travel south.\n");
    add_item( ({ "board", "readerboard" }), exa_readerboard);
    add_item( ({ "mist", "magic", "purple", "purple mist",
                 "purple magic", "magic purple mist", "strange mist",
                 "strange purple mist" }),
        "It floats around the room helping even ogres to <know>"
      + " things here.\n");

    add_prop(ROOM_I_INSIDE, 1);

    setuid();
    seteuid(getuid());

    add_exit("courtyard", "south");
} /* create_emerald_room */


/*
 * Function name:        exa_readerboard
 * Description  :        allow players to look at the readerboard
 *                       using <exa>.
 * Returns      :        null string
 */
public string
exa_readerboard()
{
    if (this_player()->query_wiz_level())
    {
        return "Normally, we would have the player <know readerboard>"
          + " here using command(). Since you are a wizard, that won't"
          + " work, so you'll just have to type it yourself.\n";
    }

    this_player()->command("$know readerboard");
    return "";
} /* exa_readerboard */


/*
 * Function name:        exa_vault
 * Description  :        give the player a description of how full the
 *                       vault is
 * Returns      :        string - the description
 */
public string
exa_vault()
{
    string  desc = "";
    string  spread = "spread";

    switch (AOD_MASTER->query_guild_total())
    {
        case 0..100:
            desc = "A few unimpressive piles of skulls ";
            break;
        case 101..1000:
            desc = "A number of large heaps of skulls ";
            break;
        case 1001..10000:
            desc = "Many impressive piles of skulls ";
            break;
        case 10001..100000:
            desc = "Vast mounds of skulls ";
            break;
        case 100001..1000000:
            desc = "Towering mountains of skulls ";
            break;
        case 1000001..10000000:
            desc = "A vast sea of skulls ";
            spread = "spreads";
            break;
        default:
            desc = "A staggering ocean of innumerable skulls ";
            spread = "spreads";
            break;
    }

    return "You peer through the opening in the north wall into the"
      + " great cavernous vault of the Army of Darkness. " + desc
      + spread + " out beneath your eyes, extending into the dark"
      + " recesses of the mountain, almost beyond sight.\n";
} /* exa_vault */


/*
 * Function name:        do_read
 * Description  :        Called when players try to read the sign
 *                       which explains how to read the stat knows.
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_read(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[at] [the] [large] [west] [western] 'wall' / 'sign' / 'know'"
      + " / 'knows' / 'records'"))
    {
        return 0;
    }

    write(List_Options);

    return 1;
} /* do_read */


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
                        "goblins", "others", "miscellaneous" });
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

        write("\t" + sprintf("%36s  ", "Hours logged since last election:")
          + CONVTIME(AOD_MASTER->membership_duration(
            this_player()->query_real_name())) + "\n");
        write("\t" + sprintf("%36s  ", "Heads ripped since last election:")
          + sprintf("%,d",
            AOD_MASTER->query_skull_total(this_player(), 0)
          - AOD_MASTER->get_info(this_player(), "Election_Total"))
          + " Skulls\n");
        write("\t" + sprintf("%36s  ", "Skulls Per Hour:") + sprintf("%,d",
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
            case "others":
            case "miscellaneous":
            {
                races[0] = "other";
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


/*
 * Function name:        do_climb
 * Description  :        allow a player to try to climb the steps,
 *                       but force them to use <deposit> instead
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 0 - failure
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [stone] 'step' / 'steps' / 'stair' / 'stairs'"
      + " / 'stairway'"))
    {
        return 0;
    }

    notify_fail("There is no need to climb the stairs unless you"
      + " wish to <deposit> skulls.\n");
    return 0;
} /* do_climb */      


/*
 * Function name:        do_drink
 * Description  :        allow players to try to drink from the
 *                       bowl, but we don't actually let them do it
 *                       this way.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 0 - failure
 */
public int
do_drink(string arg)
{
    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[from] [the] [large] [stone] 'bowl'"))
    {
        return 0;
    }

    notify_fail("The stone bowl is currently empty. To consume"
      + " mind essence, you will need to deposit skulls into the"
      + " rendering vat.\n");
    return 0;
} /* do_drink */


/*
 * Function name:        deposit_fail
 * Description  :        We'll let people try to deposit things, but
 *                       it'll fail. The collecting sack will do the
 *                       real deal if they are a guild member, and
 *                       if they have it.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 0 - always fail
 */
public int
deposit_fail(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you want to deposit?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] 'head' / 'heads' / 'skull' / 'skulls' [in] [into] [the]"
      + " [repository] [vat]"))
    {
        notify_fail("You can't deposit that!\n");
        return 0;
    }

    notify_fail("Either you aren't in the Army or you've managed to"
      + " misplace your harvesting sack. If you need a new sack, you"
      + " can <request sack> here to get a new one.\n");
    return 0;
} /* deposit_fail */


/*
 * Function name:        request_sack
 * Description  :        Allow players to request a new harvesting sack
 *                       if they should happen to have lost theirs.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
request_sack(string arg)
{
    object  sack;

    if (!strlen(arg))
    {
        notify_fail("Claim what, a harvesting sack?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[a] [new] [harvesting] 'sack'"))
    {
        notify_fail("What? You may <claim sack> if you need a"
          + " harvesting sack.\n");
        return 0;
    }

    if (!IS_OGRE(this_player()))
    {
        notify_fail("Only members of the Army of Darkness may claim"
          + " a harvesting sack! Go join if you want one!\n");
        return 0;
    }

    if (present("_aod_guild_sack", this_player()))
    {
        notify_fail("You already have a sack! No need to carry two.\n");
        return 0;
    }

    setuid();
    seteuid(getuid());
    
    if (AOD_OGG_MASTER->get_info(this_player(), "Tutorial") ==
        "tutorial1")
    {
        write("Your Ogre brain is confused. You aren't even sure how"
          + " you got here, let alone how to request something. Maybe"
          + " you'd better wait for some instructions first.\n");
        return 1;
    }

    if (sack = clone_object(AOD_EMBLEM))
    {    
        sack->move(this_player(), 1);
        this_player()->catch_tell("You receive a blood-soaked sack,"
          + " which you sling effortlessly over your massive shoulder.\n");

        if (AOD_OGG_MASTER->get_info(this_player(), "Tutorial") ==
            "tutorial2")
        {
            set_alarm(3.0, 0.0, &do_tutorial_sack(this_player()));
            AOD_OGG_MASTER->set_info(this_player(), "Tutorial",
                "tutorial3");
        }

        return 1;
    }

    notify_fail("There was some error. Please notify Gorboth.\n");
    return 0; /* should never happen */
} /* request_sack */


public int
circle_tell(string str)
{
    if (!strlen(str))
    {
        notify_fail("Usage: circle <str>.\n");
        return 0;
    }

    if (str == "test")
    {
        AOD_MASTER->tell_ogres(
          "**************************************************"
        + " The time has come! Officer positions have been newly"
        + " assigned! Gorbothjr is the Headhunter General with"
        + " Gorbjr as the Black Corporal! Behold, the glory of the"
        + " Harvest!"
        + " **************************************************",
            1);
    }

    DARKLING_TELL(str);
    return 1;
}


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(request_sack, "claim");
    add_action(deposit_fail, "deposit");
    add_action(do_read, "read");
    add_action(do_read, "exa");
    add_action(do_read, "look");
    add_action(do_know, "know");
    add_action(do_drink, "drink");
    add_action(do_climb, "climb");
    add_action(circle_tell, "circle");
} /* init */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * We want to redefine this function for Ogres who are progressing
 * through the AoD tutorial process.
 */
public void
enter_inv(object ob, object from)
{
    if (IS_OGRE(ob))
    {
        if (AOD_OGG_MASTER->get_info(ob, "Tutorial") == "tutorial1")
        {
            if (!Tell_Alarm || !sizeof(get_alarm(Tell_Alarm)))
            {
                Tell_Alarm = set_alarm(3.0, 0.0, &do_tutorial(ob));
            }
        }
    }

    ::enter_inv(ob, from);
} /* enter_inv */


/*
 * Function name:        do_tutorial
 * Description  :        a part of the tutorial for new ogres. This
 *                       function is part of a delay call for a darkling
 *                       message
 * Arguments    :        object player - the player in question
 */
public void
do_tutorial(object player)
{
    /* better check to make sure they didn't grab a sack while the
     * alarm was waiting to execute this function.
     */
    if (AOD_OGG_MASTER->get_info(player, "Tutorial") == "tutorial1")
    {
        AOD_OGG_MASTER->set_info(player, "Tutorial", "tutorial2");

        set_this_player(player);           
        DARKLING_TELL(read_file(AOD_DIR + "tutorial2.txt", 0));
    }
} /* do_tutorial */


/*
 * Function name:        do_tutorial_sack
 * Description  :        a part of the tutorial for new ogres. This
 *                       function is part of a delay call for a darkling
 *                       message
 * Arguments    :        object player - the player in question
 */
public void
do_tutorial_sack(object player)
{
    set_this_player(player);           
    DARKLING_TELL(read_file(AOD_DIR + "tutorial3.txt", 0));
} /* do_tutorial_sack */