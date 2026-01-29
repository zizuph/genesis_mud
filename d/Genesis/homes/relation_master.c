/*
 * /d/Genesis/homes/relation.c
 *
 * This file is the master that keeps track of every relation in Genesis. It
 * is meant to be used in complyance with the homes system, but can also be
 * accessed by other code to see whether people have a relation with
 * eachother. Marriage is the most important relation, though other
 * relations can be possible.
 *
 * /Mercade, 20 december 1993
 *
 * Revision history:
 */

#pragma no_clone           /* no messing with the master    */
#pragma no_inherit         /* no messing with the master    */
#pragma save_binary        /* easy loading                  */
#pragma strict_types       /* why not... you should be tidy */

inherit "/std/object";     /* the basic object definitions  */

#include "relation.h"      /* our own relation definitions  */
#include <composite.h>     /* definitions for compositions  */
#include <macros.h>        /* never leave home without them */
#include <std.h>           /* definitions for security      */
#include <stdproperties.h> /* all properties defined        */

/*
 * Saved structure.
 *
 * relations:
 *     This structure consists of an array with a string determining the
 *     type of relation and an array of string with the people in the
 *     relation. Players can only be in one relation at a time and there
 *     cannot be a relation with only one player.
 *
 *     ({ "marriage", ({ "kithkanan", "rae" }),
 *        "marriage", ({ "remo",      "bixi" }),
 *     })
 *
 * possible_relation_types:
 *     This is an array of string with all possible relation types.
 *
 *     ({ "marriage" })
 */
mixed  relations                = ({ });
string *possible_relation_types = ({ });

/*
 * Function name: create_object
 * Description  : Is called to configure the object when it is loaded.
 */
public nomask void
create_object()
{
    if (IS_CLONE)
    {
	call_out("remove_object", 1);
	return;
    }

    set_name("_relations_master_");
    set_short("relations master");
    set_long("You'll never see this object, but if you do:\n" +
        VBFC("query_prop:" + file_name(this_object()) + "|" + OBJ_S_WIZINFO));
    set_no_show();

    add_prop(OBJ_S_WIZINFO, "\n" + break_string(
        "This object is the master that registers all relations between " +
        "individual players in Genesis. These relations will mainly be " +
        "marriage, though other relations (if supported) are also " +
        "possible. To limit interaction between wizards and players, they " +
        "are not supposed to have a close relationship, though it is not " +
        "made impossible in this system. To get a list of all relations " +
        "that are stored in this master, you have to make the following " +
        "call:", 75) + "\n" +
        "  Call " + MASTER + " dump_relations\n");
}

/*
 * Function name: restore_relations
 * Description  : reads the file that describes the relations.
 */
static nomask void
restore_relations()
{
    seteuid(getuid(this_object()));

    if (!restore_object(RELATION_SAVE_FILE))
    {
	this_interactive()->catch_msg("ERROR: could not restore the " +
            "relations save file.\n");
	/* Maybe I should do something else here as well... */
    }
}

/*
 * Function name: save_relations
 * Description  : saves the file that describes the relations.
 */
static nomask void
save_relations()
{
    seteuid(getuid(this_object()));

    save_object(RELATION_SAVE_FILE);
}

/*
 * Function name: relation_entry
 * Description  : Returns the sub-array in which the player is in.
 * Arguments    : player_name - the name of the player to check
 * Returns      : -1   - the player hasn't got a relation
 *                >= 0 - the entry
 */
static nomask int
relation_entry(string player_name)
{
    int i;

    player_name = lower_case(player_name); /* never be too sure */

    restore_relations();

    for (i = 1; i < sizeof(relations); i += 2)
    {
        if (member_array(player_name, relations[i]) != -1)
        {
            return i;
        }
    }

    return -1;
}

/*
 * Function name: query_relation
 * Description  : Return whether the player has a relation or not.
 * Arguments    : player_name - the name of the player to check.
 * Returns      : 1/0
 */
public nomask int
query_relation(string player_name)
{
    return (relation_entry(player_name) != -1);
}

/*
 * Function name: valid_relation_type
 * Description  : Returns whether a certain relation type is valid.
 * Arguments    : relation_type - the type to check
 * Returns      : 1/0
 */
public nomask int
valid_relation_type(string relation_type)
{
    restore_relations();

    return (member_array(relation_type, possible_relation_types) != -1);
}

/*
 * Function name: query_relation_type
 * Description  : Return the type of relation of a player.
 * Arguments    : player_name - the name of the player to check.
 * Returns      : 0      - the player has no relation.
 *                string - the type of relation
 */
public nomask string
query_relation_type(string player_name)
{
    int entry = relation_entry(player_name);

    if (entry == -1)
    {
        return 0;
    }

    return (relations[entry - 1]);
}

/*
 * Function name: query_partners
 * Description  : Get an array with all partners of a player.
 * Arguments    : player_name - the name of the player to check
 * Returns      : string *    - the partners of player_name
 *                0           - the player isn't in a relation
 */
public nomask string *
query_partners(string player_name)
{
    int entry = relation_entry(player_name);
    int player_entry;

    if (entry == -1)
    {
        return 0;
    }

    player_name = lower_case(player_name); /* never be too sure */
    player_entry = member_array(player_name, relations[entry]);

    return (exclude_array(relations[entry], player_entry,
        player_entry));
}

/*
 * Function name: query_have_a_relation
 * Description  : Query whether two players have a relation.
 * Arguments    : player1, player2 - the players to check
 * Returns      : 1/0
 */
public nomask int
query_have_a_relation(string player1, string player2)
{
    int entry = relation_entry(player1);

    if (entry == -1)
    {
        return 0;
    }

    player2 = lower_case(player2); /* never be too sure */

    return (member_array(player2, relations[entry]) != -1);
}

/*
 * Function name: query_has_relation_of_type
 * Description  : Query whether a player has a specific relation.
 * Arguments    : player_name   - the players to check
 *                relation_type - The relation player_name should be in
 * Returns      : 1/0
 */
public nomask int
query_has_relation_of_type(string player_name, string relation_type)
{
    int entry = relation_entry(player_name);

    if (entry == -1)
    {
        return 0;
    }

    return (relations[entry - 1] == relation_type);
}

/*
 * Function name: query_possible_relation_types
 * Description  : Return all possible relation types.
 * Returns      : string * - the possible relation types
 */
public nomask string *
query_possible_relation_types()
{
    restore_relations();

    return possible_relation_types;
}

/*
 * Function name: add_relation
 * Description  : This function will add a new relation to the list of
 *                relations.
 * Arguments    : string * - the players in the relation
 *                string   - the type of relation
 * Returns      : 1/0
 */
public nomask int
add_relation(string *players, string relation_type)
{
    int i;

    if (!valid_relation_type(relation_type))
    {
        return 0;
    }

    for (i = 0; i < sizeof(players); i++)
    {
        players[i] = lower_case(players[i]); /* never be too sure */

        if ((!(SECURITY->exist_player(players[i]))) ||
            (query_relation(players[i])))
        {
            return 0;
        }
    }

    relations = relations + ({ relation_type, players });

    save_relations();

    return 1;
}

/*
 * Function name: remove_relation
 * Description  : Remove a relation from the list of relations.
 * Arguments    : player_name - one of the members of the relation.
 * Returns      : 1/0
 */
public nomask int
remove_relation(string player_name)
{
    int entry = relation_entry(player_name);

    if (entry == -1)
    {
        return 0;
    }

    relations = exclude_array(relations, (entry - 1), entry);

    save_relations();

    return 1;
}

/*
 * Function name: remove_player_from_relation
 * Description  : This function will remove a player from a relation (for
 *                instance is he leaves Genesis) and if the relation the
 *                consists of only one player, the relation as a whole will
 *                be removed.
 * Arguments    : player_name - the name of the player to remove
 * Returns      : 1/0
 */
public nomask int
remove_player_from_relation(string player_name)
{
    int entry = relation_entry(player_name);
    int player_entry;

    if (entry == -1)
    {
        return 0;
    }

    if (sizeof(relations[entry]) == 2)
    {
        return (remove_relation(player_name));
    }

    player_name = lower_case(player_name); /* never be too sure */
    player_entry = member_array(player_name, relations[entry]);
    relations = (exclude_array(relations[entry],
        player_entry, player_entry));

    save_relations();

    return 1;    
}

/*
 * Function name: change_relation_type
 * Description  : Change the type of a relation that is stored.
 * Arguments    : player_name   - the name of a player in the relation
 *                relation_type - the new relation type
 * Returns      : 1/0
 */
public nomask int
change_relation_type(string player_name, string relation_type)
{
    int entry = relation_entry(player_name);

    if (entry == -1)
    {
        return 0;
    }

    if (!valid_relation_type(relation_type))
    {
        return 0;
    }

    relations[entry - 1] = relation_type;

    save_relations();

    return 1;
}

/*
 * Function name: add_relation_type
 * Description  : This function will add a new relation type to the list
 *                of defined relation types.
 * Access level : Archwizard, if this_interactive() is not an archwizard,
 *                this function will not work.
 * Arguments    : relation_type - the type to add
 * Returns      : 1/0
 */
public nomask int
add_relation_type(string relation_type)
{
    if (SECURITY->query_wiz_rank(geteuid(this_player())) < WIZ_ARCH)
    {
        this_interactive()->catch_msg("You are not allowed to add a " +
            "new relation type.\n");
        return 0;
    }

    restore_relations();

    if (valid_relation_type(relation_type))
    {
        this_interactive()->catch_msg("That relation type already exists.\n");
        return 0;
    }

    this_interactive()->catch_msg("Added: " + relation_type + ".\n");

    possible_relation_types = possible_relation_types + ({ relation_type });

    save_relations();

    return 1;
}

/*
 * Function name: remove_relation_type
 * Description  : This function will remove a new relation type from the list
 *                of defined relation types.
 * Access level : Archwizard, if this_interactive() is not an archwizard,
 *                this function will not work.
 * Arguments    : relation_type - the type to remove
 * Returns      : 1/0
 */
public nomask int
remove_relation_type(string relation_type)
{
    int i;

    if (SECURITY->query_wiz_rank(geteuid(this_player())) < WIZ_ARCH)
    {
        this_interactive()->catch_msg("You are not allowed to remove a " +
            "relation type.\n");
        return 0;
    }

    restore_relations();

    if (!valid_relation_type(relation_type))
    {
        this_interactive()->catch_msg("That relation type does not exist.\n");
        return 0;
    }

    this_interactive()->catch_msg("Removed: " + relation_type + ".\n");

    i = member_array(relation_type, possible_relation_types);
    possible_relation_types = exclude_array(possible_relation_types, i, i);

    save_relations();

    return 1;
}

/*
 * Function name: get_all_relations
 * Description  : Returns all relations that are added to the system
 * Returns      : mixed - the relations
 */
public nomask mixed
get_all_relations()
{
    restore_relations();

    return relations;
}

/*
 * Function name: dump_relations
 * Description  : This function will dump a list of all relations to
 *                the active wizard, this_interactive().
 * Access level : Wizard, if this_interactive() is not a wizard, this
 *                function will not do anything.
 * Returns      : 1/0
 */
public nomask int
dump_relations()
{
    int i;

    if (!(this_interactive()->query_wiz_level()))
    {
        return 0;
    }

    this_interactive()->catch_msg(
        "THE RELATIONS STORED IN THE RELATION MASTER\n" +
        "===========================================\n" +
        "\n");

    restore_relations();

    for (i = 0; i < sizeof(relations); i += 2)
    {
        this_interactive()->catch_msg(sprintf("%-15s", relations[i])
            + " : " + COMPOSITE_WORDS(map(relations[i + 1],
            "return_capitalize", this_object())) + ".\n");
    }

    return 1;
}

/*
 * Function name: return_capitalize
 * Description  : This is a mapping function that returns the name of a
 *                player capitalized.
 * Arguments    : name   - the name to capitalize
 * Returns      : string - the capitalized name
 */
static nomask string
return_capitalize(string name)
{
    return capitalize(name);
}
