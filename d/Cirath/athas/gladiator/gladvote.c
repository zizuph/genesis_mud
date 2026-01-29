/*

 gladvote.c: The gladiator voting device: Serpine, 5/4/95.

 completely recoded by Valen, Jun 2004
 - repaired an error, that was making it impossible to promote the winner
 - changed voting system to two-round
 - added logging and old voting data storage
 - added status and rules display

 */

inherit "/std/object";

#include "defs.h"
#include <macros.h>
#include <composite.h>
#include <files.h>

// The following define allows to call some internal functions
//#define TESTING

#define SAVEFILE (GLAD_LOG + "running_election")

#define SAVE save_object(SAVEFILE)

#define VOTE_LOG_FILE (GLAD_LOG + "vote_log")
#define VOTE_LOG(x) write_file(VOTE_LOG_FILE, ctime(time()) + " " + (x))

#define ROUND_ZERO_TIME (86400*7)
#define ROUND_ONE_TIME (86400*7)
#define ROUND_TWO_TIME (86400*7)

int round;
int elections_start_time;
int next_round_time;
mapping *candidates;
mapping *votes;

static int vote_alarm = 0;

static void update_status(void);

static void
set_vote_alarm(int newtime)
{
    if(newtime < 0) return;
    if(vote_alarm) remove_alarm(vote_alarm);
    vote_alarm = set_alarm(itof(newtime), 0.0, update_status);
}

public void
log(string str)
{
    VOTE_LOG(str);
}

static int destruct_flag;

void
remove_object()
{
    if(destruct_flag)
      log("Voting basket destructed (TP=" + capitalize(TP->query_real_name()) + ").\n");
    ::remove_object();
}

#ifndef TESTING
static
#endif
void
archive_data()
{
    if(file_size(SAVEFILE + ".o") > 0)
    {
        SAVE;
        rename(SAVEFILE + ".o", GLAD_LOG + "old_elections_" +
               elections_start_time + ".o");
    }
}

#ifndef TESTING
static
#endif
void
end_elections()
{
    log("End of elections, data archived and removed.\n");
    archive_data();
    if(IS_ROOM_OBJECT(environment(this_object())))
        tell_room(environment(this_object()), "A gladiator arrives, unmounts the " +
            short() + " and leaves to count the votes.\n");
    remove_object();
}

static void
make_overseer(string who)
{
    object winner;

    winner = find_player(who);

    log(capitalize(who) + " promoted to the High Overseer post.\n");
    ADD_OVERSEER(who, "high");
    if(winner) winner->catch_msg("You were chosen as the High Overseer " +
                                 "of the Gladiators. Congratulations.\n");
    end_elections();
}

#ifndef TESTING
static
#endif
void
reset_vote()
{
    archive_data();

    round = 0;
    candidates = ({([]), ([]), ([])});
    votes = ({([]), ([]), ([])});
    elections_start_time = time();
    next_round_time = elections_start_time + ROUND_ZERO_TIME;
    SAVE;
}

static int
votes_sort_fun(mixed a, mixed b)
{
    int diff = b[1] - a[1];

    if(diff) return diff;

    return b[2] - a[2];
}

#ifndef TESTING
static
#endif
mixed compute_results()
{
    string *cands;
    string *voters;
    mixed results;
    mapping sumvote;
    int allvotes;

    int i;

    cands = m_indexes(candidates[round]);
    voters = m_indexes(votes[round]);
    results = ({});
    sumvote = ([]);
    allvotes = 0;

// This is most likely redundant, but lets make the code explicit
    for(i = 0; i < sizeof(cands); i++)
        sumvote[cands[i]] = 0;

// beware, a horrible spell approaches
    for(i = 0; i < sizeof(voters); i++)
        sumvote[votes[round][voters[i]][0]] += votes[round][voters[i]][1];

    for(i = 0; i < sizeof(cands); i++)
    {
        allvotes += sumvote[cands[i]];
        results += ({ ({ cands[i], sumvote[cands[i]],
                         candidates[round][cands[i]] }) });
    }

    results = sort_array(results, votes_sort_fun);

    return ({ results, allvotes });
}

void
update_status(void)
{
    if(time() < next_round_time) return;

    if(round == 0 && m_sizeof(candidates[0]) < 2) return;

    if(round == 0)
    {
        log("Round 1 started with " + m_sizeof(candidates[0]) + " candidates.\n");
        candidates[1] = candidates[0] + ([]);
        round = 1;
        next_round_time = time() + ROUND_ONE_TIME;
        set_vote_alarm(ROUND_ONE_TIME);
        SAVE;
    }
    else
    {
        mixed res = compute_results();

        if (round == 1)
        {
            log("End of first round, computing results.\n");
            if(res[1] && res[0][0][1] * 2 >= res[1])
            {
                // The winner got majority of all votes, promote him
                log("Winner: " + capitalize(res[0][0][0]) + " got " +
                    res[0][0][1] + " votes out of " + res[1] + "\n");
                make_overseer(res[0][0][0]);
            }
            else
            {
                log("No candidate got majority, final round started.\n");
                candidates[2][res[0][0][0]] = res[0][0][2];
                candidates[2][res[0][1][0]] = res[0][1][2];
                round = 2;
                next_round_time = time() + ROUND_TWO_TIME;
                set_vote_alarm(ROUND_TWO_TIME);
                SAVE;
            }
        }
        else
        {
            log("End of final round, computing results.\n");
            log("Winner: " + capitalize(res[0][0][0]) + " got " +
                res[0][0][1] + " votes out of " + res[1] + "\n");
            make_overseer(res[0][0][0]);
        }
    }
}

static void
where_cloned()
{
    string se;
    object env = environment(this_object());


    if(!env)
        se = "<empty environment>";
    else
        se = file_name(env);

    log("Voting basket cloned into " + se + "\n");

    if(IS_ROOM_OBJECT(environment(this_object())))
        tell_room(environment(this_object()), "A gladiator arrives, fastens a " +
            short() + " to the floor and goes away.\n");
}

#ifdef TESTING
string
wizlong(void)
{
    if(!TP->query_wiz_level()) return "";

    return "\nAs a wizard, you may also issue command <vhelp> to get instructions " +
           "useful in debugging the elections system.";
}
#endif

void create_object()
{
    set_name("basket");
    set_adj("wicker");
    add_adj("voting");
    set_long("This shabby old container holds the markers used to vote "+
      "for the High Overseer of the Gladiators. To show "+
      "your opinion on this important matter, 'vote <name>'. "+
      "Or you can 'run' and 'withdraw' to join/enter the race "+
      "or hit 'candidates' to get a list. You may also do 'status' to look at present " +
      "situation and 'rules' to read rules of the elections." +
#ifdef TESTING
      "@@wizlong@@" +
#endif
      "\n");
    add_prop(OBJ_M_NO_GET, "It seems to have been bolted down.\n");

    setuid(); seteuid(getuid());

    destruct_flag = 0;

    if(!IS_CLONE)
    {
        log("Voting basket object loaded.\n");
    }
    else if(sizeof(object_clones(this_object())) > 1)
    {
        log("A clone of the voting basket already exists, exiting.\n");
        set_alarm(0.0, 0.0, remove_object);
    }
    else
    {
        int timeout;

        log("Voting basket created.\n");

        destruct_flag = 1;

        set_alarm(0.0, 0.0, where_cloned);

        if(file_size(SAVEFILE + ".o") > 0)
        {
            restore_object(SAVEFILE);
            log("Data found and restored (timestamp = " +
                 elections_start_time + ").\n");
        }
        else
        {
            reset_vote();
            log("Data not found, elections reset and started.\n");
        }

        timeout = next_round_time - time();
        if(timeout >= 0) set_vote_alarm(timeout);
    }
}


#ifdef TESTING
void
next_round(void)
{
    write("Next round scheduled.\n");
    if(round == 0 && m_sizeof(candidates[0]) < 2)
    {
        write("There are not enough candidates to start voting, though.\n");
        remove_alarm(vote_alarm);
        vote_alarm = 0;
    }
    next_round_time = time();
    update_status();
}
#endif


/*
  This function is called from the room where the basket is cloned.
  We do not really need that, but better to check a bit more often than
  to wait indefinitely if something goes wrong.
 */

int
check_over_time()
{
    int interval = next_round_time - time();

    if(interval <= 0)
        update_status();
    else
        set_vote_alarm(interval);
    return 1;
}

int
can_participate(object who)
{
    if(IS_WIZ(who))
    {
        write("Wizards should stay out of mortal affairs.\n");
        return 0;
    }

    if(!IS_MEMBER(who))
    {
        write("But you aren't even a Gladiator!\n");
        return 0;
    }

    if ((who->query_gladiator_level()) < 10)
    {
        write("To participate in the elections you must " +
              "be more accomplished as a Gladiator.\n");
        return 0;
    }

    return 1;
}

#ifndef TESTING
static
#endif
int
do_vote_core(string voter, string candidate, int weight)
{
    log(capitalize(voter) + " votes for " + capitalize(candidate) +
           " with weight of " + weight + "\n");
    votes[round][voter] = ({ candidate, weight });
    SAVE;
}

int
do_vote(string who)
{
    int weight;
    string *s;
    string voter;

    if(!who || who == "" || sizeof(s = explode(who, " ")) > 1)
    {
        NF("Vote <who>?\n");
        return 0;
    }

    if (!can_participate(TP)) return 1;

    who = lower_case(s[0]);

    if (round == 0)
    {
        write("You can't vote during the candidates registration period.\n");
        return 1;
    }

    voter = lower_case(TP->query_real_name());

    if (votes[round][voter])
    {
        write("But you have already voted.\n");
        return 1;
    }

    if(!candidates[round][who])
    {
        write("That person isn't in the running.\n");
        return 1;
    }

    weight = 1;
    if ((TP->query_gladiator_level()) > 19) weight = 2;

    do_vote_core(voter, who, weight);

    TP->catch_msg("You cast your vote into the basket.\n");
    say(QCTNAME(TP) + " tosses a marker into the basket.\n");

    return 1;
}

#ifndef TESTING
static
#endif
int
do_add_core(string candidate, int exp)
{
    log(capitalize(candidate) + " (" + exp +
        ") decides to become a candidate.\n");
    candidates[round][candidate] = exp;
    SAVE;

// This may be needed as we may be waiting for another candidate to sign up.
    update_status();
}

int
do_run(string parms)
{
    string who;

    if(parms && parms != "")
    {
        NF("Do you want to <run> as a candidate for the High Overseer?\n");
        return 0;
    }

    who = (TP->query_real_name());

    if(!can_participate(TP)) return 1;

    if(member_array(who, m_indexes(candidates[round])) > -1)
    {
        write("But you are already a candidate.\n");
        return 1;
    }

    if(round > 0)
    {
        write("Too late, the voting is already in progress. Maybe next time.\n");
        return 1;
    }

    do_add_core(who, TP->query_acc_exp(SS_OCCUP));

    TP->catch_msg("You enter the running for High Overseer.\n");
    say (QCTNAME(TP)+" decides to run for High Overseer.\n");

    return 1;
}

#ifndef TESTING
static
#endif
int
do_remove_core(string candidate)
{
    log(capitalize(candidate) + " decides to withdraw from the elections.\n");
    candidates[round] = m_delete(candidates[round], candidate);
    SAVE;
}

int
do_withdraw(string parms)
{
    string who;

    if(parms && parms != "")
    {
        NF("Do you want to <withdraw> yourself from the elections?\n");
        return 0;
    }

    who = (TP->query_real_name());

    if(!can_participate(TP)) return 1;

    if(member_array(who, m_indexes(candidates[round])) == -1)
    {
        write("But you are not a candidate.\n");
        return 1;
    }

    if(round > 0)
    {
        write("Too late, the voting is already in progress.\n");
        return 1;
    }

    do_remove_core(who);

    TP->catch_msg("You remove yourself from the race.\n");
    say(QCTNAME(TP)+" doesn't want to run for High Overseer anymore.\n");

    return 1;
}

int
list_fools(string parms)
{
    string *ac;

    if(parms && parms != "")
    {
        NF("Use just <candidates> command to see the list of candidates.\n");
        return 0;
    }

    if(!m_sizeof(candidates[0]))
    {
        write("There are no candidates yet.\n");
        return 1;
    }
    if(round == 2)
    {
        write("In the second round, these two candidates compete:\n");
    }
    else
    {
        write("\nThose who currently want to be High Overseer:\n");
    }

    ac = m_indexes(candidates[round]);
    ac = map(ac, capitalize);
    ac = sort_array(ac);
    write(COMPOSITE_WORDS(ac) + ".\n");

    return 1;
}

int
do_rules(string parms)
{
    string s;

    if(parms && parms != "")
    {
        NF("Use just <rules> command to read the rules.\n");
        return 0;
    }

    s = read_file(GLAD_HELP + "vote_rules.txt");
    write(s);
    say(QCTNAME(TP) + " reads the rules of the elections.\n");
    log(capitalize(TP->query_real_name()) + " reads the rules of the elections.\n");

    return 1;
}

static string
add_wizinfo(string name)
{
  return name + " (" + candidates[round][name] + ")";
}

static string
show_candidates(void)
{
    string *ac;

    ac = m_indexes(candidates[round]);
    if(TP->query_wiz_level()) ac=map(ac, add_wizinfo);
    ac = map(ac, capitalize);
    ac = sort_array(ac);
    return COMPOSITE_WORDS(ac);
}

int
do_status(string parms)
{
    if(parms && parms != "")
    {
        NF("Use just <status> command to examine the status of the elections.\n");
        return 0;
    }

    say(QCTNAME(TP) + " checks the status of the elections.\n");
    log(capitalize(TP->query_real_name()) + " checks the status of the elections.\n");

    write("The state of the elections is as follows:\n");

    if(round == 0)
    {
        int ncand = m_sizeof(candidates[0]);

        write("The first part of the elections is active, candidates can register " +
              "themselves.\n");
        if(ncand < 1)
            write("There are no candidates registered so far.\n");
        else
        {
            write("Registered candidates: " + show_candidates() + ".\n");
        }
        if(time() < next_round_time)
        {
            write("Voting will start at: " +
                  ctime(next_round_time) +
                  ((ncand < 2) ?
                     " if at least two candidates are registered." : "") +
                  "\n");
        }
        else
          write("Voting will start as soon as two candidates are registered.\n");
    }
    else
    {
        int v = m_sizeof(votes[round]);
        mixed res;

        if(round == 1)
        {
            write("The second part of the elections is active, gladiators can vote " +
                  "for their favourite candidates.\n");
        }
        if(round == 2)
        {
            write("The third part of the elections is active, gladiators can vote " +
                  "for one of the two winners of the previous round.\n");
        }

        write("You can vote for one of the candidates: " + show_candidates() + "\n");

        if(v < 1)
            write("No gladiator voted so far.\n");
        else if(v == 1)
            write("One gladiator voted so far.\n");
        else
            write(capitalize(LANG_WNUM(m_sizeof(votes[round]))) +
                    " gladiators voted so far.\n");
        if(votes[round][TP->query_real_name()])
            write("You already gave your vote to " +
                    capitalize(votes[round][TP->query_real_name()][0]) + ".\n");

        write("This round will last until: " + ctime(next_round_time) + "\n");

        if(TP->query_wiz_level())
        {
            int i;
            string *s;
            mixed res;
            string *tmp;

            s = m_indexes(votes[round]);

            write("Votes (only wizards see this):\n");

            tmp = ({});
            for(i = 0; i < sizeof(s); i++)
                tmp += ({ capitalize(s[i]) + " -> " +
                        capitalize(votes[round][s[i]][0]) +
                        " (weight " + votes[round][s[i]][1] + ")" });
            write(COMPOSITE_WORDS(tmp) + ".\n");

            write("Preliminary results (only wizards see this):\n");
            res = compute_results();
            write("Sum of all votes given: " + res[1] + "\n");
            for(i = 0; i < sizeof(res[0]); i++)
            {
                write(res[0][i][1] + " " + capitalize(res[0][i][0]) +
                    " (" + res[0][i][2] + ")\n");
            }
        }
    }
    return 1;
}

#ifdef TESTING
int
do_vhelp(string s)
{
    if(!TP->query_wiz_level())
    {
        notify_fail("What ?\n");
        return 0;
    }
    write("Call basket do_add_core candidate%%guildexp\n");
    write("Call basket do_remove_core candidate\n");
    write("Call basket do_vote_core voter%%votee%%weight\n");
    write("Call basket next_round\n");
    return 1;
}
#endif

void
init()
{
    ::init();
    add_action(do_vote, "vote");
    add_action(do_run, "run");
    add_action(do_withdraw, "withdraw");
    add_action(list_fools, "candidates");
    add_action(do_status, "status");
    add_action(do_rules, "rules");
#ifdef TESTING
    add_action(do_vhelp, "vhelp");
#endif
}

