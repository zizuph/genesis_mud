/*
 * warmaster.c
 *
 * This is the 'master control' object which tracks calian
 * wargames. Basically, it just serves as a central location
 * to store lists of the current wargames and their members,
 * and little else.
 *
 * Khail - March 12/97
 */
#pragma strict_types

#include "wargames.h"

string *gamenames; /* A straight array of names. */
mapping players;   /* A 2-level mapping, (["gamename":(["player":"status" */
mapping formers;   /* A straight mapping of (["gamename":"former"]) */

public void add_player(object who, string game);

/*
 * Function name: create
 * Description  : Initializes gamenames and players variable.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create()
{
    gamenames = ({});
    players = ([]);
    formers = ([]);
    setuid();
}

/*
 * Function name: query_formers
 * Description  : Returns the 'formers' mapping. If an
 *                argument is supplied, it will try to return
 *                the corresponding game or former, as necessary.
 * Arguments    : arg - 3 Options: 1 - May be omitted.
 *                                 2 - Game name string.
 *                                 3 - Object pointer.
 * Returns      : Case 1 - Returns the whole 'formers' mapping.
 *                     2 - Returns object pointer to the player who
 *                         formed the game.
 *                     3 - Returns game name formed by the objectpointer.
 *                     4 - Returns 0 if option 2 or 3 was used, but
 *                         could not be matched in the formers mapping. 
 */
public varargs mixed
query_formers(mixed arg)
{
    int i;

    if (!arg)
        return formers;

    else if (stringp(arg))
        return formers[arg];

    else if (objectp(arg))
    {
        if ((i = member_array(arg, m_values(formers))) >= 0)
            return m_indexes(formers)[i];
        else
            return 0;
    }

    return 0;
}

/*
 * Function name: add_game
 * Description  : Adds a game to the list of active games by name.
 * Arguments    : who - Object pointer to the player forming the game.
 *                game - String which is the game's name.
 * Returns      : n/a
 */
public void
add_game(object who, string game)
{
    gamenames += ({game});
    players[game] = ([]);
    add_player(who, game);
    who->add_prop(CWARGAME_FORMER, game);
    formers[game] = who;   
}

/*
 * Function name: remove_game
 * Description  : Removes a game's name from the list of active
 *                games.
 * Arguments    : game - String which is the game's name.
 * Returns      : n/a
 */
public void
remove_game(string game)
{
    gamenames -= ({game});
    players = m_delete(players, game);
}

/*
 * Function name: query_games
 * Description  : Returns the gamenames array, a list of all
 *                current games.
 * Arguments    : n/a
 * Returns      : Array of game names as strings.
 */
public string *
query_games()
{
    return gamenames + ({});
}

/*
 * Function name: query_players
 * Description  : Returns either a simple array containing all the
 *                players in the game, or if the status flag is 
 *                true, a mapping of the players marked as either
 *                active or inactive. (living or dead).
 * Arguments    : game - Name of the game to list players in.
 *                status - Optional flag. If true, list the status
 *                         of the players too.
 * Returns      : If no status flag, an array containing object pointers
 *                to players in the specified game.
 *                If status flag, a mapping. Indexes of the mapping are
 *                object pointers to players in the game, values are
 *                the status of the player.
 */
public varargs mixed
query_players(string game, int status = 0)
{
    mapping local_players;

    if (!players[game])
        return ([]);

    local_players = players[game];

    if (status)
        return local_players;
    else
        return m_indexes(local_players);
}

/*
 * Function name: add_player
 * Description  : Adds a player to the specified game. Called by
 *                the 'cwargame join <game>' command, which has
 *                already verified 'game' is an ongoing game.
 * Arguments    : who - Object pointer to the incoming player.
 *                game - Name of the game the player joined.
 * Returns      : n/a
 */     
public void
add_player(object who, string game)
{
    object *arr,
           shadow;

    seteuid(getuid());
    arr = query_players(game);
    shadow = clone_object(CWARGAME_SHADOW);

    arr->catch_msg(who->query_name() + " joined the wargame.\n");
    arr->add_wargame_player(who);
    who->add_prop(CWARGAME_PARTICIPANT, game);
    who->remove_prop(CWARGAME_DEAD);
    who->add_subloc(CWARGAME_SUBLOC, shadow);    
    players[game][who] = "Active";    
    shadow->shadow_me(who, game);
    who->add_wargame_player(arr + ({who}));
}

/*
 * Function name: remove_player
 * Description  : Removes a player from the specified game.
 * Arguments    : who - Object pointer to the outgoing player.
 *                game - Name of the game the player's leaving.
 * Returns      : n/a
 */
public void
remove_player(object who, string game)
{
    object *arr;

    players[game] = m_delete(players[game], who);
    who->remove_war_shadow();
    arr = query_players(game);
    arr->remove_wargame_player(who);
    arr->catch_msg(who->query_name() + " left the wargame.\n");
}

/*
 * Function name: change_status
 * Description  : Change the status of a player in the specified
 *                game.
 * Arguments    : game - The name of the game the player is in.
 *                who - Object pointer to the player.
 *                status - The new status as either 'Active' or
 *                         'Inactive'.
 * Returns      : n/a
 */
public void
change_status(string game, object who, string status)
{
    players[game][who] = status;
}

/*
 * Function name: query_game_by_player
 * Description  : Returns the game the specified player is involved
 *                in.
 * Arguments    : who - Object pointer to the player involved.
 * Returns      : The name of the game as a string or 0 if teh
 *                specified player isn't in one.
 */
public void
query_game_by_player(object who)
{
    int i,
        sz;
    string temp;

    sz = sizeof(m_indexes(players));

    if (!sz)
        return 0;

    for (i = 0; i < sz; i++)
    {
        temp = m_indexes(players)[i];
        if (players[temp][who])
        {
            return temp;
            break;
        }
    }

    return 0;
}

/*
 * Function name: query_player_status
 * Description  : Returns the status of the specified player as
 *                'active' or 'inactive'
 * Arguments    : who - Object pointer to the player to check.
 *                game - Game the player is involved in.
 * Returns      : String, either "Active", "Inactive", if the
 *                player and game are valid. 0 otherwise.
 */
public mixed
query_player_status(object who, string game)
{
    if (!players[game])
        return 0;

    return players[game][who];
}

public varargs string
wargame_status(string arg)
{
    string ret,
           temp;
    int i,
        j,
        sz,
        sk;
    mapping gameplay;
    object ob;

    if (!arg || !strlen(arg) ||
        member_array(arg, gamenames) < 0)
    {
        if (!sizeof(gamenames))
            return "No active wargames.\n";
        else
            return "Current active wargames:\n" +
                implode(gamenames, "\n") + "\n";
    }

    else
    {
        gameplay = query_players(arg, 1);
        sz = m_sizeof(gameplay);
         
        ret = "Game: " + arg + "\n";
        ret += "Former: " + formers[arg]->query_name() + "\n";
        ret += sprintf("%-15@s\n", ({"Player","Status","Hits","Max Hits"}));
        for (i = 0; i < sz; i++)
        {
            ob = m_indexes(gameplay)[i];
            if (!sk = sizeof(ob->query_wargame_kills()))
                ret += sprintf("%-15@s\n", ({ob->query_name(),
                    gameplay[ob],
                    ob->query_total_paint_hits() + "",
                    ob->query_max_paint_hits() + "",
                    "none"}));
            else
            {
                for (j = 0; j < sk; j ++)
                {
                    if (!j)
                    {
                        ret += sprintf("%-15@s\n", ({
                            ob->query_name(),
                            gameplay[ob],
                            ob->query_total_paint_hits() + "",
                            ob->query_max_paint_hits() + "", 
                            ob->query_wargame_kills[j]}));
                    }
                    else
                    {
                        ret += sprintf("%-15@s\n", ({
                            " ", " ", " ", " ",
                            ob->query_wargame_kills[j]}));
                    }
                }
            }
        return ret;
    }
}
