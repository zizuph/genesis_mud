#pragma strict_types
#pragma no_shadow

inherit "/std/object";

#include "../guild.h"
#include <composite.h>

private int close = 0;
private mapping votes = ([]);
private string *candidates = ({});

static private int close_id = 0;

void close_vote();

/*
 * Function name: set_close_alarm
 * Description:   Start the countdown to closing time for voting
 */
void
start_close_alarm()
{
    int t;

    remove_alarm(close_id);

    if (close > 0)
    {
        if ((t = (close - time())) > 0)
	{
            close_id = set_alarm(itof(t), 0.0, close_vote);
            return;
	}
        
        close_vote();
    }

    close_id = 0;
}   

/*
 * Function name: create_object
 * Description:   Configure the voting object
 */
void
create_object()
{
    set_no_show();
    set_name("council_vote");

    setuid();
    seteuid(getuid());
    restore_object(VAMP_LOG_DIR + "council_votes");

    start_close_alarm();
}

/*
 * Function name: save
 * Description:   Save the voting data
 */
void
save()
{
    setuid();
    seteuid(getuid());

    save_object(VAMP_LOG_DIR + "council_votes");
}

/*
 * Function name: set_candidates
 * Description:   Designate candidates to be voted for
 * Arguments:     string *who - an array of candidate names
 */
void
set_candidates(string *who)
{
    candidates = who + ({});
    save();
}

/*
 * Function name: set_close_time
 * Description:   Designate the time at which voting will be
 *                closed.
 * Arguments:     int t - the time (as returned by time())
 */
void
set_close_time(int t)
{
    close = t;

    start_close_alarm();

    save();
}

/*
 * Function name: vote
 * Description:   The vote command
 * Aruments:      Arguments to the "vote" command
 * Returns:       1/0 - syntax success/failure
 */
int
vote(string str)
{
    int i;

    sscanf(str, "for %s", str);

    if (!close)
    {
        write("Voting is closed.\n");
        return 1;
    }

    if (!sizeof(candidates))
    {
        write("There are no candidates.\n");
        return 1;
    }

    if ((i = member_array(str, candidates)) < 0)
    {    
        write(capitalize(str) + " is not a candidate.\n" + 
            "Valid candidates are: " + COMPOSITE_WORDS(candidates) + ".\n");
        return 1;
    }

    votes[this_player()->query_real_name()] = str;

    save();

    write("You vote for " + capitalize(str) + ".\n");

    return 1;
}

/*
 * Function name: init
 * Description:   Add voting commands
 */
void
init()
{
    ::init();
    add_action(vote, "vote");
}

/*
 * Function name: close_vote
 * Description:   Stop voting
 */
void
close_vote()
{
    setuid();
    seteuid(getuid());
    save_object(VAMP_LOG_DIR + "council_vote_final_" + time());

    close = 0;
    candidates = ({});
    votes = ([]);

    save();
}
