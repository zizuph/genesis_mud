/*
 * /d/Gondor/common/lib/remember.c
 *
 * This file handles the met-system for npc's. An npc will remember the
 * names of those who he met and whom introduced themselves to him. 
 *
 * /Mercade, 8 January 1994
 *
 * Revision history:
 */

#pragma save_binary

#include "/d/Gondor/defs.h"
#include <stdproperties.h>

#define TIME_BEFORE_I_FORGET_SOMEONE 2592000  /* 30 days */
#define TIME_JUST_MET_NO_REACT       60
#define TIME_BETWEEN_INTRODUCTIONS   30

/*
 * Prototype
 */
void update_met_players();

/*
 * Global variables
 */
private mapping npc_met_names = ([ ]);
/*
 * The npc will save all the names of the players who have introduced
 * themselves to him. To make sure that his (disk-)memory doesn't overload,
 * he will forget anyone whom he has not met in 30 days (RL) time.
 */
static private int    npc_last_intro; /* time() when last intro was made */
static private string npc_save_file;  /* the file to save the npc in.    */

/*
 * Function name: create_remember
 * Description  : This function should be called if this file is inherited
 *                to initialize the system
 */
nomask void
create_remember()
{
    update_met_players();
}

/*
 * Function name: set_npc_save_file
 * Description  : Sets the save-file of this npc
 * Arguments    : string - the filename
 */
nomask void
set_npc_save_file(string filename)
{
    npc_save_file = filename;
}

/*
 * Function name: query_npc_save_file
 * Description  : Query the save-file of this npc
 * Returns      : string - the filename
 */
nomask string
query_npc_save_file()
{
    return npc_save_file;
}

/*
 * Function name: npc_say
 * Description  : Make this npc say something
 * Arguments    : string - whatever he should say
 */
void
npc_say(string to_say)
{
    command("say " + to_say);
}

/*
 * Function name: save_npc
 * Description  : Save some variables of this npc to disk
 */
nomask void
save_npc()
{
    if (!strlen(npc_save_file))
    {
        npc_say("I cannot save to disk. No save-file set. Please make " +
            "a bugreport!");
        return;
    }

    if (!save_object(npc_save_file))
    {
        npc_say("I had a problem saving, please make a bugreport.");
    }
}

/*
 * Function name: restore_npc
 * Description  : Restores the saved file from an npc.
 */
nomask void
restore_npc()
{
    if (!strlen(npc_save_file))
    {
        npc_say("I cannot restore from disk. No save-file set. Please " +
            "make a bugreport!");
        return;
    }

    if (!restore_object(npc_save_file))
    {
        npc_say("I had a problem restoring, please make a bugreport.");
    }
}

/*
 * Function name: introduce_me
 * Description  : This function should be called to make the master
 *                introduce himself. It takes care of most things.
 */
varargs nomask void
introduce_me(string name)
{
    if ((npc_last_intro + TIME_BETWEEN_INTRODUCTIONS) > time())
    {
        return;
    }

    npc_last_intro = time();

    if (!strlen(name))
    {
        command("introduce myself");
    }

    command("introduce myself to " + name);
}

/*
 * Function name: update_met_player
 * Description  : When a player who was met before turns up again, the master
 *                will remember this occasion as the last time they met.
 * Arguments    : name - the real name of the player
 */
nomask static void
update_met_player(string name)
{
    restore_npc();

    if (!npc_met_names[name])
    {
        return;
    }

    npc_met_names[name] = time();

    save_npc();
}

/*
 * Function name: add_met_player
 * Description  : Checks whether a player who introduced him/herself was
 *                already met or not and adds a nonmet player to the list
 *                of met players.
 * Arguments    : name - the real name of the player
 * Returns      : 1 - the player was not met before
 *                0 - the player was met before
 */
nomask int
add_met_player(string name)
{
    restore_npc();

    if (npc_met_names[name] > 0)
    {
        update_met_player(name);

        return 0;
    }

    npc_met_names[name] = time();

    save_npc();

    return 1;
}

/*
 * Function name: query_met_player
 * Description  : Checks whether the npc remembered a player or not
 * Arguments    : name - the real name of the player
 * Returns      : 1 - the player was met before
 *                0 - the player was not met before
 */
nomask int
query_met_player(string name)
{
    update_met_player(name);

    if (find_player(name)->query_prop(LIVE_I_ALWAYSKNOWN))
    {
        return 1;
    }

    return (npc_met_names[name] > 0);
}

/*
 * Function name: query_last_meeting
 * Description  : Checks whether the npc remembered a player or not and
 *                returns the time of the last meeting if the player was
 *                met before.
 * Arguments    : name - the real name of the player
 * Returns      : int - the time the last meeting was
 *                0   - the player was not met before
 */
nomask int
query_last_meeting(string name)
{
    restore_npc();

    update_met_player(name);

    return npc_met_names[name];
}

/*
 * Function name: query_reply_name
 * Description  : Returns the name to use for the player. If he was met than
 *                his met_name will be used, otherwise, his nonmet_name will
 *                be returned.
 * Arguments    : name   - the real name of the player
 * Returns      : string - the name to use for the player
 */
nomask string
query_reply_name(string name)
{
    if (query_met_player(name))
    {
        return (string)find_player(name)->query_met_name();
    }

    return (string)find_player(name)->query_nonmet_name();
}

/*
 * Function name: player_name
 * Description  : This function returns the name that should be used for
 *                a certain living.
 * Arguments    : player - the player to reply to
 * Returns      : string - the name to use for the player
 */
nomask string
player_name(object player)
{
    return query_reply_name((string)player->query_real_name());
}

/*
 * Function name: undate_met_players
 * Description  : This function will be called on creation to check all the
 *                names from the players that he met. If it was too long ago
 *                that he met someone, he will forget about the player.
 */
nomask static void
update_met_players()
{
    int i;
    string *s;

    restore_npc();

    s = m_indices(npc_met_names);

    for (i = 0; i < sizeof(s); i++)
    {
        if ((npc_met_names[s[i]] + TIME_BEFORE_I_FORGET_SOMEONE) < time())
        {
            m_delete(npc_met_names, s[i]);
        }
    }

    save_npc();
}

/*
 * Function name: greet_player
 * Description  : This function is called whenever someone encounters the
 *                npc to greet him.
 * Arguments    : object player - the meeting player.
 */
void
greet_player(object player)
{
    string name = (string)player->query_real_name();

    if (!present(player, ENV(TO)))
    {
        return;
    }

    if (!query_met_player(name))
    {
        npc_say("We have not had the pleasure before, " +
            player_name(player) + ", if I recall correctly.");
        command("bow " + name);
        introduce_me(name);

        return;
    }

    if ((query_last_meeting(name) + TIME_JUST_MET_NO_REACT) > time())
    {
        return;
    }

    command("bow " + name);
    npc_say("How nice to see you again, " + player_name(player) + ".");
}