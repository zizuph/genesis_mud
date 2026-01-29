/*
 * /d/Ansalon/guild/society/room/vote_room.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Master room to keep track of membership and voting
 *
 * Gwyneth April 28, 2000
 * Modification log:
 *
 * Gwyneth, 12/2/03 - Added caps checking to make sure a vote isn't
 *                    called twice with different capitalizations.
 *
 * Navarre May 18th 2013, Commented out code to handle 'invite'.
 *                        We allow kenders to join the occ guild if they
 *                        solved the entrance quest.
 *
 * Arman April 3rd 2021, Removed the expel vote due to misuse from juniors
 */
#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <files.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>

inherit KENDERMORE_IN;

#define SAVE_FILE MASTER
#define MOREOBJ "/obj/more"
#define VOTE_TIME 604800
#define GUILD_AGE 1209600
#define ACC_AGE 129600
#define RESULTS KENDERG_DIR + "results"
#define GUILD_MASTER  "Arman"

/* Prototypes */
int do_vote_alarm();
int member_size();
int finalize_vote(string vote_id);
int expel_kender_from_guild(string who);
int save_this_list();
void save_list_now();

/* Global variables - Don't alter these unless you know what
   you are doing! The arrays are parallel. */
string *banished = ({ });
string *enemy = ({ });
string *expelled = ({ });
string *guild_member = ({ });
int *guild_join_time = ({ });
int *guild_join_age = ({ });
string *invited = ({ });
string *requested = ({ });
mixed *voters = ({ });
string *vote_caller = ({ });
string *vote_id = ({ });
int *end_vote = ({ });
int *vote_counts_aye = ({ });
int *vote_counts_nay = ({ });
int gAlarm = 0;
int gShdwnAlarm = 0;

void
create_kendermore_room()
{
    set_short("A messy paper-filled chamber");
    set_long("Papers are scattered everywhere in this chamber, all over " +
        "the floor, pinned on the walls and even a few stuck to the " +
        "ceiling. Hidden under a particularly large pile of papers, " +
        "a desk seems to be poking through. Almost covered by the papers, " +
        "a sign is hanging off the side of the desk. Behind the desk, a " +
        "shiny silver pole runs from a hole in the ceiling through a hole " +
        "in the ground.\n");
    add_item(({"floor", "ground"}), "It is covered in papers! " +
        "How can anyone keep track of things here!\n");
    add_item("walls", "The walls are hidden from view by the " +
        "numerous papers stuck to them.\n");
    add_item("ceiling", "How did any papers get stuck to the ceiling?! " +
        "The only clear spot seems to be around the hole that a " +
        "silver pole descends through.\n");
    add_item(({"hole", "holes"}), "There is one hole leading up " +
        "into the guild, and one fairly dark one leading down. " +
        "A silver pole leads through both.\n");
    add_item(({"pole", "silver pole", "shiny pole", "shiny silver pole"}),
        "It looks delightful to slide " +
        "down, and its sleek metallic finish shines brightly.\n");
    add_item(({ "papers", "paper"}), "The papers are all over the place!\n");
    add_item("desk",
        "Lists of the people significant to the Secret " +
        "Society, such as banished, enemies, expelled, members, requested " +
        "and those invited lie scattered on the desk as well as results " +
        "and votes. One could " +
        "probably list them as such. An odd looking figurine of " +
        "a dragon is partially buried under the papers.\n");
    add_item(({"dragon", "figurine", "dragon figurine"}),
        "@@dragon_desc");
//    add_item("sign", "Call vote <name>-<expel/banish/unbanish/" +
//              "declare/pardon/invite>.\n");

    add_item("sign", "Call vote <name>-<expel/banish/unbanish/" +
              "declare/pardon>.\n");

//    add_cmd_item("sign", "read", "Call vote <name>-<expel/banish/unbanish/" +
//            "declare/pardon/invite>.\n");
    add_cmd_item("sign", "read", "Call vote <name>-<expel/banish/unbanish/" +
                 "declare/pardon>.\n");


    add_cmd_item(({"down", "down pole", "down shiny pole",
        "down silver pole", "down shiny silver pole"}),
        "slide", "@@slide_pole");
    add_cmd_item("scroll", "read", "@@list_members");

    clone_object(KGOBJ + "voting_board")->move(TO);

    /* Don't remove these unless you know why you're removing it. */
    (KENDERG_DIR + "taunt_list")->dummy_function();
    (KGROOM + "faerie_tree")->dummy_function();

    restore_object(SAVE_FILE);

    /* Setup the vote alarms */
    do_vote_alarm();
}

void
save_this_list()
{
    int delay;


    save_list_now();
#ifdef 0
    if (SECURITY->query_uptime_limit() > 600 &&
      !ARMAGEDDON->shutdown_active())
    {
        /* It's not armageddon and there are more than 10 minutes in
           the game left. There is no alarm set, set an alarm to save
           the file in 10 minutes. */
        if (!gAlarm)
            gAlarm = set_alarm(600.0, 0.0, &save_list_now());

        /* Alarm is already set, don't worry about it. */
        return;
    }

    remove_alarm(gAlarm);

    /* How much longer until shutdown? */
    delay = ARMAGEDDON->query_delay();

    /* There is no shutdown alarm and there is more than 3 seconds left.
       Set an alarm to save the file 3 seconds before shutdown. */
    if (!gShdwnAlarm && delay > 3)
        gShdwnAlarm = set_alarm(itof(delay) - 3.0, 0.0, &save_list_now());
    /* Shutdown is 3 seconds or less. Don't bother with an alarm. */
    else if (delay <= 3)
        save_object(MASTER);
#endif
}

void
save_list_now()
{
    save_object(MASTER);
    return;
}

/* Function name: slide_pole
 * Description: Gives messages to the appropriate people and
 *     moves the player to the new room.
 * Arguments: None
 * Returns: Null
 */
string
slide_pole()
{
    tell_room(KGROOM + "train", "You turn your head slightly, " +
        "and notice that " + QCTNAME(TP) + " has wandered in from " +
        "somewhere.\n");
    write("You take a running leap at the silver pole and slide " +
        "down through the hole in the floor. You speed through " +
        "dark tunnels, spiraling up, down and sideways, eventually " +
        "grinding to a halt right before " +
        "you hit a very hard wall. You gently push on a secret " +
        "brick, and slip out into the guild.\n");
    TP->move_living("M", KGROOM + "train", 1, 0);
    tell_room(TO, QCTNAME(TP) + " takes a " +
        "running leap at the silver pole and slides down through " +
        "the hole in the floor.\n");
    return "";
}

/* Function name: dragon_desc
 * Description: Gives a fun "toy" for the kender.
 */
string
dragon_desc()
{
    write("You clear off the papers around the figurine and " +
        "find an exquisitely carved statue with ruby gems for eyes " +
        "and brightly coloured paint over his body.\n");
    if(TP->query_race_name() == "kender")
    {
        write("\nA strong urge to touch the " +
            "dragon enters your head. You snake out a finger and " +
            "delicately trace " +
            "the ruby eyes, longing to handle them. You follow " +
            "the lines of colour down to his tail, where " +
            "you notice the tail is slightly loose.\nUnable to " +
            "contain yourself you gently wiggle the tail, trying " +
            "to pry it loose.\n");
        say(QCTNAME(TP) + " snakes out a finger " +
            "and delicately traces the ruby eyes of the dragon, then " +
            "follows the lines of colour down to its tail. " +
            capitalize(HE(TP)) + " gently wiggles the tail with a look of " +
            "longing.\n");
        write("\nYou feel a funny chill, and " +
            "see the small figurine grow to enormous proportions " +
            "as the once hard stone eyes gain a sharp piercing " +
            "look in them, glaring at you.\nWith a sudden " +
            "darting of his toothy jaws, the dragon bites off your " +
            "head and shrinks back down to his previous state.\n\n" +
            "Oddly enough, your head seems to still be in place.\n");
        say(QCTNAME(TP) + "'s eyes grow wide " +
            "as " + HE(TP) + " stares at the dragon figurine. After " +
            "a moment, " + QTNAME(TP) + " shakes " + HIM(TP) +
            "self as if awakening from a dream and tenatively " +
            "touches " + HIS(TP) + " head.\n");
    }

    return "";
}

/* Function name: do_vote_alarm
 * Description: Sets the alarms for the votes in progress
 *     that should be called sooner than 30 hours from
 *     the time the function is called.
 * Arguments: None
 * Returns: 1 Always
 */
int
do_vote_alarm()
{
    int i, tme, sz;

    for (i = 0, sz = sizeof(end_vote); i < sz; i++)
    {
        tme = time();

        if(sizeof(voters[i]) == member_size())
        {
            set_alarm(100.0, 0.0, &finalize_vote(vote_id[i]));
        }
        else if(tme < end_vote[i])
        {
            /* Don't set an alarm for votes that should be called
               after 30 hours. The members can do this, or the next
               Armageddon will catch it. */
            if(end_vote[i] - tme < 108000)
            {
                set_alarm(itof(end_vote[i] - tme), 0.0,
                    &finalize_vote(vote_id[i]));
            }
        }
        else
        {
            set_alarm(100.0, 0.0, &finalize_vote(vote_id[i]));
        }
    }

    return 1;
}

public string
format_output(string *output)
{
        int size, i, scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
        string *output2, formatted = "";

        size = sizeof(output);

        if (!size)
        {
            return "";
        }

        output2 = output;

        for (i = 0, size = sizeof(output2); i < size; i++)
        {
            output2[i] = capitalize(output2[i]);
        }

        scrw = ((scrw >= 40) ? (scrw - 3) : 77);
        formatted += (sprintf("%-*#s\n", scrw, implode(output2, "\n")));
        return ("\n" + formatted + "\n");
}

/* Function name: query_banished
 * Description: Finds if the given name is considered banished
 *     from the guild.
 * Arguments: string name - the name of the player to test
 * Returns: 1 if banished, 0 if not
 */
int
query_banished(string name)
{
    name = capitalize(name);
    return (member_array(name, banished) >= 0);
}

/* Function name: query_enemy
 * Description: Finds if the given name is considered an enemy
 *     by the guild.
 * Arguments: string name - the name of the player to test
 * Returns: 1 if an enemy, 0 if not
 */
int
query_enemy(string name)
{
    name = capitalize(name);
    return (member_array(name, enemy) >= 0);
}

/* Function name: query_expelled
 * Description: Finds if the given name has been expelled from
 *     the guild.
 * Arguments: string name - the name of the player to test
 * Returns: 1 if expelled, 0 if not
 */
int
query_expelled(string name)
{
    name = capitalize(name);
    return (member_array(name, expelled) >= 0);
}

/* Function name: query_invited
 * Description: Finds if the given name has been invited to
 *     join the guild or not.
 * Arguments: string name - the name of the player to test
 * Returns: 1 if invited, 0 if not
 */
int
query_invited(string name)
{
    name = capitalize(name);
    return (member_array(name, invited) >= 0);
}

/* Function name: query_jointime
 * Description: Finds the jointime of the member
 * Arguments: string name - the name of the member
 * Returns: the time the member joined
 */
int
query_jointime(string name)
{
    int index;

    index = member_array(capitalize(name), guild_member);

    return (guild_join_time[index]);
}

/* Function name: query_member
 * Description: Finds if the given name is that of a member
 *     of the guild or not.
 * Arguments: string name - the name of the player to test
 * Returns: 1 if a member, 0 if not
 */
int
query_member(string name)
{
    if (member_array(capitalize(name), guild_member) >= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Function name: query_requested
 * Description: Finds if the given name is that of a person
 *     who has requested an invitation or not.
 * Arguments: string name - the name of the player to test
 * Returns: 1 if a person has requested an invite, 0 if not
 */
int
query_requested(string name)
{
    name = capitalize(name);
    return (member_array(name, requested) >= 0);
}

/* Function name: query_voting_member
 * Description: Finds if the member is allowed to enter the
 *     voting room or not.
 * Arguments: object name - the player to test
 * Returns: 1 if allowed, 0 if not
 */
int
query_voting_member(object name)
{
    int index;

    index = member_array(capitalize(name->query_real_name()), guild_member);

    if (index == -1)
    {
        return 0;
    }
    else if(GUILD_AGE > (time() - guild_join_time[index]))
    {
        return 0;
    }
    else if(ACC_AGE > (name->query_age() - guild_join_age[index]) &&
        guild_join_age[index] != 0)
    {
        return 0;
    }
    else if(guild_join_age[index] == 0)
    {
        guild_join_age[index] = name->query_age();
        save_this_list();
        return 0;
    }
    else
    {
        return 1;
    }
}

/* Function name: add_banished
 * Description: Adds a name to the banished list
 * Arguments: string name - the name of the player to add
 * Returns: 1 if name added, 0 if name is already added
 */
int
add_banished(string name)
{
    name = capitalize(name);

    if(!query_banished(name))
    {
        banished += ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}

/* Function name: add_enemy
 * Description: adds a name to the enemy list
 * Arguments: string name - the name of the player to add
 * Returns: 1 if the name added, 0 if the name was already there
 */
int
add_enemy(string name)
{
    name = capitalize(name);

    if(!query_enemy(name))
    {
        enemy += ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}

/* Function name: add_expelled
 * Description: add a name to the expelled list
 * Arguments: string name - the name of the player to add
 * Returns: 1 if added to the list, 0 if already added
 */
int
add_expelled(string name)
{
    name = capitalize(name);

    if(!query_expelled(name))
    {
        expelled += ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}

/* Function name: add_invited
 * Description: adds a name to the invited list
 * Arguments: string name - the name of the player to invite
 * Returns: 1 if name is added, 0 if name is already added
 */
int
add_invited(string name)
{
    name = capitalize(name);

    if(!query_invited(name))
    {
        invited += ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}

/* Function name: add_member
 * Description: adds a name to the member list, the time to
 *     the join time list, and the age to the age list, removes
 *     from the invited list
 * Arguments: string name - the name of the player to add
 * Returns: 1 always
 */
int
add_member(string name)
{
    int age;

    name = capitalize(name);

    if(query_invited(name))
    {
        invited -= ({ name });
    }

    if(!query_member(name))
    {

        guild_member += ({ capitalize(name) });
        guild_join_time += ({ time() });
        age = (find_living(lower_case(name))->query_age());
        guild_join_age += ({ age });
    }


    save_this_list();
    return 1;
}

/* Function name: add_requested
 * Description: Keeps track of those who have requested an invitation
 * Arguments: string name - the name of the person who requested
 * Returns: 1 on success, 0 on failure
 */
int
add_requested(string name)
{
    name = capitalize(name);

    if(!query_requested(name))
    {
        requested += ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}

/* Function name: rem_banished
 * Description: removes the name of a banished person from the list
 * Arguments: string name - the name of the person to remove
 * Returns: 1 if name removed, 0 if name was never on the list
 */
int
rem_banished(string name)
{
    name = capitalize(name);

    if(query_banished(name))
    {
        banished -= ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}

/* Function name: rem_enemy
 * Description: removes a name from the enemy list
 * Arguments: string name - the name of the player to remove
 * Returns: 1 if successfully removed, 0 if name wasn't on the list
 */
int
rem_enemy(string name)
{
    name = capitalize(name);

    if(query_enemy(name))
    {
        enemy -= ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}

/* Function name: rem_expelled
 * Description: removes a name from the expelled list
 * Arguments: string name - the name of the player to remove
 * Returns: 1 if successfully removed, 0 if name wasn't on the list
 */
int
rem_expelled(string name)
{
    name = capitalize(name);

    if(query_expelled(name))
    {
        expelled -= ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}

/* Function name: clear_expelled
 * Description: clears the expelled list
 * Arguments: string name - the name of the player to remove
 * Returns: 1 if successfully removed, 0 if name wasn't on the list
 */
int
clear_expelled()
{
    expelled = ({  });
    save_this_list();
    return 1;
}

/* Function name: clear_banished
 * Description: clears the banished list
 * Arguments: string name - the name of the player to remove
 * Returns: 1 if successfully removed, 0 if name wasn't on the list
 */
int
clear_banished()
{
    banished = ({  });
    save_this_list();
    return 1;
}

/* Function name: rem_invited
 * Description: removes a name from the invited list
 * Arguments: string name - the name of the player to remove
 * Returns: 1 if removed, 0 if name wasn't on list
 */
int
rem_invited(string name)
{
    name = capitalize(name);

    if(query_invited(name))
    {
        invited -= ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}


/* Function name: rem_member
 * Description: removes the name of a member and their equivalent
 *     guild ages and guild jointimes
 * Arguments: string name - the name of the player to remove
 * Returns: 1 if removed, 0 if name wasn't on the list
 */
int
rem_member(string name)
{
    int end, from, to, index;

    name = capitalize(name);
    index = member_array(name, guild_member);
    from = index - 1;
    to = index + 1;
    end = sizeof(guild_join_time) -1;

    if(query_member(name))
    {
        if(sizeof(guild_join_time) == 1)
        {
            guild_join_time = ({ });
            guild_join_age = ({ });
        }
        else if(index == 0)
        {
            guild_join_time = guild_join_time[to..end];
            guild_join_age = guild_join_age[to..end];
        }
        else if(index == sizeof(guild_join_time))
        {
            guild_join_time = guild_join_time[0..from];
            guild_join_age = guild_join_age[0..from];
        }
        else
        {
            guild_join_time = guild_join_time[0..from] +
                guild_join_time[to..end];
            guild_join_age = guild_join_age[0..from] +
                guild_join_age[to..end];
        }

        guild_member -= ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}


/* Function name: rem_requested
 * Description: removes a name from the requested list
 * Arguments: string name - the name of the player to remove
 * Returns: 1 if removed, 0 if name wasn't on list
 */
int
rem_requested(string name)
{
    name = capitalize(name);

    if(query_requested(name))
    {
        requested -= ({ name });
        save_this_list();
        return 1;
    }

    return 0;
}

/* Function name: list_banished
 * Description: finds those on the banished list
 * Arguments: none
 * Returns: a list of those banished or a list that nobody is banished
 */
string
list_banished()
{
    if(sizeof(banished) < 1)
    {
        return "Nobody has been banished from the guild.\n";
    }
    else
    {
        return ("The following are banished from the guild:\n" +
            format_output(banished));
    }
}

/* Function name: list_enemies
 * Description: finds those on the enemy list
 * Arguments: none
 * Returns: a list of those enemies or a list that nobody is an enemy
 */
string
list_enemies()
{
    if(sizeof(enemy) < 1)
    {
        return "There are no enemies of the guild.\n";
    }
    else
    {
        return ("The following are enemies of the guild:\n" +
            format_output(enemy));
    }
}

/* Function name: list_invited
 * Description: finds those on the invited list
 * Arguments: none
 * Returns: a list of those invited or a list that nobody is invited
 */
string
list_invited()
{
    if(sizeof(invited) < 1)
    {
        return "Nobody has been invited to join the guild.\n";
    }
    else
    {
        return ("The following are invited to join the guild:\n" +
            format_output(invited));
    }
}

/* Function name: list_members
 * Description: finds those on the member list
 * Arguments: none
 * Returns: a list of those members or a list that nobody is a member
 */
string
list_members()
{
    if(sizeof(guild_member) < 1)
    {
        return "There are no members of the guild!\n";
    }
    else
    {
        return ("The following are members of the guild:\n" +
            format_output(guild_member));
    }
}

/* Function name: list_requested
 * Description: Finds those on the requested list
 * Arguments: none
 * Returns: A list of those on the requested list.
 */
string
list_requested()
{
    if(sizeof(requested) < 1)
    {
        return "Nobody is on the requested list.\n";
    }
    else
    {
        return ("The following people have requested invitations in " +
            "the past, and now require a member to invite them. The " +
            "following may or may not include current guild members:\n" +
            format_output(requested));
    }
}

/* Function name: list_expelled
 * Description: finds those on the expelled list
 * Arguments: none
 * Returns: a list of those expelled or a list that nobody is expelled
 */
string
list_expelled()
{
    if(sizeof(expelled) < 1)
    {
        return "Nobody has been expelled from the guild.\n";
    }
    else
    {
        return ("The following are expelled from the guild:\n" +
            format_output(expelled));
    }
}

/* Function name: member_size
 * Description: gives the size of the member list minus that of the
 *     guildmaster for voting purposes
 * Arguments: none
 * Returns: the size of the guild_member array minus the guildmaster
 */
int
member_size()
{
    if(member_array(GUILD_MASTER, guild_member) != -1)
    {
        return (sizeof(guild_member) - 1);
    }
    else
    {
        return sizeof(guild_member);
    }
}

/* Function name: list_things
 * Description: shows a list of either votes, results, banished,
 *     enemies, expelled, requested, invited or members
 * Arguments: string str - the string typed in by the player
 * Returns: 1 for success, 0 for failure
 */
int
list_things(string str)
{
    int i, sz;

    if(!strlen(str))
    {
        NF("List what? Votes? Results? Results tail? Banished? " +
        "Enemies? Expelled? Invited? Members? Requested?\n");
        return 0;
    }

    switch(str)
    {
        case "votes":
            if(sizeof(vote_id) > 0)
            {
                for(i = 0, sz = sizeof(vote_id); i < sz; i++)
                {
                    write("The vote: " + vote_id[i] + " was called on " +
                        (ctime(end_vote[i] - VOTE_TIME)) + " by " +
                        capitalize(vote_caller[i]) + ".\nIt will be " +
                        "finalized on " + ctime(end_vote[i]) + ".\n");
                }
            }
            else
            {
                write("There are no current votes.\n");
            }
            break;

        case "results":
            if(file_size(RESULTS) > 0 && file_size(RESULTS) < 30)
            {
                cat(RESULTS);
            }
            else if(file_size(RESULTS) >= 30)
            {
                clone_object(MOREOBJ)->more(RESULTS, 1);
            }
            else
            {
                write("There are no results to list.\n");
            }
            break;

        case "results tail":
            if(file_size(RESULTS) > 0)
            {
                tail(RESULTS);
            }
            else
            {
                write("There are no results to list.\n");
            }
            break;
        case "banished":
            write(list_banished());
            break;

        case "enemies":
            write(list_enemies());
            break;

        case "expelled":
            write(list_expelled());
            break;

        case "invited":
            write(list_invited());
            break;

        case "members":
            write(list_members());
            break;

        case "requested":
            write(list_requested());
            break;

        default:
            NF("List what?\n");
            return 0;
    }

    return 1;
}

/* Function name: call_vote
 * Description: Allows a player to call a vote to expel, banish,
 *     unbanish, declare, pardon or invite a person. Does various
 *     checks to be sure the player is allowed to call that
 *     particular vote. Alters the voting arrays and gives
 *     appropriate messages.
 * Arguments: string str - the vote the player wants to call
 * Returns: 1 on success, 0 on failure
 */
int
call_vote(string str)
{
    string vname, vtype, vid, tme;
    int vnum;

    if(!strlen(str))
    {
        NF("The syntax is: call vote <name>-<expel/banish/unbanish/" +
            "declare/pardon/invite>.\n");
        return 0;
    }
    str = lower_case(str);

    sscanf(str, "vote %s", vid);
    if(sscanf(str, "vote %s-%s", vname, vtype) != 2)
    {
        NF("The syntax is: call vote <name>-<expel/banish/unbanish/" +
            "declare/pardon/invite>.\n");
        return 0;
    }

    if(member_array(vid, vote_id) != -1)
    {
        write("There is already a vote of that type called.\n");
        return 1;
    }

    if(!SECURITY->exist_player(vname))
    {
        write("Call vote to " + vtype + " whom?\n");
        return 1;
    }

    switch(vtype)
    {
        case "invite":
            write("Since when do kenders need an invitation?!\n");
            return 1;

//            if(query_member(vname))
//            {
//                write("That person is already a member!\n");
//                return 1;
            // }
            // else if(query_enemy(vname))
            // {
                // write("That person is an enemy!\n");
                // return 1;
            // }
            // else if(query_banished(vname))
            // {
                // write("That person is banished from joining. You must " +
                    // "call a vote to unbanish first.\n");
                // return 1;
            // }
            // else if(query_invited(vname))
            // {
                // write("That person is already invited.\n");
                // return 1;
            // }
            // break;

        case "expel":
            // Commented out the expel option due to abuse
            {
                write("As you consider voting on expelling a fellow " +
                    "Society member, you get distracted by a " +
                    "beautiful butterfly outside the window! Oooooh.. " +
                    "pretty!\n");
                return 1;
            }
            if(!query_member(vname))
            {
                write("That person isn't a member.\n");
                return 1;
            }
            break;

        case "pardon":
            if(!query_enemy(vname))
            {
                write("That person isn't an enemy.\n");
                return 1;
            }
            break;

        case "unbanish":
            if(!query_banished(vname))
            {
                write("That person isn't banished.\n");
                return 1;
            }
            else if(query_enemy(vname))
            {
                write("That person is still an enemy. You must pardon " +
                    "them first.\n");
                return 1;
            }
            break;

        case "declare":
            if(query_enemy(vname))
            {
                write("That person is already an enemy.\n");
                return 1;
            }
            if(query_member(vname))
            {
                write("You must expel a guild member.\n");
                return 1;
            }
            break;

        case "banish":
            if(query_banished(vname))
            {
                write("That person is already banished.\n");
                return 1;
            }
            if(query_member(vname))
            {
                write("You must expel a guild member.\n");
                return 1;
            }
            break;
        default:
            write("The syntax is: call vote <name>-<expel/banish/unbanish/" +
            "declare/pardon/invite>.\n");
            return 1;
    }

    tme = ctime(time() + VOTE_TIME);

    write("You have called a vote.\n");
    say(QCTNAME(TP) + " called a vote: " + vid + ".\n");

    log_file("kender_vote", ctime(time()) + " " + TP->query_name() +
        " called a vote: " + vid + ".\n");

    vote_id += ({vid});
    vnum = member_array(vid, vote_id);
    vote_caller += ({TP->query_real_name()});
    vote_counts_aye += ({0});
    vote_counts_nay += ({0});
    voters += ({({ })});
    end_vote += ({time() + VOTE_TIME});

    save_this_list();

    return 1;
}

/* Function name: do_vote
 * Description: Allows a player to vote on a vote in progress.
 *     Checks if that player is allowed to vote, alters the
 *     voting arrays accordingly, logs the vote and gives the
 *     appropriate messages.
 * Arguments: string str - aye/nay on vote as input by the player
 * Returns: 1 in success, 0 on failure
 */
int
do_vote(string str)
{
    int i, vnum;
    string vote, vid, *vote_arr;

    if(!strlen(str))
    {
        NF("Vote how on which topic?\n");
        return 0;
    }

    if(!MEMBER(TP))
    {
        NF("Only members get a vote.\n");
        return 0;
    }

    sscanf(str, "%s on %s", vote, vid);

    vnum = member_array(vid, vote_id);

    if(vnum == -1)
    {
        NF("There is no such vote.\n");
        return 0;
    }

    if(member_array(TP->query_real_name(), voters[vnum]) >= 0)
    {
        NF("You've already cast your vote.\n");
        return 0;
    }

    if(vote == "aye" || vote == "yes" || vote == "y")
    {
        write("You voted aye on the " + vid + " vote.\n");
        say(QCTNAME(TP) + " cast " + HIS(TP) + " vote.\n");

        log_file("kender_vote", ctime(time()) + " " + TP->query_name() +
            " voted aye on the " + vid + " vote.\n");

        vote_counts_aye[vnum]++;
    }
    else if(vote == "nay" || vote == "no" || vote == "n")
    {
        write("You voted nay on the " + vid + " vote.\n");
        say(QCTNAME(TP) + " cast " + HIS(TP) + " vote.\n");

        log_file("kender_vote", ctime(time()) + " " + TP->query_name() +
            " voted nay on the " + vid + " vote.\n");

        vote_counts_nay[vnum]++;
    }
    else
    {
        NF("Vote aye/yes on vote to support it or nay/no to not " +
            "support it.\n");
        return 0;
    }

    voters[vnum] += ({TP->query_real_name()});

    save_this_list();

    return 1;
}

/* Function name: clear_vote
 * Description: Alters the voting arrays when a vote is finalized
 * Arguments: string v - the vote to clear
 * Returns: 1 on success, 0 on failure
 */
void
clear_vote(string v)
{
    int from, to, end, vnum;
    string vid;

    vnum = member_array(v, vote_id);
    vid = vote_id[vnum];
    from = vnum - 1;
    to = vnum + 1;
    end = sizeof(vnum) - 1;
    voters = voters[0..from] + voters[to..sizeof(vnum)];

    log_file("kender_vote", ctime(time()) + " " + vid + " vote cleared.\n");

    if(sizeof(vote_id) == 0)
    {
        return 0;
    }

    if(sizeof(vote_id) == 1)
    {
        voters = ({ });
        vote_caller = ({ });
        vote_counts_aye = ({ });
        vote_counts_nay = ({ });
        end_vote = ({ });
        vote_id = ({ });
    }
    else if(vnum == 0)
    {
        voters = voters[to..end];
        vote_caller = vote_caller[to..end];
        vote_counts_aye = vote_counts_aye[to..end];
        vote_counts_nay = vote_counts_nay[to..end];
        end_vote = end_vote[to..end];
        vote_id = vote_id[to..end];
    }
    else if(vnum == sizeof(vote_id))
    {
        voters = voters[0..from];
        vote_caller = vote_caller[0..from];
        vote_counts_aye = vote_counts_aye[0..from];
        vote_counts_nay = vote_counts_nay[0..from];
        end_vote = end_vote[0..from];
        vote_id = vote_id[0..from];
    }
    else
    {
        voters = voters[0..from] + voters[to..end];
        vote_caller = vote_caller[0..from] + vote_caller[to..end];
        vote_counts_aye = vote_counts_aye[0..from] + vote_counts_aye[to..end];
        vote_counts_nay = vote_counts_nay[0..from] + vote_counts_nay[to..end];
        end_vote = end_vote[0..from] + end_vote[to..end];
        vote_id = vote_id[0..from] + vote_id[to..end];
    }

    save_this_list();
}


/* Function name: finalize_stuck_vote
 * Description: Allows a player to try to finalize a vote they
 *     think should have been finalized already, but for some
 *     reason isn't.
 * Arguments: string v - the vote to try to finalize
 * Returns: 1 on success, 0 on failure
 */
int
finalize_stuck_vote(string v)
{
    string str1, str2;
    int vnum, tme;

    if(!strlen(v))
    {
        NF("Finalize which vote?\n");
        return 0;
    }

    vnum = member_array(v, vote_id);

    if(vnum == -1)
    {
        NF("Finalize which vote?\n");
        return 0;
    }
    else
    {
        tme = time();

        if(end_vote[vnum] <= tme)
        {
            set_alarm(1.0, 0.0, &finalize_vote(v));
            write("You finalize the " + v + " vote.\n");
        }

        if(end_vote[vnum] > tme)
        {
            write("That vote hasn't finished yet.\n");
        }

    }

    return 1;
}

/* Function name: finalize_vote
 * Description: Logs the results of a finalized vote and carries out
 *     the decision based on the results.
 * Arguments: string v - the vote to finalize
 * Returns: 1
 */
int
finalize_vote(string v)
{
    int vnum, new_member = 0;
    string kname, str, vname, vtype;
    object pers;

    vnum = member_array(v, vote_id);

    str = vote_id[vnum];

    sscanf(str, "%s-%s", vname, vtype);

    kname = vote_caller[vnum];

    if(vtype == "invite")
    {
        if(vote_counts_aye[vnum] == 0 && vote_counts_nay[vnum] == 0)
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str + " vote failed due to a " +
                "lack of votes: " + vote_counts_aye[vnum] + " to " +
                vote_counts_nay[vnum] + ".\n");

            write_file(RESULTS, C(vname) + " failed to be invited due to " +
                "a lack of votes: " + vote_counts_aye[vnum] + " to " +
                vote_counts_nay[vnum] + ".\n");
        }
        else if (vote_counts_aye[vnum] == 1 && vote_counts_nay[vnum])
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str + " vote failed by " +
                vote_counts_nay[vnum] + " voting nay.\n");
            write_file(RESULTS, C(vname) + " failed to be invited by " +
            vote_counts_nay[vnum] + " voting nay and " +
            vote_counts_aye[vnum] + " voting aye.\n");
        }
        else if(vote_counts_aye[vnum] > vote_counts_nay[vnum])
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str + " vote successful by " +
                vote_counts_aye[vnum] + " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            write_file(RESULTS, C(vname) + " successfully invited by " +
            vote_counts_aye[vnum] + " voting aye and " +
            vote_counts_nay[vnum] + " voting nay.\n");

            add_invited(vname);
        }
        else
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed by " + vote_counts_nay[vnum] + " voting nay " +
                "and " + vote_counts_aye[vnum] + " voting aye.\n");

            write_file(RESULTS, C(vname) + " failed to be invited by " +
                vote_counts_nay[vnum] + " voting nay and " +
                vote_counts_aye[vnum] + " voting aye.\n");
        }

        set_alarm(1.0, 0.0, &clear_vote(v));

        return 1;
    }

    if(vtype == "expel")
    {
        if (!query_member(vname))
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str + " vote failed because " +
                C(vname) + " is no longer a member.\n");
            write_file(RESULTS, C(vname) + " failed to be expelled due " +
                "to expired membership. Votes were: " + vote_counts_aye[vnum] +
                " aye and " + vote_counts_nay[vnum] + " nay.\n");
            set_alarm(1.0, 0.0, &clear_vote(v));
            return 1;
        }
        if(end_vote[vnum] - VOTE_TIME - query_jointime(vname) < GUILD_AGE)
        {
            new_member = 1;
        }

        if(vote_counts_aye[vnum] == 0 && vote_counts_nay[vnum] == 0)
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed due to a lack of votes: " +
                vote_counts_aye[vnum] + " to " + vote_counts_nay[vnum] + ".\n");

            write_file(RESULTS, C(vname) + " failed to be expelled due to " +
                "a lack of votes: " + vote_counts_aye[vnum] + " to " +
                vote_counts_nay[vnum] + ".\n");
        }
        else if(vote_counts_aye[vnum] /2 >= vote_counts_nay[vnum] &&
                !new_member)
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote successful by " + vote_counts_aye[vnum] +
                " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            write_file(RESULTS, C(vname) + " successfully expelled by " +
                vote_counts_aye[vnum] + " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            add_expelled(vname);

            set_alarm(1.0,0.0, &expel_kender_from_guild(vname));
            if(add_banished(vname))
            {
                seteuid(getuid(TO));
                (KGROOM + "joinroom")->remove_kender_member(vname);
            }
        }
        else if(vote_counts_aye[vnum] > vote_counts_nay[vnum] &&
                new_member)
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote successful by " + vote_counts_aye[vnum] +
                " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            write_file(RESULTS, "New member " + C(vname) +
                " successfully expelled by " +
                vote_counts_aye[vnum] + " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            add_expelled(vname);

            set_alarm(1.0,0.0, &expel_kender_from_guild(vname));
            if(add_banished(vname))
            {
                seteuid(getuid(TO));
                (KGROOM + "joinroom")->remove_kender_member(vname);
            }
        }
        else
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed by " + vote_counts_nay[vnum] + " voting nay " +
                "and " + vote_counts_aye[vnum] + " voting aye.\n");

            write_file(RESULTS, C(vname) + " failed to be expelled by " +
                vote_counts_nay[vnum] + " voting nay and " +
                vote_counts_aye[vnum] + " voting aye.\n");
        }

        set_alarm(1.0, 0.0, &clear_vote(v));

        return 1;
    }

    if(vtype == "banish")
    {
        if(vote_counts_aye[vnum] == 0 && vote_counts_nay[vnum] == 0)
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed due to lack of votes: " +
                vote_counts_aye[vnum] + " to " + vote_counts_nay[vnum] + ".\n");

            write_file(RESULTS, C(vname) + " failed to be banished due " +
                "to lack of votes: " + vote_counts_aye[vnum] + " to " +
                vote_counts_nay[vnum] + ".\n");
        }
        else if(vote_counts_aye[vnum] > vote_counts_nay[vnum])
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote successful by " + vote_counts_aye[vnum] +
                " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            write_file(RESULTS, C(vname) + " successfully banished by " +
                vote_counts_aye[vnum] + " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");
            add_banished(vname);
            rem_invited(vname);
        }
        else
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed by " + vote_counts_nay[vnum] + " voting nay " +
                "and " + vote_counts_aye[vnum] + " voting aye.\n");

            write_file(RESULTS, C(vname) + " failed to be banished by " +
                vote_counts_nay[vnum] + " voting nay and " +
                vote_counts_aye[vnum] + " voting aye.\n");
        }

        set_alarm(1.0, 0.0, &clear_vote(v));

        return 1;
    }

    if(vtype == "unbanish")
    {
        if(vote_counts_aye[vnum] == 0 && vote_counts_nay[vnum] == 0)
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed due to lack of votes: " +
                vote_counts_aye[vnum] + " to " + vote_counts_nay[vnum] + ".\n");

            write_file(RESULTS, C(vname) + " failed to be unbanished due " +
                "to lack of votes: " + vote_counts_aye[vnum] + " to " +
                vote_counts_nay[vnum] + ".\n");
        }
        else if(vote_counts_aye[vnum] >= vote_counts_nay[vnum])
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote successful by " + vote_counts_aye[vnum] +
                " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            write_file(RESULTS, C(vname) + " successfully unbanished by " +
                vote_counts_aye[vnum] + " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            rem_expelled(vname);
            rem_banished(vname);
        }
        else
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed by " + vote_counts_nay[vnum] + " voting nay " +
                "and " + vote_counts_aye[vnum] + " voting aye.\n");

            write_file(RESULTS, C(vname) + " failed to be unbanished by " +
                vote_counts_nay[vnum] + " voting nay and " +
                vote_counts_aye[vnum] + " voting aye.\n");
        }

        set_alarm(1.0, 0.0, &clear_vote(v));

        return 1;
    }

    if(vtype == "declare")
    {
        if(vote_counts_aye[vnum] == 0 && vote_counts_nay[vnum] == 0)
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed due to lack of votes: " +
                vote_counts_aye[vnum] + " to " + vote_counts_nay[vnum] + ".\n");

            write_file(RESULTS, C(vname) + " failed to be declared an " +
                "enemy due to lack of votes: " + vote_counts_aye[vnum] +
                " to " + vote_counts_nay[vnum] + ".\n");
        }
        else if(vote_counts_aye[vnum] > vote_counts_nay[vnum])
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote successful by " + vote_counts_aye[vnum] +
                " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            write_file(RESULTS, C(vname) + " successfully declared an " +
                "enemy by " + vote_counts_aye[vnum] + " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            add_enemy(vname);
            add_banished(vname);
            rem_invited(vname);
        }
        else
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed by " + vote_counts_nay[vnum] + " voting nay " +
                "and " + vote_counts_aye[vnum] + " voting aye.\n");

            write_file(RESULTS, C(vname) + " failed to be declared an " +
                "enemy by " + vote_counts_nay[vnum] + " voting nay and " +
                vote_counts_aye[vnum] + " voting aye.\n");
        }

        set_alarm(1.0, 0.0, &clear_vote(v));

        return 1;
    }

    if(vtype == "pardon")
    {
        if(vote_counts_aye[vnum] == 0 && vote_counts_nay[vnum] == 0)
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed due to lack of votes: " +
                vote_counts_aye[vnum] + " to " + vote_counts_nay[vnum] + ".\n");

            write_file(RESULTS, C(vname) + " failed to be pardoned due " +
                "to lack of votes: " + vote_counts_aye[vnum] + " to " +
                vote_counts_nay[vnum] + ".\n");
        }
        else if(vote_counts_aye[vnum] > vote_counts_nay[vnum])
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote successful by " + vote_counts_aye[vnum] +
                " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            write_file(RESULTS, C(vname) + " successfully pardoned by " +
                vote_counts_aye[vnum] + " voting aye and " +
                vote_counts_nay[vnum] + " voting nay.\n");

            rem_enemy(vname);
        }
        else
        {
            log_file("kender_vote", ctime(time()) + " Vote called by: " +
                C(kname) + " on the " + str +
                " vote failed by " + vote_counts_nay[vnum] + " voting nay " +
                "and " + vote_counts_aye[vnum] + " voting aye.\n");

            write_file(RESULTS, C(vname) + " failed to be pardoned by " +
                vote_counts_nay[vnum] + " voting nay and " +
                vote_counts_aye[vnum] + " voting aye.\n");
        }

        set_alarm(1.0, 0.0, &clear_vote(v));

        return 1;
    }
}

/* Function name: expel_kender_from_guild
 * Description: Removes the kender from the guild if logged on
 * Arguments: string who - the name of the player to expel
 * Returns: 1 on success, 0 on failure
 */
int
expel_kender_from_guild(string who)
{
    int i;
    object pers = find_living(who);

    if(!strlen(who))
    {
        return 0;
    }

    if(!query_expelled(who))
    {
        return 0;
    }

    if(pers)
    {
        if(!MEMBER(pers))
        {
            return 0;
        }

        pers->catch_tell("You have been expelled from the Kender of " +
             "Ansalon!\n");
        pers->command("$ksad");

        if (!pers->remove_occ_kender())
	{
	    write("Failed to expell "+C(who)+" from the guild. Bug report?\n");
	    return 1;
	}

        return 1;
    }

    return 0;
}

/* Function name: query_voting
 * Description: queries if voting is in progress
 * Arguments: None
 * Returns: 1 if voting is in progress, 0 if not
 */
int
query_voting()
{
    return (sizeof(vote_id) > 0);
}

/* Function name: query_member_voted
 * Description: Finds how many votes a kender has voted on
 * Arguments: string name - the name of the person to test
 * Returns: the number of votes the person has voted on
 */
int
query_member_voted(string name)
{
    int i, counter = 0, size;

    for(i = 0, size = sizeof(vote_id); i < size; i++)
    {
        if(member_array(TP->query_real_name(), voters[i]) == -1)
        {
            counter++;
        }
    }

    return counter;
}

/* Function name: init
 * Description: Masks init to add in add_actions.
 */
void
init()
{
    ::init();

    add_action(call_vote, "call");
    add_action(finalize_stuck_vote, "finalize");
    add_action(list_things, "list");
    add_action(do_vote, "vote");
}

/* The following functions are meant for fixing messed up votes. */
void
add_vote(string caller, string vote, int start)
{
    if (!this_interactive()->query_wiz_level())
    {
        write("Not a wizard.\n");
        return;
    }

    if (!strlen(caller) || !strlen(vote) || !intp(start))
    {
        write("Inappropriate arguments.\n");
        return;
    }

    caller = lower_case(caller);
    vote = lower_case(vote);

    vote_id += ({ vote });
    vote_caller += ({ caller });
    vote_counts_aye += ({ 0 });
    vote_counts_nay += ({ 0 });
    voters += ({({ })});
    end_vote += ({ start });

    save_this_list();
    return;
}

void
add_voter(string voter, string vote, string aye_nay)
{
    int vnum;

    if (!this_interactive()->query_wiz_level())
    {
        write("Not a wizard.\n");
        return;
    }

    if (!strlen(voter) || !strlen(vote) || !strlen(aye_nay))
    {
        write("Inappropriate arguments.\n");
        return;
    }

    vnum = member_array(vote, vote_id);
    if (vnum == -1)
    {
        write("Invalid vote.\n");
        return;
    }

    if(aye_nay == "aye" || aye_nay == "yes" || aye_nay == "y")
        vote_counts_aye[vnum]++;
    else if (aye_nay == "nay" || aye_nay == "no" || aye_nay == "n")
        vote_counts_nay[vnum]++;
    else
        return;

    voters[vnum] += ({ voter });
    save_this_list();
    return;
}
