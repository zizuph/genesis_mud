/*
 *  /d/Emerald/common/guild/aod/cmdsoul.c
 *
 *  This is the command soul for the Army of Darkness guild in Emerald.
 *
 *  Copyright (c) May 2006, by Cooper Sherry (Gorboth)
 *      Special thanks to Mercade for much help with head ripping!
 *
 *  PLEASE NOTE! Many commands are located in a separate location:
 *      /d/Emerald/common/guild/aod/obj/belt.c
 *  This is because numerous of the functions must mask mudlib-defined
 *  commands. The inheritance chain dictates that commands are added
 *  in souls before those from objects. It was necessary to, therefore,
 *  define certain commands in the guild object.
 *
 *  2016-02-12 - Cotillion
 *  - Use the master object to check if something is a messenger
 *  2021-03-07 - Carnak
 *  - Updated the soul to add the new combat special.
 *  2021-06-01 - Carnak
 *  - Added a delay to ogrestomp.
 *  2021-07-27 - Carnak
 *  - Changed the rip command to allow for better team functionality
 */

#pragma strict_types

#include "/d/Genesis/specials/defs.h"
/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit ABILITIES_LIB;

#include "defs.h"

#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <time.h>
#include <wa_types.h>

/* prototypes */
public string        get_soul_id();
public int           query_cmd_soul();
public mapping       query_cmdlist();
public int           duty_roster(string arg);
public int           ask_ogg(string arg);
public int           ogg_help(string arg, object player, string *chapter_array);
public int           rip_skull(string arg);
public int           ogretie(string arg);
public int           aod_crush(string str);
public int           aod_sneak(string arg);
public int           aod_hide(string arg);
public int           ogrestomp(string arg);
public void          remove_stomp_prop(object room);
public void          allow_stomp(object player);
public int           know_election(string arg);
public int           bust_boulder(string arg);
public int           ogre_buttkick(string arg);
public void          stop_buttkicking(object player);
public int           ogre_report(string arg);
public int           npc_report(string arg);


/* definitions */
#define       AOD_TEAM_SKULL "_aod_team_skull_"
#define       HARVEST_LIST   ({ "alchemist",   \
                                "avatar",      \
                                "balrog",      \
                                "blacksmith",  \
                                "boy",         \
                                "centaur",     \
                                "dragon",      \
                                "drifter",     \
                                "drow",        \
                                "dwarf",       \
                                "dweller",     \
                                "elf",         \
                                "faerie",      \
                                "fisherman",   \
                                "giant",       \
                                "girl",        \
                                "gnome",       \
                                "guard",       \
                                "gypsy",       \
                                "half-elf",    \
                                "half-giant",  \
                                "half-ogre",   \
                                "haradrim",    \
                                "hill giant",  \
                                "hobbit",      \
                                "hobgoblin",   \
                                "human",       \
                                "imp",         \
                                "kender",      \
                                "karg",        \
                                "kobold",      \
                                "kroug",       \
                                "marauder",    \
                                "minotaur",    \
                                "orc",         \
                                "port thug",   \
                                "rohirrim",    \
                                "sahuagin",    \
                                "sailor",      \
                                "satyr",       \
                                "sprite",      \
                                "stone giant", \
                                "troll",       \
                                "triton",      \
                                "unicorn",     \
                                "uruk",        \
                                "uruk-hai",    \
                                "water-kroug", \
                                "villager",    \
                                "warrior",     \
                                "wizard",      \
                                "woman",       \
                             })

/* global variables */
public int      Tell_Alarm;
static int      Delay_Stomp;

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return "army_of_darkness"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
public int 
query_cmd_soul() 
{ 
    return 1; 
}


public mapping
query_ability_map()
{
    return ([
                "crush"     : (AOD_DIR + "specials/crush"),
                "buttkick"  : (AOD_DIR + "specials/crush"),
            ]);
}

/*
 * Function name: query_cmdlist
 * Description:   Get the commands available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 *
 * IMPORTANT: See the header at the top of the function if some
 *            commands seem to be absent from this list.
 */
public mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());

    return ([
            /* Command name : Function name */
              "dr"          : "duty_roster",
              "duty"        : "duty_roster",
              "ogghelp"     : "ask_ogg",
              "rip"         : "rip_skull",
              "tie"         : "ogretie",
              "ogretie"     : "ogretie",
              //"crush"       : "aod_crush",
              //"ch"          : "aod_crush",
              "hide"        : "aod_hide",
              "sneak"       : "aod_sneak",
              "autosneak"   : "aod_sneak",
              "ogrewield"   : "ogrewield",
              "ogrewield2"  : "ogrewield2",
              "ogrestomp"   : "delay_stomp",
              "os"          : "delay_stomp",
              "ogreupdate"  : "know_election",
              "ou"          : "know_election",
              "bust"        : "bust_boulder",
              //"buttkick"    : "ogre_buttkick",
              "ogrereport"  : "ogre_report",
              "npcreport"   : "npc_report",
              "block"       : "aod_block",
              "crush"       : "do_ability",
              "ch"          : "do_ability",
              "buttkick"    : "do_ability"
           ]);
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
 * Function name:        ask_ogg
 * Description  :        the player asks ogg a question. We let the arg
 *                       be anything and then resolve it in the function
 *                       ogg_help via an alarm delay.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 always
 */
public int
ask_ogg(string arg)
{
    string *temp_chapter_array;
    string *chapter_array;
    string  chapter;
    string  column1;
    string  column2;
    int     i,
            n;

    chapter = AOD_OGG_MASTER->get_info(this_player(), "Tutorial");

    if (chapter != "done")
    {
        switch(chapter)
        {
            case "tutorial1":
                column1 = "Your current orders are to locate the"
                        + " Repository of Skulls.";
                break;
            case "tutorial2":
                column1 = "Your current orders are to <claim> a"
                        + " harvesting sack at the Repository of"
                        + " Skulls.";
                break;
            case "tutorial3":
                column1 = "Your current orders are to locate your"
                        + " first prey, <crush> them with your mighty"
                        + " fists, <rip> their head from their"
                        + " lifeless corpse, and then <collect> the"
                        + " head in your harvesting sack.";
                break;
            case "tutorial4":
                column1 = "Your current orders are to return to the"
                        + " Repository of Skulls and <deposit> your"
                        + " first head.";
                break;
        }

        write("Your brain is still too primitive to contact Ogg! Follow"
          + " the instructions of the Darklings to obtain mind fluid"
          + " so that you can gain this ability. " + column1 + "\n");

        return 1;
    }

    setuid();
    seteuid(getuid());

    temp_chapter_array = get_dir(AOD_DOC_DIR);
    n = sizeof(temp_chapter_array);
    chapter_array = allocate(n);

    for (i = 0; i < n; i++)
    {
        sscanf(temp_chapter_array[i], "%s.txt", chapter);
        chapter_array[i] = chapter;
    }

    if (!strlen(arg))
    {
        write(
            sprintf("%|80s",
                ".--------------------------------------------.\n")
          + sprintf("%|80s",
                "|      Talk to Ogg! Ogg Teach! You learn!      |\n")
          + sprintf("%|80s",
                "|            SHUT UP AND LISTEN!!!             |\n")
          + sprintf("%|80s",
                "|          Ogg teach you about these:          |\n")
          + sprintf("%|80s",
                "| ============================================ |\n"));

        for (i = 0; i < n; i++)
        {
            column1 = capitalize(chapter_array[i]);
            column2 = "";

            if (!AOD_OGG_MASTER->get_info(this_player(),
                capitalize(column1)))
            {
                column1 = "---------";
            }

            if (n > (i + 1))
            {
                column2 = capitalize(chapter_array[i + 1]);

                if (!AOD_OGG_MASTER->get_info(this_player(),
                    capitalize(column2)))
                {
                    column2 = "---------";
                }
            }

            write(sprintf("%|80s",
                "|" + sprintf("        %-12s         %-12s %6s",
                column1, column2, "|\n")));

            i++;
        }

        write(
            sprintf("%|80s",
                "| ============================================ |\n")
          + sprintf("%|80s",
                "|   To ask Ogg a question on a specific topic  |\n")
          + sprintf("%|80s",
                "|            use <ogghelp topic>.              |\n")
          + sprintf("%|80s",
                "`--------------------------------------------'\n"));

        AOD_OGG_MASTER->set_info(this_player(), "ogghelp", "yes"); 
        AOD_OGG_MASTER->set_info(this_player(), "Ogg", "yes");  

        return 1;
    }

    if (!Tell_Alarm || !sizeof(get_alarm(Tell_Alarm)))
    {
        Tell_Alarm = set_alarm(3.0, 0.0, &ogg_help(lower_case(arg),
                               this_player(), chapter_array));

        write("Concentrating in a way that hurts your tiny brain, you"
          + " ask Ogg about '" + arg + "'.\n");
        return 1;
    }

    write("You've already asked Ogg something! Be patient!\n");

    return 1;
} /* ask_ogg */


/*
 * Function name:        ogg_help
 * Description  :        Ogg is a psychic ogre who gives the players
 *                       info on the guild when they commune with him
 *                       using the command <ogghelp>.
 * Arguments    :        string arg - what was typed after the command,
 *                       object player - who we are dealing with here,
 *                       string chapter_array - array of existing chapters
 * Returns      :        int 1 -- success,
 *                       int 0 -- failure.
 */
public int
ogg_help(string arg, object player, string *chapter_array)
{
    string  *chapter = allocate(sizeof(chapter_array)),
             new_chapter = "";
    int      i, j;

    setuid();
    seteuid(getuid());

    set_this_player(player);
    arg = lower_case(arg);

    if (arg == "topic")
    {
        OGG_TELL("You try being cute? OGG SMASH BIG TIME!!!! Hmmm ..."
          + " wait. Ogg not smash yet. Maybe you confused. Stupid like"
          + " stump? That okay. Ogre not smart when first learn. Me"
          + " forgive. When use <ogghelp> you do like this. If topic"
          + " you want learn is 'ogg' then you do <ogghelp ogg>. That"
          + " way me know what you want learn. Now ask Ogg and Ogg"
          + " teach! No more stupid or cute trick. SMASH IF TRICK!!");
        return 1;
    }

    if (member_array(arg, chapter_array) == -1)
    {
        OGG_TELL("Huhh?? Ogg not know anything about that. What Ogg not"
          + " know OGG NOT TEACH! YOU CHECK <OGGHELP> THEN ASK!!!");
        return 1;
    }

    if (!AOD_OGG_MASTER->get_info(this_player(), capitalize(arg)))
    {
        OGG_TELL("This some kind of trick? Ogg not teach yet! NOT TRICK OR"
          + " OGG SMASH BIG TIME!! You talk to Ogg about what"
          + " Ogg teach!");
        player->catch_tell(sprintf("%|80s",
            "You can see what Ogg has taught you using <ogghelp>.\n"));
        return 1;
    }

    switch(arg)
    {
        case "ogg":
            chapter[0] = "bosses";
            break;
        case "bosses":
            chapter[0] = "ogres";
            chapter[1] = "harvest";
            break;
        case "ogres":
            chapter[0] = "army";
            chapter[1] = "rules";
            break;
        case "army":
            chapter[0] = "smashing";
            break;
        case "smashing":
            chapter[0] = "armour";
            break;
        case "armour":
            chapter[0] = "forge";
            break;
        case "forge":
            chapter[0] = "scrap";
            break;
        case "harvest":
            chapter[0] = "juice";
            chapter[1] = "treats";
            chapter[2] = "upgrades";
            break;
        case "juice":
            chapter[0] = "training";
            chapter[1] = "skulls";
            break;
        case "treats":
            chapter[0] = "officers";
            break;
        case "officers":
            chapter[0] = "honors";
            break;
        case "skulls":
            chapter[0] = "trophy";
            break;
        case "rules":
            chapter[0] = "cutting";
            break;
        case "honors":
            chapter[0] = "buttkicking";
            break;
        default:
            break;
    }

    for (i = 0, j = 0; i < sizeof(chapter); i++)
    {
        if (!strlen(chapter[i]))
        {
            i = 100;
        }
        else
        {
            j++;

            if (j > 1)
            {
                new_chapter += " and '" + chapter[i] + "'";
            }
            else
            {
                new_chapter = " '" + chapter[i] + "'";
            }

            AOD_OGG_MASTER->set_info(this_player(),
                capitalize(chapter[i]), "yes");   
        }
    }

    OGG_TELL(read_file(AOD_DOC_DIR + arg + ".txt", 0));

    if (strlen(new_chapter))
    {
        player->catch_tell(sprintf("%|80s",
            "You can now get <ogghelp> on" + new_chapter + ".\n"));
    }

    player->catch_tell(sprintf("%|80s",
        "To see a list of topics, simply type <ogghelp>.\n"));

    return 1;
} /* ogg_help */


/*
 * Function name:        rip_skull
 * Description  :        allow the player to rip the skull off of a corpse
 *                       of something s/he has killed.
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
rip_skull(string arg)
{
    object *corpses,
            corpse,
            team_skull,
            skull,
            before_dead,
            old_this_player,
           *oteam,
           *tmpteam;
    string *killer_info,
            race,
            corpsefile,
           *player_corpse_array,
            whose_turn = "",
            logfile,
           *explode_race;
    int     i, n,
            is_messenger,
            is_slave,
            headcount = 0,
            oldest_turn = time(),
            instances = 0;

    setuid();
    seteuid(getuid());

    notify_fail("Rip what from where?\n");
    if (!strlen(arg))
    {
        return 0;
    }

    corpses = PARSE_THIS(arg, "[a] [the] 'head' / 'skull' 'off' / 'from'"
      + " [of] [the] %i");
    switch(sizeof(corpses))
    {
    case 0:
        return 0;
    case 1:
        corpse = corpses[0];
        break;
    default:
        notify_fail("Please try to rip off only a single head at"
          + " a time.\n");
        return 0;
    }

    if (living(corpse))
    {
        notify_fail("Skull collecting isn't quite that easy. You'll have"
          + " to kill " + corpse->query_the_name(this_player()) + " first!\n");
        return 0;
    }

    /* determine if the object is a corpse */
    if (!pointerp(killer_info = corpse->query_prop(CORPSE_AS_KILLER)))
    {
        notify_fail("You aren't able to rip such a thing from the "
          + corpse->short() + ".\n");
        return 0;
    }

    race = corpse->query_prop(CORPSE_S_RACE);

    if (!strlen(race))
    {
        notify_fail("You don't recognize this creature as anything"
          + " that the Darklings would value.\n");
        return 0;
    }

    /* determine if this is a collectable racetype */
    if (member_array(race, HARVEST_LIST) == -1)
    {
        switch(race)
        {
        case "hill dwarf":
        case "hill-dwarf":
        case "gully dwarf":
        case "gully-dwarf":
            corpse->add_prop(CORPSE_S_RACE, "dwarf");
            race = "dwarf";
            break;
        case "sea-elf":
        case "sea elf":
        case "shadow elf":
        case "shadow-elf":
        case "dark elf":
        case "dark-elf":
            corpse->add_prop(CORPSE_S_RACE, "elf");
            race = "elf";
            break;
        case "halfling":
            corpse->add_prop(CORPSE_S_RACE, "hobbit");
            race = "hobbit";
            break;
        default:
            /* I'm going to keep track of these failures */

            /* First thigns first. The data manager can't handle
             * whitespace, so we need to change racenames that are
             * more than one word. I'm going to substitute <-> for
             * spaces.
             */
            explode_race = explode(race, " ");

            if (sizeof(explode_race) > 1)
            {
                race = implode(explode_race, "<->");
            }

            instances  = METAL_MASTER->get_info("skull_rejects", race);
            instances ++;

            METAL_MASTER->set_info("skull_rejects", race, instances);

            /* Now we have to remove the <-> so the player doesn't
             * see it!
             */
            explode_race = explode(race, "<->");

            if (sizeof(explode_race) > 1)
            {
                race = implode(explode_race, " ");
            }

            notify_fail("The darklings cannot use " + race + " skulls!\n");
            return 0;
            break;
        }
    }

    /* determine if the corpse has already been decapitated */
    if (corpse->query_prop(AOD_DECAPITATED_PROP))
    {
        if (this_player()->query_real_name() == killer_info[0])
        {
            notify_fail("You've already taken the head of this corpse.\n");
        }
        else
        {
            notify_fail("This corpse has no head. One of your tribemates"
              + " must have beaten you to it!\n");
        }
        return 0;
    }

    /* New oteam functionality // Carnak */
    oteam = this_player()->query_team_others();
    
    if (sizeof(oteam) && !objectp(corpse->query_prop(AOD_TEAM_SKULL)))
    {
        object whose_turn = this_player();
        
        foreach(object ogre: oteam)
        {
            // Only ogres matter for this sort of thing
            if (!IS_OGRE(ogre))
                continue;
            
            // Ogres who arent here cant interrupt your collection
            if (environment(this_player()) != environment(ogre))
                continue;
            
            if (AOD_MASTER->get_info(ogre, "Last_Turn") < 
                AOD_MASTER->get_info(whose_turn, "Last_Turn"))
                whose_turn = ogre;
        }
        
        // Add a prop so that the corpse remembers whose skull it is
        corpse->add_prop(AOD_TEAM_SKULL, whose_turn);
        // Reset the players last turn
        AOD_MASTER->set_info(whose_turn, "Last_Turn", time());
    }
    
    // Check if the corpse has a team prop, that it isnt the users and that it
    // is a team member
    team_skull = corpse->query_prop(AOD_TEAM_SKULL);
    if (objectp(team_skull) && team_skull != this_player() &&
        member_array(team_skull, oteam) > -1)
    {
        notify_fail("It is " + capitalize(team_skull->query_real_name()) + "'s "
        + "turn to harvest! You decide to be patient.\n");
        return 0;
    }
    /* END of oteam */

    old_this_player = this_player();
    /* Find out whether this corpse belongs to a messenger. */
    corpsefile = corpse->query_prop(CORPSE_S_LIVING_FILE);

    if (strlen(corpsefile))
    {
        int cloned = 0;
        before_dead = find_object(corpsefile);
        if (!objectp(before_dead)) {
            before_dead = clone_object(corpsefile);
            cloned = 1;
        }
        is_messenger = before_dead->id("messenger") ||
                       before_dead->id("courier");
        is_slave = before_dead->id("_sanction_slave_npc");
        if (cloned)
            before_dead->remove_object();
    }
    else
    {
        notify_fail("Oops! You actually destroyed the corpse in the"
          + " act of decapitation! Looks like it was too frail.\n");
        corpse->remove_object();
        return 0;
    }

    /* Cloning of a new NPC causes this_player() to change, so we must reset it. */
    set_this_player(old_this_player);

    if (is_messenger)
    {
        notify_fail("Your bretheren would laugh you out of the Army"
          + " if they saw you toting messenger heads around! Forget"
          + " it!\n");
        return 0;
    }

    if (is_slave)
    {
        notify_fail("These slaves have had their brains turned to"
          + " mush long ago. The Darklings do not desire them!\n");
        return 0;
    }

    write("You lean down over the " + corpse->short_func() + " and rip its"
      + " head off with your bare hands.\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " leans down over the "
      + corpse->short_func() + " and rips its head off with "
      + this_player()->query_possessive() + " bare hands!\n",
        this_player());

    player_corpse_array = ({
        "/d/Genesis/race/human_std",
        "/d/Genesis/race/hobbit_std",
        "/d/Genesis/race/goblin/std",
        "/d/Genesis/race/gnome_std",
        "/d/Genesis/race/elf_std",
        "/d/Genesis/race/dwarf_std", });

    skull = clone_object(AOD_OBJ_DIR + "head");

    skull->set_skull_id(OB_NAME(corpse));
    skull->set_skull_race(race);
    skull->set_skull_nonmet(corpse->query_nonmet_name());
    skull->set_skull_met(corpse->query_met_name());

    if (member_array(corpse->query_prop(CORPSE_S_LIVING_FILE),
        player_corpse_array) != -1)
    {
        skull->set_playerskull(1);
    }

    headcount = DECAP_MASTER->get_info(this_player()->
        query_real_name(), corpsefile);
    headcount++;

    DECAP_MASTER->set_info(this_player()->query_real_name(),
                           corpsefile, headcount);

    /* Cycle on 100K log file. */
    logfile = AOD_LOG_DIR + "decapitation_log/"
      + this_player()->query_real_name();
    if (file_size(logfile) > 100000)
    {
        rename(logfile, logfile + ".old");
    }
    write_file(logfile,
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + " -- (" + corpse->query_nonmet_name() + ":" 
      + corpse->query_met_name() + ")\n");

    corpse->set_state_desc("headless corpse of ");
    corpse->set_pstate_desc("headless corpses of ");
    corpse->add_adj( ({ "headless", "decapitated" }) );
    corpse->remove_leftover("scalp");
    corpse->remove_leftover("skull");
    corpse->remove_leftover("ear");
    corpse->remove_leftover("nose");
    corpse->remove_leftover("eye");
    corpse->add_prop(AOD_DECAPITATED_PROP, 1);

    /* Finally, we make sure to add the timestamp to the player to
     * determine when their next turn should be */
    AOD_MASTER->set_info(this_player(), "Last_Turn", time());

    if (!skull->move(this_player()))
    {
        return 1;
    }

    /* move to player failed ... get rid of the skull */
    write("You can't carry any more! You decide to just eat the head"
      + " instead. Mmm ... delicious!\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " eats " + LANG_THESHORT(skull) + "!\n",
        this_player());
    skull->remove_object();

    return 1;
} /* rip_skull */


/*
 * Function name:        ogretie
 * Description  :        give the ogres a way to see a fail message for
 *                       ogretie even if they don't have a head.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        0 always
 */
public int
ogretie(string arg)
{
    mixed   obj;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o 'to' [the] [trophy] 'belt'", obj))
    {
        if (!obj)
        {
            notify_fail("You don't have such a thing in your"
              + " possession.\n");
            return 0;
        }

        notify_fail(capitalize(query_verb()) + " what to what?\n");
        return 0;
    }

    if (!obj->id("_aod_head"))
    {
        notify_fail("You aren't able to tie the " + obj->short()
          + " to the trophy belt.\n");
    }

    return 0;
} /* ogretie */


/*
 * Function name: aod_crush
 * Description:   This is the code for the "aod_crush" command.
 *                This is a special attack.
 * Arguments:     The arguments the player gave to the "aod_crush"
 *                command.
 * Returns:       1 / 0 - command succeeded / command failed
 */
public int
aod_crush(string str)
{
    object ob, *obj;
    string how;

    /* What are we attacking anyway? */
    if (strlen(str))
    {
        if (!sizeof(obj = parse_this(str, "[the] %l")))
        {
            notify_fail("Choose a more appropriate target.\n");
            return 0;
        }

        ob = obj[0];
    }
    /* if the player doesn't specify a target, we assume the player's
     * current enemy.
     */
    else if (!(ob = this_player()->query_attack()))
    {
        notify_fail("But you aren't in battle with anyone!\n");
        return 0;
    }

    /* Does attacker have the skill? */
    /* I've decided against this block for now.
    if (!(this_player()->query_skill(SS_AOD_WALLOP)))
    {
        write("You haven't yet learned how to do any kind of tricky"
          + " attacks. Better visit a trainer.\n");
        return 1;
    } */
 
    /* Is the attacker already busy? */
    if (this_player()->query_crush())
    {
        write("You are already preparing such an attack.\n");
        return 1;
    }
 
    /* Are we even allowed to attack it?  Use can_attack_with_occ_special(),
     * which is defined in the guild shadow, to find out.
     */
    if (stringp(how = this_player()->can_attack_with_occ_special(ob, "crush")))
    {
        write(how);
        return 1;
    }
 
    /* The shadow takes care of the rest */
    this_player()->ogre_crush(ob);

    return 1;
} /* aod_crush */


/*
 * Function name:        aod_sneak
 * Description  :        prevent ogres from sneaking
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - to catch the command successfully
 */
public int
aod_sneak(string arg)
{
    write("Nice try! Ogres sneak about as well as they sing!\n");
    return 1;
} /* aod_sneak */


/*
 * Function name:        aod_hide
 * Description  :        prevent ogres from hiding
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - to catch the command successfully
 */
public int
aod_hide(string arg)
{
    if (!strlen(arg))
    {
        write("You? Hide? What, behind a castle? You're an Ogre!\n");
        return 1;
    }

    write("You are far too stupid and clumsy to properly hide"
      + " anything.\n");
    return 1;
} /* aod_hide */


/*
 * Function name:        aod_block
 * Description  :        prevent ogres from using block
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - to catch the command successfully
 */
public int
aod_block(string arg)
{
    if (!strlen(arg))
    {
        write("Block which exit?\n");
        return 1;
    }

    write("Err ... um ... too confusing! Smash instead!!\n");
    return 1;
} /* aod_block */


/*
 * Function name:        ogrewield
 * Description  :        Allow ogres to wield corpses as weapons!
 * Arguments    :        string arg: What was typed following the verb
 * Returns      :        1: success, 0: failure
 */
public int
ogrewield(string arg)
{
    object *corpses,
            corpse,
            wep,
           *weapons = this_player()->query_weapon(-1),
           *loot;
    string *killer_info,
            race,
            corpsefile;
    int     i, n;

    setuid();
    seteuid(getuid());

    notify_fail("What do you want to wield, as only an ogre can?\n");
    if (!strlen(arg))
    {
        return 0;
    }

    corpses = PARSE_THIS(arg, "[a] [the] %i");
    switch(sizeof(corpses))
    {
    case 0:
        return 0;
    case 1:
        corpse = corpses[0];
        break;
    default:
        notify_fail("Please try to wield only a single thing at a"
          + " time.\n");
        return 0;
    }

    if (living(corpse))
    {
        notify_fail("Err ... you'll probably have to do some killing"
          + " first. Its hard to wield something that wiggles so"
          + " much.\n");
        return 0;
    }

    /* determine if the object is a corpse */
    if (!pointerp(killer_info = corpse->query_prop(CORPSE_AS_KILLER)))
    {
        if (corpse->check_weapon() && corpse->query_name(
            "_aod_corpse_weapon"))
        {
            this_player()->command("$wield " + OB_NAME(corpse));
            return 1;
        }

        notify_fail("Wield the " + corpse->short() + "? Wielding a"
          + " corpse is what Ogres like to do. Go get one!\n");
        return 0;
    }

    if (sizeof(weapons) > 1)
    {
        notify_fail("You'll need to free up a hand first.\n");
        return 0;
    }

    write("You lean down and grasp the " + corpse->short_func() + " in"
      + " your big hands, hoisting it into a combat-ready position!\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " leans down and grasps the "
      + corpse->short_func() + " in "
      + this_player()->query_possessive() + " big hands, hoisting it"
      + " into a combat-ready position!\n",
        this_player());

    loot = all_inventory(corpse);

    if (sizeof(loot))
    {
        tell_room(environment(this_player()),
            capitalize(COMPOSITE_DEAD(loot))
          + ((sizeof(loot) > 1) ? " spill" : "spills") + " from the"
          + " corpse to the ground.\n", 0);
    }

    wep = clone_object(AOD_WEP_DIR + "corpse_weapon");

    wep->set_wep_id(OB_NAME(corpse));
    wep->set_wep_race(corpse->query_race_name());
    wep->set_wep_nonmet(corpse->query_nonmet_name());
    wep->set_wep_met(corpse->query_met_name());
    wep->set_wep_weight(corpse->query_prop(CONT_I_WEIGHT));
    wep->set_wep_volume(corpse->query_prop(CONT_I_VOLUME));
    wep->set_wep_max_weight(corpse->query_prop(CONT_I_MAX_WEIGHT));
    wep->set_wep_max_volume(corpse->query_prop(CONT_I_MAX_VOLUME));
    wep->set_wep_as_killer(corpse->query_prop(CORPSE_AS_KILLER));
    wep->set_wep_living_file(corpse->query_prop(CORPSE_S_LIVING_FILE));
    wep->update_things();

    if (!wep->move(this_player()))
    {
        corpse->remove_object();
        this_player()->command("$wield corpse");
        return 1;
    }

    /* move to player failed ... get rid of the wep */
    write("Oops! You can't carry any more. You end up dropping the"
      + " corpse back to the ground.\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " fumbles " + LANG_THESHORT(wep)
      + ", sending it plopping back to the ground.\n");
    wep->remove_object();

    return 1;
} /* ogrewield */


/*
 * Function name: ogrewield2
 * Description  : Allow ogres to wield corpses as weapons!
 * Arguments    : string arg - What was typed following the verb
 * Returns      : int - 1: success, 0: failure
 */
public int
ogrewield2(string arg)
{
    object *items;
    object  corpse;
    object  weapon;
    object *loot;

    items = parse_this(arg, "[the] %i");
    switch(sizeof(items))
    {
    case 0:
        notify_fail("What do you want to wield, as only an ogre can?\n");
        return 0;
    case 1:
        corpse = items[0];
        break;
    default:
        notify_fail("Just one at a time will do, even for an ogre.\n");
        return 0;
    }

    if (living(corpse))
    {
        notify_fail("Err ... you'll probably have to do some killing"
          + " first. Its hard to wield something that wiggles so much.\n");
        return 0;
    }

    /* determine if the object is a corpse. */
    if (!IS_CORPSE_OBJECT(corpse))
    {
        /* If it is a corpse weapon, just try to wield it. */
        if (corpse->id(AOD_CORPSE_WEAPON_ID))
        {
            this_player()->command("$wield " + OB_NAME(corpse));
            return 1;
        }

        notify_fail("Wield the " + corpse->short() + "? Wielding a"
          + " corpse is what Ogres like to do. Go get one!\n");
        return 0;
    }

    /* Find out whether both hands are free. */
    if (objectp(this_player()->query_weapon(W_LEFT)) ||
        objectp(this_player()->query_weapon(W_RIGHT)))
    {
        notify_fail("You'll need to free up your hands first.\n");
        return 0;
    }

    write("You lean down and grasp the " + corpse->short() + " in"
      + " your big hands, hoisting it into a combat-ready position!\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " leans down and grasps the "
      + QSHORT(corpse) + " in " + this_player()->query_possessive()
      + " big hands, hoisting it into a combat-ready position!\n",
        this_player());

    /* If there is loot left in the corpse, throw it onto the ground. */
    loot = all_inventory(corpse);
    loot = filter(loot, &not() @ &->move(environment()));
    if (sizeof(loot))
    {
        tell_room(environment(this_player()),
            capitalize(COMPOSITE_DEAD(loot))
          + ((sizeof(loot) > 1) ? " spill" : "spills") + " from the "
          + corpse->short() + " to the ground.\n", 0);
    }

    /* If we are not carrying the corpse yet, we need to pick it up first. */
    if ((environment(corpse) != this_player()) &&
        corpse->move(this_player()))
    {
        write("Oops! You can't carry any more. You end up dropping "
          + corpse->short() + " back to the ground.\n");
        tell_room(environment(this_player()),
            QCTNAME(this_player()) + " fumbles the " + corpse->short()
          + ", sending it plopping back to the ground.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    weapon = clone_object(AOD_WEP_DIR + "corpse_club");
    weapon->move(this_player(), 1);
    weapon->weaponise_corpse(corpse);

    this_player()->command("$wield " + OB_NAME(weapon));
    return 1;
} /* ogrewield2 */


/*
 * Function name:        ogrestomp
 * Description  :        A combat special that allows Ogres to stomp
 *                       the ground hard enough to trigger a minor
 *                       earthquake. While the quake sustains, players
 *                       (including the Ogre) are prevented from using
 *                       room exits.
 * Arguments    :        string arg - what was typed along with the verb
 * Returns      :        int 1: success, 0: failure
 *
 * Comments:
 *
 *   The idea here is to allow the Ogres this nice special to help
 *   prevent their prey from running away all the time. However, this
 *   could be disastrous if it were allowed to be abused. So ... the
 *   implementation includes diminishing returns for repeated use
 *   as follows:
 *
 *       - A player can only perform an <ogrestomp> once every five
 *         minutes. A prop is added to the player that guarantees
 *         this.
 *       - When an <ogrestomp> is performed, a prop is also added to the
 *         room in which it was performed that lasts for 2 minutes.
 *       - When an <ogrestomp> is performed for the *FIRST* time in a
 *         room, it inserts the effect object into that room. The
 *         object is set to last for 15 seconds.
 *       - If, *WHILE THE OBJECT IS YET PRESENT IN THE ROOM* another
 *         <ogrestomp> is performed, the duration of the effect object
 *         is extended by half of the current duration. In this way,
 *         the absolute maximum duration for any effect is 30 seconds,
 *         regardless of how many Ogres you have in the room stomping.
 *       - Each additional <ogrestomp> increases the value of the room
 *         prop by one.
 *       - So, after the final <ogrestomp> is performed, there are always
 *         two minutes before the prop is removed from the room.
 *       - While the prop persists in the room, any new ogrestomp
 *         effects added to the room are set to only 5 seconds.
 *       - Once the room prop is removed from the room, new ogrestomps
 *         will again last for 15 seconds in duration.
 *
 *   Lets imagine a scenareo to paint this more clearly. Lets imagine
 *   That a team of 5 Ogres, A, B, C, D, and E, each decide to use
 *   their <ogrestomp> ten seconds apart to trap their prey in the
 *   room.
 *
 *     00:00 - Ogre A stomps, creating effect that lasts 15 seconds.
 *     00:10 - Ogre B stomps, extending the effect to 22.5 seconds.
 *     00:20 - Ogre C stomps, extending the effect to 26.25 seconds.
 *     00:27 - stomp effect disappears.
 *     00:30 - Ogre D stomps, creating effect that lasts 5 seconds.
 *     00:35 - stomp effect disappears.
 *     00:40 - Ogre E stomps, creating effect that lasts 5 seconds.
 *     00:45 - stomp effect disappears.
 *     
 *   At this point, no new stomps would be able to be done for another
 *   4 minutes and 15 seconds.
 */
public int
ogrestomp(string arg)
{
    object    stomp_effect,
              current_quake,
              room = environment(this_player());
    float     delay = 8.0;
    int       quake = 0,
              stomp_prop = 0;
    
    if (objectp(this_player()->query_prop(AOD_I_STOMP_PROP)))
    {
        object old_room = this_player()->query_prop(AOD_I_STOMP_PROP);
        this_player()->add_prop(AOD_I_STOMP_PROP, 0);
        
        if (old_room != room)
        {
            notify_fail("You forgot to stomp while moving around.\n");
            return 0;
        }
    }

    if (arg)
    {
        notify_fail("Huh ... ? No need to specify a target, just"
          + " <ogrestomp> and you'll hit the ground!\n");
        return 0;
    }

    if (this_player()->query_prop(AOD_I_STOMP_PROP))
    {
        notify_fail("Your legs are still too sore to do another"
          + " ogrestomp.\n");
        return 0;
    }

    this_player()->add_prop(AOD_I_STOMP_PROP, 1);
    set_alarm(300.0, 0.0, &allow_stomp(this_player()));

    if (current_quake = present(AOD_OGRESTOMP_EFFECT, room))
    {
        current_quake->set_prolonged();
        tell_room(room,
            QCTNAME(this_player()) + " brings "
          + this_player()->query_possessive() + " massive foot down"
          + " in a mighty battle-stomp, prolonging shaking of the"
          + " ground!\n", this_player());
        write("You bring your massive foot down in a mighty battle-"
          + "stomp, prolonging the shaking of the ground!\n");

        stomp_prop = room->query_prop(AOD_I_STOMP_PROP);
        room->add_prop(AOD_I_STOMP_PROP, stomp_prop + 1);
        set_alarm(120.0, 0.0,
            &remove_stomp_prop(room));

        write_file(AOD_LOG_DIR + "stomp_log",
            TIME2FORMAT(time(), "mm/dd") + " ("
          + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name()) + " -- "
          + "prolonged the stomp!\n");

        return 1;
    }

    tell_room(room,
        QCTNAME(this_player()) + " brings "
      + this_player()->query_possessive() + " massive foot down" 
      + " in a mighty battle-stomp, triggering a minor earthquake!\n",
        this_player());
    write("You bring your massive foot down in a mighty battle-stomp,"
      + " triggering a minor earthquake!\n");

    setuid();
    seteuid(getuid());

    stomp_prop = room->query_prop(AOD_I_STOMP_PROP);

    if (stomp_prop)
    {
        delay = 5.0;
    }

    stomp_effect = clone_object(AOD_OBJ_DIR + "stomp_effect");
    stomp_effect->move(room);
    stomp_effect->remove_ogrestomp_object(delay);
    TELL_G("Delay = " + ftoi(delay));

    write_file(AOD_LOG_DIR + "stomp_log",
        TIME2FORMAT(time(), "mm/dd") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_name()) + " stomped -- "
      + "Delay = " + ftoi(delay) + "\n");

    /* So here is what I do. I add a prop to the room that lasts
     * for two minutes. The special checks to see if this prop is
     * in the room when determining the length of the effect. We
     * want to prevent players from using the stomp to create a
     * permenant block to exits. This will force the effect into
     * diminishing returns which will (hopefully) prevent this.
     */
    room->add_prop(AOD_I_STOMP_PROP, stomp_prop + 1);
    set_alarm(120.0, 0.0,
        &remove_stomp_prop(room));

    return 1;
} /* ogrestomp */


/*
 * Function name:        remove_stomp_prop
 * Description  :        Reduce the prop value by one.
 * Arguments    :        object room - the room to check for the prop
 */
public void
remove_stomp_prop(object room)
{
    int        stomp_value = room->query_prop(AOD_I_STOMP_PROP);

    if (stomp_value)
    {
        room->add_prop(AOD_I_STOMP_PROP, stomp_value - 1);
    }
} /* remove_stomp_prop */


/*
 * Function name:        allow_stomp
 * Description  :        remove the prop that prevents players from
 *                       performing the ogrestomp.
 * Arguments    :        object player - the player object
 */
public void
allow_stomp(object player)
{
    if (objectp(player))
    {
        player->add_prop(AOD_I_STOMP_PROP, 0);
        player->catch_tell("Your legs feel stomp-worthy again!\n");
    }
} /* allow_stomp */

/*
 * Function name:   delay_stomp
 * Description:     Adds a crude prep time to the ogrestomp.
 * Arguments:        object player - the player object
 */
public int
delay_stomp(string arg)
{
    notify_fail("You are already preparing to stomp the ground.\n");
    if (get_alarm(Delay_Stomp))
        return 0;
    
    if (PVP_ABILITY_DISABLED)
    {
        notify_fail("Divine intervention prevents you from performing "
        + "this action.\n");
        return 0;
    }
    
    if (arg)
    {
        notify_fail("Huh ... ? No need to specify a target, just"
          + " <ogrestomp> and you'll hit the ground!\n");
        return 0;
    }

    if (this_player()->query_prop(AOD_I_STOMP_PROP))
    {
        notify_fail("Your legs are still too sore to do another"
          + " ogrestomp.\n");
        return 0;
    }
    
    this_player()->add_prop(AOD_I_STOMP_PROP, environment(this_player()));
    
    this_player()->catch_msg("You raise your foot high in order to cause a "
    + "quake.\n");
    say(QCTNAME(this_player()) + " raises " + this_player()->query_possessive()
    + " massive foot high in order cause a quake.\n");
    
    Delay_Stomp = set_alarm(3.0, 0.0, &ogrestomp(arg));
    return 1;
} /* delay_stomp */


/*
 * Function name:        know_election
 * Description  :        Allow ogres to check the amount of time
 *                       remaining until the next election of new
 *                       officers. This is also a useful way of
 *                       allowing players to trigger the event itself
 *                       without having to return to the Repository.
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
know_election(string arg)
{
    int     duedate;
    string  chief;

    setuid();
    seteuid(getuid());

    chief = AOD_MASTER->get_info(REPOSITORY_FILE, "GENERAL");

    if (chief && chief != NOT_YET_ASSIGNED)
    {
        duedate = AOD_MASTER->check_leader_update() - time();

        write("\n"
          + sprintf("%|80s", "The Darklings will assign new officers in:\n")
          + sprintf("%|80s", CONVTIME(duedate) + "\n"));
    }
    else
    {
        write(sprintf("%|80s",
            "The first Harvester of 10,000 skulls will become Headhunter"
          + " General!"));
    }

    return 1;
} /* know_election */


/*
 * Function name:        bust_boulder
 * Description  :        Allow Ogres to break boulders apart, so that
 *                       they can use the shards as really crappy
 *                       knives.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success
 *                           0 - failure
 */
public int
bust_boulder(string arg)
{
    object    obj,
              piece,
              knife;
    int       i, n;

    setuid();
    seteuid(getuid());

    if (!strlen(arg))
    {
        notify_fail("Bust what apart?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o [apart]", obj))
    {
        if (!obj)
        {
            notify_fail("You don't have such a thing in your"
              + " possession.\n");
            return 0;
        }

        notify_fail("What do you want to bust apart?\n");
        return 0;
    }

    if (!obj->id("boulder"))
    {
        notify_fail("Hmmm ... you really only feel like busting"
          + " boulders. The " + obj->short() + " isn't going to"
          + " work.\n");
        return 0;
    }

    write("Lifting the " + LANG_SHORT(obj) + " to eye-level, you give"
      + " it a good headbut. CRACK!!! The " + LANG_SHORT(obj)
      + " fragments into lots of little pieces which fly to the"
      + " ground!\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " lifts " + obj->short() + " to eye level, and stares at it"
      + " blankly for a few seconds. Suddenly, "
      + this_player()->query_pronoun() + " lunges forward, to"
      + " shatter it with a devastating head butt! CRACK!!! The "
      + LANG_SHORT(obj) + " fragments into lots of little pieces"
      + " which fly to the ground.\n", this_player());

    for (i = 0, n = random(4) + 3; i < n; i++)
    {
        piece = clone_object(AOD_OBJ_DIR + "boulder_fragment");
        piece->move(environment(this_player()));
    }

    knife = clone_object(AOD_WEP_DIR + "boulder_knife");
    knife->move(environment(this_player()));

    obj->remove_object();
    return 1;
} /* bust_boulder */


/*
 * Function name:        ogre_buttkick
 * Description  :        allow the general to use his special combat
 *                       ability, thus boosting the power of his Ogre
 *                       teammates. See tax_doc.txt for details.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 success, 0 failure
 */
public int
ogre_buttkick(string arg)
{
    object  *team_members;
    int      i, n,
             lastkick;

    if (!AOD_GENERAL(this_player()) && !AOD_CORPORAL(this_player()) )
    {
        notify_fail("You wish! You aren't General or Corporal!\n");
        return 0;
    }

    if (!strlen(arg) || arg != "team")
    {
        notify_fail("You can <buttkick team> if you want. Is that what"
          + " you want?\n");
        return 0;
    }

    /* We only allow buttkicking every 10 minutes.
     */
    lastkick = time() - AOD_MASTER->get_info(this_player(), "Last_Buttkick");
    if (lastkick < 600)
    {
        TELL_G("Last buttkick was " + (time() - AOD_MASTER->get_info(
            this_player(), "Last_Buttkick")) + " seconds ago.");

        if (lastkick < 60)
        {
            notify_fail("You are already kicking some serious butt!\n");
            return 0;
        }

        notify_fail("Your kicking foot is still too sore! Better wait"
          + " a while longer.\n");
        return 0;
    }

    team_members = this_player()->query_team_others();

    if (!sizeof(team_members))
    {
        notify_fail("You are not teamed up with anyone! No butts to"
          + " kick!\n");
        return 0;
    }

    /* Lets make sure there are Ogres on the team, and that they are in
     * the same room as the General.
     */
    for (n = 0, i = 0; i < sizeof(team_members); i++)
    {
        TELL_G("i = " + i);
        TELL_G("team_members["+i+"] = " + team_members[i]->query_real_name());
        if (IS_OGRE(team_members[i]) && environment(team_members[i]) ==
            environment(this_player()))
        {
            n++;
        }
    }

    if (!n)
    {
        notify_fail("There are no Ogre butts in the area!\n");
        return 0;
    }

    /* Looks like all is in place for some serious butt-kicking. Proceed! */

    write("Butt-kicking time!! You start \"motivating\" your team, Ogre-"
      + "style!\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " roars in anger and begins kicking everyone forcefully in the"
      + " butt! LOOK OUT!!\n", this_player());

    /* Set the time in the playerfile when this most recent buttkicking
     * session took place.
     */
    AOD_MASTER->set_info(this_player(), "Last_Buttkick", time());

    /* Now, we set the Buttkick status in the playerfile of each Ogre
     * team member to 1 so that they get the combat benefit. To do this,
     * we call a function that is in the shadow for each player.
     */
    for (n = 0, i = 0; i < sizeof(team_members); i++)
    {
        if (IS_OGRE(team_members[i]))
        {
            team_members[i]->get_buttkicked(this_player());
            TELL_G("set general to " + this_player()->query_real_name());
        }
    }

    set_alarm(60.0, 0.0, &stop_buttkicking(this_player()));
    set_alarm(600.0, 0.0, &write("Your foot ... its back in shape! Butts"
      + " must be kicked!\n"));

    return 1;
} /* ogre_buttkick */


/*
 * Function name:        stop_buttkicking
 * Description  :        Send the message that the buttkicking has come
 *                       to an end for now.
 * Arguments    :        object player - who was buttkicking
 */
public void
stop_buttkicking(object player)
{
    player->catch_tell("Arrgh! Your foot is getting sore. Better let it"
      + " rest for a while. No more buttkicking for now.\n");
    tell_room(environment(player), QCTNAME(player)
      + " gives " + player->query_possessive() + " aching foot a break"
      + " and brings the buttkicking to a halt for now.\n", player);
} /* stop_buttkicking */


/*
 * Function name:        ogre_report
 * Description  :        Allow Ogres to report an item that they feel should
 *                       be something they can wield or wear for quest
 *                       purposes. Ogres are restricted from wearing any
 *                       equipment not made by the forge or from wielding
 *                       anything that is not two handed. When reported,
 *                       the file name of the item will appear in the log:
 *
 *                         /d/Emerald/common/guild/aod/log/reports
 *
 *                       If the item reported does indeed correspond to a quest
 *                       that the Ogre is being prevented from completing,
 *                       then the filename of the item should be added to the
 *                       array contained in the file:
 *
 *                         /d/Emerald/common/guild/aod/exceptions.h
 *
 * Arguments    :        string arg - whatever was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
ogre_report(string arg)
{
    object  obj;

    if (!strlen(arg))
    {
        notify_fail("What item do you wish to ogrereport?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o", obj))
    {
        if (!obj)
        {
            notify_fail("You don't have such a thing in your"
              + " possession.\n");
            return 0;
        }

        notify_fail("What do you wish to ogrereport?\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    write_file(AOD_LOG_DIR + "reports",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " "
      + capitalize(this_player()->query_name()) + " reported -- "
      + MASTER_OB(obj) + "\n");

    write("You smash the " + obj->short() + " against your thick skull a"
      + " few times. Somehow, you feel the Darklings will know of your"
      + " frustration.\n");
    return 1;
} /* ogre_report */


/*
 * Function name:        npc_report
 * Description  :        Allow Ogres to report quest npcs that do not
 *                       seem to accept their all-caps dialogue. Reports
 *                       are written to the file:
 *
 *                         /d/Emerald/common/guild/aod/log/npc_reports
 *
 *                       It will then be necessary to look at the code
 *                       of the reported npcs and make sure that their
 *                       quest parsing code uses a lower_case() call.
 *
 * Arguments    :        string arg - whatever was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
npc_report(string arg)
{
    object  obj;

    if (!strlen(arg))
    {
        notify_fail("Who do you wish to npcreport?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(environment(this_player())),
        "[the] %o", obj))
    {
        if (!obj)
        {
            notify_fail("There is no such npc to report.\n");
            return 0;
        }

        notify_fail("Who do you wish to npcreport?\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    write_file(AOD_LOG_DIR + "npc_reports",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " "
      + capitalize(this_player()->query_name()) + " reported -- "
      + MASTER_OB(obj) + "\n");

    write("You stare really hard at " + obj->query_the_name() + " and"
      + " try to think hard about the problem. You endure this process"
      + " for as long as you are able (about three seconds) and then"
      + " belch loudly. You somehow feel that the Darklings will hear"
      + " your prayer, and know of your problem with this person.\n");
    return 1;
} /* npc_report */
