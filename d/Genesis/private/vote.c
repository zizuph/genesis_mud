/*
 * /d/Genesis/domain/private/vote.c
 *
 * A voting room for wizards to anonymously vote.
 *
 * Coded by Gwyneth on March 28, 2001
 */
#pragma strict_types
#pragma no_shadow

inherit "/std/room";

#include <cmdparse.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#define WORDING	"Enter the wording of the vote you wish to call or ~q to " + \
		"quit: "
#define ANSWERS	"Enter no more than six different answers, separated by " + \
		"commas. Note that the answer 'none of the " + \
		"above/uncertain' will always be given as a choice: "
#define VOTES	"Enter vote number or ~q to quit: "
#define CONFIRM_VOTE	"Enter yes to confirm your vote, no to cancel " + \
			"your vote and choose again or ~q to quit: "

/* One week voting time */
#define VOTE_TIME	604800

#define VOTE_DIR	"/d/Genesis/domain/private/vote/"

//#define DEBUG_ON
#ifdef DEBUG_ON
#undef VOTE_TIME
#define VOTE_TIME	60
#endif DEBUG_ON

#define RESULTS		("/d/Genesis/log/votes")
#define MOREOBJ		"/obj/more"

/* Global Variables */
/* new_votes */
mapping a = ([]);
/* votes */
mapping b = ([]);
/* voted */
mapping c = ([]);

static object gBoard;

/* Prototypes */
string read_sign();
private int cast_vote(string str);
private int test_voted(string name, string vote);
private void display_options(string vote);
private void catch_vote(string choice, string vote, string name);
private void record_vote(string confirm, int vote_num, string vote, string name);

private int display_results(string str);
private int list_votes(string str);
private int clear_vote(string vote);
private void finalize_votes();
private int remove_vote(string vote);

private int start_vote(string str);
private void setup_vote(string wording, string label);
private void get_answers(string answer, string wording, string label);
private void set_vote(string cont, string answer, string wording, string label);

void
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("a dimly lit chamber");
    set_long("This is a dimly lit chamber where wizards may call a " +
        "vote on a topic and cast their votes. The votes are purely " +
        "advisory. This means that no vote is binding. They simply " +
        "let other people know the general sentiment. A sign hangs " +
        "off-center on the wall.\n");

    add_item(({"sign", "wall"}), &read_sign());
    add_cmd_item("sign", "read", &read_sign());

    gBoard = clone_object(VOTE_DIR + "board");
    gBoard->move(this_object(), 1);

    add_prop(ROOM_I_INSIDE, 1);
    restore_object(MASTER);
    finalize_votes();
}

/*
 * Function name: finalize_votes
 * Description  : Checks if a vote needs to be ended and recorded. If
 *                not it checks if a vote will need ending before the
 *                planned armageddon. If it does, sets an alarm to do so.
 */
private void
finalize_votes()
{
    int i, size, current_time, vote_time;
    string *votes = m_indexes(a);

    current_time = time();

    for(i = 0, size = sizeof(votes); i < size; i++)
    {
        vote_time = a[votes[i]][0] - current_time;
        if (vote_time <= 0)
        {
            clear_vote(votes[i]);
        }
        else if (vote_time > 0 && 
             vote_time < SECURITY->query_uptime_limit() + 
             SECURITY->query_start_time() - current_time)
        {
            set_alarm(itof(vote_time), 0.0, &clear_vote(votes[i]));
        }
    }
}

string
read_sign()
{
    return("You tilt your head slightly to read the sign:\n\n" +
        " - call vote <name>....Start a new vote with a short id as <name>.\n" +
        "                       You will be prompted for details.\n" +
        " - list votes/<name>...List all votes, or see the details of one.\n" +
        " - view results........See the results of finished votes.\n" +
        " - view recent.........Tail the vote results.\n" +
        " - vote on <name>......Cast your vote. You will be prompted for " +
        "more.\n" +
        " - recall <name>.......Remove a vote if you are an arch or on the " +
        "                       AoD team.\n\n" +
        "All votes are anonymous. Please do not abuse your privileges.\n");
}

void
init()
{
    ::init();

    add_action(cast_vote, "vote");
    add_action(display_results, "view");
    add_action(list_votes, "list");
    add_action(remove_vote, "recall");
    add_action(start_vote, "call");
}

private int
exist_vote(string vote)
{
    return(member_array(vote, m_indexes(a)) != -1);
}

/*
 * Function name: cast_vote
 * Description  : Initial parsing to handle vote casting. Tests if
 *                voter has voted on this vote before and if vote
 *                exists. Voter's name is encrypted. Voter is prompted
 *                to enter their vote.
 * Arguments    : string str - As entered by the user.
 * Returns      : 0 on failure, 1 on success
 */
private int
cast_vote(string str)
{
    string vote, name;

    if (!this_player()->query_wiz_level())
    {
        return 0;
    }
    else if (!strlen(str))
    {
        notify_fail("Vote on which vote?\n");
        return 0;
    }
    else if (!parse_command(str, ({}), "[on] [vote] %w", vote))
    {
        notify_fail("Vote on what?\n");
        return 0;
    }
    else if (!exist_vote(vote))
    {
        notify_fail("No such vote, " + vote + ". You may 'list votes' to " +
            "view what is up for vote.\n");
        return 0;
    }
    else
    {
        name = crypt(this_player()->query_real_name(), vote);

        if (test_voted(name, vote))
        {
            write("You have already voted on this vote.\n");
            return 1;
        }

        display_options(vote);
        write(VOTES);
        input_to(&catch_vote(, vote, name));
        return 1;
    }
    return 1;
}

/*
 * Function name: test_voted
 * Description  : Checks if player has voted on a particular vote before.
 * Arguments    : string name - the name of the player
 *                string vote - the vote to check for
 * Returns      : 1 if player has voted, 0 if not
 */
private int 
test_voted(string name, string vote)
{
    if (member_array(name, c[vote]) == -1)
        return 0;
    else
        return 1;
}

/*
 * Function name: display_options
 * Description  : Display vote wording and options numerically.
 * Arguments    : string vote - the vote to display
 */
private void 
display_options(string vote)
{
    int i, size;
    write(a[vote][1] + "\n\n");
    for(i = 1, size = sizeof(a[vote][2]); i <= size; i++)
        write(i + ". " + a[vote][2][i - 1] + "\n");
    return;
}

/*
 * Function name: catch_vote
 * Description  : Takes the vote and asks to confirm the choice and
 *                makes sure that the option is valid. Passes the
 *                vote on to record_vote, ~q will quit
 *                out completely.
 * Arguments    : string choice - the actual vote
 *                string vote - the vote being voted on
 *                string name - the encrypted identifier of the voter
 */
private void
catch_vote(string choice, string vote, string name)
{
    int vote_num;

    if (!exist_vote(vote))
    {
        write("The vote has ended while you were trying to vote. No vote " +
            "was cast.\n");
        return;
    }

    if (!strlen(choice))
    {
        display_options(vote);
        write(VOTES);
        input_to(&catch_vote(, vote, name));
        return;
    }

    if (choice == "~q")
    {
        write("Aborting vote.\n");
        return;
    }

    vote_num = atoi(choice);
    vote_num--;

    if (vote_num < 0 || vote_num >= sizeof(a[vote][2]))
    {
        display_options(vote);
        write("Invalid number. " + VOTES);
        input_to(&catch_vote(, vote, name));
        return;
    } 
    else
    {
        write("You have chosen " + choice + ". " + 
            a[vote][2][vote_num] + "\n" + CONFIRM_VOTE);
        input_to(&record_vote(, vote_num, vote, name));
        return;
    }
}

/*
 * Function name: record_vote
 * Description  : Takes a confirmation, cancellation or quit.
 *                If no, process starts all over. If quit (~q),
 *                the process is aborted. If yes, the vote is
 *                recorded along with the encrypted identifier of the
 *                voter.
 * Arguments    : string confirm - y(es)/n(o)/~q
                  int vote_num - the vote choice
 *                string vote - the vote id
 *                string name - the encrypted identifier
 */
private void
record_vote(string confirm, int vote_num, string vote, string name)
{
    setuid();
    seteuid(getuid());

    if (!exist_vote(vote))
    {
        write("The vote ended while you were trying to cast your vote. No " +
            "vote was recorded, sorry.\n");
        return;
    }

    if (!strlen(confirm))
    {
        write("You have chosen " + (vote_num + 1) + ". " + 
            a[vote][2][vote_num] + "\n" + CONFIRM_VOTE);
        input_to(&record_vote(, vote_num, vote, name));
        return;
    }

    if (confirm == "~q")
    {
        write("Aborting vote casting.\n");
        return;
    }

    confirm = lower_case(confirm);

    if (confirm == "n" || confirm == "no")
    {
        write("Cancelling vote. Choose another number or ~q to quit.\n");
        cast_vote(vote);
        return;
    }
    else if (confirm != "y" && confirm != "yes")
    {
        write("You have chosen " + vote_num + ". " + 
            a[vote][2][vote_num - 1] + "\n" + CONFIRM_VOTE);
        input_to(&record_vote(, vote_num, vote, name));
        return;
    }
    else
    {
        b[vote][vote_num] += 1;
        c[vote] += ({ name });
        save_object(MASTER);
        write("OK.\n");
        return;
    }
}

/*
 * Function name: display_results
 * Description  : shows the results of finished votes
 * Arguments    : string str - as entered by the user (should be 'results')
 * Returns      : 1 for success, 0 for failure
 */
private int
display_results(string str)
{
    if (!this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!strlen(str) || 
      (lower_case(str) != "results" && lower_case(str) != "recent"))
    {
        list_votes(str);
        return 1;
    }

    if (lower_case(str) == "recent")
    {
        if (file_size(RESULTS) > 0)
            tail(RESULTS);
        else
            write("There are no results to list.\n");
        return 1;
    }
    else
    {
        if (file_size(RESULTS) < 30 && file_size(RESULTS) > 0)
            cat(RESULTS);
        else if (file_size(RESULTS) >= 30)
            clone_object(MOREOBJ)->more(RESULTS, 1);
        else
            write("There are no results to list.\n");
        return 1;
    }
}

/*
 * Function name: list_votes
 * Description  : Displays a list of all vote ids or the details of
 *                a specific vote.
 * Arguments    : string str - as entered by the user
 * Returns      : 1 on success, 0 on failure
 */
private int
list_votes(string str)
{
    string vote;
    int i, size;

    if (!this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("List votes?\n");
        return 0;
    }
    else if (lower_case(str) == "results" || lower_case(str) == "recent")
    {
        display_results(str);
        return 1;
    }
    else if (lower_case(str) == "votes" || lower_case(str) == "all" ||
      lower_case(str) == "all votes")
    {
        size = sizeof(m_indexes(a));

        if (!size)
        {
            write("There are no active votes.\n");
            return 1;
        }

        for (i = 0; i < size; i++)
        {
            vote = m_indexes(a)[i];
            write("Vote name: " + vote + "\n");
        }

        write("To view the wording and options of a specific vote, you " +
            "may list that vote by name.\n");
        return 1;
    }
    else if (member_array(str, m_indexes(a)) != -1)
    {
        write("Vote name: " + str + "\n");
        display_options(str);
        return 1;
    }
    else
    {
        notify_fail("No such vote to list. You may list all of the " +
            "votes for a list or a specific one for more details.\n");
        return 0;
    }
}

/*
 * Function name: start_vote
 * Description  : Initial parsing for starting a new vote. Checks that
 *                the name is not too long and prompts for wording,
 *                which is passed to setup_vote
 * Arguments    : string str - as entered by the user
 * Returns      : 1 on success, 0 on failure
 */
private int
start_vote(string str)
{
    string label;

    if (!this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!parse_command(lower_case(str), ({}), "[a] [new] 'vote' [called] %w",
      label))
    {
        notify_fail("Call a new vote named what? For example, 'call " +
            "vote coolest' might be a vote for the coolest wizard in " +
            "Genesis.\n");
        return 0;
    }
    else if (strlen(label) > 12)
    {
        write("Vote name is too long.\n"); 
        return 1;
    }
    else
    {
        write(WORDING);
        input_to(&setup_vote(, label));
        return 1;
    }
}

/*
 * Function name: setup_vote
 * Description  : Prompts for a list of possible answers or aborts.
 * Arguments    : string wording - the wording of the vote
 *                string label - the vote id
 */
private void
setup_vote(string wording, string label)
{
    if (!strlen(wording))
    {
        write(WORDING);
        input_to(&setup_vote(, label));
        return;
    }
    else if (wording == "~q")
    {
        write("Aborting new vote.\n");
        return;
    }
    else
    {
        write(ANSWERS);
        input_to(&get_answers(, wording, label));
        return;
    }
}

/*
 * Function name: get_answers
 * Description  : Takes possible vote options, tests for at least
 *                two and no more than six. Asks to confirm the
 *                vote before starting it.
 * Arguments    : string answer - in the form: answer1,answer2,answer3
 *                string wording - the wording of the vote
 *                string label - the vote id
 */
private void
get_answers(string answer, string wording, string label)
{
    string *options;

    if (!strlen(answer))
    {
        write(ANSWERS);
        input_to(&get_answers(, wording, label));
        return;
    }
    else if (lower_case(answer) == "~q")
    {
        write("Aborting new vote.\n");
        return;
    }

    options = explode(answer, ",");

    if(sizeof(options) > 6)
    {
        write("You've given too many answers. " + ANSWERS);
        input_to(&get_answers(, wording, label));
        return;
    }
    else if (sizeof(options) < 2)
    {
        write("You must give at least two options. " + ANSWERS);
        input_to(&get_answers(, wording, label));
        return;
    }

    write("You have called a vote named " + label + " as:\n" + wording +
        "\nWith answers: " + answer + ", None of the Above or Uncertain. Are " +
        "you sure you want to call this vote? If you enter yes, it cannot " +
        "be changed. yes/no: ");
    input_to(&set_vote(, answer, wording, label));
    return;
}

/*
 * Function name: set_vote
 * Description  : Tests that the caller wants to continue with the
 *                vote. Aborts if not, records the information if yes.
 * Arguments    : string cont - continue?
 *                string wording - the wording of the vote
 *                string label - the vote id
 */
private void
set_vote(string cont, string answer, string wording, string label)
{
    int i, size, *vote_num = ({});
    string extra, *options, words = "";

    setuid();
    seteuid(getuid());

    if (!strlen(cont))
    {
        write("You have called a vote named " + label + " as:\n" + wording +
            "\nWith answers: " + answer + ", uncertain/none of the above. " +
            "Are you sure you want to call this vote? If you enter yes, it " +
            "cannot be changed. yes/no: ");
        input_to(&set_vote(, answer, wording, label));
        return;
    }

    cont = lower_case(cont);

    if (cont == "~q" || 
      cont == "n" ||
      cont == "no")
    {
        write("Aborting new vote.\n");
        return;
    }
    else if (cont != "y" && cont != "yes")
    {
        write("Please enter yes to continue the vote, no to cancel the " +
            "vote or ~q to quit: ");
        input_to(&set_vote(, answer, wording, label));
        return;
    }

    options = explode(answer, ",");

    /* Get rid of any extra leading spaces for a nice display. */
    for (i = 0, size = sizeof(options); i < size; i++)
    {
        extra = extract(options[i], 0, 0);
        if (extra == " ")
            options[i] = extract(options[i], 1);
    }

    options += ({ "None of the Above or Uncertain" });

    for (i = 0, size = sizeof(options); i < size; i++)
        vote_num += ({0});

    a += ([ label : ({ time() + VOTE_TIME, wording, options }) ]);
    b += ([ label : vote_num ]);
    c += ([ label : ({}) ]);
    write("You start a new vote called " + label + ".\n" + wording + "\n");
    save_object(MASTER);
    words += ("A new vote has been called " + label + ".\n\n");
    words += break_string(wording, 70);
    words += "\nPossible answers are:\n";

    for (i = 0, size = sizeof(options); i < size; i++)
    {
        words += options[i] + "\n";
    }

    words += ("\nYou have until " + ctime(time() + VOTE_TIME) + " to vote.\n");
    if (!objectp(gBoard))
    {
        gBoard = clone_object(VOTE_DIR + "board");
        gBoard->move(this_object(), 1);
    }

    gBoard->create_note("New Vote Called", "Moderator", words);
    return;
}

/*
 * Function name: log_vote
 * Description  : Logs a vote for result viewing once it is finished.
 * Arguments    : string vote - the vote id
 */
private void
log_vote(string vote)
{
    int i, size;
    string text = a[vote][1] + "\nFinal " + vote + " vote results: ";
    string words = text + "\n";
    string *choices = a[vote][2];

    for (i = 0, size = sizeof(choices); i < size; i++)
    {
        words += choices[i] + ": " + b[vote][i] + "\n";
        text += choices[i] + ": " + b[vote][i] + ", ";
    }

    log_file("votes", ctime(time()) + " " + text + "\n", -1);

    if (!objectp(gBoard))
    {
        gBoard = clone_object(VOTE_DIR + "board");
        gBoard->move(this_object(), 1);
    }

    gBoard->create_note("Finalized Vote", "Moderator", words + "\n");
    return;
}

/*
 * Function name: clear_vote
 * Description  : Clears the vote information from the save file.
 * Arguments    : string vote - the vote id
 * Returns      : 1 always
 */
private int 
clear_vote(string vote)
{
    setuid();
    seteuid(getuid());

    log_vote(vote);
    a = m_delete(a, vote);
    c = m_delete(c, vote);
    b = m_delete(b, vote);
    save_object(MASTER);
    return 1;
}

/*
 * Function name: remove_vote
 * Description  : Removes the vote without logging the results. Arch+
 * Arguments    : string vote - the vote id to remove
 * Returns      : 1 if removed, 0 if not
 */
private int 
remove_vote(string vote)
{
    string name = this_interactive()->query_real_name();

    setuid();
    seteuid(getuid());

    if (SECURITY->query_wiz_rank(name) >= WIZ_ARCH ||
      SECURITY->query_team_member("aod", name))
    {
        if (member_array(vote, m_indexes(a)) == -1)
        {
            notify_fail("No such vote to remove.\n");
            return 0;
        }

        log_file("recalled_votes", ctime(time()) + " " + 
            capitalize(this_interactive()->query_real_name()) +
            " removed the " + vote + " vote.\n", -1);
        a = m_delete(a, vote);
        c = m_delete(c, vote);
        b = m_delete(b, vote);
        write("You recall the " + vote + " vote.\n");
        save_object(MASTER);

        if (!objectp(gBoard))
        {
            gBoard = clone_object(VOTE_DIR + "board");
            gBoard->move(this_object(), 1);
        }

        gBoard->create_note("Vote Removed", "Moderator", "The " + vote +
            " vote was removed.\n");
        return 1;
    }

    return 0;
}
