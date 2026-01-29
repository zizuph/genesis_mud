/*
 * shire_council.c
 *
 * This object defines all functions that make the Council tick. The
 * function check_council() is called every time a guildmember logs in,
 * to see if something is waiting for her. Another important object is
 * the Council-room ("rooms/council.c"). "shire_council.h" defines all
 * important things-that-need-to-be-defined.
 *                                               Tricky, december 1994
 */

inherit "/std/object";

#include "/sys/macros.h"
#include "/secure/std.h"
#include "defs.h"

/* Improve readability */
#define ACCEPT 0
#define DENIED 1
#define DONT_SAVE 0
#define DO_SAVE   1

/* Debugging: the story of my life... */
#define DEBUG 1

/* Global variables to save */
mapping member_map;        /* Members of the Council                       */
mapping action_map;        /* Actions to take on guildmembers              */
mapping apply_map;         /* People applying for the Council and votes    */
string hailing_message;    /* A message for all guild members upon login   */
int council_max;           /* The size the Council chooses to be           */

/* Prototypes */
string warning_txt();
string expell_txt();
string deny_txt();
string accept_txt();
string relieve_txt();
string take_action(int action, mixed target, int save);

void
create_object()
{
    set_name("table");
    set_short("table");
    set_long("A table for the Council of the Hin Warrior guild.\n");

    seteuid(getuid());
    restore_object(MASTER);
}

int
sizeof_council()
{
    return m_sizeof(member_map);
}

int
set_council_max(int max)
{
    if (max < 1 || max > MAX_MEMBERS)
        return 0;

    council_max = max;

    /* And store everything */
    seteuid(getuid());
    save_object(MASTER);
    return 1;
}

int
query_council_max()
{
    return council_max;
}

int
query_council_full()
{
    return m_sizeof(member_map) == council_max;
}

mapping
query_council_members()
{
    return member_map;
}

/*
 * Function name:   is_council_member
 * Description:     Test whether someone is a member of the Council or not.
 * Arguments:       who: Name of the person to test
 * Returns:         1 if the person is a member, 0 if not.
 */
int
is_council_member(string who)
{
    if (member_array(who, m_indexes(member_map)) >= 0)
        return 1;

#if DEBUG
    /* For testing purposes */
    if (who == "tricky")
        return 1;
#endif

    return 0;
}

/*
 * Function name:   add_council_member
 * Description:     Add a new member to the Council, if possible.
 * Arguments:       who: Name of the person to test
 * Returns:         1 if the person was added, 0 if not.
 */
int
add_council_member(string who)
{
    /* Are there any members? */
    if (!m_sizeof(member_map))
        member_map = ([ ]);

    /* May we add another member? */
    if (m_sizeof(member_map) >= MAX_MEMBERS - 1)
        return 0;

    /* Is this already a member? */
    if (member_array(who, m_indexes(member_map)) >= 0)
        return 1;

    /* Okay, add this one and store some useful information */
    member_map[who] = ({ time() });

    /* And store everything */
    seteuid(getuid());
    save_object(MASTER);
    return 1;
}

/*
 * Function name:   remove_council_member
 * Description:     Remove a member from the Council, if possible.
 * Arguments:       who: Name of the person to test
 */
void
remove_council_member(string who)
{
    string name;

    /* Are there any members? */
    if (!m_sizeof(member_map))
        return;

    /* Delete this member */
    member_map = m_delete(member_map, who);

    /*
     * Take action if this emptied the Council. Note that we don't take
     * action when we only get under the minimum. No need to do that; 
     * there are still councilmembers left that can vote for applications.
     * Only an empty Council creates a state of emergency.
     */
    if (!m_sizeof(member_map))
    {
        log_file(COUNCIL_LOG, ctime(time())
         + " Ack! Last member left the Council!\n");

        /* Take the first possible applicant */
        if (m_sizeof(apply_map))
        {
            name = m_indexes(apply_map)[0];

            /* Get her name off the application list */
            m_delete(apply_map, name);

            log_file(COUNCIL_LOG, ctime(time())
             + " Automagically accepted " + capitalize(name) + ".\n");

            /* Let the applicant in on this secret */
            take_action(ACTION_ACCEPT, who, DONT_SAVE);

            /*
             * Note: this does not automatically clean all other applicants
             * if the council-size is 1. Then again, I'll leave the minimum-
             * size at three, so the need for this will never occur. :-)
             */
 
            /* And add her as a new member */
            add_council_member(name);
        }
        else
        {
            /*
             * Panic! The Council is empty and there is noone to substitute.
             * Still we remain cool, and wait for someone to apply.
             */
 	}
    }
    /* And store the results */    
    seteuid(getuid());
    save_object(MASTER);
}

/*
 * Function name:   query_hailing_message
 * Description:     Every member of the guild has a pipe that calls this
 *                  function upon login. This allows the council to set
 *                  a nice hailing message for the guild members.
 * Returns:         The message ((tm) Grandmaster Flash).
 */
string
query_hailing_message()
{
    if (!strlen(hailing_message))
        hailing_message = "Welcome, True Hin Warrior!\n";

    return hailing_message;
}

/*
 * Function name:   set_hailing_message
 * Description:     Every member of the guild has a pipe that calls this
 *                  function upon login. This allows the council to set
 *                  a nice hailing message for the guild members.
 * Arguments:       str: The string to set as message.
 */
void
set_hailing_message(string str)
{
    hailing_message = str + "\n";
    seteuid(getuid());
    save_object(MASTER);
}

/*
 * Function name:   set_action
 * Description:     Allow the Council to set an action to be taken upon
 *                  login of a guild member. If someone already has a
 *                  pending action, it will be changed to the new action.
 * Arguments:       who: the person to take the action on.
 *                  action: the number of the action to be taken.
 * Returns:         1 upon success.
 */
void
set_action(string who, int action)
{
    string *action_arr;

    /* Delete any old action there might be */
    action_map = m_delete(action_map, who);

    /* And add the new action */
    if (action != ACTION_NOTHING)
    {
        if (m_sizeof(action_map))
            action_map += ([ who : action ]);
        else
            action_map = ([ who : action ]);
    }

    /* And save everything */
    seteuid(getuid());
    save_object(MASTER);
}

mapping
query_actions()
{
    return action_map;
}

/*
 * Function name:   notify_action
 * Description:     Let a target in on our secret.
 * Arguments:       action: The action to enforce.
 *                  target: The person to take the action on.
 */
void
notify_action(int action, string target)
{
    object target_ob;
    int index;

    target = lower_case(target);

    /* Does the target exist? */
    if (!SECURITY->exist_player(target))
        return;

    target_ob = find_player(target);

    /* Check whether the target is in the game or not */
    if (target_ob)
    {
        /* The player is in the game */
        switch (action)
        {
        case ACTION_NOTHING:
            return;

        case ACTION_WARN:
            target_ob->catch_msg(warning_txt());
            log_file(COUNCIL_LOG, ctime(time()) + " " + capitalize(target)
             + " received warning.\n");
            break;

        case ACTION_EXPELL:
            target_ob->catch_msg(expell_txt());
            log_file(COUNCIL_LOG, ctime(time()) + " " + capitalize(target)
                 + " notified of " + target_ob->query_possessive()
                 + " expelling from the Guild.\n");
            /* The actual expelling will be done in the pipe */
            break;

        case ACTION_SUMMON:
            if (target_ob->query_wiz_level())
            {
                target_ob->catch_msg("You are magically summoned to a Council "
                 + "meeting of the Hin Warrior guild.\n");
                target_ob->move_living("X", HINROOM_DIR + "council", 1);
                log_file(COUNCIL_LOG, ctime(time()) + " " + capitalize(target)
                 + " was summoned to the Councilroom.\n");
            }
            else
            {
                target_ob->catch_msg("The Hin Warrior Guild Council kindly "
                 + "summons you to its meeting.\n");
                log_file(COUNCIL_LOG, ctime(time()) + " " + capitalize(target)
                 + " notified of " + target_ob->query_possessive()
                 + " summoning by the Council.\n");
            }
            break;

        case ACTION_RESTORE:
            target_ob->catch_msg("The Council of the Hin Warrior guild has "
             + "restored its confidence in you.\n");
            log_file(COUNCIL_LOG, ctime(time()) + " " + capitalize(target)
             + " notified of " + target_ob->query_possessive()
             + " restoration by the Council.\n");
            break;

        case ACTION_ACCEPT:
            target_ob->catch_msg(accept_txt());
            log_file(COUNCIL_LOG, ctime(time()) + " " + capitalize(target)
             + " notified that " + target_ob->query_possessive()
             + " application was accepted by the Council.\n");
            break;

        case ACTION_DENY:
            target_ob->catch_msg(deny_txt());
            log_file(COUNCIL_LOG, ctime(time()) + " " + capitalize(target)
             + " notified that " + target_ob->query_possessive()
             + " application was denied by the Council.\n");
            break;

        case ACTION_RELIEVE:
            target_ob->catch_msg(relieve_txt());
            log_file(COUNCIL_LOG, ctime(time()) + " " + capitalize(target)
             + " notified that " + target_ob->query_pronoun()
             + " lost Council membership.\n");
            break;
        }
    }
    else
    {
        /* The player is not in the game */
        switch (action)
        {
        case ACTION_NOTHING:
            break;

        case ACTION_SUMMON:
            break;

        default:
            /* Store the action for later */
            set_action(target, action);
            break;
        }
    }
}

/*
 * Function name:   take_action
 * Description:     The Council has voted positive on some action.
 *                  Now we only have to implement that very action.
 * Arguments:       action: The action to enforce.
 *                  target: The person to take the action on.
 *                  save:   Perform a save_object().
 * Returns:         A string with the errormessage, "" if all went well.
 */
string
take_action(int action, mixed target, int save)
{
    object target_ob;
    int index;
    string action_txt;

    /*
     * Quickly bail out if this is a resize. Else string-operations
     * on target will cause horrible actions...
     */
    if (action == ACTION_RESIZE)
    {
        set_council_max(target);
	log_file(COUNCIL_LOG, ctime(time()) + " Council resized to "
         + target + " members.\n");
        return "";
    }

    target = lower_case(target);

    /* Does the target exist? */
    if (!SECURITY->exist_player(target))
        return capitalize(target) + " does not exist.\n";

    switch (action)
    {
    case ACTION_NOTHING:
        return "";

    case ACTION_WARN:
        log_file(COUNCIL_LOG, ctime(time()) + " Council sent warning to "
         + capitalize(target) + ".\n");
        break;

    case ACTION_EXPELL:
        log_file(COUNCIL_LOG, ctime(time()) + " Council decided to expell "
         + capitalize(target) + ".\n");
        SHIRE_PIPE->add_expelled(target);
        break;

    case ACTION_SUMMON:
	log_file(COUNCIL_LOG, ctime(time()) + " Council decided to summon "
         + capitalize(target) + " to the Councilroom.\n");
        break;

    case ACTION_RESTORE:
        log_file(COUNCIL_LOG, ctime(time()) + " Council restored its faith in "
         + capitalize(target) + ".\n");
        SHIRE_PIPE->remove_expelled(target);
        break;

    case ACTION_ACCEPT:
        add_council_member(target);
        log_file(COUNCIL_LOG, ctime(time()) + " Council accepted application "
         + "of " + capitalize(target) + ".\n");
        break;

    case ACTION_DENY:
        log_file(COUNCIL_LOG, ctime(time()) + " Council denied application of "
         + capitalize(target) + ".\n");
        break;

    case ACTION_RELIEVE:
        remove_council_member(target);
        log_file(COUNCIL_LOG, ctime(time()) + " Council relieved "
         + capitalize(target) + " of membership of the Council.\n");
        break;
    }

    /* Inform the person about the action */
    notify_action(action, target);

    /* And store everything if necessary */
    if (save)
    {
        seteuid(getuid());
        save_object(MASTER);
    }
}

/*
 * Function name:   check_council
 * Description:     Every member of the guild has a pipe that calls this
 *                  function upon login. This allows the council to make
 *                  decisions even when people are not present to face
 *                  the consequences. 
 * Arguments:       who: the person to check.
 */
void
check_council(string who)
{
    int index, action;
    string action_txt;

    if (!who)
        return;

    who = lower_case(who);

    if (member_array(who, m_indexes(action_map)) == -1)
        return;

    action = action_map[who];
    action_map = m_delete(action_map, who);
    notify_action(action, who);
    seteuid(getuid());
    save_object(MASTER);
}

/*
 * Function name:   council_members
 * Description:     Gives a composed string of all members of the Council.
 * Returns:         That string.
 */
string
council_members()
{
    string *member_arr, result;
    int s;

    member_arr = m_indexes(member_map);
    s = sizeof(member_arr);

    if (s == 0)
        return "noone";

    member_arr = map(member_arr, "make_capitalized", this_object());

    if (s == 1)  /* One member */
        result = member_arr[0];
    else  /* Several other members */
        result = implode(member_arr[0..(s-2)], ", ") + " and "
               + member_arr[s-1];

    return result;
}

/*
 * Function name:   make_capitalized
 * Description:     You figure. ;-)
 * Returns:         The capitalized string
 */
string
make_capitalized(string str)
{
    return capitalize(str);
}

/*
 * Function name:   application_list
 * Description:     Gives a composed string of all people who have applied
 *                  for Councilmembership.
 * Returns:         That string.
 */
string
application_list()
{
    string *apply_arr, result;
    int s;

    apply_arr = m_indexes(apply_map);
    s = sizeof(apply_arr);

    if (s == 0)
        return "noone";

    apply_arr = map(apply_arr, "make_capitalized", this_object());

    if (s == 1)  /* One member */
        result = apply_arr[0];
    else  /* Several other members */
        result = implode(apply_arr[0..(s-2)], ", ") + " and "
               + apply_arr[s-1];

    return result;
}

void
apply_for_council(string who)
{
    if (!who)
        return;

    who = lower_case(who);

    if (m_sizeof(apply_map))
        apply_map += ([ who : ({({ }), ({ })})]);
    else
    {
        if (sizeof_council() == 0)
        {
            /* Immediately accept this volunteer to become a new member */
            take_action(ACTION_ACCEPT, who, DONT_SAVE);
        } 
        else
            apply_map = ([ who : ({({ }), ({ })})]);
    }

    /* And store everything */
    seteuid(getuid());
    save_object(MASTER);
}

int
deny_application(string who)
{
    if (!who)
    {
        notify_fail(capitalize(query_verb()) + " who?\n");
        return 0;
    }

    /* Is "who" applying? */
    if (member_array(who, m_indexes(apply_map)) == -1)
    {
        notify_fail(capitalize(who) + " is not applying.\n");
        return 0;
    }

    /* Is this Councilmember allowed to vote? */
    if (member_array(this_player()->query_name(),
                     apply_map[who][ACCEPT] + apply_map[who][DENIED]) >= 0)
    {
        notify_fail("You have already spoken on the matter.\n");
        return 0;
    }

    /* Add one vote to the denials */
    if (sizeof(apply_map[who][DENIED]))
        apply_map[who][DENIED] += ({ this_player()->query_name() });
    else 
        apply_map[who][DENIED] = ({ this_player()->query_name() });

    write(capitalize(who) + " now has " + sizeof(apply_map[who][0])
     + " votes for, and " + sizeof(apply_map[who][1]) + " votes against.\n");

    /* Log it */
    log_file(COUNCIL_LOG, ctime(time()) + " Application of "
     + capitalize(who) + " denied by " + this_player()->query_name() + ".\n");

    /* Are there enough votes to deny the whole application? */
    if (sizeof(apply_map[who][DENIED]) >
        (sizeof_council() - VOTES_NEEDED[sizeof_council()]))
    {
        apply_map = m_delete(apply_map, who);	
        take_action(ACTION_DENY, who, DO_SAVE);
        write("That is enough to reject the application.\n");
    }
    write("Ok.\n");
    return 1;
}

int
accept_application(string who)
{
    string *apply_arr;
    int i;

    if (!who)
    {
        notify_fail(capitalize(query_verb()) + " who?\n");
        return 0;
    }

    who = lower_case(who);

    /* Is "who" applying? */
    if (member_array(who, m_indexes(apply_map)) == -1)
    {
        notify_fail(capitalize(who) + " is not applying at the moment.\n"
         + "Perhaps a decision has been reached already.\n");
        return 0;
    }

    if (who->query_wiz_level())
    {
        notify_fail(capitalize(who) + " is not elegible as an immortal!\n");
        return 0;
    }

    if (SHIRE_PIPE->is_member(who))
    {
        notify_fail(capitalize(who) + " is no longer a member of our Guild.\n");
        return 0;
    }

    /* Is this Councilmember allowed to vote? */
    if (member_array(this_player()->query_name(),
                     apply_map[who][ACCEPT] + apply_map[who][DENIED]) >= 0)
    {
        notify_fail("You have already spoken on the matter.\n");
        return 0;
    }

    /* Add one vote to the aceptances */
    if (sizeof(apply_map[who][ACCEPT]))
        apply_map[who][ACCEPT] += ({ this_player()->query_name() });
    else 
        apply_map[who][ACCEPT] = ({ this_player()->query_name() });

    write(capitalize(who) + " now has " + sizeof(apply_map[who][0])
     + " votes for, and " + sizeof(apply_map[who][1]) + " votes against.\n");

    /* Log it */
    log_file(COUNCIL_LOG, ctime(time()) + " Application of "
     + capitalize(who) + " accepted by " + this_player()->query_name() + ".\n");

    /* Are there enough votes to accept the whole application? */
    if (sizeof(apply_map[who][ACCEPT]) >= VOTES_NEEDED[sizeof_council()])
    {
        apply_map = m_delete(apply_map, who);	
        take_action(ACTION_ACCEPT, who, DONT_SAVE);

        /* Check if this completes the search for new members. */
        if (sizeof_council() == council_max)
        {
            /* If so, all other applications can be discarded. */
            apply_arr = m_indexes(apply_map);

            for (i = 0; i < sizeof(apply_arr); i++)
            {
                /* Save us a lot of saves by not saving */
                take_action(ACTION_DENY, apply_arr[i], DONT_SAVE);
            }
        }
        write("That is enough to accept the application.\n");
    }

    /* Now we will save all changes at once */
    seteuid(getuid());
    save_object(MASTER);
    write("Ok.\n");
    return 1;
}

int
give_status(string who)
{
    if (!who)
    {
        notify_fail("Usage:    status <person>\n");
        return 0;
    }

    who = lower_case(who);

    /* Does the target exist? */
    if (!SECURITY->exist_player(who))
    {
        write(capitalize(who) + " does not exist.\n");
        return 1;
    }

    /* Check if the person has been expelled */
    if (SHIRE_PIPE->is_expelled(who))
        write(capitalize(who) + " has been expelled from the Guild.\n");
    else
        write(capitalize(who) + " has not been expelled from the Guild.\n");

    /* Check if the person has a pending action */
    if (member_array(who, m_indexes(action_map)) >= 0)
    {
        switch (action_map[who])
        {
        case ACTION_EXPELL:
            write(capitalize(who)
             + " has not yet been notified of expellation from the Guild.\n");
            break;

        case ACTION_WARN:
            write(capitalize(who)
             + " has not yet received the warning from the Council.\n");
            break;

        case ACTION_RESTORE:
            write(capitalize(who)
             + " has not yet been notified of the restoration of faith.\n");
            break;

        case ACTION_ACCEPT:
            write(capitalize(who)
             + " has not yet received the acceptance of the application "
             + "for the Council.\n");
            break;

        case ACTION_DENY:
            write(capitalize(who)
             + " has not yet received the denial of the application for "
             + "the Council.\n");
            break;
        }
    }
    else
        write(capitalize(who) + " has no pending Council action.\n");

    /* Check if the person has applied */
    if (member_array(who, m_indexes(apply_map)) >= 0)
    {
        write(capitalize(who)
         + " is applying for membership of the Council.\n");
        write("For: " + sizeof(apply_map[who][0]) + ", against: "
         + sizeof(apply_map[who][1]) + ".\n");
    }
    else
        write(capitalize(who)
         + " is not applying for membership of the Council.\n");

    /* Check if the person is a member of the Council */
    if (member_array(who, m_indexes(member_map)) >= 0)
    {
        write(capitalize(who) + " is a member of the Council since "
         + ctime(member_map[who][0]) + ".\n");
    }
    else
        write(capitalize(who) + " is not a member of the Council.\n");

    return 1;
}

/*
 * And now some functions that return messages. Why functions? Well,
 * perhaps in some distant future we want to allow the Council to
 * define those messages themselves. We'll see...
 */

/*
 * Function name:   warning_txt
 * Description:     Return the text for an ACTION_WARN message.
 */
string
warning_txt()
{
    return "The Council of the Hin Warrior guild sends you a severe warning.\n"
     + "Do not take this lightly; the next warning might lead to expelling\n"
     + "of the Hin Warrior Guild.\n"
     + "Ask any Council member if you do not understand the reason of the\n"
     + "warning.\n";
}

/*
 * Function name:   expell_txt
 * Description:     Return the text for an ACTION_EXPELL message.
 */
string
expell_txt()
{
    return "The Council of the Hin Warrior guild has decided to expell you\n"
     + "from the guild.\n";
}

/*
 * Function name:   accept_txt
 * Description:     Return the text for an ACTION_ACCEPT message.
 */
string
accept_txt()
{
    return "The Council of the Hin Warrior guild has decided to accept you\n"
     + "as a new member of the Council.\n";
}

/*
 * Function name:   deny_txt
 * Description:     Return the text for an ACTION_DENY message.
 */
string
deny_txt()
{
    return "The Council of the Hin Warrior guild has regrettably decided "
     + "not to accept you as a new member of the Council.\n";
}

/*
 * Function name:   relieve_txt
 * Description:     Return the text for an ACTION_RELIEVE message.
 */
string
relieve_txt()
{
    return "The Council of the Hin Warrior guild has regrettably decided "
     + "to relieve you of your duties as a member of the Council.\n";
}
