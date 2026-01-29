/*
 * /d/Gondor/common/dwarf_guild/dwarf_shadow.c
 *
 * Copyright (C) Mercade @ Genesis - November 3 1993
 *
 * This is the shadow of the dwarf race guild.
 */

#pragma save_binary

inherit "/std/guild/guild_race_sh";

#include "dwarf.h"
#include "titles.h"
#include "/d/Gondor/defs.h"
#include <const.h>
#include <language.h>
#include <ss_types.h>
#include <state_desc.h>
#include <stdproperties.h>

#define QSW                  query_shadow_who()
#define JOINROOM             (DWARF_DIR + "join")
#define WRITE_NAME(o)        sprintf("%-11s", CAP((o)->query_real_name()))
#define MAX_SS_CON_SUPPORTED (100)
#define MAX_INTOXICATED(c)   ((c) * 2)

/*
 * Function name: query_guild_tax_race
 * Description  : Returns the tax for the dwarven race guild.
 * Returns      : int - the tax value
 */
nomask public int
query_guild_tax_race()
{
    return DWARVEN_RACE_GUILD_TAX;
}

/*
 * Function name: query_guild_name_race
 * Description  : Returns the name of the guild
 * Returns      : string - the name
 */
nomask public string
query_guild_name_race()
{
    return DWARVEN_RACE_GUILD_NAME;
}

/*
 * Function name: query_def_post
 * Description  : returns the path of the post office where the player will
 *                receives his mail.
 * Returns      : string - the path ;-)
 */
public string
query_def_post()
{
    return (DWARF_DIR + "post");
}

/*
 * Function name: query_guild_not_allow_join_race
 * Description  : Returns whether we should allow this player to join another
 *                guild if he wants to.
 * Arguments    : object player - the player that wants to join
 *                string type   - the type of the guild
 *                string style  - the styles of the guild
 *                string name   - the name of the guild
 * Returns      : int 1 - if the player is rejected
 *                    0 - if the player is accepted as a member
 */
nomask public int
query_guild_not_allow_join_race(object player, string type, string style,
    string name)
{
    /* It is a redefinition, so call the original too. */
    if (::query_guild_not_allow_join_race(player, type, style, name))
    {
        return 1;
    }

    /* If the player is not a dwarf, do not allow him/her. */
    if (player->query_race() != "dwarf")
    {
        notify_fail("You must be a dwarf to be a member of the " +
            DWARVEN_RACE_GUILD_NAME + ".\n");
        return 1;
    }

    return 0;
}

/*
 * Function name: query_guild_keep_player
 * Description  : Tests whether we want to keep a player if he logs in.
 * Arguments    : object player - the player to check
 * Returns      : int 0 - if the player will be kicked out
 *                    1 - the player will remain
 */
public int
query_guild_keep_player(object player)
{
    FIX_EUID;

    /* If the player changed his/her race, we kick him/her out. */
    if (player->query_race() != "dwarf")
    {
        JOINROOM->remove_player_changed_race(player);

        return 0;
    }

    if (JOINROOM->query_player_killed_dwarf(player->query_real_name()))
    {
        JOINROOM->remove_player_killed_dwarf(player);

        return 0;
    }

    player->add_subloc(DWARVEN_RACE_GUILD_NAME, TO);

    return 1;
}

/*
 * Function name: query_rockfriend_level
 * Description  : This function will return the level of the player in this
 *                guild. The level will range from 0 to the number of
 *                titles possible (defined in NUM_TITLES) minus one.
 * Returns      : int - the level
 */
nomask public int
query_rockfriend_level()
{
    int level = QSW->query_stat(SS_RACE);

    level = ((level * NUM_TITLES) / MAX_SS_RACE) - 1;

    return ((level >= NUM_TITLES) ? (NUM_TITLES - 1) :
        ((level < 0) ? 0 : level));
}

/*
 * Function name: query_rockfriend_beard_description
 * Description  : This function will return the beard description of the
 *                player if (s)he is a Rockfriend. Female members will get
 *                whiskers.
 * Returns      : string - the description.
 */
nomask public string
query_rockfriend_beard_description()
{
    return JOINROOM->query_rockfriend_beard_description(query_rockfriend_level());
}

/*
 * Function name: query_guild_title_race
 * Description  : This function will return the title for the Rockfriends.
 * Returns      : string - the title.
 */
nomask public string
query_guild_title_race()
{
    return JOINROOM->query_guild_title_race(query_rockfriend_level());
}

/*
 * Function name: query_guild_trainer_race()
 * Description  : The path to the trainer of the guild.
 * Returns      : string - the path to the trainer.
 */
nomask public string
query_guild_trainer_race()
{
    return DWARVEN_RACE_GUILD_DECAY;
}

/*
 * Function name: show_subloc
 * Description  : This function is called to display the sublocs. We mask it
 *                to show the beard/whiskers of Rockfriend members.
 * Arguments    : string subloc  - the sublock to check.
 *                object on_obj  - whom the subloc is on.
 *                object for_obj - who wants to know the subloc.
 * Returns      : string - the subloc text to display.
 */
public string
show_subloc(string subloc, object on_obj, object for_obj)
{
    string beard;

    /* Since this is a redefinition, call the original if the call was
     * not meant for us.
     */
    if ((on_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
        (subloc != DWARVEN_RACE_GUILD_NAME))
    {
        return QSW->show_subloc(subloc, on_obj, for_obj);
    }

    beard = query_rockfriend_beard_description() +
        ((QSW->query_age() > SILVER_BEARD_AGE) ? " silvery" : "");

    return (((for_obj == on_obj) ? "You are" :
        (CAP(PRONOUN(on_obj)) + " is")) + " wearing " +
        ((QSW->query_gender() == G_FEMALE) ? (beard + " whiskers") :
        (LANG_ADDART(beard) + " beard")) + ".\n");
}

/*
 * Function name: punish_rockfriend_for_killing
 * Description  : Rockfriends should not kill other players. If they do
 *                so, their level within the guild is lowered. Killing
 *                something way below your size will result in greater
 *                loss of beard-lenght.
 * Arguments    : object victim - the victim of the murder
 */
static nomask void
punish_rockfriend_for_killing(object victim)
{
    /* We compute the number difference in levels (novice, veteran, etc)
     * and add one to it for killing the player.
     */
    int difference = member_array(QSW->query_exp_title(), SD_AV_TITLES) -
        member_array(victim->query_exp_title(), SD_AV_TITLES) + 1;

    /* When you kill something bigger, you still kill, so you should
     * loose at least one level.
     */
    int level = query_rockfriend_level() -
        ((difference <= 0) ? 1 : difference);

    /* You cannot go beyond level 0. */
    if (level < 0)
    {
        level = 0;
    }

    /* Convert the level into a value for SS_RACE. */
    level = (((level + 1) * MAX_SS_RACE) / NUM_TITLES);

    /* Set the new status to the player. */
    QSW->set_guild_stat(SS_RACE, (QSW->stat_to_exp(level) + 1));
}

/*
 * Function name: notify_you_killed_me
 * Description  : This function is called whenever a player kills something
 *                or someone. It logs the kill if it was an act of PK for
 *                actions may then be taken. I do not like PK!
 * Arguments    : object victim - the victim of the murder
 */
public void
notify_you_killed_me(object victim)
{
    if (interactive(victim) &&
        (victim != QSW) &&
        (QSW->query_wiz_level() == 0))
    {
        FIX_EUID;

        write_file(DWARVEN_RACE_GUILD_LOG, (ctime(time()) + " " +
            WRITE_NAME(QSW) + " (" + QSW->query_average_stat() +
            ") killed " + WRITE_NAME(victim) + " (" +
            victim->query_average_stat() + ").\n"));

#ifdef NOT_IN_THE_MUDLIB_YET
        punish_rockfriend_for_killing(victim);
#endif NOT_IN_THE_MUDLIB_YET
    }

    QSW->notify_you_killed_me(victim);
}

/*
 * Function name: remove_rockfriend_guild
 * Description  : Called to remove the shadow from the player.
 * Returns      : int - the return value from remove_guild_race().
 */
nomask public int
remove_rockfriend_guild()
{
    QSW->add_prop(LIVE_I_MAX_INTOX,
        MAX_INTOXICATED(QSW->query_stat(SS_CON)));

    return remove_guild_race();
}

/*
 * Function name: process_help
 * Description  : Handle help on the Rockfriend Guild.
 * Arguments    : string category - the categorh (rockfriend / rf)
 *                string topic - the topic
 * Returns      : int 1/0 - if true, we handled it.
 */
public int
process_help(string category, string topic)
{
    /* Handling is in the soul, just for historic reasons. */
    if (DWARVEN_RACE_GUILD_SOUL->process_help(category, topic))
    {
        return 1;
    }

    return QSW->process_help(category, topic);
}

/*
 * Function name: init_race_shadow
 * Description  : This function is called when a Rockfriend logs in.
 *                It sends the current Rockfriend status to the admin
 *                object to keep the list correct.
 * Arguments    : string foobar - an init-string if there was any.
 */
nomask public void
init_race_shadow(string foobar)
{
    FIX_EUID;

    JOINROOM->update_level(QSW->query_real_name(), query_rockfriend_level());
}
