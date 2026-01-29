/*
 *  /d/Sparkle/area/tutorial/obj/journal.c
 *
 *  This is the journal that newbies receive that keeps track of
 *  the tutorial chapters they have read, and allows them to
 *  access them at any time. It is an autoloading object.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 *
 *  Teleportation functions copied from the newbie pin originally coded
 *  by Lucius, and modified by Tapakah and Altrus.
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"

inherit "/std/object";
inherit LIB_DIR + "quest_reward";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>


/* Prototypes */
public void        create_object();
public void        tutorial_init(object who);
public int         do_read(string arg);
public int         do_list(string arg);
public void        print_chapter();
public void        count_unread(object player);
public int         do_reward();
public string      query_auto_load();
public void        do_recall(object who, string where, object last);
public int         f_home(string str);
public void        do_destroy(string arg);
private int        in_tutorial();
public string      journal_description();

/* Global Variables */
public int         Journal_Size = sizeof(CHAPTER_TITLES);
public int         Column1_Size = (Journal_Size / 2);
public int         Chapter_Number = 1;
public int         Column2 = (Column1_Size + Chapter_Number) -1;
public int         Unread_Counter = 0;
static private int Home_Alarm;


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("journal");
    add_name( ({ "_tutorial_journal", "book", }) );
    add_adj( ({ "tutorial" }) );

    set_short("tutorial journal");
    set_long("@@journal_description@@");

    add_prop(OBJ_I_WEIGHT, 5); /* do not burden newbies with it */
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_M_NO_DROP, "The journal is too important to drop.\n");
    add_prop(OBJ_M_NO_GIVE, "The journal is too important to give"
               + " away.\n");
    add_prop(OBJ_M_NO_SELL, "The journal has no value.\n");
    add_prop(TUTORIAL_ITEM_PROP, 1);

    setuid();
    seteuid(getuid());

    set_alarm(15.0, 0.0, "tutorial_init");
} /* create_object */


/*
 * Function name:        tutorial_init
 * Description  :        inform the player that they have had the first
 *                       few chapters of the tutorial written into their
 *                       journal for them.
 * Arguments    :        object who - the player
 */
public void
tutorial_init(object who)
{
    object who = environment(this_object());

    if (!TUTORIAL_MASTER->query_tutorial(who->query_real_name(), 1))
    {
        TUTORIAL_MASTER->set_tutorial(who->query_real_name(), 1);
        TUTORIAL_MASTER->set_tutorial(who->query_real_name(), 2);
        TUTORIAL_MASTER->set_tutorial(who->query_real_name(), 3);
        TUTORIAL_MASTER->set_tutorial(who->query_real_name(), 4);
        TUTORIAL_MASTER->set_tutorial(who->query_real_name(), 5);
        TUTORIAL_MASTER->set_tutorial(who->query_real_name(), 6);
        TUTORIAL_MASTER->set_tutorial(who->query_real_name(), 7);

        who->catch_tell("\nYour tutorial vibrates suddenly, and"
          + " you notice that a few entries have been added to it. You can"
          + " <exa journal> begin learning about the game.\n");
    }
} /* tutorial_init */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(f_home, "home");
    add_action(do_read, "read");
    add_action(do_list, "list");
    add_action(do_reward, "reward");
    add_action(do_destroy, "destroy");
} /* init */

/*
 * Function name:        in_tutorial
 * Description  :        Checks the room map property to see whether
 *                       the player is in the tutorial or not. This
 *                       is needed since the journal can exist outside
 *                       the tutorial, and we don't want to give the
 *                       "home" ability outside of the tutorial.
 * Arguments    :        none
 * Returns      :        0/1 - not in tutorial/in tutorial
 */
private int
in_tutorial()
{
    if (environment(this_player())->query_prop("_room_i_tutorial"))
    {
        return 1;
    }
    
    return 0;
} /* in_tutorial */

/*
 * Function name:        journal_description
 * Description  :        Returns the long description of the journal. The
 *                       reason it is being used like this is to remove
 *                       the <home> line when outside the tutorial
 * Arguments    :        none
 * Returns      :        long description
 */
public string
journal_description()
{
    string long_description;
    
    long_description =
       "You open the Tutorial Journal, and read the following:\n\n"
     + "\t<list chapters>    - show a list of chapters that can be read.\n"
     + "\t<read #>           - read a specific chapter.\n";

    if (in_tutorial())
    {
        long_description +=
            "\t<home>             - teleport to your starting place.\n";
    }
    
    long_description +=        
        "\t<read explanation> - a note for experienced Genesis players.\n"
      + "\t<destroy journal>  - do just that (not recommended!)\n";
      
    if (in_tutorial())
    {
        long_description +=
        "\nIf you have copied down all of the chapters, you can type"
      + " <reward> and Lars will give you a reward.\n";
    }
    
    return long_description;    
} /* journal_description */

/*
 * Function name:        do_read
 * Description  :        allow the player to read chapters that they
 *                       have copied into the book.
 * Arguments    :        string arg - what the player typed 
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_read(string arg)
{
    string   page;
    int      number;

    if (!strlen(arg))
    {
        notify_fail("What do you wish to read?\n");
        return 0;
    }

    if (!this_player()->can_see_in_room())
    {
        notify_fail("It is too dark here to read anything!\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[the] [tutorial] 'journal'"))
    {
        write(long());
        return 1;
    }

    if (!parse_command(arg, ({}),
        "[chapter] %d", number))
    {
        if (parse_command(arg, ({}),
            "[chapter] '#'"))
        {
            write("For # use the number of the chapter. For example:"
              + " <read 2> or <read chapter 2>.\n");
            return 1;
        }

        if (arg == "explanation")
        {
            this_player()->more(read_file(TEXT_DIR + "explanation", 0));
            return 1;
        }

        return 0; /* bad syntax */
    }

    if (number > (Journal_Size - 1))
    {
        notify_fail("There is no such chapter.\n");
        return 0;
    }

    if (in_tutorial()
        && !TUTORIAL_MASTER->query_tutorial(
            this_player()->query_real_name(), number))
    {
        notify_fail("You have not copied that chapter into your journal"
          + " yet. Once you find the sign upon which it is written, you"
          + " will be able to read it from this book.\n");
        return 0;
    }

    page = TEXT_DIR + "chapter_" + number;
    this_player()->more(read_file(page, 0));

    return 1;
} /* do_read */


/*
 * Function name:        do_list
 * Description  :        print a list of the chapters that they player
 *                       has copied into the journal
 * Arguments    :        string arg - what the player typed 
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_list(string arg)
{
    if (!strlen(arg) || arg != "chapters" && arg != "chapter")
    {
        notify_fail("List what? <list chapters> perhaps?\n");
        return 0;
    }

    while (Chapter_Number <= Column1_Size)
    {
        print_chapter();
        Chapter_Number++;
    }

    if (in_tutorial())
    {
        if (Unread_Counter == 0)
        {
            write("\nYou have copied down all of the Tutorial "
                + "Chapters.\n");
        }
        else if (Unread_Counter == 1)
        {
            write("\nYou only have one Tutorial Chapter left to find.\n");
        }
        else
        {
            write("\nYou still have " + Unread_Counter 
                + " Tutorial Chapters left to find.\n");
        }
    }
    
    write("You can <read #> to read a specific chapter.\n");

    Chapter_Number = 1; /* reinitialize the variables */
    Unread_Counter = 0;

    return 1;
} /* do_list */


/*
 * Function name:        print_chapter
 * Description  :        print a specific line of the list
 */
public void
print_chapter()
{
    string   title = CHAPTER_TITLES[Chapter_Number];
    string   title2 = "";
    string   num2 = "";
    string   format = "%3s %-36s %3s %-36s\n";

    if (in_tutorial()
        && !TUTORIAL_MASTER->query_tutorial(
            this_player()->query_real_name(), Chapter_Number))
    {

        title = "------------------------------------";
        Unread_Counter++;
    }

    if (Chapter_Number + Column2 < Journal_Size)
    {
        title2 = CHAPTER_TITLES[Chapter_Number + Column2];
        num2 = Chapter_Number + Column2 + ":";

        if (in_tutorial()
            && !TUTORIAL_MASTER->query_tutorial(
               this_player()->query_real_name(), Chapter_Number + Column2))
        {
            title2 = "----------------------------------";
            Unread_Counter++;
        }
    }

    write(sprintf(format,
                  Chapter_Number + ":",
                  title,
                  num2,
                  title2));
    return;
} /* print_chapter */


/*
 * Function name:        count_unread
 * Description  :        determinte the number of unread chapters
 */
public void
count_unread(object player)
{
    if (!TUTORIAL_MASTER->query_tutorial(
        player->query_real_name(), Chapter_Number))
    {
        Unread_Counter++;
    }

    Chapter_Number++;
} /* count_unread */


/*
 * Function name:        do_reward
 * Description  :        reward the player if they have read all of
 *                       the chapters
 * Returns      :        1 - success, 0 - failure
 */
public int
do_reward()
{
    if (!in_tutorial())
    {
        return 0;
    }
    
    while (Chapter_Number < Journal_Size)
    {
        count_unread(this_player());
    }

    if (Unread_Counter)
    {
        if (Unread_Counter == 1)
        {
            write("\nYou still have one Tutorial Chapter left to"
              + " find.\n");
        }
        else
        {
            write("\nYou still have " + Unread_Counter + " Tutorial"
              + " Chapters left to find.\n");
        }

        return 1;
    }

    write("Lars appears through a rift in the fabric of space.\n");
    write("Lars smiles at you.\n");
    write("Lars says: It looks like you've found every chapter.\n");
    write("Lars says: I'd say that's worth a little something.\n");

    give_reward(this_player(), TUTORIAL_JOURNAL_GROUP,
        TUTORIAL_JOURNAL_BIT, TUTORIAL_JOURNAL_EXP,
        "Tutorial Journal"); 

    write("Lars winks at you and disappears.\n");

    Chapter_Number = 1; /* reinitialize the variables */
    Unread_Counter = 0;

    return 1;
} /* do_reward */


/*
 * Function name:        query_auto_load
 * Description  :        players may keep this item over multiple
 *                       logins
 * Returns      :        string - the filename of this module.
 */
public string
query_auto_load()
{
    return MASTER + ":";
} /* query_auto_load */


/*
 * Function name:        do_recall
 * Description  :        Copied from the original newbie pin (see below)
 * Arguments    :        object who - the player being teleported home
 *                       string where - the location to teleport to
 *                       object last - room in which command was typed
 *
 * This is stage 2 of recall. It does the actual movement
 * and drains the players fatigue. All successful recalls
 * are also logged.
 */
private void
do_recall(object who, string where, object last)
{
    Home_Alarm = 0;

    if (!objectp(who))
        return;

    if (last != environment(who))
    {
        this_player()->catch_tell("Your movement has caused the magicks"
          + " to cease and you fail to be returned home.\n");
        return;
    }

    this_player()->move_living("shimmering then fading away",
        where, 1, 0);
    this_player()->add_fatigue(-(this_player()->query_max_fatigue()));

    this_player()->catch_tell("\nThe magicks leave you feeling extremely"
      + " fatigued. It would be a good idea to find something to eat"
      + " and drink when you've recovered some.\n\n");
} /* do_recall */


/*
 * Function name:        f_home
 * Description  :        copied from the original newbie pin (see below)
 * Arguments    :        string str - what was typed after the verb
 * Returns      :        1 - success, 0 - otherwise.
 *
 * Recall:  Send a newbie to their start position.
 *          This ability will wipe their fatigue as it
 *          should be used only when hopelessly lost and
 *          they can't get help via other means.
 */
public int
f_home(string str)
{
    if (this_player()->query_wiz_level())
    {
        return 0;  /* don't want to override the wiz command */
    }

    if (!in_tutorial())
    {
        // don't allow use of the home command outside the tutorial
        return 0;
    }
    
    if (strlen(str))
    {
        notify_fail("Simply typing <home> will do.\n");
        return 0;
    }

    if (Home_Alarm)
    {
        write("You are already preparing to go home.\n");
        return 1;
    }

    str = this_player()->query_default_start_location();
    if (str == file_name(environment(this_player())))
    {
        write("You are already at your starting location!\n");
        return 1;
    }

    write("You feel yourself beginning to fade ... remember to "+
        "hold still or the magick will go awry.\n");

    Home_Alarm = set_alarm(5.0, 0.0, &do_recall(this_player(),
        str, environment(this_player())));
    return 1;
} /* f_home */


/*
 * Function name:        do_destroy
 * Description  :        allow players to destroy this journal if it
 *                       is (for some inappropriate reason) lingering
 *                       in their inventory.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 -- success, 0 -- failure
 */
public int
do_destroy(string arg)
{
    if (!strlen(arg) ||
        !parse_command(arg, ({}),
        "[the] [tutorial] 'journal'"))
    {
        notify_fail("What do you wish to destroy?\n");
        return 0;
    }

    write("Very well! You rip your tutorial journal to shreds. It shall"
      + " pester you no more!\n");
    this_object()->remove_object();
    return 1;
} /* do_destroy */
