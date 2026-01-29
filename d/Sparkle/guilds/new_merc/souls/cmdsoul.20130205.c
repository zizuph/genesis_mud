/*
 *  /d/Sparkle/guilds/new_merc/cmdsoul.c 
 *
 *  The command soul for the Free Mercenary Guild of Sparkle.
 *
 *  Created December 2008, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

/* Definitions */
#define SOULDESC(x) (this_player()->add_prop("_live_s_soulextra", (x)))

/* We include the Krynn defs for the old Merc emotes that borrowed
 * heavily from Krynn code. Lame, but oh well.
 */
#include "/d/Krynn/common/defs.h"
#include "../merc_defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <time.h>
#include <wa_types.h>
#include "include_emotes.h"

/* Prototypes */
public int     adapt(string arg);


/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
} /* get_soul_id */


/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
public int 
query_cmd_soul() 
{ 
    return 1; 
} /* query_cmd_soul */

public mapping
query_ability_map()
{
    return ([
    "mattack" : SPECIALS_DIR + "mattack",
    "ma" : SPECIALS_DIR + "mattack",
    ]);
}

/*
 * Function name: query_cmdlist
 * Description:   Get the commands available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
public mapping
query_cmdlist()
{
    return ([
            /* Command name : Function name */
              "adapt"       : "adapt",
              "maffiliate"  : "maffiliate",
              "ma"          : "do_ability",
              "mattack"     : "do_ability",
              "merchelp"    : "merchelp",
              "mercpay"     : "mercpay",
              "mercs"       : "merc_who_list",
              "mincognito"  : "mincognito",
              "stop"        : "stop_training",


                       /* Emotes */
              "madvise"     : "madvise",
              "madv"        : "madvise",
              "mappraise"   : "mappraise",
              "mapp"        : "mappraise",
              "mbattle"     : "mbattle",
              "mbat"        : "mbattle",
              "mcheck"      : "mcheck",
              "mche"        : "mcheck",
              "mclean"      : "mclean",
              "mcle"        : "mclean",
              "mdestiny"    : "mdestiny",
              "mdes"        : "mdestiny",
              "mface"       : "mface",
              "mglance"     : "mglance",
              "mglan"       : "mglance",
              "minspect"    : "minspect",
              "mins"        : "minspect",
              "mnarrow"     : "mnarrow", 
              "mnar"        : "mnarrow",
              "moffer"      : "moffer",
              "moff"        : "moffer",
              "mresolve"    : "mresolve",
              "mres"        : "mresolve",
              "mrest"       : "mrest",
              "mserious"    : "mserious",
              "mser"        : "mserious",
              "msettle"     : "msettle",
              "mset"        : "msettle",
              "mspit"       : "mspit",
              "msuggest"    : "msuggest",
              "msug"        : "msuggest",
              "mtalk"       : "mtalk",
              "mtomorrow"   : "mtomorrow",
              "mtom"        : "mtomorrow",
              "mwipe"       : "mwipe",
              "mwork"       : "mwork",
           ]);
} /* query_cmdlist */


/*
 * Function name:        mincognito
 * Description  :        Allow the player to toggle their incognito
 *                       setttings
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
mincognito(string arg)
{
    mixed     incog; /* True if the player is set to be incognito */

    setuid();
    seteuid(getuid());

    incog = MERC_MASTER->get_info(this_player(), "incognito");

    if (!strlen(arg))
    {
        switch(incog)
        {
        case "on":
            write("You are currently incognito, revealing your title and"
              + " affiliations to no one. You may use <mincognito off>"
              + " or <incognito affiliation only> to change this.\n");
            break;
        case "affiliation":
            write("You are currently revealing your affiliations, but"
              + " hiding your title to anyone who knows you. You may use"
              + " <mincognito on> to hide your title and affilations,"
              + " or <mincognito off> to show both title and"
              + " affiliations.\n");
            break;
        default:
            write("You are currently showing both your title and your"
              + " affiliations to all who know you. You may use"
              + " <mincognito on> to hide your title and affiliations"
              + " or <mincognito affiliation only> to hide your title"
              + " but reveal your affiliation.\n");
            break;
        }

        return 1;
    }

    if (arg == "on")
    {
        if (incog == "on")
        {
            notify_fail("You are already incognito!\n");
            return 0;
        }

        MERC_MASTER->set_info(this_player(), "incognito", "on");

        write("You have gone incognito, hiding your title and"
          + " affiliations from all who would otherwise see them.\n");
        return 1;
    }

    if (arg == "off")
    {
        if (incog == "off")
        {
            notify_fail("You are not incognito to begin with!\n");
            return 0;
        }

        MERC_MASTER->set_info(this_player(), "incognito", "off");
        write("You are no longer incognito, and all are free to see"
          + " your title and affiliations as normal.\n");
        return 1;
    }

    if (arg == "affiliation"      ||
        arg == "affiliation only" ||
        arg == "affiliations"     ||
        arg == "affiliations only")
    {
        if (incog == "aff")
        {
            notify_fail("You are already revealing only your"
                   + " affiliations!\n");
            return 0;
        }

        if (!MERC_MASTER->get_info(this_player(), "affiliation"))
        {
            notify_fail("You are not currently affiliated with"
              + " anything, so that will not work!\n");
            return 0;
        }

        MERC_MASTER->set_info(this_player(), "incognito", "aff");
        write("You are now revealing only your affiliations, and hiding"
          + " your Mercenary title to all who know you.\n");
        return 1;
    }

    notify_fail("Usage: <mincognito on/off/affiliation only>\n");
    return 0;
} /* mincognito */


/*
 * Function name:        adapt
 * Description  :        This is the method Mercs use to train with
 *                       the various "master" trainers they are tasked
 *                       to find in the realms.
 * Arguments    :        arg - what was typed after the verb. A skill
 *                             name is expected.
 * Returns      :        int 1 - success, 0 - failure
 */
public int
adapt(string arg)
{
    mapping  a_map;
    string   trainer_name;
    string   skill;
    object  *npcs;
    object   npc;
    int      i;

    if (!strlen(arg))
    {
        notify_fail("The following adaptation commands exist for Free"
          + " Mercenaries:\n\n"
          + "   adapt list              - Display a list of your current"
          + " skill adaptation\n"
          + "                             information.\n"
          + "   adapt <skillname>       - Attempt to adapt a specific"
          + " skill.\n"
          + "   adapt clear <skillname> - Clear your allocations for a"
          + " specific skill.\n"
          + "   adapt clear all         - Clear all of your allocations"
          + " for all adapted\n"
          + "                             skills.\n"
          + "   adapt help              - See information about the"
          + " adaptability skill.\n\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    a_map = MERC_MASTER->query_adapt_map();

    if (!a_map[arg])
    {
        if (arg == "list")
        {
            MERC_MASTER->adapt_display(this_player());
            return 1;
        }

        if (arg == "skillname")
        {
            notify_fail("Which skill are you trying to adapt? For"
              + " example, you could try to <adapt sword> or <adapt"
              + " swim> - both of which are valid skillnames.\n");
            return 0;
        }

        if (arg == "help")
        {
            this_player()->more(read_file(
                DOC_DIR + "adaptation.txt",0));
            return 1;
        }

        if (arg == "clear")
        {
            notify_fail("Which skill do you wish to clear from your"
              + " current adaptations?\n");
            return 0;
        }

        if (arg == "clear all")
        {
            MERC_MASTER->clear_adapt(this_player());
            return 1;
        }

        if (parse_command(arg, ({}),
            "'clear' %s", skill))
        {
            if (!a_map[skill])
            {
                notify_fail("That is not even an adaptable skill! You"
                  + " cannot remove what you do not have.\n");
                return 0;
            }

            MERC_MASTER->clear_adapt(this_player(), skill);
            return 1;
        }

        notify_fail("There is no such skill. Simply type <adapt> to"
          + " receive a list of commands.\n");
        return 0;
    }

    trainer_name = a_map[arg][MERC_ADAPT_TRAINER];

    npcs = FILTER_LIVE(all_inventory(environment(this_player())));

    for (i = 0; i < sizeof(npcs); i++)
    {
        if (npcs[i]->query_real_name() == trainer_name)
        {
            if (!interactive(npcs[i]))
            {
                npc = npcs[i];
            }
        }
    }

    if (!npc)
    {
        write("You must seek out the appropriate master of that skill"
          + " before you can work on adapting it. Locate "
          + MERC_SCHOLAR + " in the training yard of the Mercenary"
          + " Guild and ask him about any skill to learn where the"
          + " master for each can be found.\n");
        return 1;
    }

    MERC_MASTER->adapt_script1(arg, this_player(), npc);
    return 1;
} /* adapt */


/*
 * Function name:        mercpay
 * Description  :        This is the method Mercs use to pay
 *                       the various "master" trainers they are tasked
 *                       to find in the realms.
 * Arguments    :        arg - what was typed after the verb. A skill
 *                             name is expected.
 * Returns      :        int 1 - success, 0 - failure
 */
public int
mercpay(string arg)
{
    mapping  a_map;
    string   trainer_name;
    object  *npcs;
    object   npc;
    int      i;

    if (!strlen(arg))
    {
        notify_fail("What skill do you wish to pay for?\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    a_map = MERC_MASTER->query_adapt_map();

    if (!a_map[arg])
    {
        notify_fail("There is no such skill. You must <mercpay"
          + " skillname> in the presence of the appropriate skill"
          + " master.\n");
        return 0;
    }

    trainer_name = a_map[arg][MERC_ADAPT_TRAINER];

    npcs = FILTER_LIVE(all_inventory(environment(this_player())));

    for (i = 0; i < sizeof(npcs); i++)
    {
        if (npcs[i]->query_real_name() == trainer_name)
        {
            if (!interactive(npcs[i]))
            {
                npc = npcs[i];
            }
        }
    }

    if (!npc)
    {
        write("You are not in the presence of the appropriate master"
          + " trainer for that skill. There is no one to pay!\n");
        return 1;
    }

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " offers to pay " + QTNAME(npc) + " for some training.\n",
        this_player());

    MERC_MASTER->merc_pay1(arg, this_player(), npc);
    return 1;
} /* mercpay */


/*
 * Function name:        set_adapt
 * Description  :        set the adapt skill for the player
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
set_adapt(string arg)
{
    int     n;
    string  skill;
    mapping a_map;

    notify_fail("Syntax: <setadapt skillname amount>\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}), "%w %d", skill, n))
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    a_map = MERC_MASTER->query_adapt_map();

    if (!a_map[skill])
    {
        notify_fail("There is no such skill.\n");
        return 0;
    }

    TELL_G("skill = " + skill);
    
    if (query_verb() == "lessadapt")
    {
        MERC_MASTER->set_skill_enhance(this_player(), skill, -n);
        return 1;
    }

    MERC_MASTER->set_skill_enhance(this_player(), skill, n);
    return 1;
} /* set_adapt */


/* 
 * Function name:        display_adapt
 * Description  :        print the list of adapted skills for the 
 *                       player.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1
 */
public int
display_adapt(string arg)
{
    setuid();
    seteuid(getuid());

    MERC_MASTER->display_skill_enhance(this_player());
    return 1;
} /* display_adapt */


/* 
 * Function name:        adapt_list
 * Description  :        Display the main list of adaptable skill
 *                       information for the player
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1
 */
public int
adapt_list(string arg)
{
    setuid();
    seteuid(getuid());

    MERC_MASTER->adapt_display(this_player());
    return 1;
} /* adapt_list */


/*
 * Function name:        stop_training
 * Description  :        Allow the player to stop training with one
 *                       of the adaptation masters.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success,
 *                       int 0 - failure
 */
public int
stop_training(string arg)
{
    if (!strlen(arg) || arg != "training")
    {
        if (this_player()->query_prop(TRAINING_PROP))
        {
            notify_fail("Stop what? Training?\n");
        }

        return 0;
    }

    if (intp(this_player()->query_prop(TRAINING_PROP)) &&
        this_player()->query_prop(TRAINING_PROP) == 1)
    {
        notify_fail("Hold on, you haven't even trained yet!\n");
        return 0;
    }

    write("Ok.\n");
    this_player()->add_prop(TRAINING_PROP, "stop");

    return 1;
} /* stop_training */


/*
 * Function name:        maffiliate
 * Description  :        Allow a Merc to declare an official affiliation
 *                       with a given person, place, or guild.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
maffiliate(string arg)
{
    mixed   affiliated;
    string  affiliation;

    setuid();
    seteuid(getuid());

    affiliated = MERC_MASTER->get_info(this_player(), "affiliation");

    if (affiliated)
    {
        affiliation = MERC_MASTER->format_the_the(affiliated);

        if (!affiliation)
        {
            affiliation = capitalize(affiliated);
        }
    }

    if (!strlen(arg))
    {
        write("A Mercenary who is a Free Agent may affiliate themselves"
          + " with the various entities to be found in Genesis, be"
          + " they people or actual guilds. Commands are as"
          + " follows:\n\n"
          + "\tmaffiliate <player name> - affiliate yourself with a"
          + " fellow player\n"
          + "\tmaffiliate <guild name>  - affiliate yourself with a"
          + " specific guild\n\n"
          + "\tmaffiliate clear         - Remove your current"
          + " affiliation\n\n"
          + ((affiliated) ? "You have currently declared yourself"
          + " to be affiliated with " + affiliation :
            "You are currently a Free Agent") + ".\n");

        return 1;
    }

    if (arg == "clear")
    {
        if (!affiliated)
        {
            write("You are already a Free Mercenary, and have no"
              + " ties to break.\n");
            return 1;
        }

        write("You break your ties with " + affiliation
          + ", declaring yourself as a Free Agent once more!\n");
        MERC_MASTER->set_info(this_player(), "affiliation", 0);
        MERC_MASTER->set_info(this_player(), "title", 0);

        write_file(LOG_DIR + "affiliations",
            TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
          + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_real_name()) 
          + " broke their affiliation with " + capitalize(affiliation)
          + ".\n");

        return 1;
    }

    if (MERC_MASTER->parse_affiliation(arg, this_player()));
    {
        return 1;
    }

    /* We already wrote a fail message from parse_affiliation */
    return 1;
} /* maffiliate */


/*
 * Function name:        merchelp
 * Description  :        Allow the Mercenary to get help on the guild
 *                       and commands
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success,
 *                           0 - failure
 */
public int
merchelp(string arg)
{
    string *titles;

    if (!strlen(arg))
    {
        write("The following commands give help on Mercenary"
          + " knowledge:\n\n"
          + "\tmerchelp           - display this list\n"
          + "\tmerchelp abilities - display a list of guild abilities\n"
          + "\tmerchelp adapt     - detailed info on the adapt"
          + " ability\n"
          + "\tmerchelp commands  - display a list of guild commands\n"
          + "\tmerchelp emotes    - display a list of guild emotes\n"
          + "\tmerchelp rules     - display a list of guild rules\n"
          + "\tmerchelp skills    - display a list of guild skills\n"
          + "\tmerchelp titles    - display a list of guild titles\n\n");

        return 1;
    }

    if (arg == "commands")
    {
        write("Commands for the Mercenary Guild:\n\n"
          + "\tadapt              - Allocate skill points as needed\n"
          + "\tmaffiliate         - Affiliate yourself with something\n"
          + "\tmattack (or ma)    - Use mercenary tactics in combat\n"
          + "\tmerchelp           - Learn about the guild\n"
          + "\tmercs              - List the Mercenaries who are\n"
          + "\t                     currently in the realms.\n"
          + "\tmincognito         - Toggle whether to reveal your titles\n\n");

        return 1;
    }

    setuid();
    seteuid(getuid());

    if (arg == "emotes")
    {
        this_player()->catch_msg(read_file(
            DOC_DIR + "emotes.txt"));
        return 1;
    }

    if (arg == "history")
    {
        this_player()->more(read_file(
            DOC_DIR + "history.txt"));
        return 1;
    }

    if (arg == "rules")
    {
        this_player()->more(read_file(
            DOC_DIR + "rules.txt"));
        return 1;
    }

    if (arg == "abilities")
    {
        this_player()->more(read_file(
            DOC_DIR + "abilities.txt"));
        return 1;
    }

    if (arg == "skills")
    {
        this_player()->more(read_file(
            DOC_DIR + "skills.txt"));
        return 1;
    }

    if (arg == "adapt")
    {
        this_player()->more(read_file(
            DOC_DIR + "adaptation.txt"));
        return 1;
    }

    if (arg == "titles" || arg == "title")
    {
        write("\n" + sprintf("%|80s", "Titles Based on"
          + " Adaptability:\n"));
        write(sprintf("%|80s", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"));
        titles = this_player()->query_ad_titles();

        foreach(string title : titles)
        {
            write("\t\t\t\t" + title + "\n");
        }

        titles = this_player()->query_gs_titles();

        write(sprintf("\n" + "%|80s", "Titles Based on Guild Experience:\n"));
        write(sprintf("%|80s",        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"));

        foreach(string title : titles)
        {
            if (title == "Weaponmaster for Hire")
            {
                title = "Weaponmaster/mistress for Hire";
            }
            if (title == "Warlord of Fortune")
            {
                title = "Warlord/lady of Fortune";
            }

            write("\t\t\t\t" + title + "\n");
        }

        return 1;
    }

    notify_fail("That is not a merchelp option. Type <merchelp> by"
      + " itself for a list of options.\n");
    return 0;
} /* merchelp */


/*
 * Function name:        is_merc
 * Description  :        check to see if this person is an merc
 * Arguments    :        object who - the person to check
 * Returns      :        1 - is an merc, 0 - not an merc
 */
public int
is_merc(object who)
{
    return IS_MERC(who);
} /* is_merc */


/*
 * Function name:        merc_who_list
 * Description  :        provide a list of all mercs who are
 *                       currently online
 * Arguments    :        string arg - whatever was typed after the verb
 * Returns      :        1 - success always
 */
public int
merc_who_list(string arg)
{
    string  *mercs = filter(users(), is_merc);

    setuid();
    seteuid(getuid());

    /* Print the header */
    write(sprintf("%|80s",
        ".------------------------------------------------------------.\n")
      + sprintf("%|80s",
        "|   -**-  Mercenaries who are currently in the realms  -**-    |\n")
      + sprintf("%|80s",
        "|                                                              |\n")
      + sprintf("%|80s",
        "| Name:        Rank:                                           |\n")
      + sprintf("%|80s",
        "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n"));

    /* Print the list of players, of that there are none. */
    if (!sizeof(mercs))
    {
        write(sprintf("%|80s",
        "|                       (none currently)                       |\n"));
    }
    else
    {
        foreach(object merc : mercs)
        {
            write(sprintf("%|80s", "| "
              + sprintf("%-12s %-47s",
                    capitalize(merc->query_real_name()),
                    merc->get_merc_ranks())
              + " |\n"));
        }
    }

    /* Print the footer */
    write(sprintf("%|80s",
        "|                                                              |\n")
      + sprintf("%|80s",
        "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n")
      + sprintf("%|80s", sprintf("%-1s %|60s %-1s",
            "|", 
            "-**-  Members Present: " + sizeof(mercs) + " out of "
          + sizeof(get_dir(MEMBER_DIR)) + "  -**-", "|\n"))
      + sprintf("%|80s",
        ".____________________________________________________________.\n"));

    return 1;
} /* merc_who_list */
