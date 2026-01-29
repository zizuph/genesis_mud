/*
 * File:     monklib.c
 * Created:  Cirion, 1998.4.25
 * Purpose:  This file is to be inherited by everything in
 *           the monk guild. It contains some global functions
 *           that all objects should be able to call.
 * Note:     All functions should be preceeded by an 'm_', to
 *           indicate that they are part of the standard monk
 *           library.
 * Caveat:   All checks within the guild should use these functions
 *           whenever possible. This allows us to globally define
 *           the behavior of certain checks, and makes maintaining
 *           the code much easier. I know from experience that
 *           when you have a dozen individual checks throughout
 *           the guild for the same thing, changing the behavior
 *           of that check can be a nightmare.
 * Caveat 2: Most functions have been declared varargs to allow
 *           an easy interface to the these functions. Typically,
 *           the default for a certain check (when it is checking
 *           a player) is this_player(). When creating new functions,
 *           options should be appended to the end, in the
 *           order of the most frequently non-default being first.
 *
 * WARNING:  When the monk guild is open, this file MUST ALWAYS
 *           LOAD. Failure to load will cause the entire monk
 *           guild to shut down, and possibly have a permanent
 *           effect on saved data. When making changes and additions
 *           to this file, make sure to test loading on a copy
 *           of the file loads before updating this particular file.
 */
#pragma strict_types

#include "defs.h"
#include <ss_types.h>  /* Skill types (SS_OCCUP, et. al.) */
#include <composite.h> /* COMPOSITE_WORDS                 */
#include <std.h>       /* SECURITY                        */
#include <time.h>      /* CONVTIME()                      */

inherit MONK_LIB + "support";
inherit MONK_LIB + "voting";

// the object used for creating and sending mail
#define RESET_EUID                seteuid(getuid(this_object()))

#define GENDER_SWITCH(who, male, female)   (who->query_gender() != G_FEMALE ? (male) : (female))

varargs int m_move_from_old_guild(object who = this_player());
varargs int m_is_old_member(object who = this_player());
static void m_remove_member(object who, int type);

/*
 * Function name: m_query_guild_state
 * Description:   The guild may be open or closed. This will
 *                return the state of the guild. If it is closed,
 *                training, etc. will be disabled.
 * Returns:       The state of the guild (MONK_GUILD_STATE_OPEN or
 *                    MONK_GUILD_STATE_CLOSED)
 */
static int
m_query_guild_state ()
{
    // todo: add in ability to close and open the guild.
    return MONK_GUILD_STATE_OPEN;
}



/*
 * Function name: m_list_council_members
 * Description:   Returns the names of all the council members
 * Returns:       The names of council members
 */
public string *
m_list_council_members()
{
    mapping mem;
    int     num_council, i;
    string  *ind, who;
    string  *councils = ({});

    mem = MANAGER->query_members();

    num_council = 0;
    ind = m_indices(mem);

    for(i=0;i<m_sizeof(mem);i++)
    {
        who = ind[i];

        if(mem[who][1])
            councils += ({ who });
    }

    return councils;
}


/*
 * Function name: m_query_may_join()
 * Description:   Checks to see if a certain player may
 *                join the monks.
 *                
 * Arguments:     guild_type: SS_OCCUP to check for occupational,
 *                SS_LAYMAN to check for layman.
 * Returns:       1 if the player may join, or the failure
 *                string if the player is not permitted.
 */
varargs static mixed
m_query_may_join(int guild_type, object who = this_player())
{
    return 1;
}


/*
 * Function name: m_query_active_members
 * Description:   Gets a list of all the players that are currently
 *                on as monks.
 * Arguments:     filter_wizards: 1 if you want to filter out all
 *                    wizards from the list (default is 0)
 *                guild_type: -1 for a list of all active monks
 *                            SS_OCCUP for all occupational monks
 *                            SS_LAYMAN for all lay monks
 * Returns:       An array of OBJECTS of the currently active monks
 */
varargs static object *
m_query_active_members(int filter_wizards = 0, int guild_type = -1)
{
    object *monks;

    /* Get a list of all the actve monks.   */
    monks = filter(users(), &m_query_monk(, guild_type));

    /* Now filter out all the wizards and JRs if we specified to do so */
    if(filter_wizards)
        monks -= filter(monks, m_query_wizard_or_jr);

    return (monks - ({ 0 }));
}


/*
 * Function name: m_tell_guild_masters
 * Description:   Send a message to all active guild masters
 *                
 * Arguments:     str: The string to send
 *                importance: The importance of the message. This may, in
 *                   the future, be compared against some preference
 *                   the wizard may set for the verbosity of messages
 *                   they receive. Default is 1 (most important).
 *                preface: The string to preface the message with (default
 *                   is " - Kaheda guild master message")
 * Returns:       void
 * Note:          Use this for debugging, or important status messages
 */
static void
m_tell_guild_masters(string str, int importance = 1,
                     string preface = " - Kaheda guild master message")
{
    object    *people;
    string     msg;

    if(strlen(preface))
        msg = preface + ": " + str;
    else
       msg = str;

    people = filter(users(), m_query_is_guild_master);

    people->catch_tell(msg);
}



/*
 * Function name: m_throw
 * Description:   Log an error message as well as throwing
 *                a runtime error.
 * Arguments:     str - the message
 * Returns:       void
 */
void
m_throw(string str)
{
    m_log(str);
    throw(str);
}

/*
 * Function name: m_clone_here
 * Description:   cover function to clone an object and move
 *                it to this_object()
 * Arguments:     file - the filename to clone
 *                prevent - string or object. If the specified
 *                    arg is present in this object, we will not
 *                    clone the object (used for NPCs, etc).
 *                init_proc - name of a function to call in an
 *                    object once it is cloned and moves. E.g.,
 *                    "arm_me" for NPCs.
 *                composite_desc - string or func to show in the composite desc
 *                    of the room representing this object (for NPCs).
 * Returns:       object pointer of the cloned object, or 0 if failed
 */
static varargs object
m_clone_here (string file, mixed prevent = 0, string init_proc = "", mixed composite_desc = 0)
{
    object ob;

    if(prevent)
    {
        if(objectp(prevent)) // check to see if the object is in this room
            if (present (prevent, TO))
                return 0;
        else if(stringp(prevent))
            if (present (prevent, TO))
                return 0;

    }

    RESET_EUID; // set the user ID so I can clone things

    // allow partly qualified path names
    if(!wildmatch("/*", file))
        file = MONK_OBJ + file;

    ob = clone_object (file);
    ob->move(TO, 1);

    if (strlen(init_proc)) // call the initialization function, if specified
        call_other(ob, init_proc);

    if(functionp(composite_desc) || strlen(composite_desc))
    {
        ob->set_monk_room_composite(composite_desc, this_object());
        this_object()->set_composite_npc(ob); // enable the compiste desc in the room (see room_base)
    }

    return ob;
}




/******************************************************************
 *        Title functions
 */

/*
 * Function name: m_query_guild_rank
 * Description:   Returns the numeric "rank" in the guild.
 *                It is based on the following formula:
 *                10% focus skill
 *                10% unarmed combat skill
 *                10% wisdom stat
 *                30% guild stat
 *                40% time in guild
 * Arguments:     
 * Returns:       The numeric guild rank (1-100)
 */
varargs static int
m_query_guild_rank(object who = this_player())
{
    int focus, ua_combat, wisdom, gstat, guild_time, rank;
    mixed member_data;

    focus = who->query_skill(MONK_SKILL_FOCUS);
    ua_combat = who->query_skill(SS_UNARM_COMBAT);
    wisdom = who->query_stat(SS_WIS);

    if(m_query_monk(who, SS_OCCUP))
        gstat = who->query_stat(SS_OCCUP);
    else
        gstat = who->query_stat(SS_LAYMAN);

    member_data = (MANAGER->query_members())[m_get_name(who)];
    if(sizeof(member_data))
        guild_time = time() - member_data[0]; // get the join time for that member

    if(guild_time <= 0)
        guild_time = 1;

    guild_time /= (60 * 60 * 24 * 30); // number of months (approx.) the player has been in the guild

    rank = (((10 * focus) / 100) +
        ((10 * ua_combat) / 100) +
        ((10 * wisdom) / 100) +
        ((30 * gstat) / 100) +
        ((40 * guild_time) / 100));



    return MIN(rank, 100);
}


/*
 * Function name: m_query_alignment_rank
 * Description:   Returns the textual description of
 *                the player's alignment rank, for use
 *                in the player's title.
 * Arguments:     the alignment int to check
 * Returns:       the string of the title's alignment description
 */
static string
m_query_alignment_rank(int align)
{
    switch(align)
    {
        case 860 .. 1200:
            return "Resplendent";
            break;
        case 600 .. 859:
            return "Radiant";
            break;
        case 400 .. 599:
            return "Luminescent";
            break;
        case 200 .. 399:
            return "Lustrous";
            break;
        case -199 .. 199:
            return "Shadowwalking";
            break;
        case -399 .. -200:
            return "Onyx";
            break;
        case -599 .. -400:
            return "Ebon";
            break;
        case -859 .. -600:
            return "Obsidian";
            break;
        default:
            return "Stygian";
            break;
    }
}


/*
 * Function name: m_query_title_rank
 * Description:   Returns the rank part of the title for
 *                the player.
 * Arguments:     who - the player to check
 *                male - the male title
 *                female - the female title
 * Returns:       "counsellor" if the player is on the council,
 *                else male argument for male or neuther players,
 *                female argument for female players.
 */
varargs public string
m_query_title_rank(object who, string male, string female = male)
{
    string              prefix;

    prefix = "";

    if(m_query_punishment(who, M_PUNISH_DISGRACE))
        prefix = "Disgraced ";

    if(m_query_council_member(who))
        return prefix + "Councillor";
    else if(m_query_elder(who))
        return prefix + "Elder";
    else
        return prefix + GENDER_SWITCH(who, male, female);
}

/*
 * Function name: m_query_title_base
 * Description:   returns the base title of the player in
 *                the guild.
 *                Possible titles are:
 * Fledgling of Segoy, Acolyte of the Dragon Order
 * Seeker of Segoy, Acolyte of the Dragon Order
 * Learned of Segoy, Acolyte of the Dragon Order
 * Loremaster/Loremistress of Segoy, High Acolyte of the Dragon Order
 * Initiate of Dragons, Elder Acolyte of the Dragon Order
 * Disciple of Dragons, Novice Priest/Priestess of the Dragon Order
 * Initiate of Mysteries, Priest/Priestess of the Dragon Order
 * Adept of Mysteries, Priest/Priestess of the Dragon Order
 * Master/Mistress of Mysteries, Priest/Priestess of the Dragon Order
 * Dragon Adept of the Chimerical Vision, Elder Priest/Priestess of the Dragon Order
 * Dragon Sage of the Ancient Gremayre, Elder Priest/Priestess of the Dragon Order
 * Dragonmaster/Dragonmistress of the Rising Dawn, High Priest/Priestess of the Dragon Order
 * Dragonmaster/Dragonmistress of the Elyzerin Sun, High Priest/Priestess of the Dragon Order
 * Dragonmaster/Dragonmistress of the Harvest Twilight, High Priest/Priestess of the Dragon Order
 * Dragonmaster/Dragonmistress of the Tempest Moon, High Priest/Priestess of the Dragon Order
 * Dancer on the West Wind, High Priest/Priestess of the Dragon Order
 *
 * Arguments:     The player for whom to check
 * Returns:       the base title
 */
static varargs string
m_query_title_base (object who = this_player())
{
    int rank;
    int	occup;
    int is_elder;
    string ret;

    rank = m_query_guild_rank(who);
    ret = "";


    if (m_query_council_member(who))
        ret = MANAGER->get_council_title (who->query_real_name ());

    occup = m_query_monk(who, SS_OCCUP);
    is_elder = m_query_elder (who);

    switch(rank)
    {
        case 0 .. 5:
            if (ret == "")
                ret = "Fledgling of Segoy";

            if(occup)
                ret += ", " + m_query_title_rank(who, "Acolyte")
                + " of "
                + "the Dragon Order";
            break;
        case 6 .. 10:
            if (ret == "")
                ret = "Seeker of Segoy";

            if(occup)
                ret += ", " + m_query_title_rank(who, "Acolyte")
                + " of the "
                + "Dragon Order";
            break;
        case 11 .. 15:
            if (ret == "")
                ret = "Learned of Segoy";

            if(occup)
                ret += ", " + m_query_title_rank(who, "Acolyte")
                + " of the"
                + "Dragon Order";
            break;
        case 16 .. 20:
            if (ret == "")
                ret = GENDER_SWITCH(who, "Loremaster", "Loremistress")
                    + " of Segoy";


            if(occup)
                ret += ", High " + m_query_title_rank(who, "Acolyte")
                + " of the Dragon Order";
            break;
        case 21 .. 30:
            if (ret == "")
                ret = "Initiate of Dragons";

            if(occup)
                ret += ", Eminent " + m_query_title_rank(who, "Acolyte")
                + " of the Dragon Order";
            break;
        case 31 .. 35:
            if (ret == "")
                ret = "Disciple of Dragons";

            if(occup)
                ret += ", "
                + m_query_title_rank(who, "Novice Priest", "Novice Priestess")
                + " of the Dragon Order";
            break;
        case 36 .. 40:
            if (ret == "")
                ret = "Initiate of Mysteries";

            if(occup)
                ret += ", " + m_query_title_rank(who, "Priest", "Priestess")
                + " of the Dragon Order";
            break;
        case 41 .. 45:
            if (ret == "")
                ret = "Adept of Mysteries";

            if(occup)
                ret += ", "
                + m_query_title_rank(who, "Priest", "Priestess")
                + " of the "
                + "Dragon Order";
            break;
        case 46 .. 50:
            if (ret == "")
                ret = m_query_title_rank(who, "Master", "Mistress")
                + " of Mysteries";

            if(occup)
                ret += ", "
                + m_query_title_rank(who, "Priest", "Priestess")
                + " of the Dragon Order";
            break;
        case 51 .. 55:
            if (ret == "")
                ret = "Dragon Adept of the Chimerical Vision";

            if(occup)
                ret += ", "
                + "Eminent "
                + m_query_title_rank(who, "Priest", "Priestess")
                + " of the Dragon Order";
            break;
        case 56 .. 60:
            if (ret == "")
                ret = "Dragon Sage of the Ancient Gremayre";

            if(occup)
                ret += ", "
                + "Eminent "
                + m_query_title_rank(who, "Priest", "Priestess")
                + " of the Dragon Order";
            break;
        case 61 .. 70:
            if (ret == "")
                ret = GENDER_SWITCH(who, "Dragonmaster", "Dragonmistress")
                + " of the Rising Dawn";

            if(occup)
                ret += ", High "
                + m_query_title_rank(who, "Priest", "Priestess")
                + " of the Dragon Order";
            break;
        case 71 .. 80:
            if (ret == "")
                ret = GENDER_SWITCH(who, "Dragonmaster", "Dragonmistress")
                + " of the Elyzerin Sun";

            if(occup)
                ret += ", High "
                + m_query_title_rank(who, "Priest", "Priestess")
                + " of the Dragon Order";
            break;
        case 81 .. 90:
            if (ret == "")
                ret = GENDER_SWITCH(who, "Dragonmaster", "Dragonmistress")
                + " of the Harvest Twilight";

            if(occup)
                ret += ", High "
                + m_query_title_rank(who, "Priest", "Priestess")
                + " of the Dragon Order";
            break;
        case 91 .. 95:
            if (ret == "")
                ret = GENDER_SWITCH(who, "Dragonmaster", "Dragonmistress")
                + " of the Tempest Moon";

            if(occup)
                ret += ", High "
                + m_query_title_rank(who, "Priest", "Priestess")
                + " of the Dragon Order";
            break;
        default:
            if (ret == "")
                ret = "Dancer on the West Wind";

            if(occup)
                ret += ", High "
                + m_query_title_rank(who, "Priest", "Priestess")
                + " of the Dragon Order";
            break;

    }

    // layman Elders need "Elder" in their title, which usually
    // ends up in the second part (which lay members do not have).
    if (!occup && is_elder)
	ret = "Elder " + ret;

    if (ret == "")
        ret = "Strange Monk of the Dragon Order";

    return ret;
}

/*
 * Function name: m_query_title
 * Description:   returns the full title for the player
 *                in question
 * Arguments:     The player for whom to check
 * Returns:       the title of the player
 */
static string
m_query_title(object who)
{
    return m_query_alignment_rank(who->query_alignment())
        + " " + m_query_title_base(who);
}




/******************************************************************
 *        Shadow / Login functions
 */
/*
 * Function name: m_login
 * Description:   Called by the shadow one second after the
 *                player logs in. Will do the following:
 *                1 - check to see if the player is on
 *                    the members list. If not, it will
 *                    add them and log the wierd fact.
 *                2 - check to see if the player is
 *                    banished, boot them if they are.
 *                3 - add the command soul, update hooks
 *                4 - check for any special messages the
 *                    player should receive (e.g., "You
 *                    have been promoted to the Council")
 * Arguments:     who: the player object
 *                type: the guild type (SS_OCCUP, SS_LAYMAN)
 *                calling_shadow: the shadow object
 * Returns:       void
 */
void
m_login(object who, int guild_type, object calling_shadow)
{
    string soul_name;

    if(!living(who))
        return;

    RESET_EUID;

    // 1. Check if they are on the list
    if(interactive(who) && !m_query_monk(who, guild_type))
    {
        m_log("ERR: " + who->query_name() + " logged in with the "
            + "shadow, but was not on the members list. Attempting "
            + "to add member to the list.");

        if(!m_add_member(who))
        {
            m_log("ERR: " + who->query_name() + " could not be added to "
                + "the members list. Removing shadow.");

            // punt
            who->remove_autoshadow(calling_shadow); // get rid of the autoshadow entry...
            calling_shadow->remove_shadow(); // ...as well as the actual shadow

            return;
        }
    }

    // 2. Check if they are banished
    if(m_query_punishment(who, M_PUNISH_BANISH))
    {
        who->catch_tell("You have been banished from the monks.\n");
        m_remove_member(who, guild_type);
        m_log(who->query_name() + " logged on and was banished.");
        return;
    }

    // 3. Set council info, if they are a council member
    if(m_query_council_member(who))
    {
        MANAGER->set_council_info(who->query_real_name());
    }

    soul_name = MONK_SOUL + "soul";
    who->add_cmdsoul(soul_name);
    who->update_hooks();
}

/******************************************************************
 *        Joining/leaving/applying functions & commands
 */

/*
 * Function name: m_do_apply
 * Description:   Command to apply for membership in the
 *                guild.
 * Arguments:     argument passed to the command
 * Returns:       1 if the command was successful
 */
public int
m_do_apply(string str)
{
    int    guild_type;

    notify_fail("Apply to which branch? occupational or layman?\n");
    if(!strlen(str))
        return 0;

    if(str == "occupational")
        guild_type == SS_OCCUP;
    else if(str == "layman")
        guild_type == SS_LAYMAN;
    else
        return 0;

    if(m_query_monk())
    {
        notify_fail("You are already a member.\n");
        return 0;
    }

    // only need to apply if there is a council
    if(!m_count_council_members())
    {
        notify_fail("Since there is currently no council, "
            + "it is not necessary to apply. You can "
            + "simply join the guild.\n");
        return 0;
    }

    if(!m_apply(this_player(), guild_type))
        return 0; // m_apply() handles notify_fail() for failures

    write("You apply for membership to the "
        + str + " branch of the monks. You can later "
        + "check the status your application with "
        + "\"check application\" in this area.\n");
    return 1;
}

/*
 * Function name: m_do_application_stat
 * Description:   Check on the status of your
 *                application.
 * Arguments:     argument passed to the command
 * Returns:       1 if the command executed successfully
 */
public int
m_do_application_stat(string str)
{
    string name = this_player()->query_real_name();
    int    stat;

    notify_fail(capitalize(query_verb()) + " what? Application?\n");
    if(str != "application")
        return 0;

    stat = MANAGER->query_application_status(name);

    if(stat == 0) // already applied, no decision
    {
        write("You have already submitted your application "
            + "for membership. No decision has yet been made.\n");
        return 1;
    }

    if(stat == 1) // already been accepted
    {
        write("Your application for membership has been accepted.\n");
        return 1;
    }

    if(stat == -1) // already been rejected
    {
        /*
        notify_fail("Your application has been rejected. You can "
            + "apply again for membership in "
            + CONVTIME(MANAGER->query_application_time_left(name))
            + ".\n");
        */

        write("Your application has been rejected. You may "
            + "reapply for membership now if you so choose.\n");
        return 1;
    }

    write("You have not applied for membership.\n");
    return 1;
}


/*
 * Function name: m_do_join_guild
 * Description:   Command to allow joining into the
 *                monks. Check for other guild,
 *                application status, etc.
 * Arguments:     the argument - either "occupational"
 *                    or "layman"
 *                no_skill_remove - set to 1 ro prevent
 *                    clearing out skills (for the transfer from
 *                    old monk guild to new)
 * Returns:       1 if the command executed successfuly
 */
varargs public int
m_do_join_guild(string str, int no_skill_remove = 0)
{
    string    name, shadow_name, soul, guild_type, guild_style, guild_name;
    int       type, stat, ret, result, guild_tax;
    object    shadow, emblem, tp;

    tp = this_player();

    name = tp->query_real_name();

    notify_fail("Dedicate youself to which branch of the order? "
        + "Occupational or layman?\n");
    if(!strlen(str))
        return 0;

    sscanf(str, "myself %s", str);
    sscanf(str, "to %s", str);
    sscanf(str, "the %s", str);

    if(str == "occupational")
        type = SS_OCCUP;
    else if(str == "layman")
        type = SS_LAYMAN;
    else
        return 0;

    if(tp->m_query_monk())
    {
        notify_fail("You are already a member.\n");
        return 0;
    }

    // If there are council members, we need to apply
    // before we can join. Check the application status.
    if(m_count_council_members() && !no_skill_remove)
    {
        stat = MANAGER->query_application_status(name);

        if(stat == 0) // already applied, no decision
        {
            notify_fail("You application for membership has not "
                + "yet been approved.\n");
            return 0;
        }

        if(stat == -2) // no application
        {
            notify_fail("You must first apply for membership before "
                + "you may join.\n");
            return 0;
        }

        if(stat == -1) // rejected
        {
            notify_fail("Your application for membership has been "
                + "rejected. You can re-apply in "
                + CONVTIME(MANAGER->query_application_time_left())
                + ".\n");
            return 0;
        }
    }

    // perform any additional joining check. m_query_may_join()
    // will handle notify_fail() for failures.
    if(!m_query_may_join(type, tp))
        return 0;

    // add the appropriate shadow
    if(type == SS_LAYMAN)
    {
        shadow = clone_object(MONK_LAY_SHADOW);
        // emblem = clone_object(MONK_LAY_EMBLEM);
        soul = MONK_LAY_SOUL;
        shadow_name = MONK_LAY_SHADOW;
        guild_type = MONK_LAY_TYPE;
        guild_style = MONK_LAY_STYLE;
        guild_name = MONK_LAY_NAME;
        guild_tax = MONK_LAY_TAX;
    }
    else if(type == SS_OCCUP)
    {
        shadow = clone_object(MONK_OCC_SHADOW);
        // emblem = clone_object(MONK_OCC_EMBLEM);
        soul = MONK_OCC_SOUL;
        shadow_name = MONK_OCC_SHADOW;
        guild_type = MONK_OCC_TYPE;
        guild_style = MONK_OCC_STYLE;
        guild_name = MONK_OCC_NAME;
        guild_tax = MONK_OCC_TAX;
    }
    else
    {
        notify_fail("Something goes wrong -- please leave a bug report.\n");
        return 0;
    }

    // inform wizards what they must do, since only a wizard
    // can add a shadow and soul to themselves
    if(tp->query_wiz_level())
        write("Since you are a wizard, you will need to execute "
            + "the following commands:\n"
            + "Call me add_autoshadow " + shadow_name + ":\n"
            + "Call me add_cmdsoul " + soul + "\n"
            + "newhooks\n");


    if((result = shadow->shadow_me(tp, guild_type, guild_style, guild_name)) != 1)
    {
        notify_fail("Something has gone wrong!\nYour shadow quivers and "+
            "seems to fade slightly.\n");
        m_log("ERROR: " + tp->query_real_name() + " failed to "
            + "have " + shadow_name
            + " shadow added when joining. Result code was " + result);

        shadow->remove_shadow();
        return 0;
    }
   
    // colone the emblem to the player, if there is one
    if(objectp(emblem))
        emblem->move(tp, 1);

    // add the command soul, give the commands to the player
    tp->add_cmdsoul(soul);
    tp->update_hooks();

    if(!no_skill_remove)
    {
        // set the guild stat & prefs
        tp->clear_guild_stat(type);
        tp->set_guild_pref(type, guild_tax);

        // Make sure the guild skills are clear
        tp->remove_skill(MONK_SKILL_FOCUS);
        tp->remove_skill(MONK_SKILL_STRIKE);
        tp->remove_skill(MONK_SKILL_PLEXUS);
    }

    // add the member to the member list
    ret = MANAGER->add_member(name, type);

    // remove their application
    m_remove_application(name);

    // log the event
    m_log(capitalize (name) + " joined the " + str + " branch.");

    write("You join the " + str + " branch of the monks.\n");
    write("Enter 'help monks' for commands and other information.\n");
    return 1;
}


/*
 * Function name: m_transfer_branch
 * Description:   Transfer the selected member to the specified
 *                branch of the monks.
 * Arguments:     who - the player to transfer
 *                to_branch - the branch (SS_LAYMAN or SS_OCCUP)
 * Returns:       1 if successful
 */
public int
m_transfer_branch (object who, int to_branch)
{
    string      name, shadow_name, soul, guild_type, guild_style, guild_name,
		old_shadow;
    int         stat, guild_tax, result, ret, old_branch;
    object      shadow, emblem;

    // this removes the shadow: don't call it in the shadow!
    if(this_object()->query_monk_shadow())
        throw ("Must not be called in the shadow!");


    if(to_branch == SS_LAYMAN)
    {
	old_branch = SS_OCCUP;
        shadow = clone_object(MONK_LAY_SHADOW);
        soul = MONK_LAY_SOUL;
        shadow_name = MONK_LAY_SHADOW;
        guild_type = MONK_LAY_TYPE;
        guild_style = MONK_LAY_STYLE;
        guild_name = MONK_LAY_NAME;
        guild_tax = MONK_LAY_TAX;

	old_shadow = MONK_OCC_SHADOW;

        present(MONK_OCC_EMBLEM, who)->remove_object();
        who->remove_cmdsoul(MONK_OCC_SOUL);
        who->update_hooks();

    }
    else if(to_branch == SS_OCCUP)
    {
	old_branch = SS_LAYMAN;
        shadow = clone_object(MONK_OCC_SHADOW);
        soul = MONK_OCC_SOUL;
        shadow_name = MONK_OCC_SHADOW;
        guild_type = MONK_OCC_TYPE;
        guild_style = MONK_OCC_STYLE;
        guild_name = MONK_OCC_NAME;
        guild_tax = MONK_OCC_TAX;

	old_shadow = MONK_LAY_SHADOW;

        present(MONK_LAY_EMBLEM, who)->remove_object();
        who->remove_cmdsoul(MONK_LAY_SOUL);
        who->update_hooks();
    }


    // remove the old shadow
    who->remove_autoshadow(old_shadow);

    who->query_monk_shadow()->remove_shadow();

    /*** This seems to fail randomly!
    if(who->query_monk_shadow())
    {
        notify_fail("Something has gone wrong!\nYour shadow refuses to "+
            "leave you.\nPlease make a bug report..\n");
        m_log("ERROR: " + who->query_real_name() + " failed to "
            + "have " + file_name(who->query_monk_shadow())
            + " removed on transfer.");

	return 0;
    }
    ***/

    // Change the member's guild type
    ret = MANAGER->set_guild_type(who, to_branch);

    if((result = shadow->shadow_me(who, guild_type, 
        guild_style, guild_name)) != 1)
    {
        notify_fail("Something has gone wrong!\nYour shadow quivers and "+
            "seems to fade slightly.\n");
        m_log("ERROR: " + who->query_real_name() + " failed to "
            + "have " + shadow_name
            + " shadow added when transferring branches. "
	    + "Result code was " + result);

        shadow->remove_shadow();
        return 0;
    }


    // colone the emblem to the player, if there is one
    if(objectp(emblem))
        emblem->move(who, 1);

    // add the command soul, give the commands to the player
    who->add_cmdsoul(soul);
    who->update_hooks();

    // transfer guild stats
    who->set_guild_stat(to_branch,
	who->query_acc_exp(old_branch));
    who->clear_guild_stat(old_branch);

    // set the guild stat & prefs
    who->set_guild_pref(to_branch, guild_tax);
    who->set_guild_pref(old_branch, 0);

    // guild skills don't decay: force them to be set to their
    // maximum for the layman branch.
    if(to_branch == SS_LAYMAN)
    {
        who->set_skill(MONK_SKILL_FOCUS, 
            min(MAX_LAY_FOCUS, who->query_skill(MONK_SKILL_FOCUS)));
        who->set_skill(MONK_SKILL_STRIKE, 
            min(MAX_LAY_STRIKE, who->query_skill(MONK_SKILL_STRIKE)));
        who->set_skill(MONK_SKILL_PLEXUS, 
            min(MAX_LAY_PLEXUS, who->query_skill(MONK_SKILL_PLEXUS)));
    }

    if(who->query_wiz_level())
    {
        write("Since you are a wizard, you will need to execute "
            + "the following commands:\n"
            + "Call me add_autoshadow " + shadow_name + ":\n"
            + "Call me add_cmdsoul " + soul + "\n"
            + "newhooks\n");
    }

    m_log(who->query_real_name() + " transferred membership to the "
	+ (to_branch == SS_OCCUP ? "occupational" : "layman")
	+ " branch with success: " + m_query_monk (who, to_branch));

    return ret;
}

/*
 * Function name: m_do_transfer_branch
 * Description:   Command to transfer branches
 * Arguments:     arg - the argument to the command.
 * Returns:       1 if successful
 */
public int
m_do_transfer_branch (string arg)
{
    object tp = this_player();
    string warn_prop = "_monk_i_warned_about_transferring";
    int type;

    if(!m_query_monk(tp))
    {
	notify_fail("You must be a monk in the first place.\n");
	return 0;
    }

    if(arg == "occupational")
	{
	type = SS_OCCUP;

	if(tp->query_guild_name_occ())
	    {
	    notify_fail("You are already a member of an occupational "
		+ "guild. You will need to leave it before you "
		+ "can transfer.\n");
	    return 0;
	    }
	}
    else if(arg == "layman")
	{
	type = SS_LAYMAN;

	if(tp->query_guild_name_lay())
	    {
	    notify_fail("You are already a member of a layman "
		+ "guild. You will need to leave it before you "
		+ "can transfer.\n");
	    return 0;
	    }
	}
    else
    {
	notify_fail(capitalize(query_verb()) + " to which branch? "
	    + "Occupational or layman?\n");
	return 0;
    }

    if(m_query_monk(tp, type))
    {
	notify_fail("You are already a member of the " + arg
	    + " branch.\n");
	return 0;
    }

    // give them a warning about the significance of their actions
    if(!tp->query_prop(warn_prop))
    {
	write("Are you sure you want to transfer your membership "
	    + "to the " + arg + " branch?\n");
	if(type == SS_LAYMAN)
	    write("Your special skills will be reduced to the maximum "
		+ "allowed for the layman branch.\n");
	write("Enter the command again to confirm.\n");

	tp->add_prop(warn_prop, 1);

	return 1;
    }

    if(m_transfer_branch(tp, type))
	write("You successfully transfer your membership to the "
	    + arg + " branch.\n");
    else
	write("Something goes wrong. Please leave a bug report.\n");

    return 1;
}

/*
 * Function name: m_delay_remove_shadow
 * Description:   Remove the specified shadow. This is in
 *                an alarm, because the object calling any
 *                removal functions may be the shadow itself.
 *                Thus, we need to be sure that the shadow
 *                is not removed until all other functions
 *                have completed execution.
 * Arguments:     shadow - the shadow object to remove
 * Returns:       void
 */
void
m_delay_remove_shadow(object shadow)
{
    shadow->remove_shadow(); // ...as well as the actual shadow
}

/*
 * Function name: m_remove_member
 * Description:   Handles all the mechanics for removing a player
 *                from the monks:
 *                1. removes shadows, soul, emblem
 *                2. Clears guild-related skills
 *                3. Removes from the member list
 * Arguments:     who: player to be removed
 *                type: type of guild to remove (SS_OCCUP, SS_LAYMAN)
 * Returns:       void
 */
static void
m_remove_member(object who, int type)
{
    object shadow;

    m_log("Trying to remove " + who->query_name() + "( of type "
        + type + " ) from the monks.");

    // 1. Remove soul, shadow, emblem
    if(type == SS_LAYMAN)
    {
        present(MONK_LAY_EMBLEM, who)->remove_object();
        who->remove_cmdsoul(MONK_LAY_SOUL);
        who->update_hooks();
    }
    else
    {
        present(MONK_OCC_EMBLEM, who)->remove_object();
        who->remove_cmdsoul(MONK_OCC_SOUL);
        who->update_hooks();
    }

    shadow = who->query_monk_shadow();

    if(!shadow) // sort of a hack, since the object inheriting the monklib might be the shadow itself!
        shadow = this_object()->query_monk_shadow();

    if(!objectp(shadow))
        m_log("ERROR: shadow was 0");
    else
    {
        m_log("Trying to remove shadow: " + file_name(shadow));

        who->remove_autoshadow(MASTER_OB(shadow)); // get rid of the autoshadow entry
        // remove the shadow via an alarm, since this may have been called from
        // the shadow itself, and we need to complete processing.
        set_alarm(2.0, 0.0, &m_delay_remove_shadow(shadow));
    }

    // 2. Clear guild skills
    who->clear_guild_stat(type);
    who->set_guild_pref(type, 0); // not being taxed anymore

    // Make sure the guild skills are clear
    who->remove_skill(MONK_SKILL_FOCUS);
    who->remove_skill(MONK_SKILL_STRIKE);
    who->remove_skill(MONK_SKILL_PLEXUS);

    // 3. remove the member from the member list
    MANAGER->remove_member(m_get_name(who));

    m_log("Remove completed successfully.");
}


/*
 * Function name: m_do_leave_guild
 * Description:   Leave the guild. Handles warning,
 *                clearing skills, and reming the player
 *                from any 
 * Arguments:     the argument passed to the command
 * Returns:       1 if the command executed successfully
 */
public int
m_do_leave_guild(string str)
{
    int    type, ret;
    string name;
    object tp;

#define MONK_LEAVE_WARNING_PROP "monk_leave_warning_prop"

    tp = this_player();

    name = tp->query_real_name();

    if(m_query_monk(tp, SS_LAYMAN))
        type = SS_LAYMAN;
    else if(m_query_monk(tp, SS_OCCUP))
        type = SS_OCCUP;
    else // not a monk!
        return 0;

    // give a warning, since this is a fairly
    // important command
    if(!(tp->query_prop(MONK_LEAVE_WARNING_PROP)))
    {
        tp->add_prop(MONK_LEAVE_WARNING_PROP, 1);
        write("Are you sure you want to leave the monks forever? "
            + "Enter the command again if you are sure.\n");
        return 1;
    }

    m_remove_member(tp, type);

    // remove 1/6th of their combat experience
    // Cirion, 1999.08.08 No penalty for leaving, for now.
    // Cirion, 1999.11.22 Re-instated penalty now that Kaheda is closed
    tp->add_exp(-((tp->query_exp_combat()) / 6), 1);

    m_log(capitalize (tp->query_real_name()) + " left the monks.");

    write("As you break your vows to the Order, you feel your limbs "
        + "become heavy and weak, and you feel much less experienced "
        + "in combat.\nA feeling of sadness and dread washes over you.\n");

    return 1;
}

/*
 * Function name: m_do_transfer
 * Description:   Command to transfer from the old kaheda guild
 *                to the new.
 */
public int
m_do_transfer(string str)
{
    object tp = this_player();

    if(!m_is_old_member(tp))
    {
        notify_fail("You are not a member of Kaheda!\n");
        return 0;
    }

    if(m_move_from_old_guild(tp))
    {
        write("You transfer your membership from Kaheda to the Order "
            + "of the Dragon.\n");
        return 1;
    }
    else
    {
        write("Something goes wrong! Please leave a bug report.\n");
        return 1;
    }

}

/*
 * Function name: m_do_fix_membership
 * Description:   The monk is on the Monk list, but does not have the shadow.
 *                Try to fix the monk.
 */
public int
m_do_fix_membership (string str)
{
    object          who = this_player ();
    string           type;

    if (m_query_monk (who, SS_OCCUP))
        type = "occupational";
    else if (m_query_monk (who, SS_OCCUP))
        type = "layman";
    else
    {
        write ("You are *really* screwed up. Please contact the guildmaster or "
            + "the AoP to help you.\n");
        m_throw ("Error fixing " + who->query_name() + " (could not determine "
            + "membership type)");
        return 1;
    }

    if(!m_do_join_guild(type, 1)) // add the player without clearing out the old prefs/skills
    {
        write ("Something goes wrong. Please contact the guildmaster or "
            + "the AoP to help you.\n");
        m_throw ("Error fixing " + who->query_name() + " (could not add shadow)");
    }

    write ("You are now fixed.\n");
    return 1;
}

/*
 * Function name: m_join_init
 * Description:   Initialize joining functions for
 *                the room in which players may
 *                apply and join.
 */
void
m_join_init()
{
    add_action(m_do_join_guild, "dedicate");
    add_action(m_do_join_guild, "mdedicate");
    add_action(m_do_join_guild, "mjoin");
    add_action(m_do_application_stat, "check");
    add_action(m_do_application_stat, "mcheck");
    add_action(m_do_apply, "apply");
    add_action(m_do_apply, "mapply");
    add_action(m_do_leave_guild, "betray");
    add_action(m_do_leave_guild, "mleave");
    add_action(m_do_transfer_branch, "transfer");

    // check to see if the player is screwed up somehow...
    if (m_query_monk() && (!(this_player ()->m_query_monk ())))
    {
        add_action(m_do_fix_membership, "mfix");
        set_alarm(1.0, 0.0, &m_tell_player(this_player(), "Something is "
            + "wrong with your membership! Enter 'mfix' to try to "
            + "fix it.\n"));
    }

}


/******************************************************************
 *        Compat functions to translate old monks to new monks
 */
#define M_OLD_FOCUS_SKILL 136000
#define M_OLD_SHADOW_LOCATION_OCC "/d/Roke/common/gont/monks/obj/monk_occ_shadow"
#define M_OLD_SHADOW_LOCATION_LAY "/d/Roke/common/gont/monks/obj/monk_lay_shadow"
#define M_OLD_KAHEDA_GROUP   0
#define M_OLD_KAHEDA_MEMBER  12
#define M_OLD_KAHEDA_OCCUP   13

/*
 * Function name: m_is_old_member
 * Description:   Check to see if they are a member of the
 *                previous monks guild.
 * Arguments:     who - the player to test for
 * Returns:       SS_LAYMAN for a layman member, SS_OCCUP for
 *                an occupational member, 0 for none.
 */
varargs int
m_is_old_member(object who = this_player())
{
    string  domain;

    domain = "Roke";

    // ### FOR TESTING
    domain = "Avenir";

    //if(who->test_bit(domain, M_OLD_KAHEDA_GROUP, M_OLD_KAHEDA_OCCUP))

    if (who->query_guild_name_occ () == "Ancient Kaheda Order")
        return SS_OCCUP;

//    if(who->test_bit(domain, M_OLD_KAHEDA_GROUP, M_OLD_KAHEDA_MEMBER))

    if (who->query_guild_name_lay () == "Ancient Kaheda Order")
        return SS_LAYMAN;

    return 0;
}

/*
 * Function name: m_move_from_old_guild
 * Description:   Move the monk from the old guild to the
 *                new guild.
 * Arguments:
 * Returns:
 */
varargs int
m_move_from_old_guild(object who = this_player())
{
    int old_skill, new_distribution;
    string  shad;
    string  type;
    int     mtype;

    set_this_player(who);

    m_log("Starting to transfer " + who->query_name() + " from old guild to new...");

    mtype = m_is_old_member(who);
    shad = M_OLD_SHADOW_LOCATION_OCC;

    if(mtype == SS_OCCUP)
    {
        shad = M_OLD_SHADOW_LOCATION_OCC;
        type = "occupational";
    }
    else if(mtype == SS_LAYMAN)
    {
        shad = M_OLD_SHADOW_LOCATION_LAY;
        type = "layman";
    }
    else
        m_throw("Error: " + who->query_name() + " is not a Kahedean monk.");

    old_skill = who->query_skill(M_OLD_FOCUS_SKILL);
    new_distribution = (old_skill / 3) * 2;

    who->set_skill(M_OLD_FOCUS_SKILL, 0);
    who->kick_out_monk(1); // kick them out without making them loose experience, etc.

    who->remove_autoshadow(shad);

    if(!m_do_join_guild(type, 1)) // add the player without clearing out the old prefs/skills
        m_throw ("Error transferring " + who->query_name() + " to new guild");

    // divide the old skills among the new (2/3rd of the
    // old focus skill goes into the new skills)
    who->set_skill(MONK_SKILL_FOCUS, new_distribution);
    who->set_skill(MONK_SKILL_STRIKE, new_distribution);
    who->set_skill(MONK_SKILL_PLEXUS, new_distribution);
    who->setup_skill_decay();

    return 1;
}

// to test, do the followng exec funciton
/*
LAYMAN:
exec int occup = 0; object who = JR; string occ_shadow = "/d/Roke/common/gont/monks/obj/monk_occ_shadow"; string lay_shadow = "/d/Roke/common/gont/monks/obj/monk_lay_shadow"; int KAHEDA_GROUP = 0; int KAHEDA_MEMBER  = 12; int KAHEDA_OCCUP  = 13; object shadow; if(occup) { shadow = clone_object(occ_shadow); if (shadow->add_monk_shadow(who) != 1) throw("Error adding monk shadow");  who->set_bit(KAHEDA_GROUP, KAHEDA_OCCUP); } else { shadow = clone_object(lay_shadow); if (shadow->add_monk_shadow(who) != 1)  th

OCCUPATIONAL:
exec int occup = 1; object who = JR; string occ_shadow = "/d/Roke/common/gont/monks/obj/monk_occ_shadow"; string lay_shadow = "/d/Roke/common/gont/monks/obj/monk_lay_shadow"; int KAHEDA_GROUP = 0; int KAHEDA_MEMBER  = 12; int KAHEDA_OCCUP  = 13; object shadow; if(occup) { shadow = clone_object(occ_shadow); if (shadow->add_monk_shadow(who) != 1) throw("Error adding monk shadow");  who->set_bit(KAHEDA_GROUP, KAHEDA_OCCUP); } else { shadow = clone_object(lay_shadow); if (shadow->add_monk_shadow(who) != 1)  th

*/

