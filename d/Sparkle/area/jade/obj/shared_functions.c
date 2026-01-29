/*
* /d/Sparkle/area/jade/npc/family.c
* A generic relative of the Runaway.
* Created 2017-01-23 by Martin Berka on Genesis MUD
*/

#include "../defs.h"
#include "../bandit_quest_constants.h"
#include <macros.h>
#include <math.h>

/* Global variables */
int     family_index;

int     runaway_role_index(string player_name, int role_ind);
string  runaway_relation(string player_name, int family_index, int invert = 0);


/*
 * Function name: hurt_message
 * Description  : Returns the message from Runaway that player must deliver to
 *          Hurt; if flag set, returns a parse_command pattern for it.
 * Arguments    : (string) player_name from query_living_name()
 *                (int) Flag to return wildmatch pattern
 * Returns      : (string) The phrase, or the wildmatch pattern to match it.
 */
varargs string
hurt_message(string player_name, int check_pattern = 0)
{
    int h_index = runaway_role_index(player_name, HURT);
    string gen =  h_index % 2 ? "he" : "she";
    switch (NAME_TO_RANDOM(player_name, HURT_IDENT, HURT_RANGE))
    {
        case 0:
            return (check_pattern ?  "*you*re the better archer*" :
                gen + "really is the better archer");
        case 1:
            return (check_pattern ?  "*was an idiot*" :
                "I was an idiot");
        case 2:
            return (check_pattern ?  "*admits that*was wrong*" :
                "I admit that I was wrong");
        case 3:
            gen = (gen == "he" ? "his" : "her");
            return (check_pattern ?  "*was*jealous of*pit trap*" :
                "I was actually just jealous of " + gen + " pit trap");
        case 4:
            string h_role = runaway_relation(player_name, h_index);
            return (check_pattern ?  "*you are the greatest " + h_role + "*" :
                gen + " is the greatest " + h_role);
        default:
            gen = (gen == "he" ? "him" : "her");
            return (check_pattern ?  "*will make it up to you*" :
                "I will make it up to " + gen);
    }
}


/*
 * Function name: kidnap_index
 * Description	: Returns the index of the correct method to kidnap Dearest
 * Arguments	: (string) Name of player for whom this works.
 * Returns		: (int) Index
 */
int kidnap_index(string player_name)
{
    return NAME_TO_RANDOM(player_name, KIDNAP_IDENT, KIDNAP_RANGE);
}

 /*
 * Function name: query_outside_pronoun
 * Description  : Returns a Runaway pronoun depending on the player's name
 * Arguments    : (int) Gender constant for pronoun
 *              : (string) Pronoun form (optional) - "subject", "object",
 *      "possessive", or first 3 letters thereof.
 * Returns      : (string) gender pronoun
 */
varargs string
query_outside_pronoun(int gender_constant = G_FEMALE, string form = "subject")
{
    switch (gender_constant)
    {
    case G_MALE:
        switch (form)
        {
        case "object":
        case "obj":
            return "him";
        case "possessive":
        case "pos":
            return "his";
        default:
            return "he";
        }
    default:
        switch (form)
        {
        case "object":
        case "obj":
        case "possessive":
        case "pos":
            return "her";
        default:
            return "she";
        }
    }
}


/*
 * Function name: remove_origan
 * Description  : Announce departure of bandit leader after guest appearance
 * Arguments    : (object) The leader
 */
void
remove_origan(object origan)
{
    string *exits = environment()->query_exit_cmds();
    if (sizeof(exits))
    {
        tell_room(environment(this_player()), QCTNAME(origan) + " leaves "
            + one_of_list(exits) + ".\n");
    }
    else
    {
        tell_room(environment(this_player()), QCTNAME(origan)
            + " hurries away.\n");
    }
    origan->remove_object();
}


/*
 * Function name: runaway_gender
 * Description  : Returns a Runaway pronoun depending on the player's name
 * Arguments    : (string) Name of player for whom Runaway has this gender
 * Returns      : (int) gender constant
 */
 int
 runaway_gender(string player_name)
 {
    return (strlen(player_name) % 2 ? G_MALE : G_FEMALE);
 }

/*
 * Function name: runaway_name
 * Description  : Returns the runaway's name, custom for the given player.
 * Arguments    : (string) Name of player for whom Family has this role
 * Returns      : (string) capitalized name
 */
string
runaway_name(string player_name)
{
    int name_index = NAME_TO_RANDOM(player_name, RUN_IDENT, RUN_RANGE);
    string *runaway_names = RUN_NAMES;
    return capitalize(runaway_names[name_index]);
}

/*
 * Function name: runaway_relation
 * Description  : Returns the Family member's relationship to Runaway, e.g.,
 *      sister of Runaway, for the given player.
 * Arguments    : (string) Name of player who perceives this relation
                : (int) Index of Family with whom relationship exists
 *              : (int) Optional flag to invert the relationship: Runaway-Family
 * Returns      : (string) relationship of Family to Runaway, or vice-versa
 */
varargs string
runaway_relation(string player_name, int family_index, int invert = 0)
{
    mapping all_relations = ([ "0":({ "aunt", "cousin", "grandmother", "sister",
        "grandmother", "sister" }), "1":({ "uncle", "cousin", "grandfather",
        "brother", "grandfather", "brother" }), "2":({ "sister",
        "grandmother", "sister", "mother", "mother", "godmother" }),
        "3":({ "brother", "grandfather", "brother", "father",
        "father", "father" }) ]);
    int relations_range = 6; //Number of options per array in the mapping
    //Array of possible relations

    int rel_index = NAME_TO_RANDOM(player_name, family_index, relations_range);
    string *relations;

    if(family_index > relations_range)
    {
        relations = all_relations["" + (family_index % 2)];
        //Keys "0" and "1" in all_relations hold default female and male arrays
    }
    else
    {
        relations = all_relations["" + (family_index % 2 + 2)];
        //Values <= the range are intentional and can access higher arrays #'s.
    }

    //tell_object(find_player("mar"), "INDEX: " + rel_index + "\n");
    //tell_object(find_player("mar"), relations[0]);
    if(invert)
    {
        switch (relations[rel_index])
        {
        case "aunt":
        case "uncle":
            switch (runaway_gender(player_name))
            {
            case G_MALE:
                return "nephew";
            default:
                return "niece";
            }
        case "cousin":
            return "cousin";
        case "grandfather":
        case "grandmother":
            switch (runaway_gender(player_name))
            {
            case G_MALE:
                return "grandson";
            default:
                return "granddaughter";
            }
        case "father":
        case "mother":
            switch (runaway_gender(player_name))
            {
            case G_MALE:
                return "son";
            default:
                return "daughter";
            }
        case "brother":
        case "sister":
        default:
            switch (runaway_gender(player_name))
            {
            case G_MALE:
                return "brother";
            default:
                return "sister";
            }
        }
    }

    return relations[rel_index];
}

/*
 * Function name: runaway_role_index
 * Description  : Determine the index of the Family member who has a given role
 *      in the Runaway quest, for given player.
 * Arguments:   (string) Name of player for whom Family has this role
 *              (int) Int, representing a role to be checked, used as a seed.
 *
 * Returns:       (int) result of comparison of own index with the index that
 *      that serves this role for this player.
 */
int
runaway_role_index(string player_name, int role_ind)
{
    return NAME_TO_RANDOM(player_name, role_ind, ROLE_CANDIDATES);
}

/*
 * Function name: token_index
 * Description  : Returns the name of the token to be given to the player by
 *      Dearest, custom for the given player.
 * Arguments    : (string) Name of player for whom this token is selected
 * Returns      : (string) index of token
 */
int
token_index(string player_name)
{
    return NAME_TO_RANDOM(player_name, TOKEN_IDENT, TOKEN_RANGE);
}

/*
 * Function name: regret_message
 * Description  : Returns the message from Regrets that player must deliver to
 *          Runaway; if flag set, returns a parse_command pattern for it.
 * Arguments    : (string) player_name from query_living_name()
 *                (int) Flag to return wildmatch pattern
 * Returns      : (string) The phrase, or the wildmatch pattern to match it.
 */
varargs string
regret_message(string player_name, int check_pattern = 0)
{
    string gen = runaway_gender(player_name) ? "she" : "he";
    switch (NAME_TO_RANDOM(player_name, REGRET_IDENT, REGRET_RANGE))
    {
        case 0:
            return (check_pattern ?  "*thornfruit*great idea*" :
                "the thornfruit was actually a great idea");
        case 1:
            return (check_pattern ?  "*barkhound can stay*" :
                "the barkhound can stay*");
        case 2:
            return (check_pattern ?  "*can lead*next purge*" :
                gen + " can lead the next purge");
        case 3:
            gen = (runaway_gender(player_name) ? "her" : "his");
            return (check_pattern ?  "*your*arrow*ogre*" :
                "that was actually " + gen + " arrow in the ogre last week");
        case 4:
            return (check_pattern ?  "*you really*greenest*" :
                gen + "really is the greenest");
        default:
            return (check_pattern ?  "*smells*better*juice incident*" :
                "the kitchen smells much better since the juice incident");
    }
}


/*
 * Function name: summon_origan
 * Description  : Create and announce arrival of bandit leader
 * Argument     : (object) The room to summon to and notify
 * Returns      : (object) The leader
 */
object
summon_origan(object this_room)
{
    object origan = clone_object(BANDIT_DIR + "npc/origan");
    mixed *calls = origan->get_all_alarms();
    if (sizeof(calls))
    {
        remove_alarm(calls[0][0]); //Block the wield/wear alarm
    }
    origan->move(this_room);
    string *entrances = this_room->query_exit_cmds();
    tell_room(this_room, "Origan arrives from the " + one_of_list(entrances) + ".\n");
    return origan;
}


/*
 * Function name: token_name
 * Description  : Returns the name of the token to be given to the player by
 *      Dearest, custom for the given player.
 * Arguments    : (string) Name of player for whom Family has this role
 * Returns      : (string) name of token
 */
string
token_name(string player_name)
{
    int token_index = NAME_TO_RANDOM(player_name, TOKEN_IDENT, TOKEN_RANGE);
    string *tokens = TOKEN_NAMES;
    return tokens[token_index];
}
