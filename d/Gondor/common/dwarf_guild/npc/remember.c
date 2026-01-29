/*
 * /d/Gondor/common/dwarf_guild/npc/remember.c
 *
 * Copyright (C) Stas van der Schaaf - January 8 1994
 *               Mercade @ Genesis
 *
 * This file handles the met-system for npc's. An npc will remember the
 * names of those whom he met and who introduced themselves to him. 
 */

#pragma strict_types

inherit "/std/monster";

#include <filter_funs.h>
#include <login.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define TIME_BEFORE_I_FORGET_SOMEONE (31536000) /* 365 days   */
#define TIME_JUST_MET_NO_REACT       (1800)     /* 15 minutes */
#define TIME_BETWEEN_INTRODUCTIONS   (60)
#define LINE_LENGTH                  (70)

#define GREET_EMOTES ({ "bow to", "greet", "shake with", "smile at" })

#define DEBUG(s) find_player("mercade")->catch_msg((s) + "\n");

/*
 * Prototypes. I do not like them, but the new implementation of efuns with
 * the function-type requires them.
 */
void npc_say(string to_say);
nomask static void update_met_players();
void greet_player(object player);

/*
 * Global variables
 */
static private mapping npc_met_names = ([ ]);
static private int     npc_last_intro = 0;
static private string  npc_save_file = 0;
static private string *npc_variables = ({ });

/*
 * Function name: save_npc
 * Description  : Save some variables of this npc to disk
 */
static nomask void
save_npc()
{
    if (!strlen(npc_save_file))
    {
	npc_say("I cannot save to disk. No save-file set. Please make a " +
	    "bugreport!\n");
	return;
    }

    if (!save_map(npc_met_names, npc_save_file))
    {
	npc_say("I had a problem saving, please make a bugreport.");
    }
}

/*
 * Function name: restore_npc
 * Description  : Restores the saved file from an npc.
 */
static nomask void
restore_npc()
{
    if (!strlen(npc_save_file))
    {
	npc_say("I cannot restore from disk. No save-file set. Please " +
	    "make a bugreport!\n");
	return;
    }

    if (!mappingp(npc_met_names = restore_map(npc_save_file)) ||
	!m_sizeof(npc_met_names))
    {
	npc_say("I had a problem restoring, please make a bugreport.\n");

	npc_met_names = ([ ]);
    }
}

/*
 * Function name: create_remember
 * Description  : This function should be called if this file is inherited
 *                to initialize the system
 * Arguments    : string *vars - the names of the variables in the NPC that
 *                    are set with set_npc_variable() and that should not
 *                    be updated.
 */
nomask varargs void
create_remember(string *vars)
{
    FIX_EUID;

    if (pointerp(vars))
    {
	npc_variables = vars;
    }

    restore_npc();

    /* Only update this information on monday. Since we have > 1 week uptimes,
     * no need to do this on Mondays only anymore.
    if (ctime(time())[0..2] == "Mon")
    {
	set_alarm(5.0, 0.0, update_met_players);
    }
     */
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
 * Function name: set_npc_variable
 * Description  : To have a variable saved in the NPC, use this function to
 *                add it to the saved mapping. Note that all variable names
 *                must be listed in the argument to create_remember().
 * Arguments    : string name - the name of the variable.
 *                mixed value - the value of the variable to store.
 */
nomask void
set_npc_variable(string name, mixed value)
{
    npc_met_names[name] = value;
}

/*
 * Function name: query_npc_variable
 * Description  : After a variable is saved in the NPC, use this function to
 *                retrieve it. When the variable does not exist anymore, it
 *                will return 0.
 * Arguments    : string name - the name of the variable.
 * Returns      : mixed - the value of the variable.
 */
nomask mixed
query_npc_variable(string name)
{
    return npc_met_names[name];
}

#ifdef THIS_IS_NOT_DEFINED
/*
 * Function name: race_sound
 * Description  : Returns the race sound that a certain player or npc will
 *                hear from this npc.
 * Argument     : object - the player to hear the sound.
 * Returns      : string - the racesound.
 */
string
race_sound(object player)
{
    string raceto = (string)player->query_race();

    if (member_array(raceto, RACES) < 0)
    {
	return "says";
    }

    return RACESOUND[query_race_name()][raceto];
}
#endif THIS_IS_NOT_DEFINED

/*
 * Function name: npc_say
 * Description  : Make this npc say something
 * Arguments    : string - whatever he should say
 *                This string should NOT contain any VBFC.
 */
void
npc_say(string to_say)
{
#ifdef THIS_IS_NOT_DEFINED

    object *livings;
    string *tmp;
    string tmp2;
    string rsound;
    string insert;
    string actual_say;
    int    i;

    if (!objectp(ENV(TO)))
    {
	return;
    }

    livings = FILTER_LIVE(all_inventory(ENV(TO))) - ({ TO });

    for(i = 0; i < sizeof(livings); i++)
    {
	rsound = race_sound(livings[i]);

	actual_say = query_The_name(livings[i]) + " " + rsound + ": " + to_say;

	tmp = explode(break_string(actual_say, LINE_LENGTH), "\n");
	actual_say = tmp[0] + "\n";

	if (sizeof(tmp) > 1)
	{
	    insert = CAP(PRONOUN(TO)) + " " + rsound + ": ";
	    tmp2 = implode(tmp[1..(sizeof(tmp) - 1)], " ");

	    actual_say += break_string(tmp2, LINE_LENGTH, insert) + "\n";
	}

	livings[i]->catch_msg(actual_say);
    }
#endif THIS_IS_NOT_DEFINED

/*
 * The easiest way to do an npc_say.
 */
    command("say " + to_say);

}

/*
 * Function name: fix_souls
 * Description  : Make sure that the necessary souls are loaded.
 */
void
fix_souls()
{
    add_cmdsoul(DWARVEN_RACE_GUILD_SOUL);
    update_hooks();
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
/*
    if (!strlen(name))
    {
	command("introduce myself");
	return;
    }
*/
    command("introduce myself");
/*
    command("introduce myself to " + CAP(name));
 */
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
 */
nomask void
add_met_player(string name)
{
    if (!(SECURITY->exist_player(name)))
    {
	return;
    }

    if (npc_met_names[name] > 0)
    {
	update_met_player(name);
	return;
    }

    npc_met_names[name] = time();

    save_npc();
}

/*
 * Function name: add_introduced
 * Description  : This function will be called in me whenever someone
 *                introduces him/herself to me.
 * Arguments    : string name - the person being introduced.
 */
void
add_introduced(string name)
{
    add_met_player(name);

    set_alarm(2.0, 0.0, &introduce_me(name));
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
    if (!strlen(name))
    {
        return 0;
    }

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
    int met = npc_met_names[name];

    update_met_player(name);

    return met;
}

/*
 * Function name: player_name
 * Description  : Returns the name to use for the player. If he was met than
 *                his met_name will be used, otherwise, his nonmet_name will
 *                be returned.
 * Arguments    : player - the player
 * Returns      : string - the name to use for the player
 */
nomask string
player_name(object player)
{
    string name = (string)player->query_real_name();

    if (query_met_player(name))
    {
	return (string)player->query_met_name();
    }

    return (string)player->query_nonmet_name();
}

/*
 * Function name: init_living
 * Description  : This function will trigger to greet someone if they
 *                encounter them.
 */
void
init_living()
{
    object player = TP;

    ::init_living();

    if (interactive(player))
    {
	set_alarm(2.0, 0.0, &greet_player(player));
    }
}

/*
 * Function name: update_met_players
 * Description  : This function will be called on creation to check all the
 *                names from the players that he met. If it was too long ago
 *                that he met someone, he will forget about the player.
 */
nomask static void
update_met_players()
{
    string *met_names = (string*)m_indices(npc_met_names) - npc_variables;
    int    size = sizeof(met_names);
    int    removed = 0;
    int    limit = (time() - TIME_BEFORE_I_FORGET_SOMEONE);

    while(--size >= 0)
    {
	if (npc_met_names[met_names[size]] < limit)
	{
	    npc_met_names = m_delete(npc_met_names, met_names[size]);
	    removed = 1;
	}
    }

    if (removed)
    {
	save_npc();
    }
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

    if ((!objectp(player)) ||
	(!present(player, ENV(TO))) ||
	(!CAN_SEE(TO, player)))
    {
	return;
    }

    if (!query_met_player(name))
    {
	npc_say("We have not had the pleasure before, " +
	    player_name(player) + ", if I recall correctly.");
	command(ONE_OF_LIST(GREET_EMOTES) + " " + CAP(name));
	introduce_me(name);

	return;
    }

    if ((query_last_meeting(name) + TIME_JUST_MET_NO_REACT) > time())
    {
	return;
    }

    command(ONE_OF_LIST(GREET_EMOTES) + " " + CAP(name));
    npc_say("Nice to see you again, " + player_name(player) + ".");
}
