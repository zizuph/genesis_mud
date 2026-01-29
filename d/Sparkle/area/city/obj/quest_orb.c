/*
 * /d/Sparkle/area/city/obj/quest_orb.c
 *
 * Orb that tells a player what quests he has done in
 * a particular domain
 *
 * Created April 2008, by Petros
 *
 *
 *
 * INSTRUCTIONS FOR USE:
 * 1. Clone the object in the room that you want it in
 * 2. call set_orb_domain("domain name")
 *    eg. set_orb_domain("Sparkle")
 * 3. Optional: Add an extra line to the end of the description
 *    eg. set_extra_line("The orb sits on the large oak desk.")
 *
 * If you have quests, make sure they get added to the questdb
 * file. If a quest has a validation function, make sure that you
 * create your own validation file, and inherit it in this file.
 * see QUEST_VALIDATION for an example of how to do this.
 *
 * Modification Log:
 *   9/27/2008 - Modified so that Calia orb has hints enabled. (Petros)
 *   7/10/2020 - Modified so that Cirath orb has hints enabled. (Mirandus)
 */
 
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

#include "../defs.h"

// Inherits for Validation Functions
inherit QUEST_VALIDATION;

// Defines
#define COL_DOMAIN      0
#define COL_DESC        1
#define COL_GROUP       2
#define COL_BIT         3
#define COL_HINT        4
#define COL_VALIDATION  5
#define COL_ARGUMENTS   6
#define COL_LAST        COL_VALIDATION

#define NUM_GROUPS          4
#define NUM_BITS_PER_GROUP  20

#define QUEST_DO_NOT_SHOW       -1
#define QUEST_INELIGIBLE         0
#define QUEST_ELIGIBLE           1
#define QUEST_ALWAYS_SHOW        2

#define DASHES "----------------------------------"

// Global Variables
string Domain;
string Extraline;


// Prototypes
public void             create_object();
public string           orb_description();
public void             set_orb_domain(string domain);
public void             set_extra_line(string extradesc);
public int              quests_cmd(string arg);
public int              hint_cmd(string arg);
public string           format_description(object player, 
                                           string * details,
                                           mapping set_bits);
public void             print_quests(string * quests, string domain);
public void             print_quests_for_player(string domain, 
                                                object player);
public void             log_quest_request(string domain, object player,
                                          mapping set_bits);
public int              hints_enabled();                                          
public string           query_orb_domain() { return Domain; }




/*
 * Function name:       create_object
 * Description  :       creates the object.
 */
public void
create_object()
{
    set_name("_genesis_quest_orb");
    add_name( ({"genesis_quest_orb", "orb" }) );
    add_adj( ({ "dark", "crystal" }) );

    set_short("dark crystal orb");    
    set_long("@@orb_description@@");

    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_SELL, "This is much too valuable to sell!\n"); 
    add_prop(OBJ_M_NO_GET, "As hard as you try, you just cannot get the "
                         + "orb.\n");    


    // These lines are necessary for loading the quest control room
    // since we access it implicitly
    setuid(); 
    seteuid(getuid());
    
} // create_object





/* Function name:       orb_description
 * Description  :       Returns the long description for the quest orb
 */
public string
orb_description()
{
    string desc;
    
    desc = "Before you is an orb of dark crystal. Within its center,"
         + " you glimpse milky wisps of truth which swim lazily before"
         + " your eyes. You may type <quests> here to know those tasks"
         + " which you have mastered within the lands of " 
         + capitalize((Domain ? Domain : "Sparkle"))
         + ". ";
         
    if (hints_enabled())
    {
        desc += "You can also type <hint quest_number> to discover useful "
              + "information about each quest. "; 
    }     
    
    desc += (Extraline ? Extraline : "") + "\n";
         
    return desc;
}




/* Function name:       init
 * Description  :       adds the action
 */
public void
init()
{
    ::init();    
    
    add_action(quests_cmd, "quests");
    add_action(hint_cmd, "hint");
    if (this_player()->query_wiz_level())
    {
        add_action(quests_cmd, "questcheck");
    }
} // init




/* Function name:       set_orb_domain
 * Description  :       Sets up the domain that this orb will look
 *                      at. Must be called after cloning.
 */
public void
set_orb_domain(string domain)
{
    Domain = domain;
}




/* Function name:       set_extra_line
 * Description  :       An added description at the end so that
 *                      each domain can customize how it looks
 *                      in the room.
 */
public void
set_extra_line(string extradesc)
{
    Extraline = extradesc;
}




/* Function name:       parse_bit_number
 * Description  :       
 *                      
 *                      
 */
private string
parse_bit_number(int bitindex)
{
    string result = "";
    int group, remainder;
    
    remainder = bitindex % NUM_BITS_PER_GROUP;
    group = (bitindex - remainder) / NUM_BITS_PER_GROUP;
    result += group + ":" + remainder;
    return result;
}




/* Function name:       log_quest_request
 * Description  :       Logs the usage of the quest orb
 * Arguments    :       domain - domain to check quests in
 *                      player - player to test bits in
 *                      set_bits - bits that have been set in player
 * Returns      :       nothing
 */
public void
log_quest_request(string domain, object player, mapping set_bits)
{
    string log_message;
    string hanging_bits;

    log_message = ctime(time());
    if (this_player() == player)
    {
        log_message += " " + capitalize(player->query_real_name()) + " "
                     + "requested quest data for the domain " 
                     + capitalize(domain) + ".\n";
    }
    else
    {
        log_message += " " + capitalize(this_player()->query_real_name())
                     + " requested quest data for the player "
                     + capitalize(player->query_real_name()) + " for the "
                     + "domain " + capitalize(domain) + ".\n";
    }
    
    // We go through all the set_bits to see which quests are possibly
    // missing from the questdb. If there are bits set in the player
    // which are not described, it will add a line to the log message
    hanging_bits = "";
    foreach (int bitindex : m_indices(set_bits))
    {
        if (set_bits[bitindex] == 1)
        {
            hanging_bits += " " + parse_bit_number(bitindex) + " ";
        }
    }
    if (hanging_bits != "")
    {
        hanging_bits = ctime(time()) + " " 
                     + capitalize(player->query_real_name())
                     + " has bits set for the " + capitalize(domain)
                     + " domain which do not correspond to quests in "
                     + " the questdb: " + hanging_bits + "\n";
        log_file(QUEST_ORB_ERRORS, hanging_bits);
    }
    log_file(QUEST_ORB_LOG, log_message);
}




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
    for (int group = 0; group < NUM_GROUPS; ++group)
    {
        for (int curbit = 0; curbit < NUM_BITS_PER_GROUP; ++curbit)
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
}




/* Function name:       get_eligible_quests
 * Description  :       Helper function to assist in retrieving
 *                      all the quests the player is eligible for
 *                      in a particular domain. Used for both printing
 *                      and giving hints
 * Arguments    :       domain - domain to check quests in
 *                      player - player to test bits in
 * Returns      :       subset of the quests that they're eligible for
 */
public mixed
get_eligible_quests(string domain, object player)
{
    string description;
    mixed * quests;
    mixed * eligible_quests;
    mapping set_bits;
    
    set_bits = get_player_bits(domain, player);
    
    quests = QUEST_CONTROL_ROOM->get_quests(domain);
    eligible_quests = ({ });
    foreach (string * details : quests)
    {
        description = format_description(player, details, set_bits);
        if (description == "")
        {
            continue;
        }
        eligible_quests += ({ details });
    }
    
    return eligible_quests;
}




/* Function name:       print_quests_for_player
 * Description  :       Helper function to assist in the actual
 *                      printing of the quest information. this
 *                      is useful for debugging purposes.
 * Arguments    :       domain - domain to check quests in
 *                      player - player to test bits in
 * Returns      :       nothing
 */
public void
print_quests_for_player(string domain, object player)
{
    mapping set_bits = get_player_bits(domain, player);    
    // Get the eligible quests for this domain/player combination
    string * eligible_quests = get_eligible_quests(domain, player);
    string * descriptions = ({ });
    foreach (string * details : eligible_quests)
    {
        descriptions += ({ format_description(player, details, set_bits) });
    }
    print_quests(descriptions, domain);
    
    // Log the quest request to keep statistics on how often
    // the orb is being used.
    log_quest_request(domain, player, set_bits);
}




/* Function name:       hint_cmd
 * Description  :       This command gives the player a bit of hint
 *                      to get started on the quests that they do
 *                      not know about.
 * Arguments    :       arg - parameters
 * Returns      :       0/1 - whether command was successful.
 */
public int
hint_cmd(string arg)
{
    mixed  * eligible_quests;
    string * details;
    string   domain, hint_info, description; 
    int      quest_number;
    
    if (!hints_enabled())
    {
        notify_fail("This quest orb does not yet contain any hint "
                  + "information.\n");
        return 0;
    }
    
    if (!arg)
    {
        notify_fail("Usage: hint <quest number>\n");
        return 0;
    }
    
    quest_number = atoi(arg);
    if (quest_number <= 0)
    {
        notify_fail("Usage: hint <quest number>\n");
        return 0;
    }
    
    domain = lower_case(Domain ? Domain : "sparkle");    
    eligible_quests = get_eligible_quests(domain, this_player());    
    
    if (sizeof(eligible_quests) < quest_number)
    {
        notify_fail("There is no quest with that number.\n");
        return 0;
    }

    details = eligible_quests[quest_number - 1];    
    hint_info = details[COL_HINT];
    if (hint_info == "")
    {
        notify_fail("Peering into the orb, you don't sense anything "
                  + "helpful for quest #" + quest_number + ".\n\n");
        return 0;
    }
    
    description = format_description(this_player(), details, ([ ]));
    if (description == details[COL_DESC])
    {
        write("Peering into the orb, you realize you have already "
            + "completed quest #" + quest_number + ", but you see "
            + "the following:\n\n");
    }
    else
    {
        write("Peering into the orb, you sense the following about "
            + "quest #" + quest_number + ":\n\n");
    }
    write(hint_info + "\n\n");
    return 1;
}




/* Function name:       quests_cmd
 * Description  :       This function tests the bits in the player
 *                      and reports back to the player
 * Arguments    :       arg - parameters
 * Returns      :       0/1 - whether command was successful.
 */
public int
quests_cmd(string arg)
{
    string domain;
    object player;
    
    // Domain always defaults to Sparkle.
    domain = lower_case(Domain ? Domain : "sparkle");
    
    if (!IN_ARRAY(domain, QUEST_CONTROL_ROOM->get_domains()))
    {
        notify_fail("The quest orb does not contain information for "
                  + "the " + capitalize(domain) + " domain.\n");
        return 0;
    }
    
    // This is a command that should be used sparingly to check
    // player's completed quests. It's in here mostly as a testing
    // tool.
    if (query_verb() == "questcheck"
        && this_player()->query_wiz_level() 
        && arg && arg != "")
    {
        player = find_living(lower_case(arg));
        if (!player)
        {
            write("No player named " + capitalize(arg) + " is currently "
                + "in the game.\n");
            return 1;
        }
        print_quests_for_player(domain, player);
        return 1;
    }
    
    // This is the default behavior for mortals.
    print_quests_for_player(domain, this_player());
    
    return 1;
}




public int
validate_quest(object player, string * details, mapping set_bits)
{
    // Return values and their meanings
    // -1 : Never display this quest even if the bit is set
    //  0 : Only display this quest if it is finished
    //  1 : Quest is valid. Display --- if not finished, and normal text
    //      if it is
    //  2 : Display as 1, but don't test the bit
    
    if (details[COL_VALIDATION] == "default")
    {
        return QUEST_ELIGIBLE;
    }
    
    if (sizeof(details) <= COL_LAST)
    {
        // This is a normal call for a quest that has
        // not defined arguments for its validation
        // function
        return call_other(this_object(), details[COL_VALIDATION], player);
    }
    
    // For quest lines that have arguments, we implode the arguments
    // and send them to the validation function
    return call_other(this_object(), details[COL_VALIDATION], player, 
                      details[COL_DOMAIN], 
                      implode(details[COL_ARGUMENTS..], ","), set_bits);
}




/*
 * Function name:        format_description
 * Description  :        This is the function that actually does the
 *                       testing of the bits. It returns the short 
 *                       description if the player has done the quest
 *                       or dashes if they have not. It returns the
 *                       description in parentheses if it's a wizard
 *                       viewing the orb
 * Arguments    :        player - the person checking his quest status
 *                       details - the detail array of the quest
 *                       set_bits - mapping of player set bits
 * Returns      :        the formatted description
 */
public string
format_description(object player, string * details, mapping set_bits)
{
    // Array is listed as follows
    // [0] - Domain
    // [1] - Short Description
    // [2] - Group Number
    // [3] - Bit Number
    // [4] - Hints
    // [5] - Validation Function for this Quest
    string result = "";
    int    valid_quest;
    int    group, bit, bitindex;
    
    group = atoi(details[COL_GROUP]);
    bit   = atoi(details[COL_BIT]);
    valid_quest = validate_quest(player, details, set_bits);
    if (valid_quest == QUEST_DO_NOT_SHOW)
    {
        // if the validation function returns -1, that means do not
        // display no matter what.
        return result;
    }
    else if (valid_quest == QUEST_ALWAYS_SHOW)
    {
        // Put this before the next if statement so that even if
        // the player is no longer eligible for the quest, it shows
        // up because they did it when they were eligible
        result = details[COL_DESC];
    }
    else if (player->test_bit(details[COL_DOMAIN], group, bit))
    {
        // Put this before the next if statement so that even if
        // the player is no longer eligible for the quest, it shows
        // up because they did it when they were eligible
        bitindex = (group * NUM_BITS_PER_GROUP) + bit;
        set_bits[bitindex] = 0; // unset the bit
        result = details[COL_DESC];
    }
    else if (valid_quest == QUEST_INELIGIBLE)
    {
        // Did not pass validation. Simply return an empty string
        return result;
    }    
    else
    {
        // For wizzes, we want to be able to see the quest even
        // if it hasn't been done
        if (player->query_wiz_level())
        {
            result = "(" + details[COL_DESC] + ")";
        }
        else
        { 
            // 34 dashes
            result = DASHES;
        }        
    }
    return result;
}




/*
 * Function name:        print_quests
 * Description  :        output formatting function. This displays the
 *                       quests in two columns, with the numbers going
 *                       sequentially down column 1 first, then column
 *                       two.
 * Arguments    :        quests - array of the quests the user is eligible
 *                                to see.
 *                       domain - The domain that is currently being
 *                                queried.
 * Returns      :        nothing
 */
public void
print_quests(string * quests, string domain)
{
    int total, rows, leftcolumn;
    
    if (!quests)
    {
        return;
    }
    
    total = sizeof(quests);

    write("Of the " + total + " eligible quests in " + capitalize(domain)
        + ", you have completed the following:\n\n");
    rows = total / 2; // rounds down
    leftcolumn = rows + (total % 2);    
    for (int index = 0; index < rows; ++index)
    {
        write(
            sprintf("%3d: %-34s%3d: %-34s\n", index + 1, quests[index],
                leftcolumn + index + 1, quests[index + leftcolumn]));
    }
    // Finally, add the last row if the number of quests was odd. This
    // means that only column one will be printed. Nothing should be
    // there for column 2
    if (total % 2 != 0)
    {
        write(sprintf("%3d: %-34s\n", leftcolumn, quests[leftcolumn - 1]));
    }
    write("\n");
}




/*
 * Function name: hints_enabled
 * Description  : We are gradually releasing hints to orbs. To control
 *                the enabling of hints, this function will list the
 *                domains that currently have hints.
 * Arguments    : none
 * Returns      : 0/1 - disabled/enabled
 */
public int
hints_enabled()
{
    string domain;
    
    domain = lower_case(Domain);
    switch(domain)
    {
    case "emerald":
    case "sparkle":
    case "calia":
    case "cirath":
    case "avenir":
    case "gondor":
    case "shire":
    case "krynn":
    case "terel":
    case "earthsea":
    case "raumdor":
    case "faerun":
    case "kalad":
    case "ansalon":
    case "khalakhor":
        return 1;
    
    }
    
    return 0;
}
