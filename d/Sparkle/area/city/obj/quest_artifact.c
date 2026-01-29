/*
 *  /d/Sparkle/area/city/obj/quest_artifact.c
 *
 *  This object is designed to make more interesting and rewarding the
 *  efforts players expend to solve quests in the game. It is a jeweled
 *  pendant worn around the neck. The various facets of the jewel show
 *  the name of each domain, along with the number of quests remaining
 *  to be solved in that domain. If all quests in a domain are solved,
 *  the facet is pure and glitters with an asterix.
 *
 *  Rewards via additional powers and specials are doled out as players
 *  complete all the quests in a given domain, as follows:
 *
 *    Domains Complete:      Reward:
 *    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 1.        TBA
 *                 2.        TBA
 *                 3.        TBA
 *                 4.        TBA
 *                 5.        TBA
 *                 6.        TBA
 *                 7.        TBA
 *                 8.        TBA
 *                 9.        TBA
 *                10.        TBA
 *                11.        TBA
 *                12.        TBA
 *                13.        TBA
 *                14.        TBA
 *
 *  The above powers will only function as players add to their count
 *  of fully-solved domains. This will serve two functions - rewarding
 *  players for their hard work, and alerting players when new quests
 *  are added to the realms (i.e. powers will be re-locked.) 
 *
 *  NOTA BENE: There are three empty facets in the gem to leave room
 *             for potential new domains in the game. Should they be
 *             added, alterations will need to be made to this item
 *             to integrate functionality. Also, new powers will need
 *             to be added to the above list. Maybe we don't need any
 *             new domains!! *grin*
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 *
 *    Much thanks to Petros' fantastic quest_orb.c functionality,
 *    which ended up being the basis for much of the workings here.
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <composite.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

inherit QUEST_VALIDATION;

/* Definitions */
#define           QUEST_ARTIFACT_ID    "_global_quest_artifact"

/* Global Variables */
/*           Note: currently we do not include Cirath. It has no quests.
 */
mapping      Unsolved_Mapping = ([
                                "ansalon"   : 0,
                                "avenir"    : 0,
                                "calia"     : 0,
                                "earthsea"  : 0,
                                "emerald"   : 0,
                                "faerun"    : 0,
                                "gondor"    : 0,
                                "kalad"     : 0,
                                "khalakhor" : 0,
                                "krynn"     : 0,
                                "raumdor"   : 0,
                                "shire"     : 0,
                                "sparkle"   : 0,
                                "terel"     : 0,
                             ]);
string     *Pendant_Powers = ({
                                "Level 1 power",
                                "Level 2 power",
                                "Level 3 power",
                                "Level 4 power",
                                "Level 5 power",
                                "Level 6 power",
                                "Level 7 power",
                                "Level 8 power",
                                "Level 9 power",
                                "Level 10 power",
                                "Level 11 power",
                                "Level 12 power",
                                "Level 13 power",
                                "Level 14 power",
                             });


/* Prototypes */
public void        create_object();
public string      display_facets();
public string      describe();
public string      df(string which);
public mapping     get_player_bits(string domain, object player);
public int         unsolved_in_domain(string domain, object player);
public int         validate_quest(object player, string * details,
                                  mapping set_bits);
public int         check_unsolved(string domain, object player,
                                  string * details,
                                  mapping set_bits);
public void        init_unsolved_mapping(object who);
public mapping     query_unsolved() { return Unsolved_Mapping; }
public int         finished_domains();
public void        init();
public int         display_powers(string arg);
public int         pendant_link(string arg);
public int         pendant_check(string arg);
public void        enter_env(object dest, object old);


/*
 * Function name:        create_object
 * Description  :        the constructor
 */
public void
create_object()
{
    set_name(QUEST_ARTIFACT_ID);
    add_name( ({ "pendant" }) );

    set_short("glittering pendant");
    add_adj( ({ "glittering" }) );

    set_long(describe);

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 10);
//  add_prop(OBJ_M_NO_DROP, "The pendant is soulbound to you and cannot"
//    + " be discarded or given away.\n");

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        display_facets
 * Description  :        This routine prints out the display in ascii
 *                       of the pendant's jewel. Each facet of the
 *                       jewel will display the name of one of the
 *                       domains in Genesis, along with the number of
 *                       quests a player has remaining to solve there.
 *                       If all quests are solved, the facet is empty.
 * Returns      :        string - the text to display.
 *
 * Nota Bene: The ascii text is a disaster to try to read here in the
 *            code itself. I thought this was the easier way to implement
 *            rather than dealing with a text file and then keeping track
 *            of coordinates. So ... apologies for the eye-strain below!
 *
 *            Tips for future needs of modification:
 *               \\   - becaase "\" is an escape character, it must be
 *                      doubled to display properly for the ascii here.
 *               df() - this is a call to a function that displays
 *                      the correct domain name or quest number remaining
 *                      and inserted into the ascii image.
 *                      args: domain name - for the name  (e.g. "shire")
                              name + _n   - for quest num (e.g. "shire_n")
 */
public string
display_facets()
{
    string   pendant_txt = "\n";
    string   extraline;
    int      done = finished_domains();
    string  *pendant = ({
"                           __________________________",
"                         .' |                      | `.",
"                       .'"+df("terel_n")+" |          "+df("ansalon_n")+"          |   `.",
"                     .'"+df("terel")+"|        "+df("ansalon")+"       |     `.",
"                   .'_______|______________________|_______`.",
"                  /        /\\                      /\\        \\",
"                 /        /  \\                    /  \\        \\",
"                /        /    \\                  /    \\        \\",
"               /  "+df("calia_n")+"    /      \\     "+df("krynn")+"      /      \\    "+df("emerald_n")+"  \\",
"              /        /        \\              /        \\        \\",
"             / "+df("calia")+"  /          \\     "+df("krynn_n")+"     /          \\"+df("emerald")+" \\",
"            /        /            \\          /            \\        \\",
"           /        /      "+df("avenir_n")+"      \\        /      "+df("raumdor_n")+"      \\        \\",
"          /        /                \\      /                \\        \\",
"         |`.      /      "+df("avenir")+"      \\    /      "+df("raumdor")+"     \\      .'|",
"         |  `.   /                    \\  /                    \\   .'  |",
"         |    `./______________________\\/______________________\\.'    |",
"         |    .'\\                      /\\                      /`.    |",
"         |  .'   \\                    /  \\                    /   `.  |",
"         |.'      \\     "+df("khalakhor")+"    /    \\     "+df("earthsea")+"     /      `.|",
"          \\        \\                /      \\                /        /",
"           \\        \\      "+df("khalakhor_n")+"      /        \\      "+df("earthsea_n")+"      /        /",
"            \\        \\            /          \\            /        /",
"             \\ "+df("sparkle")+"\\          /     "+df("gondor_n")+"     \\          / "+df("kalad")+"  /",
"              \\        \\        /              \\        /        /",
"               \\  "+df("sparkle_n")+"    \\      /     "+df("gondor")+"     \\      /    "+df("kalad_n")+"  /",
"                \\        \\    /                  \\    /        /",
"                 \\        \\  /                    \\  /        /",
"                  \\________\\/______________________\\/________/",
"                   `.       |                      |"+df("faerun")+" .'",
"                     `.     |         "+df("shire")+"        | "+df("faerun_n")+"  .'",
"                       `.   |          "+df("shire_n")+"          |   .'",
"                         `._|______________________|_.'",
                       });

    foreach (string pend_line : pendant)
    {
        pendant_txt += pend_line + "\n";
    }

    return pendant_txt + "\n";
} /* display_facets */


/*
 * Function name:        describe
 * Description  :        What the player gets when they <exa pendant>
 *                       and trigger the long_desc() function.
 * Returns      :        string - the description
 */
public string
describe()
{
    string   extraline;
    int      done = finished_domains();

    extraline = "Each facet of the jewel upon your pendant is connected"
      + " to a particular orb in the Tower of Realms, and will display"
      + " the number of quests you have yet to solve. When all are"
      + " solved, that facet will glitter. Currently, "
      + ((done == 0) ? "none" : LANG_NUM2WORD(done)) + " of the"
      + " facets " + ((done == 1) ? "is" : "are") + " glittering.\n\n"
      + "    <pendantlist>  - learn of powers the pendant is"
      + " granting you.\n"
      + "    <pendantlink>  - at a quest orb to update your quests in"
      + " a given domain.\n"
      + "    <pendantcheck> - display the facets of the pendant.\n";

    return extraline;
} /* describe */


/*
 * Function name:        df
 * Description  :        The function name df is abbreviated for
 *                       display_facet, but is shortened to facilitate
 *                       the construction of ascii in the previous
 *                       function. Here, we take arguments of the
 *                       domain_name for the name itself or the
 *                       domain_name_n for the domain number of quests
 *                       remaining to be solved, and then display
 *                       accordingly.
 * Arguments    :        string which: the domain or num to display
 * Returns      :        string - the correct text to insert into the
 *                                ascii display for the pendant.
 */
public string
df(string which)
{
    string *domain_arr = explode(which, "_");
    string  domain = domain_arr[0];
    string  q_num;

    q_num = Unsolved_Mapping[domain] + "";

    if (sizeof(domain_arr) > 1)
    {
        if (!atoi(q_num))
        {
            return " *";
        }

        if (strlen(q_num) == 1)
        {
            return " " + q_num;
        }

        return q_num;
    }

    if (!atoi(q_num))
    {
        return " " * strlen(domain);
    }

    return capitalize(domain);
} /* df */


/* Function name:       get_player_bits
 * Description  :       checks all the bits in the domain to see
 *                      what bits have been set in the player
 * Arguments    :       domain - domain to check quests in
 *                      player - player to test bits in
 * Returns      :       mapping - bitnumber -> 1/0
 */
public mapping
get_player_bits(string domain, object player)
{
    int bitindex;
    mapping player_bits = ([]);
    
    bitindex = 0;
    for (int group = 0; group < 4; ++group)
    {
        for (int curbit = 0; curbit < 20; ++curbit)
        {
            player_bits[bitindex] = 0;
            if (player->test_bit(domain, group, curbit))
            {
                player_bits[bitindex] = 1;
            }            
            ++bitindex;
        }
    }
    
    return player_bits;
} /* get_player_bits */


/* Function name:       unsolved_in_domain
 * Description  :       Discover how many unsolved quests remain
 *                      in this domain for this player.
 * Arguments    :       domain - domain to check quests in
 *                      player - player to test bits in
 * Returns      :       the number of unsolved quests in this domain
 */
public int
unsolved_in_domain(string domain, object player)
{
    string     description;
    mixed     *quests;
    int        unsolved_quests = 0;
    mapping    set_bits;
    
    set_bits = get_player_bits(domain, player);
    
    quests = QUEST_CONTROL_ROOM->get_quests(domain);

    foreach (string * details : quests)
    {
        unsolved_quests += check_unsolved(domain, player,
                                          details, set_bits);
    }
    
    return unsolved_quests;
} /* unsolved_in_domain */


public int
validate_quest(object player, string * details, mapping set_bits)
{
    if (details[5] == "default")
    {
        return 1;
    }

    return 0;
} /* validate_quest */


/*
 * Function name:        check_unsolved
 * Description  :        This is the function that actually does the
 *                       testing of the bits. It returns 0
 *                       if the player has done the quest
 *                       or 1 if not.
 * Arguments    :        player - the person checking his quest status
 *                       details - the detail array of the quest
 *                       set_bits - mapping of player set bits
 * Returns      :        0 - solved, 1 - unsolved
 */
public int
check_unsolved(string domain, object player, string * details, mapping set_bits)
{
    /* Array is listed as follows
     * [0] - Domain
     * [1] - Short Description
     * [2] - Group Number
     * [3] - Bit Number
     * [4] - Validation Function for this Quest
     */

    int    valid_quest;
    int    group, bit, bitindex;
    
    group = atoi(details[2]);
    bit   = atoi(details[3]);
    valid_quest = validate_quest(player, details, set_bits);

    if (!valid_quest)
    {
        return 0;
    }    

    if (player->test_bit(domain, group, bit))
    {
        return 0;
    }

    return 1;
} /* check_unsolved */


/*
 * Function name:        init_unsolved_mapping
 * Description  :        populate the unsolved mapping with the
 *                       number of unsolved quests for this player
 *                       for each domain.
 * Arguments    :        object who - who to do it for
 */
public void
init_unsolved_mapping(object who)
{
    foreach(string domain : m_indices(Unsolved_Mapping))
    {
        Unsolved_Mapping[domain] = unsolved_in_domain(domain, who);
    }
} /* init_unsolved_mapping */


/*
 * Function name:        finished_domains
 * Description  :        return the number of domains within which
 *                       the player has solved all available quests.
 * Returns      :        int - the number of finished domains
 */
public int
finished_domains()
{
    int    finished = 0;

    foreach(string domain : m_indices(Unsolved_Mapping))
    {
        if (!Unsolved_Mapping[domain])
        {
            finished++;
        }
    }

    return finished;
} /* finished_domains */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    add_action(display_powers, "pendantlist");
    add_action(pendant_link, "pendantlink");
    add_action(pendant_check, "pendantcheck");

    ::init();
} /* init */


/*
 * Function name:        display_powers
 * Description  :        List the powers the pendant has granted
 *                       us so far.
 * Arguments    :        string arg - what was typed
 * Returns      :        int - 1 success always
 */
public int
display_powers(string arg)
{
    int      i;
    int      done = finished_domains();
    string  *valid_domains = ({ });

    write("For each domain in which you have solved every available"
      + " quest, one of the facets on the pendant will begin to"
      + " glitter. Each glittering facet increases the powers"
      + " granted to you by the pendant.");

    if (done)
    {
        foreach(string domain : m_indices(Unsolved_Mapping))
        {
            if (!Unsolved_Mapping[domain])
            {
                valid_domains += ({ capitalize(domain) });
            }
        }
    }
    else
    {
        write("\n\nYour pendant does not have any facets which"
          + " glitter. You will need to complete all quests in"
          + " one of the domains in the realm to change that.\n");
        return 1;
    }

    write(" Powers your pendant now gives you include:\n\n");

    for (i = 0; i < done; i++)
    {
        write("\t - " + Pendant_Powers[i] + "\n");
    }

    write("\nThese powers are currently available to you in the "
      + ((done > 1) ? "lands" : "land") + " of "
      + COMPOSITE_WORDS(valid_domains) + ".\n");

    return 1;
} /* display_powers */


/*
 * Function name:        pendant_link
 * Description  :        allow players to update the pendant's
 *                       knowledge of their number of unfinished
 *                       quests in a given domain by linking it
 *                       with the appropriate quest orb in the
 *                       tower of realms.
 * Arguments    :        what the player typed (unused)
 * Returns      :        int 1 - success, 0 - failure (no orb)
 */
public int
pendant_link(string arg)
{
    write("Coming soon.\n");
    return 1;
} /* pendant_link */


/*
 * Function name:        pendant_check
 * Description  :        allow players to get a display of the
 *                       facets of the pendant to see how many
 *                       quests they need to solve in each domain.
 * Arguments    :        what the player typed (unused)
 * Returns      :        int 1 - success, 0 - failure (no orb)
 */
public int
pendant_check(string arg)
{
    write(display_facets());
    return 1;
} /* pendant_check */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 * We mask this to have the pendant update whenever it enters the
 * environment of a player.
 */
public void
enter_env(object dest, object old)
{
    init_unsolved_mapping(dest);

    ::enter_env(dest, old);
} /* enter_env */
