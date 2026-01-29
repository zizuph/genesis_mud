/*
 * /d/Genesis/race/generic.c
 *
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 *
 * The generic race object for all the races in Genesis.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/player";
inherit "/d/Genesis/std/mail_stuff";
inherit "/d/Genesis/std/special_stuff";

inherit "/std/combat/humunarmed";

#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <macros.h>
#include <std.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Genesis/login/login.h"

#define COMMON_BOARD "/d/Genesis/obj/common_master"

/*
 * Function name: finger_info
 * Description  : This function is called when this player is fingered. It
 *                prints special information and mail information about
 *                this player.
 */
public void
finger_info()
{
    finger_mail();
    finger_special();
}

/*
 * Function name: In this function you can do the add_actions for Genesis
 *                specific commands.
 */
static void 
genesis_commands()
{
}

/*
 * Function name: query_race
 * Description  : Returns the "true" race for this player. This function
 *                is masked in the individual standard race files.
 * Returns      : string "human" - here, will be masked.
 */
string
query_race()
{
    return "human";
}

/*
 * Function name: common_board_check
 * Description  : This function will check the common board and see whether
 *                a new note has been posted since we last logged in.
 */
static nomask void
common_board_check()
{
    string file;
    int note_time;

    if (catch(COMMON_BOARD->teleledningsanka()))
    {
	return;
    }

    file = COMMON_BOARD->query_latest_note();
    if (!stringp(file) ||
	(sscanf(file, "b%d", note_time) != 1))
    {
	return;
    }

    if (note_time > query_login_time())
    {
	write("\nThe COMMON board contains a new note since you last " +
	      "logged in!\nPlease read the COMMON board for it contains " +
	      "valuable information!\n\n");
    }
}

/*
 * Function name: start_player
 * Descripiton  : When the player logs in, we set some race-specific stuff.
 */
public void
start_player()
{
    /* For players, reset the race to the default value. */
    if (!query_wiz_level())
    {
	set_race_name(query_race());
    }

    /* Add the race-commandsouls. */
    if (!sizeof(query_cmdsoul_list()))
    {
	add_cmdsoul(RACESOULCMD[query_race()]);
	add_cmdsoul(RACEMISCCMD[query_race()]);
    }

    /* Set the weight of this living. That is dependant on the race. */
    if (query_prop(CONT_I_WEIGHT) <= 1)
    {
	add_prop(CONT_I_WEIGHT, RACEATTR[query_race()][1] * 1000);
    }

    /* Set the volume of this living. That is dependant on the race. */
    if (query_prop(CONT_I_VOLUME) <= 1)
    {
	add_prop(CONT_I_VOLUME, RACEATTR[query_race()][4] * 1000);
    }

    /* Set the height of this living. That is dependant on the race. */
    if (query_prop(CONT_I_HEIGHT) <= 1)
    {
	add_prop(CONT_I_HEIGHT, RACEATTR[query_race()][0]);
    }

    /* Give the player a message about his mail-status. */
    start_mail(this_object()->query_def_post());

    /* Possible Genesis specific commands. */
    genesis_commands();

    /* Inform the player of a new note on the common board. */
    common_board_check();

    ::start_player();
}

/*
 * Function name: query_def_start
 * Description  : This function returns the very basic starting location
 *                for people of this race. Notice that we use query_race
 *                and not query_race_name since query_race always returns
 *                a valid race name. To alter the starting location of the
 *                player, use set_default_start_location.
 */
public nomask string
query_def_start()
{
    return RACESTART[query_race()];
}

/*
 * Function name: query_def_post
 * Description  : This function returns the location of the post office for
 *                people of this race. It might be good to shadow this
 *                function in guild shadows if the post office is supposed
 *                to be located somewhere special for the guild.
 */
public string
query_def_post()
{
    return RACEPOST[query_race()];
}

/*
 * Function name: query_def_start
 * Description  : This function returns initial stats for people of this
 *                race. Notice that we use query_race, not query_race_name
 *                since query_race always returns a valid race name.
 * Returns      : int * - the initial stats.
 */
public int *
query_orig_stat()
{
    return RACESTAT[query_race()];
}

/*
 * Function name: query_combat_file
 * Description  : Give the name of the file to use for combat.
 * Returns      : string - the file to use.
 */
public string
query_combat_file()
{
    return "/std/combat/chumlock";
}

/*
 * Function name: stats_to_acc_exp
 * Description  : Translates the current base stats into acc_exp and take
 *                the race modofiers into account. This function is only
 *                used from the default setup in player_sec::new_init()
 */
static nomask void
stats_to_acc_exp()
{
    int il  = (SS_STR - 1);
    int sum = 0;
    int tmp;

    while(++il < SS_NO_STATS)
    {
        tmp = stat_to_exp(query_base_stat(il)) * 10 /
	    RACESTATMOD[query_race()][il];

        if (tmp > 0)
        {
            set_acc_exp(il, tmp);
            sum += tmp;
        }
        else
        {
            set_acc_exp(il, 0);
        }
    }

    set_exp(sum);
    set_exp_combat(0);
}

/*
 * Function name: acc_exp_to_stats
 * Description  : Translates the current accumulated exp into stats and
 *                takes the racial modifiers into account.
 */
void
acc_exp_to_stats()
{
    int il = (SS_STR - 1);

    while(++il < SS_NO_STATS)
    {
        if (query_base_stat(il) >= 0)
        {
            set_base_stat(il, exp_to_stat(query_acc_exp(il) *
		RACESTATMOD[query_race()][il] / 10));
        }
    }
}

/*
 * Function name: update_stat
 * Description  : Convert exp to stat for a single stat and take the racial
 *                modifiers into account. This usually used by a guild that
 *                wants its stat to behave like the normal.
 * Arguments    : int stat - the stat to update.
 */
public nomask void
update_stat(int stat)
{
    set_base_stat(stat, exp_to_stat(query_acc_exp(stat)) *
	RACESTATMOD[query_race()][stat] / 10);
}

/*
 * Function name: query_statmod
 * Description  : This function returns the racial stat modifier for this
 *                player for a particular stat.
 * Arguments    : int stat - the stat to get the modifier for.
 * Returns      : int - the racial stat modifier for that stat.
 */
public nomask int
query_statmod(int stat)
{
    return RACESTATMOD[query_race()][stat];
}
