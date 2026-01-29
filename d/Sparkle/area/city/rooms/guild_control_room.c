/*
 *  /d/Sparkle/area/city/rooms/guild_control_room.c
 *
 *  Room to monitor and process various things to do with guilds in
 *  Genesis and the players who belong to them.
 *
 *  Created by Cooper Sherry (Gorboth), September 2013
 */

#pragma strict_types

#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit "/std/room";

/* Global Variables */
mapping   guilds = ([]);


/* Prototypes */
public void             create_room();
public void             init();
public int              is_wizard(object who);
nomask int              sort_name(string a, string b);
public int              get_guild_members(string arg);


/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();
    
    add_action(get_guild_members, "glist");
} /* init */


/* 
 * Function name:       create_room
 * Description  :       This function overrides the one in the base class
 */
public void
create_room()
{
    set_short("Genesis Guilds Control Room");
    set_long("This is the main control room for all the guilds in "
           + "the Realms of Genesis.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
} /* create_room */


/* Function name:        query_open_guilds
 * Description  :        Generates a mapping containing all open
 *                       guilds in the game.
 * Returns      :        mapping - the guild info
 *
public mapping
query_open_guilds()
{
    string  *open_guilds;
    mapping  results;

    setuid();
    seteuid(getuid());

    open_guilds = filter(SECURITY->query_guilds(), guild_is_open);

    results = ([ ]);
    foreach (string guild : open_guilds)
    {
        results[guild] = SECURITY->query_guild_long_name(guild);
    }

    return results;
} */ /* query_open_guilds */


/*
 * Function name:        is_wizard
 * Description  :        returns true if player is a wizard
 * Arguments    :        object who - the player to check
 * Returns      :        1 - wizard, 0 - non-wizard
 */
public int
is_wizard(object who)
{
    return who->query_wiz_level();
} /* is_wizard */


/*
 * Function name: sort_name
 * Description  : Sort two words alphabetically
 * Arguments    : string a - the first word
 *                string b - the second word
 * Returns      : int -1 - a comes before b alphabetically
 *                     1 - b comes before a alphabetically
 */
nomask int
sort_name(string a, string b)
{
    return ((a == b) ? 0 : ((a < b) ? -1 : 1));
} /* sort_name * /


/*
 * Function name:        get_guild_members
 * Description  :        Generate a list of the guilds of all mortals
 *                       currently logged in.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
get_guild_members(string arg)
{
    object  *mortals;
    mapping  memberships = ([]);
    string   guild;
    string  *guild_array;
    string  *names_array;
    string   border = "==========================================\n";
    int      leader;
    int      i;

    notify_fail("Useage: <glist [occ/lay/race/craft]>\n");

    if (!strlen(arg) ||
        !IN_ARRAY(arg, ({ "occ", "lay", "race", "craft" })) )
    {
        return 0;
    }

    mortals = filter(users(), not @ is_wizard);

    foreach(object mortal : mortals)
    {
        switch(arg)
        {
            case "occ":
                guild = mortal->query_guild_name_occ();
                break;
            case "lay":
                guild = mortal->query_guild_name_lay();
                break;
            case "race":
                guild = mortal->query_guild_name_race();
                break;
            case "craft":
                guild = mortal->query_guild_name_craft();
                break;
            default: /* should never happen, but hey ... */
                return 0;
                break;
        }

        if (!strlen(guild))
        {
            guild = "Guildless";
        }

        if (!IN_ARRAY(guild, m_indices(memberships)))
        {
            memberships += ([ guild : ({}) ]);
        }

        memberships[guild] += ({ mortal->query_real_name() });

    }   

    write("\n" + border);
    write(sprintf("%|42s", upper_case(arg) + " GUILD MEMBERS PRESENT\n"));
    write(border);

    guild_array = sort_array(m_indices(memberships), sort_name);

    foreach(string guild_name: guild_array)
    {
        if (guild_name == "Guildless")
        {
            continue;
        }

        write("   " + guild_name + ":\n");
        write("   " + ("~" * strlen(guild_name)) + "~\n");

        names_array = sort_array(memberships[guild_name], sort_name);

        foreach(string name : names_array)
        {
            switch(arg)
            {
                case "occ":
                    leader = find_player(name)->query_guild_leader_occ();
                    break;
                case "lay":
                    leader = find_player(name)->query_guild_leader_lay();
                    break;
                case "race":
                    leader = find_player(name)->query_guild_leader_race();
                    break;
                case "craft":
                    leader = find_player(name)->query_guild_leader_craft();
                    break;
                default: /* should never happen, but hey ... */
                    return 0;
                    break;
            }

            write("\t"
              + ((leader) ? "*" : " ")
              + capitalize(name) + "\n");
        }
    }

    write("\n   No " + arg + " membership:\n");
    write("   ~~~~~~~~~~~~~~~" + ("~" * strlen(arg)) + "\n");

    foreach(string name : sort_array(memberships["Guildless"], sort_name))
    {
        if (name == "logon")
        {
            continue;
        }

        write("\t " + capitalize(name) + "\n");
    }

    write(border);
    write("     * = council member\n");
    write(border + "\n");

    return 1;
} /* get_guild_members */
