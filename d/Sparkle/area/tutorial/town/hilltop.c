/*
 *  /d/Sparkle/area/tutorial/town/hilltop.c
 *
 *  This is the startlocation for all new players in Genesis. It is also
 *  the point to which players can transport themselves using the
 *  Newbie Necklace if they get lost or trapped.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include <state_desc.h>
#include "../defs.h"
#include "/d/Genesis/start/newbie/newbie.h"
#include <macros.h>
#include <stdproperties.h> 

inherit SD_ROOM;
inherit LIB_DIR + "random_noise";

/* definitions */
#define  TUTORIAL_CHAPTER    9  /* the chapter for the sign */
#define  NOTIFY_PROP         "_tutorial_i_notify_skip"

/* prototypes */
public void        create_silverdell();
public void        give_journal(object who);
public void        init();
public int         random_noise();
public void        hint(string arg);
public void        reset_room();
public int         start(string arg);
public string      which_room();
public int         enter_portal(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("a green hilltop near the town of Greenhollow");
    set_long("These are the lands of Silverdell. You are standing on a"
      + " beautiful green hilltop. Cold air blows across your face as you"
      + " stand gazing at the expansive"
      + " view to the north. A sense of excitement rises in your blood,"
      + " and you get the feeling that many adventures are in store"
      + " for you in this strange new land. Your eyes trace a dirt"
      + " road which begins directly at your feet, runs a ways"
      + " down to the base of the hill, and then travels north toward"
      + " a small town that is visible in the distance. Right beside"
      + " the road stands a shimmering blue portal. If you haven't"
      + " already done so, you might wish to read the sign here.\n\n");

    add_item( ({ "portal", "shimmering portal", "blue sportal", "shimmering blue portal" }),
      "This portal will take you on a short adventure through a series of"
    + " rooms meant to introduce you to the basic commands used to navigate this"
    + " world. To get started simply <enter portal>.\n");
    add_item( ({ "air", "clean air", "breeze", "wind", "steady wind" }),
        "A steady wind blows across this hilltop. There is a crisp"
      + " freshness to the air that envigorates you.\n");
    add_item( ({ "east-west road", "east west road", "east road",
                 "west road", "long road", "long east-west road" }),
        "North of the town, a more substantial looking road travels"
      + " a great distance to both the east and west.\n");
    add_item( ({ "base", "base of the hill", "lowland", "lowlands" }),
        "Lowlands spread out from the base of the hill, extending far"
      + " beyond the town toward a forest to the northeast.\n");
    add_item( ({ "hill", "hilltop", "beautiful hill", "beautiful hilltop",
                 "green hill", "green hilltop", "beautiful green hill",
                 "beautiful green hilltop", "top" }),
        "The height of the hill gives it a commanding view of the"
      + " landscape to the north. Beautiful green grass is thick to"
      + " both sides of a road which runs down the north side of the"
      + " hill.\n");
    add_item( ({ "view", "commanding view", "expansive view",
                 "landscape", "view of the landscape" }),
        "You peer around, surveying the landscape as it spreads out"
      + " before your eyes to the north. Just below this hill, the"
      + " road travels toward and through a small town before joining"
      + " a long east-west road which travels into a forest to the"
      + " northeast, and toward some mountain peaks to the northwest.\n");
    add_item( ({ "forest", "trees", "tree", "dense trees" }),
        "To the northeast, the dense trees of a forest are visible"
      + " in the distance. You sense danger lurking in those trees.\n");
    add_item( ({ "mountain", "mountains", "mountain peaks", "peak",
                 "peaks", "mountain peak" }),
        "To the northwest, dark and forbidding mountains loom above"
      + " the town. You get a feeling that great danger awaits you"
      + " in those mountains.\n");
    add_item( ({ "town", "village", "greenhollow", "town of greenhollow",
                 "houses", "buildings", "house", "building", "small town"}),
        "The town of Greenhollow lies nestled in the lowlands beneath"
      + " this hilltop. You sense a peace and calm within the houses"
      + " and other buildings, as if no amount of outside evil could"
      + " ever penetrate those gentle streets.\n");
    add_item( ({ "street", "streets", "gentle street",
                 "gentle streets", "townsfolk", "people" }),
        "Even from this distance, you glimpse the carefree townsfolk"
      + " of Greenhollow moving along the streets of the town.\n");
    add_item( ({ "road", "path", "dirt road", "dirt path", "hillside",
                 "northern slope", "north side of the hill",
                 "north side", "pathway" }),
        "A road runs down the north side of the hill, heading directly"
      + " to a very cozy looking town.\n");
    add_item( ({ "grass", "grasses", "green grass" }),
        "The grass which grows all along this hill is vivid green and"
      + " thick. The blades dance with the breeze.\n");
    add_outdoor_items();
    add_road_items();

    prevent_attacks();
    reset_room();

    add_exit(which_room, "north");
} /* create_silverdell */


/*
 * Function name:        give_journal
 * Description  :        give the player a tutorial journal
 * Arguments    :        object who - the player to get it
 */
public void
give_journal(object who)
{
    if (who->query_wiz_level())
    {
        return; /* lets not bother wizards with this thing */
    }

    if (present("_tutorial_journal", who))
    {
        return; /* sanity check */
    }

    setuid();
    seteuid(getuid());
    clone_object(OBJ_DIR + "journal")->move(who, 1);
    who->catch_tell("\nYou suddenly notice that your tutorial journal"
      + " has been returned to you.\n\n");
} /* give_journal */

/*
 * Function name:        give_newbie_pin
 * Description  :        give the player a newbie pin
 * Arguments    :        object who - the player to get it
 */
public void
give_newbie_pin(object who)
{
    if (who->query_wiz_level())
    {
        return; /* lets not bother wizards with this thing */
    }

    if (!SD_IS_NEWBIE(who))
    {
        // Only give the pin to newbies.
        return;
    }
    
    if(present(PIN_UNIQUE_ID, who))
    {
        return; /* sanity check */
    }

    setuid();
    seteuid(getuid());
    clone_object(NEWBIE_PIN)->move(who, 1);
} /* give_journal */

/*
 * Function name:        notify_skip
 * Description  :        give the player information about how to skip
 *                       the tutorial
 * Arguments    :        object player - this_player()
 */
public void
notify_skip(object player)
{
    player->catch_tell("\n\n"
      + "If you wish to skip the tutorial, you may <read explanation>"
      + " in your tutorial journal for information on how to do so.\n\n"
      + "Also, remember! Use <ntell> to get help from other players. For"
      + " example, you could type <ntell I'm new, and lost! Help"
      + " please?>\n\n");
    player->catch_tell("A few useful commands to get you started:\n\n" +
    " <look> or <l>          - To look around.\n" + 
    " <examine> or <exa>     - Examine an item. Try: <exa me>\n" + 
    " <say Hello>            - Speak to someone.\n" + 
    " <introduce me>         - Introduce yourself to someone.\n" + 
    " <n>, <s>, <e>, <w>     - Go north, south, east or west.\n\n" +
    " More information on how to play can be found here:\n" +
    " http://www.genesismud.org/guide.html\n\n");

    return;
} /* notify_skip */


/*
 * Function name:        init
 * Description  :        set up the room noises
 */
public void
init()
{
    int     how_full = this_player()->query_stuffed(),
            how_fat = this_player()->eat_max(),
            feast_size = how_fat - how_full,
            i;

    ::init();
    init_random_noise();

    if (!present("_tutorial_journal", this_player()))
    {
        set_alarm(0.5, 0.0, &give_journal(this_player()));
    }

    if(!present(PIN_UNIQUE_ID, this_player()))
    {
        set_alarm(0.5, 0.0, &give_newbie_pin(this_player()));
    }

    if (!this_player()->query_prop(NOTIFY_PROP))
    {
        set_alarm(1.0, 0.0, &notify_skip(this_player()));
        this_player()->add_prop(NOTIFY_PROP, 1);
    }

    if (!this_player()->query_default_start_location())
    {
        if (this_player()->set_default_start_location(
            file_name(this_object())))
        {
            write("You will start here from now on.\n");
        }
        else
        {
            write("For some reason, you were unable to start here. Please"
              + " make a bug report.\n");
        }
    }

    /* Fill 'em up!
     * There appears to be a maximum limit on eat_food() set to approximately
     * this_player()->eat_max() / 5. So ... we'll do this in 5 chunks of
     * just that portion, with the last a bit smaller.
     *
     * We do this so players new to the game do not suffer hunger as
     * soon as they might otherwise.
     */
    for (i = 0; i < 5; i++)
    {
        if (i > 4)
        {
            this_player()->eat_food(feast_size - 5);
        }
        else
        {
            this_player()->eat_food(how_fat / 5);
        }
    }

    add_action(hint, "hint");
    add_action(start, "start");
	add_action(enter_portal, "enter");
} /* init */


/*
 * Function name: random_noise
 * Description  : add blowing breeze to the room
 * Returns      : int -- non-zero if noises should continue,
 *                 zero if they should stop
 */
public int
random_noise()
{
    tell_room(this_object(), ({
        "A cool, refreshing breeze blows against your cheeks.\n",
        "Wind tugs gently against your clothing.\n",
        "The light whistle of the wind picks up suddenly.\n",
        "A few birds fly overhead, twisting in the wind.\n",
        })[random(3)] );
    return 1;
} /* random_noise */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("Need a hint? No problem ... you can either go <n>orth and"
     + " travel to the town of Greenhollow and start exploring,"
     + " or you can <enter portal> to go through a small introduction"
     + " adventure that teaches you the basics on how to play the game.\n");

    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
	
	object  portal;
	
    if (!present("_pre_tutorial_portal"))
    {
        portal = clone_object("/std/object");
        portal->set_short("shimmering blue portal");
        portal->set_name("_pre_tutorial_portal");
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
 * Function name:        start
 * Description  :        allow players to try to set this as
 *                       their start location.
 * Arguments    :        string arg - what the player typed after
 *                                    "start"
 * Returns      :        1 - success, 0 - failure
 */
public int
start(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("You must type <start here> to start here.\n");
        return 0;
    }

    if (arg != "here")
    {
        notify_fail("What? Do you wish to <start here> ?\n");
        return 0; /* bad syntax */
    }

    if (this_player()->set_default_start_location(
        file_name(this_object())))
    {
        write_file(LOG_DIR + "start", this_player()->query_name()
          + " chose the hilltop startloc on "
          + ctime(time()) + ".\n");
        write("You will start here from now on.\n");
    }
    else
    {
        write("For some reason, you were unable to start here. Please"
          + " make a bug report.\n");
    }

    return 1;
} /* start */

/* Function name:        enter_portal
 * Description  :        allow players to enter the portal and get to the tutorial
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
enter_portal(string arg)
{
    if (arg == "portal")
    {
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " enters the shimmering blue portal!\n", this_player());
        write("You step through the portal, and feel yourself magically"
          + " transported.\n\n");

        this_player()->move_living("M", TUTORIAL_DIR + "pre_creation_new/0", 1);

        tell_room(environment(this_player()), QCTNAME(this_player())
          + " appears through the shimmering blue portal!\n", this_player());

        return 1;	
    }
	else
	{
        write("Do you wish to <enter portal>?\n");
        return 1;
    }
} /* enter_portal */


/*
 * Function name:        which_room
 * Description  :        define which room the exit leads to
 * Returns      :        string - the filename
 */

public string
which_room()
{
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return TOWN_DIR + "road_0_ash";
    }

    return TOWN_DIR + "road_0";
} /* which_room */
