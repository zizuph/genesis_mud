/*
 *  /d/Gondor/clubs/nisse/shadow/nisse_shadow.c
 *
 *  The Nisse Ohtar club shadow.
 *
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

#include <const.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>
#include <std.h>
#include <ss_types.h>
#include <language.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

inherit "/std/shadow";
    
/*
 *  Prototypes
 */
mapping		gMembers = ([]);

/*
 *  Function name: query_nisse_member
 *  Description  : Is this person a member of the Nisse Ohtar club.
 *  Returns:       1 if member, 0 if not member
 */
int
query_nisse_member()
{
    return (MANAGER->query_nisse(shadow_who->query_real_name()));
}

/*
 *  Function name: query_nisse_level
 *  Description  : A Nisse function to give their membership level.
 *                 Options are:
 *                 0 - not a Nisse
 *                 1 - tan
 *                 2 - light brown
 *                 3 - brown
 *                 4 - deep brown
 *                 5 - red
 *                 6 - gold
 *                 7 - bronze
 */
int
query_nisse_level()
{
    return (MANAGER->query_nisse_level(shadow_who->query_real_name()));
}

/*
 *  Function name: query_nisse_rank
 *  Description  : A Nisse function that gives the rank
 *                 that the player has.
 *  Returns      : string - the name of the rank
 */
string
query_nisse_rank()
{
    return (MANAGER->query_nisse_rank(shadow_who->query_real_name()));
}

/*
 *  Function name: expel_nisse
 *  Description  : Expel a club member:
 *                 - Update member list
 *                 - Remove guild token
 *                 - Remove soul and update hooks
 *                 - Log the leaving with the reason
 *  Arguments    : string reason - the reason they are to be expelled
 */
varargs void
expel_nisse(string reason)
{
    object feather;
    object who = query_shadow_who();

    /* Reset start location if they are using the nisse start. */
    if (who->query_default_start_location() == NISSE_START)
        who->set_default_start_location(who->query_def_start());

    /* Update the member list */
    MANAGER->remove_nisse(who->query_real_name());

    /* Remove the guild token */
    feather = present(NISSE_FEATHER_ID, who);
    if (objectp(feather))
    {
        feather->remove_object();
        who->catch_tell("Your hawk feather turns to dust.\n");
        say(QCTNAME(who) + "'s hawk feather turns to dust.\n");
    }

    /* Remove the nisse soul */
    who->remove_cmdsoul(NISSE_SOUL);
    who->update_hooks();

    /* Keep a log of those removed from the guild. */
    MANAGER->rlog(extract(ctime(time()), 4, 15) + " " +
        CAP(who->query_real_name()) + " successfully removed from " +
        "the club because of " + reason + ".\n");

    /* Remove the club shadow */
    who->remove_autoshadow(NISSE_SHADOW);
}

/*
 *  Function name : query_nisse_keep_player
 *  Description   : Test if we want to keep the player in the guild,
 *                  and call expel_nisse() if necessary.
 *                  Reasons for not keeping:
 *                   - Has not logged in for a long time
 *                   - He has been marked to be removed in the manager
 *  Arguments     : who - the player to test
 *  Returns       : 1 if keeping, 0 if not
 */
int
query_nisse_keep_player(object who)
{
    string reason = "";

    /* Wizards are exempt */
    if (who->query_wiz_level())
    {
        return 1;
    }

    /* A Nisse may be marked for expulsion in the manager. */
    if (MANAGER->query_expelled_nisse(who->query_real_name()))
    {
        set_alarm(2.0, 0.0, &expel_nisse("expelled while asleep"));
        return 1;
    }

    /* If a reason is assigned, expel member for the reason given. */
    if (strlen(reason))
    {
        set_alarm(1.0, 0.0, &expel_nisse(reason));
        return 1;
    }
    
    return 1;
}

/* 
 *  Function name: init_nisse_shadow
 *  Description  : A Nisse function. This is called with a slight
 *                 delay after login. It clones the guild item, adds the 
 *                 soul and does other things that are necessary upon login.
 */
void
init_nisse_shadow()
{
    object	player = TO->query_shadow_who();
    object	feather, scroll;
    string	name = player->query_real_name();
    string	rank;
    int		current_age = player->query_age();
    int		join_age, tt;
    string	msg = "A red-tailed hawk swoops into view and drops " +
                      "an ornamented scroll.\nYou catch the ornamented " +
                      "scroll skillfully.\n";

    setuid();
    seteuid(getuid());

    rank = MANAGER->query_nisse_rank(name);

    gMembers = restore_map(NISSE_LOG_DIR + "members");
    join_age = gMembers[name];
    
    if (player->query_gender() != G_FEMALE)
    {
        player->catch_msg("Your gender has changed, males cannot " +
            "be the members of the Nisse Ohtar club.\n");
        player->catch_msg("You have been expelled from the Nisse.\n");
        expel_nisse("changing gender to male");
        return;
    }
    
    if (player->query_prop("_live_i_am_dancer_of_veils"))
    {
        player->catch_msg("The Dancers cannot " +
            "be the members of the Nisse Ohtar club.\n");
        player->catch_msg("You have been expelled from the Nisse.\n");
        expel_nisse("being a Dancer of Veils");
        return;
    }
    
    if (join_age == 0)
    {
        join_age = player->query_age();
    }
    
    tt = current_age - join_age;
    tt = (tt * 2) / 86400;	/* 86400 -- 1 day */

    if (tt > 15 && tt < 30 && rank != "light brown")
    {
        player->catch_msg(msg);
        scroll = clone_object(NEWS_SCROLL);
        scroll->move(player, 1);
        MANAGER->add_to_graduate(name, rank);
    }
    else if (tt > 30 && tt < 45 && rank != "brown")
    {
        player->catch_msg(msg);
        scroll = clone_object(NEWS_SCROLL);
        scroll->move(player, 1);
        MANAGER->add_to_graduate(name, rank);
    }
    else if (tt > 45 && tt < 60 && rank != "deep brown")
    {
        player->catch_msg(msg);
        scroll = clone_object(NEWS_SCROLL);
        scroll->move(player, 1);
        MANAGER->add_to_graduate(name, rank);
    }
    else if (tt > 60 && tt < 75 && rank != "red")
    {
        player->catch_msg(msg);
        scroll = clone_object(NEWS_SCROLL);
        scroll->move(player, 1);
        MANAGER->add_to_graduate(name, rank);
    }
    else if (tt > 75 && tt < 90 && rank != "gold")
    {
        player->catch_msg(msg);
        scroll = clone_object(NEWS_SCROLL);
        scroll->move(player, 1);
        MANAGER->add_to_graduate(name, rank);
    }
    else if (tt > 90 && rank != "bronze")
    {
        player->catch_msg(msg);
        scroll = clone_object(NEWS_SCROLL);
        scroll->move(player, 1);
        MANAGER->add_to_graduate(name, rank);
    }

    shadow_who->add_cmdsoul(NISSE_SOUL);
    shadow_who->update_hooks();

    feather = clone_object(NISSE_FEATHER);

    feather->move(player, 1);

    query_nisse_keep_player(player);
}

public void
autoload_shadow(mixed arg)
{
    ::autoload_shadow(arg);
    
    set_alarm(2.0, 0.0, &init_nisse_shadow()); 
}
