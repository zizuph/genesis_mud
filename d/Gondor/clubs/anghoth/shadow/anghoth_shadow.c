/*
 * anghoth_shadow.c
 *
 * The Anghoth club shadow
 *
 *   Alto, 04 June 2002
 *
 */

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
#include "../anghoth_defs.h"

inherit "/std/shadow";

/* Prototypes */

/* Function name: query_anghoth_member
 * Description  : Is this person a member of the Anghoth club.
 * Returns:       1 if member, 0 if not member
 */
public int
query_anghoth_member()
{
    return (MANAGER->query_anghoth(shadow_who->query_real_name()));
}



/* Function name: query_anghoth_level
 * Description  : Unique Anghoth function to give their membership level.
 *                Options are:
 *                0 - Not an Anghoth
 *                1 - Kriechek
 *                2 - Korrak
 *                3 - Dath
 *                4 - Durub
 */
public int
query_anghoth_level()
{
    return (MANAGER->query_anghoth_level(shadow_who->query_real_name()));
}

/* Function name: query_anghoth_rank
 * Description  : A unique Anghoth function that gives the rank
 *                that the player is in.
 * Returns      : string - the name of the rank
 */
public string
query_anghoth_rank()
{
    return (MANAGER->query_anghoth_rank(shadow_who->query_real_name()));
}

/* Function name: query_ashuk
 * Description  : Unique Anghoth function to test whether ashuk (lost).
 *                Options are:
 *                0 - Not an Ashuk
 *                1 - Ashuk (lost without a sponsor)
 */
public int
query_ashuk()
{
    return (MANAGER->query_ashuk(shadow_who->query_real_name()));
}



/* Function name: expel_anghoth
 * Description  : Expel a club member:
 *                - Reset starting location
 *                - Update member list
 *                - Remove guild token
 *                - Remove soul and update hooks
 *                - Remove from the guildhouse
 *                - Log the leaving with the reason
 * Arguments    : string reason - the reason they are to be expelled
 */
public varargs void
expel_anghoth(string reason)
{
    object emblem;
    object who = query_shadow_who();

    /* Reset start location if they are using the anghoth start. */
    if (who->query_default_start_location() == ANGHOTH_START)
        who->set_default_start_location(who->query_def_start());

    /* Update the member list */
    MANAGER->remove_anghoth(who->query_real_name());

    /* Remove the guild token */
    emblem = present(ANGHOTH_TOKEN_ID, who);
    if (objectp(emblem))
    {
        who->catch_tell("A small black bat snatches your " + emblem->short() + 
            " and flies away with it.\n");
        emblem->remove_object();
    }

    /* Remove the anghoth subloc */
    who->remove_subloc(ANGHOTH_SUBLOC);

    /* Remove the anghoth soul */
    who->remove_cmdsoul(ANGHOTH_SOUL);
    who->update_hooks();

    /* Keep a log of those removed from the guild. */
    MANAGER->rlog(extract(ctime(time()), 4, 15) + " " +
        capitalize(who->query_real_name()) + " successfully removed from " +
        "the club because of " + reason + ".\n");

    /* Remove the club shadow */
    who->remove_autoshadow(ANGHOTH_SHADOW);
//    who->remove_shadow(ANGHOTH_SHADOW);
}


/* Function name: check_banned_race
 * Description  : Tests if the race is allowed in the club.
 *                Starts the expelling of player if necessary.
 * Arguments    : object who - the player to test
 */
public void
check_banned_race(object who)
{
    string race, reason;

    /* Race restrictions */
    race = who->query_race_name();

    if (member_array(race, BANNED_RACE) != -1)
    {
        who->catch_tell("The Anghoth of Morgul do not trust the " 
            + race + " race!\n");
        reason = race + " race";
        expel_anghoth(reason);
        return;
    }
}


/* Function name : query_anghoth_keep_player
 * Description   : Test if we want to keep the player in the guild,
 *                 and call expel_anghoth() if necessary.
 *                 Reasons for not keeping:
 *                  - Has an alignment above the minimum allowed.
 *                  - He has been marked to be removed in the manager
 *                 Calls check_banned_race to expel banned races
 *                 if necessary.
 * Arguments     : who - the player to test
 * Returns       : 1 if keeping, 0 if not
*/
public int
query_anghoth_keep_player(object who)
{
    int align;
    string reason = "";

    /* Wizards are exempt */
    if (who->query_wiz_level())
    {
        return 1;
    }

    /* An Anghoth may be marked for expulsion in the manager. */

    if (MANAGER->query_expelled_anghoth(who->query_real_name()))
    {
        set_alarm(2.0, 0.0, &expel_anghoth("expelled while asleep"));
        return 1;
    }

    /* Wait a little bit to be sure that race shadows are loaded. */
    set_alarm(10.0, 0.0, &check_banned_race(who));

    align = who->query_alignment();

    /* Alignment warning. Give a warning, but keep them. */
    if (align > ALIGN_WARN)
    {
        who->catch_tell("Your heart is in danger of crossing into the "
            + "Light! Your dark Lord is not pleased.\n");
    }

    /* Alignment restriction reached */
    if (align > ALIGN_MIN)
    {
        who->catch_tell("Goodness and virtue stir in your heart, a sickness "
            + "detected by your dark Lord. You are cast from the Anghoth!\n");
        reason = "good alignment: " + align;
    }

    /* If a reason is assigned, expel member for the reason given. */
    if (strlen(reason))
    {
        set_alarm(1.0, 0.0, &expel_anghoth(reason));
        return 1;
    }
    
    return 1;
}

/* 
 * Function name: init_anghoth_shadow
 * Description  : Unique Anghoth function. This is called with a slight 
 *                delay after login. It clones the guild item, adds the 
 *                soul and does other things that are necessary upon login.
 */
void
init_anghoth_shadow()
{
    object player = TO->query_shadow_who(),
           emblem;
    string name = player->query_real_name();
    string rank = MANAGER->query_anghoth_rank(name);
    string sponsor = MANAGER->query_anghoth_sponsor(name);
    int ashuk = MANAGER->query_ashuk(name);

    seteuid(getuid(TO));

    /* Add the soul to the member */
    if (MANAGER->query_anghoth_level(name) > 1)
    {
    shadow_who->add_cmdsoul(ANGHOTH_SOUL);
    shadow_who->update_hooks();
    }

    player->add_subloc(ANGHOTH_SUBLOC, TO);

    /* Add the club token */

    if (ashuk)
    {
        rank = "ashuk";
    }

    switch(rank)
    {
        case "ashuk":
            emblem = clone_object(ANGHOTH_ASHUK_TOKEN);
            break;
        case "korrak":
            emblem = clone_object(ANGHOTH_KORRAK_TOKEN);
            break;
        case "dath":
            emblem = clone_object(ANGHOTH_DATH_TOKEN);
            break;
        case "durub":
            emblem = clone_object(ANGHOTH_DURUB_TOKEN);
            break;
        default:
            emblem = clone_object(ANGHOTH_KRIECHEK_TOKEN);
            break;
    }

    emblem->move(player, 1);
    emblem->set_emblem_short(player);
    emblem->set_emblem_long(player);


    switch(ashuk)
    {
        case 0:
            player->catch_tell("Your Lord " + sponsor + " calls you to "
                + "service once again, " + CAP(rank) + " Angoth\n");
            break;
        case 1:
            player->catch_tell("You are lost, Ashuk Anghoth! You must seek "
                + "the honour of shielding a new Lord!\n");
            break;
        default:
            break;
    }

    query_anghoth_keep_player(player);

}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - the subloc string
 *                on      - the wearer
 *                for_obj - the one looking
 * Returns:       The string that is to be seen (subloc)
 */
string
show_subloc(string subloc, object on, object for_obj)
{
    string rank;
    object player = TO->query_shadow_who();

    string name = on->query_real_name();
    int ashuk = MANAGER->query_ashuk(name);

    rank = MANAGER->query_anghoth_rank(name);
    rank = capitalize(rank);

    if (subloc != ANGHOTH_SUBLOC)
	       return player->show_subloc(subloc, on, for_obj);

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
  
    if (for_obj == on)
    {
        if(ashuk)
        {
            return "You are marked as Ashuk Anghoth, Lost Shield of Morgul.\n";
        }
        return "You are marked as a " + rank + " Anghoth, Shield of Morgul.\n";
    }
    else
    {
        if(for_obj->query_morgul_level() || for_obj->query_anghoth_level())
        {
            if(ashuk)
            {
                return CAP(PRONOUN(on)) + " is marked an Ashuk Anghoth, "
                + "Lost Shield of Morgul.\n";
            }
            return CAP(PRONOUN(on)) + " is marked a " + rank + " Anghoth, "
            + "Shield of Morgul.\n";
        }
        return "";
    }
}

/* 
 * Function name: change_tokens
 * Description  : Unique Anghoth function. Used to replace rank-specific
 *                token after promotion/demotion.
 */
int
change_tokens(string rank)
{
    object player = TO->query_shadow_who(),
           emblem, old_emblem;
    object *inv;
    string name = player->query_real_name();
    inv = all_inventory(player);
    rank = lower_case(rank);

    if (!sizeof(filter(inv, &->id(ANGHOTH_TOKEN_ID))))
    {
        return 0;
    }

    /* Remove the old guild token */
    old_emblem = present(ANGHOTH_TOKEN_ID, player);
    if (objectp(old_emblem))
    {
        old_emblem->remove_object();
    }

    switch(rank)
    {
        case "korrak":
            emblem = clone_object(ANGHOTH_KORRAK_TOKEN);
            break;
        case "dath":
            emblem = clone_object(ANGHOTH_DATH_TOKEN);
            break;
        case "durub":
            emblem = clone_object(ANGHOTH_DURUB_TOKEN);
            break;
        case "ashuk":
            emblem = clone_object(ANGHOTH_ASHUK_TOKEN);
            break;
        default:
            emblem = clone_object(ANGHOTH_KRIECHEK_TOKEN);
            break;
    }

    /* Add the new guild token */
    emblem->move(shadow_who, 1);
    emblem->set_emblem_short(shadow_who);
    emblem->set_emblem_long(shadow_who);

    return 1;
}


public void
autoload_shadow(mixed arg)
{
    ::autoload_shadow(arg);
        set_alarm(2.0, 0.0, &init_anghoth_shadow()); 
}

