/*
 * /d/Gondor/guilds/rangers/council_base.c
 *
 * A base room for the councils. It includes:
 * A voting system for the council to call free-form votes.
 * You must call init_council_votes(board_path) from your room
 * create function, where board_path is the directory where you
 * store your board notes.
 *
 * Retirement code and council event viewing.
 *
 * Coded by Gwyneth on April 2, 2002
 *
 * Modification log:
 *  Gwyneth, 16 July 2004 - Removed snoop capability
 *  Gwyneth, 20 July 2004 - Moved note posting into its own function for
 *                          use with outside notifications.
 *  Tigerlily, August 18, 2004-Added option to view apprentice log
 */
#pragma no_shadow

#include "/d/Gondor/defs.h"
#include "rangers.h"

#include <files.h>
#include <language.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#define MOREOBJ   "/obj/more"

/* Assuming 3 line rules (240 characters) and 8 rules, this enables a 
   standard terminal to view all the rules without scrolling off. We 
   only want the most important rules listed anyways. */
#define MAX_RULES    8
#define MAX_RULE_LEN 240

/* Example:
   mapping gVote = ([ vote_name : ({end_time, caller, votetxt}) ])
   mapping gVoters = ([ vote_name : ([voters : votevals]) ]) 
*/

mapping        gVote = ([ ]);
mapping        gVoters = ([ ]);
string *       gRules = ({ });

string         gEvents;
string         gConfirm;
static string  gCompany = "general";
static object  gBoard;

public void     init_council_votes(string board_path);
public void     init_council_actions();
public void     finalize_votes();
public void     finish_vote(string vote_name);
public int      call_vote(string str);
public int      vote(string str);
public int      view(string vote_name);
public int      withdraw(string vote_name);
public int      end_vote(string vote_name);
public int      events(string str);
public int      messages(string str);
public int      ferret_names(string str);
public int      apprentice(string str);
public int      retire(string str);
public int      rule(string str);

/* Function name: init_council_votes
 * Description  : Call this function in the inheriting council room's
 *                create function.
 * Arguments    : string company - The company to initiate the council
 *                room for.
 */
public void
init_council_votes(string company)
{
    gBoard = clone_object(STD_DIR + "board");

    if (!objectp(gBoard))
        return;

    restore_object(MASTER);

    gCompany = company;

    switch(company)
    {
    case "ithilien":
        gBoard->set_board_name(RANGERS_BOARD + "roi_cboard");
        gEvents = ITHILIEN_LOG;
        break;
    case "north":
        gBoard->set_board_name(RANGERS_BOARD + "ron_cboard");
        gEvents = NORTH_LOG;
        break;
    default:
        gBoard->set_board_name(RANGERS_BOARD + "hq_cboard");
        gEvents = "";
        break;
    }

    gBoard->set_num_notes(50);
    gBoard->set_silent(0);
    gBoard->set_show_lvl(0);
    gBoard->set_remove_rank(WIZ_NORMAL);
    gBoard->set_remove_str("The note is firmly affixed to the board.\n");
    gBoard->move(TO, 1);
    return;
}

/* Function name: init_council_actions
 * Description  : Adds commands to the player when called in the init()
 *                function in the inheriting room.
 */
public void
init_council_actions()
{
    add_action(call_vote,   "call");
    add_action(vote,        "vote");
    add_action(view,        "view");
    add_action(withdraw,    "withdraw");
    add_action(end_vote,    "end");
    add_action(events,      "events");
    add_action(messages,    "messages");
    add_action(apprentice,  "apprentice");
    add_action(retire,      "retire");
    add_action(rule,        "rule");
    add_action(ferret_names,"ferrets");

}

/* Function name: eject_intruder
 * Description  : Removes a player who isn't allowed in the council room.
 * Arguments    : object ob - the player, object from - previous location
 */
public void
eject_intruder(object ob, object from)
{
    if (!objectp(ob))
        return;

    tell_object(ob, "You are not allowed to enter this room!\n");

    if (objectp(from))
        ob->move(from, 1);
    else
        ob->move(find_object(ob->query_default_start_location()), 1);

    return;
}

/* Function name: finalize_votes
 * Description  : Checks if any votes are ready to end. Ends them if so.
 *                If not, checks to see if the vote will end before the
 *                next armageddon, and sets an alarm to end it if it will.
 */
public void
finalize_votes()
{
    int i, size, current_time, vote_end;
    string *votes = m_indexes(gVote);

    current_time = time();

    for(i = 0, size = sizeof(votes); i < size; i++)
    {
        vote_end = gVote[votes[i]][0] - current_time;
        if (vote_end <= 0)
        {
            finish_vote(votes[i]);
        }
        else if (vote_end < (current_time - SECURITY->query_start_time() +
          SECURITY->query_uptime_limit()))
        {
            set_alarm(itof(vote_end), 0.0, &finish_vote(votes[i]));
        }
    }
}

/* Function name: post_results
 * Description  : Post a note on the board
 * Arguments    : string header - the subject of the post
 *                string msg - the message to post
 */
public void
post_results(string header, string msg)
{
    gBoard->create_note(header, "Moderator", msg);
}

/* Function name: finish_vote
 * Description  : Finishes a vote and records it, tallies up the winner.
 * Arguments    : string vote_name - the name of the vote to end.
 */
public void
finish_vote(string vote_name)
{
    int i, size, nays = 0, ayes = 0;
    object library;
    string book, ayetxt, naytxt, words, *voters, *vote_vals = ({});

    if (!strlen(vote_name))
        return;

    vote_name = capitalize(vote_name);
    if (member_array(vote_name, m_indexes(gVote)) == -1)
        return;

    vote_vals = m_values(gVoters[vote_name]);
    for (i = 0, size = sizeof(vote_vals); i < size; i++)
    {
        if (vote_vals[i] == "aye")
            ayes++;
        if (vote_vals[i] == "nay")
            nays++;
    }
    
    words = "The final results of the vote, " + vote_name +
        " are in!\n\n" + gVote[vote_name][2] + "\n\n";
    words += ("     ==========================================    \n\n");

    voters = m_indexes(gVoters[vote_name]);
    for (i = 0, size = sizeof(voters); i < size; i++)
    {
        words += MANAGER->query_title_name(voters[i]) + " voted: " + 
            gVoters[vote_name][voters[i]] + ".\n";
    }

    ayetxt = (!ayes ? "none" : LANG_NUM2WORD(ayes));
    naytxt = (!nays ? "none" : LANG_NUM2WORD(nays));

    words += "Total ayes: " + ayetxt + "; Total nays: " + naytxt + ".\n";

    post_results(vote_name + " Results", words);

/*  Needed to isolate it for use in outside applications.
    gBoard->create_note(vote_name + " Results", "Moderator", words);
*/

    tell_room(this_object(), "The Moderator enters, posts a note and " +
        "leaves again.\n");

    gVote = m_delete(gVote, vote_name);
    gVoters = m_delete(gVoters, vote_name);
    save_object(MASTER);

    /* Write to the vote book here once a path is figured out! */
    book = RANGERS_LIBRARY + "book/Votes_" + 
        (lower_case(gCompany) != "gondor" ? capitalize(gCompany) + "_" : "") + 
        extract(ctime(time()), -4);

    if (file_size(book) == -1)
    {
        (RANGERS_LIBRARY + "hq_library.c")->teleledningsanka();
        library = find_object(RANGERS_LIBRARY + "hq_library.c");
        if (objectp(library))
            library->add_vote_book(gCompany);
    }

    write_file(RANGERS_LIBRARY + "book/votes_" + 
        (lower_case(gCompany) != "gondor" ? lower_case(gCompany) + "_" : "") + 
        extract(ctime(time()), -4), 
        "     ==========================================\n" + words); 
    return;
}

/* Function name: call_vote
 * Description  : Allows a council member to call a vote.
 * Arguments    : string str - The argument as entered by the player.
 * Returns      : 1 if the function succeeded, 0 if it failed somehow.
 */
public int
call_vote(string str)
{
    int end_time;
    string vote_name, caller, votetext;

    /* Don't give a message to non-council, non-wizard, just return. */
    caller = capitalize(this_player()->query_real_name());
    if (!MANAGER->query_is_council(caller) && 
      !this_player()->query_wiz_level())
        return 0;
    
    if (!strlen(str))
    {
        /* No argument given. Provide the syntax. */
        notify_fail("The syntax is: 'call vote <vote name> for " +
            "<duration> days <vote text>.\n");
        return 0;
    }

    if (!parse_command(str, ({}), "[vote] %w 'for' %d 'days' / 'day' %s",
      vote_name, end_time, votetext))
    {
        /* Wrong syntax. Provide the syntax. */
        notify_fail("The syntax is: 'call vote <vote name> for " +
            "<duration> days <vote text>.\n");
        return 0;
    }

    /* Votes should last 1 to 14 days. */
    end_time = (end_time < 1 ? 1 : end_time);
    end_time = (end_time > 14 ? 14 : end_time);

    /* Get end_time in seconds. 86400 = (24 * 60 * 60) */
    end_time *= 86400;

    /* Find the exact time the vote will end. */
    end_time += time();

    vote_name = capitalize(vote_name);

    if (member_array(vote_name, m_indexes(gVoters)) != -1)
    {
        notify_fail("There is already a vote called " + vote_name +
            " in progress. Please use a different name.\n");
        return 0;
    }

    if (strlen(vote_name) > 20)
    {
        notify_fail("Please provide a vote name no longer than 20 " +
            "characters.\n");
        return 0;
    }

    if (strlen(votetext) > 2000)
    {
        notify_fail("Please write a shorter vote! This one is much " +
            "too long! You must limit your vote to 2000 characters.\n");
        return 0;
    }

    write("You call the vote, " + vote_name + ", ending on " + 
        ctime(end_time) + " with wording:\n" + votetext + "\n\n" +
        "To remove this vote, enter 'withdraw " + vote_name + "'.\n");
    say(QCTNAME(this_player()) + " calls a vote, " + vote_name + ", ending " +
        "on " + ctime(end_time) + " with wording: \n" + votetext + "\n\n");
    gVote += ([ vote_name : ({ end_time, caller, votetext }) ]);
    gVoters += ([ vote_name : ([])]);
    save_object(MASTER);
    return 1;
}

/* Function name: vote
 * Description  : Allows a council member to cast a vote.
 * Arguments    : string str - The argument as entered by the player.
 * Returns      : 1 if the function succeeded, 0 if it failed somehow.
 */
public int
vote(string str)
{
    string vote_val, vote_name, caller;

    if (!MANAGER->query_is_council(this_player()->query_real_name()))
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Vote <aye/nay> on <vote name>?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "%w 'on' %w", vote_val, vote_name))
    {
        notify_fail("Vote <aye/nay> on <vote name>?\n");
        return 0;
    }

    vote_name = capitalize(vote_name);
    if (member_array(vote_name, m_indexes(gVote)) == -1)
    {
        notify_fail("There is no such vote, " + vote_name + ".\n");
        return 0;
    }

    vote_val = lower_case(vote_val);
    vote_val = (vote_val == "yes" ? "aye" : vote_val);
    vote_val = (vote_val == "no" ? "nay" : vote_val);

    if (vote_val != "aye" && vote_val != "nay")
    {
        notify_fail(capitalize(vote_val) + " is not an option. You can " +
            "vote aye (yes) or nay (no) on this vote.\n");
        return 0;
    }

    caller = capitalize(this_player()->query_real_name());
    if (member_array(caller, m_indexes(gVoters[vote_name])) != -1)
    {
        /* They want to change their vote. */
        gVoters[vote_name][caller] = vote_val;
        write("You change your vote on " + vote_name + " to " + 
            vote_val + ".\n");
        say(QCTNAME(this_player()) + " changes " + 
            this_player()->query_possessive() + " vote on " + vote_name +
            " to " + vote_val + ".\n");
    }
    else
    {
        /* Add their vote. */
        gVoters[vote_name] += ([ caller : vote_val ]);
        write("You vote " + vote_val + " on " + vote_name + ".\n");
        say(QCTNAME(this_player()) + " votes " + vote_val + " on " + 
            vote_name + ".\n");
    }

    save_object(MASTER);
    return 1;
}

/* Function name: view
 * Description  : Lists the votes in progress or a specific vote. Shows
 *                the current votes values and the voters.
 * Arguments    : string vote_name - The argument as entered by the player, 
 *                either 'votes' or a specific vote name.
 * Returns      : 1 if the function succeeded, 0 if it failed somehow.
 */
public int
view(string vote_name)
{
    int i, size, j, size2;
    mapping voters;
    mixed *votes;
    string *voter_names;

    if (!MANAGER->query_is_council(this_player()->query_real_name()) &&
      !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!strlen(vote_name))
    {
        notify_fail("View <vote name>/votes?\n");
        return 0;
    }

    vote_name = capitalize(vote_name);

    if (vote_name == "Votes")
    {
        if (!m_sizeof(gVote))
        {
            write("There are no ongoing votes at the moment.\n");
            return 1;
        }

        write("     ==========================================    \n\n");
        votes = m_indexes(gVote);
        for (i = 0, size = sizeof(votes); i < size; i++)
        {
            write("The vote " + votes[i] + " called by " + gVote[votes[i]][1] +
                " and ending on " + ctime(gVote[votes[i]][0]) + 
                " is as follows:\n\n" + gVote[votes[i]][2] + "\n\n");

            voters = gVoters[votes[i]];
            if (m_sizeof(voters))
            {
                voter_names = m_indexes(voters);
                write("It has received the following votes:\n");
                for (j = 0, size2 = sizeof(voter_names); j < size2; j++)
                {
                    write(voter_names[j] + " voted: " +
                        gVoters[votes[i]][voter_names[j]] + ".\n");
                }
            }

            write("     ==========================================    \n\n");
        }

        return 1;
    }

    if (member_array(vote_name, m_indexes(gVote)) == -1)
    {
        notify_fail("There is no such vote " + vote_name + ".\n");
        return 0;
    }
    else
    {
        write("     ==========================================    \n\n");
        write("The vote " + vote_name + " called by " + gVote[vote_name][1] +
            " and ending on " + ctime(gVote[vote_name][0]) + 
            " is as follows:\n\n" + gVote[vote_name][2] + "\n\n");
        voters = gVoters[vote_name];
        if (m_sizeof(voters))
        {
            voter_names = m_indexes(voters);
            write("It has received the following votes:\n");
            for (i = 0, size = sizeof(voter_names); i < size; i++)
            {
                write(voter_names[i] + " voted: " +
                    gVoters[vote_name][voter_names[i]] + ".\n");
            }
        }

        write("     ==========================================    \n\n");
        return 1;
    }
}

/* Function name: withdraw
 * Description  : Withdraw a vote
 * Arguments    : string vote_name - The argument as entered by the 
 *                player. It should be the name of the vote to withdraw.
 * Returns      : 1 if the function succeeded, 0 if it failed somehow.
 */
public int
withdraw(string vote_name)
{
    string caller;

    if (!strlen(vote_name))
        return 0;

    vote_name = capitalize(vote_name);
    caller = capitalize(this_player()->query_real_name());

    if (member_array(vote_name, m_indexes(gVote)) == -1)
    {
        notify_fail("There is no such vote in progress.\n");
        return 0;
    }

    if (gVote[vote_name][1] != caller &&
      MANAGER->query_council(caller) != CAPTAIN_POSITION)
    {
        write("Only a Captain or the caller of the vote may " +
            "remove a vote.\n");
        return 1;
    }

    gVote = m_delete(gVote, vote_name);
    gVoters = m_delete(gVoters, vote_name);
    save_object(MASTER);

    write("You withdraw the vote called " + vote_name + ".\n");
    say(QCTNAME(this_player()) + " withdraws the vote called " + 
        vote_name + ".\n");
    return 1;
}

/* Function name: end_vote
 * Description  : Prematurely ends the vote. This can only be done by the
 *                Captain if they want to end a vote and still make it count.
 * Arguments    : string vote_name - the name of the vote to end
 * Returns      : 1 if successful, 0 if not
 */
public int
end_vote(string vote_name)
{
    if (!strlen(vote_name))
    {
        notify_fail("End which vote?\n");
        return 0;
    }

    if (MANAGER->query_council(this_player()->query_real_name()) 
      != CAPTAIN_POSITION)
    {
        notify_fail("You cannot end a vote. Only a Captain can do so.\n");
        return 0;
    }

    vote_name = capitalize(vote_name);
    if (member_array(vote_name, m_indexes(gVote)) == -1)
    {
        notify_fail("There is no such vote, " + vote_name + ".\n");
        return 0;
    }

    write("You end the vote called " + vote_name + ".\n");
    say(QCTNAME(this_player()) + " ends the vote called " + vote_name + ".\n");
    finish_vote(vote_name);

    return 1;
}

/* Function name: events
 * Description  : See what actions have been performed on council business.
 * Arguments    : string str - the argument entered by the player
 * Returns      : 1 if successful, 0 if not
 */
public int
events(string str)
{
    int i = 1, line_num = 1;
    object more_obj;
    string option = "company";

    if (strlen(str))
    {
        str = lower_case(str);

        /* Do they have both arguments? */
        i = sscanf(str, "%s %d", option, line_num);

        /* Maybe they only have one argument. */
        if (i != 2)
        {
            i = sscanf(str, "%s", option);

            /* They want to see a certain line number of the company log. */
            if (atoi(option) > 0)
            {
                line_num = atoi(option);
                option = "company";
                i = 2;
            }
        }

        if (i != 1 && i != 2)
        {
            notify_fail("Events [company/all] [line]?\n");
            return 0;
        }
    }

    option = lower_case(option);

    if (i == 1)
    {
        switch(option)
        {
        case "company":
            if (file_size(gEvents) >= 1)
                tail(gEvents);
            else
                write("There are no events recorded.\n");
            return 1;
        case "all":
            if (file_size(RANGERS_LOG) >= 1)
                tail(RANGERS_LOG);
            else
                write("There are no events recorded.\n");
            return 1;
        default:
            notify_fail("Events [company/all] [line]?\n");
            return 0;
        }
    }
    else
    {
        if (!line_num)
        {
            notify_fail("Events [company/all] [line]?\n");
            return 0;
        }

        more_obj = clone_object(MOREOBJ);

        switch(option)
        {
        case "company":
            if (file_size(gEvents) >= 1)
                more_obj->more(gEvents, line_num);
            else
                write("There are no events recorded.\n");
            return 1;
        case "all":
            if (file_size(RANGERS_LOG) >= 1)
                more_obj->more(RANGERS_LOG, line_num);
            else
                write("There are no events recorded.\n");
            return 1;
        default:
            notify_fail("Events [company/all] [line]?\n");
            return 0;
        }

    }
}

/* Function name: messages
 * Description  : Allows a council member to read messages left by
 *                other players.
 * Arguments    : string str - The argument as entered by the player.
 *                             If entered, it should be a line number
 * Returns      : 1 for success, 0 for failure
 */
public int
messages(string str)
{
    int i, line_num = 1;
    object more_obj;

    if (strlen(str))
    {
        i = sscanf(str, "%d", line_num);
        if (i != 1)
        {
            notify_fail("Messages [line number]?\n");
            return 0;
        }
        
        line_num = (line_num < 1 ? 1 : line_num);
    }

    more_obj = clone_object(MOREOBJ);
    if (file_size(RANGERS_LOG_DIR + "messages"))
        more_obj->more(RANGERS_LOG_DIR + "messages", line_num);
    else
        write("There are no messages.\n");

    return 1;
}

/*
 * Description  : Allows a council member to see ferret names
 * Arguments    : string str - The argument as entered by the player.
 *                             If entered, it should be a line number
 * Returns      : 1 for success, 0 for failure
 */
public int
ferret_names(string str)
{
    int i, line_num = 1;
    object more_obj;

    if (strlen(str))
    {
        i = sscanf(str, "%d", line_num);
        if (i != 1)
        {
            notify_fail("Ferrets [line number]?\n");
            return 0;
        }
        
        line_num = (line_num < 1 ? 1 : line_num);
    }

    more_obj = clone_object(MOREOBJ);
    if (file_size(RANGERS_LOG_DIR + "ferret_names"))
        more_obj->more(RANGERS_LOG_DIR + "ferret_names", line_num);
    else
        write("There are no new names to report.\n");

    return 1;
}

/* Function name: apprentice
 * Description  : Allows a council member to read the apprentice activity
 *                log
 * Arguments    : string str - The argument as entered by the player.
 *                             If entered, it should be a line number
 * Returns      : 1 for success, 0 for failure
 */
public int
apprentice(string str)
{
    int i, line_num = 1;
    object more_obj;

    if (strlen(str))
    {
        i = sscanf(str, "%d", line_num);
        if (i != 1)
        {
            notify_fail("apprentice [line number]?\n");
            return 0;
        }
        
        line_num = (line_num < 1 ? 1 : line_num);
    }

    more_obj = clone_object(MOREOBJ);
    if (file_size(RANGERS_LOG_DIR + "apprentice"))
        more_obj->more(RANGERS_LOG_DIR + "apprentice", line_num);
    else
        write("There is currently no activity in the apprentice log.\n");

    return 1;
}

/* Function name: retire
 * Description  : Allows a council member to retire from the council.
 * Arguments    : string str - The argument as entered by the player.
 *                             It should be 'from council'.
 * Returns      : 1 for success, 0 for failure
 */
public int
retire(string str)
{
    string name = capitalize(this_player()->query_real_name());

    if (!strlen(str) || lower_case(str) != "from council")
    {
        notify_fail("Retire from council?\n");
        return 0;
    }

    if (!MANAGER->query_is_council(name))
    {
        notify_fail("You cannot retire from council if you are " +
            "not on it.\n");
        return 0;
    }

    if (gConfirm != name)
    {
        write("Are you sure you wish to retire from council? Try to " +
            "retire once more if you are really sure.\n");
        say(QCTNAME(this_player()) + " considers retiring from council.\n");
        gConfirm = name;
        return 1;
    }   
    else
    {
        if (MANAGER->remove_council(name))
        {
            write("Your work here is done. You return your key and " +
                "retire from council.\n");
            say(QCTPNAME(this_player()) + " work here is done. " + 
                capitalize(this_player()->query_pronoun()) + " returns " + 
                this_player()->query_possessive() + " key and retires from " +
                "council.\n");
        }
        else
        {
            write("Something went wrong! You failed to retire! Please " +
                "file a bug report.\n");
        }

        return 1;
    }
}

public int
rule(string str)
{
    int i, size, rule_num = -1;
    string rule_option = "", rule = "";

    if (!strlen(str))
    {
        notify_fail("Rule <add/remove> <rule>? or Rule list?\n");
        return 0;
    }

    if (lower_case(str) == "list")
    {
        if (sizeof(gRules) == 0)
        {
            write("There are no rules listed.\n");
            return 1;
        }

        write("These are the rules currently listed:\n");
        for (i = 0, size = sizeof(gRules); i < size; i++)
            write((i + 1) + ": " + gRules[i] + "\n");
        return 1;
    }

    if (!parse_command(str, ({}), "%w %d", rule_option, rule_num))
    {
        if (!parse_command(str, ({}), "%w %s", rule_option, rule))
        {
            notify_fail("Rule <add/remove> <rule>? or Rule list?\n");
            return 0;
        }
    }

    rule_option = lower_case(rule_option);

    if (rule_option == "add")
    {
        if (sizeof(gRules) >= MAX_RULES)
        {
            notify_fail("You can only list 8 rules. You need to remove a " +
                "rule before you can add a new one.\n");
            return 0;
        }

        if (strlen(rule) < 1 || strlen(rule) > MAX_RULE_LEN)
        {
            notify_fail("Please keep the rule between 1 and 240 characters " +
                "or less. This is, depending on your screen length, 3 " +
                "lines.\n");
            return 0;
        }

        write("You add the rule:\n" + rule + "\nto the list of rules.\n");
        say(QCTNAME(this_player()) + " adds the rule:\n" + rule + 
            "\nto the list of rules.\n");
        gRules += ({ rule });
        save_object(MASTER);
        return 1;
    }
    else if (rule_option == "remove")
    {
        if (rule_num < 1 || rule_num > sizeof(gRules))
        {
            notify_fail("There is no such rule number.\n");
            return 0;
        }

        if (stringp(gRules[rule_num - 1]))
        {
            write("You remove rule " + rule_num + ": " + gRules[rule_num - 1] +
                " from the list.\n");
            say(QCTNAME(this_player()) + " removes rule " + rule_num + ": " +
                gRules[rule_num - 1] + " from the list.\n");
            /* The shown numbers are one off, due to arrays starting with 0 */
            gRules -= ({ gRules[rule_num - 1] });
            save_object(MASTER);
            return 1;
        }
        else
        {
            notify_fail("There is no such rule number.\n");
            return 0;
        }
    }
    else
    {
        notify_fail("Rule <add/remove> <rule>? or Rule list?\n");
        return 0;
    }
}

public int
query_prevent_snoop()
{
    return 1;
}
