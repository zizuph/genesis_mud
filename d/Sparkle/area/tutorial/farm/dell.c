/*
 *  /d/Sparkle/area/tutorial/farm/dell.c
 *
 *  This is the portal out of the Tutorial area. Players who enter the
 *  portal may never return to Silverdell.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <macros.h>        /* for QCTNAME       */
#include <money.h>         /* for MONEY_MAKE_SC */
#include <filter_funs.h>   /* for FILTER_DEAD   */
#include <stdproperties.h> /* for OBJ_*         */
#include "/d/Sparkle/area/tutorial/guild/guild.h"

/* global variables */
#define     TUTORIAL_CHAPTER        43   /* chapter for the sign */
#define     WARNING_PROP            "_tutorial_portal_warning"

/* prototypes */
public void        create_silverdell();
public string      describe(string arg);
public void        init();
public int         do_enter(string arg);
public void        wipe_inventory(object player);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("in a shallow dell");
    set_long(&describe("long"));

    add_outdoor_items();
    add_road_items();

    add_item( ({ "here", "area", "dell", "shallow dell",
                 "scorched dell" }), &describe("long"));
    add_item( ({ "plant", "plants", "foliage", "ash", "ground",
                 "land", "grass", "beautiful plants", "leaves",
                 "leaf" }),
        &describe("plants"));
    add_item( ({ "portal", "shimmering portal", "blue portal",
                 "shimmering blue portal" }),
        "If you wish to leave the Genesis Tutorial, you may <enter"
      + " portal> here. Know, however, that once you leave the"
      + " tutorial, you may never return. Only enter this portal"
      + " if you are certain that you do not wish to continue"
      + " adventuring in the tutorial area.\n");

    add_exit("crossroad_3", "southwest");

    setuid();
    seteuid(getuid());

    reset_room();
} /* create_silverdell */


/*
 * Function name:        describe
 * Description  :        provide a status dependant descriptions
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - various descriptions of things
 */
public string
describe(string arg)
{
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        switch(arg)
        {
            case "long":
                return "You have descended into a scorched dell. The"
                  + " land here has been ruined, and nothing seems to"
                  + " be growing at all. A shimmering blue portal rises"
                  + " from the center of the dell. An eerie glow from the"
                  + " portal casts an alien glow along the ground.\n\n";
                break;
            case "plants":
                return "The earth here has been burned somehow. No plants"
                  + " remain, yet there is a good deal of ash.\n";
                break;
        }
    }

    switch(arg)
    {
        case "long":
            return "You have descended into a peaceful green dell where"
              + " nature has seen fit to grow all manner of beautiful"
              + " plants. Rising from the center of the grass is a"
              + " shimmering blue portal which casts a strange light"
              + " on the leaves in the area.\n\n";
            break;
        case "plants":
            return "The plants here are many and varied. They are all"
              + " very lush and green.\n";
            break;
    }
} /* describe */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    object  portal;

    if (!present("_tutorial_portal"))
    {
        portal = clone_object("/std/object");
        portal->set_short("shimmering blue portal");
        portal->set_name("_tutorial_portal");
        portal->add_prop(OBJ_M_NO_GET, "Your hand passes through the"
          + " portal as you try.\n");
        portal->move(this_object());
    }

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_enter, "enter");
} /* init */


/*
 * Function name:        do_enter
 * Description  :        allow players to enter the portal
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    string warning_text = "As you approach the portal, a strange force"
                        + " stops you in your tracks.\n\n"
                        + "Lars arrives through a rift in space.\n"
                        + "Lars smiles at you.\n";
    string destination = "/d/Genesis/start/human/town/church";

    if (!strlen(arg))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [shimmering] [blue] 'portal'"))
    {
        if (arg != "the rest of the game")
        {
            return 0; /* can't parse the syntax */
        }

        if (this_player()->query_guild_member(GUILD_NAME))
        {
            write("You will first need to return to the Patrol Guild"
              + " and <guildleave> in their entry hall.\n");
            return 1;
        }

        write("Very well. You may <enter portal> to complete the"
          + " Tutorial.\nWe hope you enjoyed it!\n");
        this_player()->add_prop(WARNING_PROP, 1);
        return 1;

    }

    if (!TUTORIAL_MASTER->query_tutorial(
        this_player()->query_real_name(), TUTORIAL_CHAPTER))
    {
        write("First, you must read the Tutorial Sign here.\n");
        return 1;
    }

    if (!this_player()->query_prop(WARNING_PROP))
    {
        if (CHECK_TUTORIAL_BIT(SAVIOR_BIT) ||
            CHECK_TUTORIAL_BIT(DESTROYER_BIT))
        {
            warning_text += "Lars says: You have learned much in the"
              + " lands of Silverdell.\n";

            if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
            {
                warning_text += "Lars says: And I see that you have"
                  + " chosen to save the land from evil.\n"
                  + "Lars says: Genesis is always looking for heroes.\n"
                  + "Lars smiles appreciatively.\n\n";
            }
            else
            {
                warning_text += "Lars says: And I see that you have"
                  + " chosen to do great evil here.\n"
                  + "Lars nods solemnly.\n"
                  + "Lars says: A balance between good and evil is"
                  + " necessary in all things.\n"
                  + "Lars says: Most people don't choose to aid the"
                  + " Baron, as you did.\n"
                  + "Lars smiles with a dark twinkle in his eyes.\n\n";
            }

            warning_text += "Lars says: You seem ready to venture on to"
              + " greater things.\n"
              + "Lars says: Even so, choose carefully, because once you"
              + " enter this portal ...\n"
              + "Lars says: ... you will never return to Silverdell.\n"
              + "Lars says: Make your intentions clear by typing:\n"
              + "Lars says: <enter the rest of the game>\n"
              + "Lars leaves through a rift in space.\n";

            write(warning_text + "\n");
            return 1;
        }
        else
        {
            warning_text += "Lars says: There is still much to be done"
              + " in these lands.\n"
              + "Lars says: You have not yet completed the quest that"
              + " the Mayor requests.\n"
              + "Lars says: Once you enter this portal, you may"
              + " never return to Silverdell.\n"
              + "Lars says: There is a good deal of quest experience that"
              + " you would miss out on.\n"
              + "Lars says: To enter anyway, type the following:\n"
              + "Lars says: <enter the rest of the game>\n"
              + "Lars leaves through a rift in space.\n";

            write(warning_text + "\n");
            return 1;
        }

        write(warning_text + "\n");
    }

/* This is all commented out now. We are starting all races in the same
 * place until such time as the playerbase is deemed healthy enough for
 * separate start locations, AND the individual racial startlocations
 * are of high enough quality.
 *
 * Gorboth
    switch (this_player()->query_race())
    {
        case "elf":
            destination = "/d/Genesis/start/elf/room/begin";
            break;
        case "dwarf":
            destination = "/d/Genesis/start/dwarf/lvl1/temple";
            break;
        case "hobbit":
            destination = "/d/Genesis/start/hobbit/v/church";
            break;
        case "goblin":
            destination = "/d/Genesis/start/goblin/caverns/quarters";
            break;
        case "gnome":
        case "human":
        default:
            destination = "/d/Genesis/start/human/town/church";
            break;
    }
 */

    write("You step into the portal, and feel yourself magically"
      + " transfered to a new place!\n");
    tell_room(destination, QCTNAME(this_player()) + " appears"
      + " in a flash of blue light!\n", 0);
    this_player()->set_default_start_location(destination);
    this_player()->move_living("M", destination, 1, 0);
    wipe_inventory(this_player());
    write("You will start here from now on. The tutorial is over. Now"
      + " that you are beginning the actual game, you might want to"
      + " find a guild to join. Ask around to discover more.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " steps into"
      + " the portal and leaves the lands of Silverdell forever.\n");

	write_file(LOG_DIR + "leaving", this_player()->query_name()
       + " left Silverdell on "
       + ctime(time()) + ".\n");

    TUTORIAL_MASTER->remove_player(this_player()->query_real_name());
    TUTORIAL_MASTER->test_members(); /* use this opportunity to clean up
                                      * the save file a bit, too.
                                      */

    return 1;
} /* do_enter */


/*
 * Function name:        wipe_inventory
 * Description  :        We pretty much want the players to lose all of
 *                       the items from the tutorial when they leave,
 *                       since many of them are not balanced for the rest.
 *                       Also, give skill-training money to players who
 *                       chose to skip the tutorial.
 *                       of Genesis. Here, we wipe all but a few.
 * Arguments    :        object player - the player to wipe
 */
public void
wipe_inventory(object player)
{
    mixed  *target = FILTER_DEAD(all_inventory(player));
    object  coins;
    int     i, n, a = 0;

    for (i = 0, n = sizeof(target); i < n; i++)
    {
        if (target[i]->id("_tutorial_item"))
        {
            if (target[i]->num_heap())
            {
                write("You lose " + target[i]->short() + " in the"
                  + " transfer.\n");
            }
            else
            {
                write("You lose your " + target[i]->short() + " in the"
                  + " transfer.\n");
            }
            target[i]->remove_object();
        }
    }

    /* now, check to see if they have trained any skills. If they have
     * not, they are probably choosing to skip the tutorial entirely. In
     * this case, we'd better give them the amount of coins previously
     * given out when players created their characters.
     */

    for (i = 0, n = 110; i < n; i++)
    {
        if (player->query_skill(i) > 0)
        {
            a++;
        }
    }

    write("\n"); /* to make the text stand out a bit */

    if (!a)
    {
        write("Lars speaks in your mind: Hmmm ... looks like you didn't"
          + " have a chance to learn any skills while in the tutorial."
          + " Take these coins so that you may train them in the"
          + " future.\n\n");
        coins = MONEY_MAKE_SC(20);
        coins->move(player);
        write("You receive 20 silver coins.\n");
    }
} /* wipe_inventory */

