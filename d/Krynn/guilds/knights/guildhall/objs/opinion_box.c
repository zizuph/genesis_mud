/* A voting box */
/* Aridor, 08/95 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../../guild.h"

#define EDITOR    "/obj/edit"
#define RESULTS_TO  KLOG+"impeach_results"
#define SAVE_FILE   MASTER
#define VOTE_TIME   604800 /*120 testing, normally: 604800*/

inherit "/std/object";


string vote_issue;
string vote_caller;
string *who_voted;
int    *vote_counts; /* an array:
			({ yes votes: black, sentry, black, squire, crown, sword, rose;
			no votes (same order) })
			*/
int    end_time_vote;
int    vote_active;
static mapping voted_once = ([]);

void
create_object()
{
    int tme;

    set_name("box");
    set_adj("voting");
    set_long("This is a voting box. You can vote here on the current issue " +
	     "by using 'vote aye' or 'vote nay' about the issue. The current " +
	     "issue to vote on is:\n@@current_issue@@" +
	     "If there is no voting going on currently, anyone can (anonymously) " +
	     "start a 'new vote' which will give an editor to describe the issue. " +
	     "Note that the issue must be formulated so that aye/nay votes " +
	     "and only aye/nay votes are possible. Each voting will run for " +
	     "exactly one week. The results of the previous votings can be " +
	     "read by everyone with 'results'.\n");
    add_prop(OBJ_M_NO_GET,1);

    if (!IS_CLONE)
      return;

    seteuid(getuid(TO));
    restore_object(SAVE_FILE);
    tme = time();
    if (vote_active)
      if (tme < end_time_vote)
	set_alarm(itof(end_time_vote - tme),0.0,"end_vote");
      else
	set_alarm(100.0,0.0,"end_vote");
}

string
current_issue()
{
    string tme = ctime(end_time_vote);
    if (vote_active)
      return implode(explode(vote_issue,"\n"),"\n     ") +
	"\nVoting ends: " +
	tme[0..9] + "," + tme[10..15] + "\n";
    else
      return "     VOTING IS NOT ACTIVE CURRENTLY.\n";
}

void
init()
{
    ADA("vote");
    ADA("results");
    ADD("start_vote","new");
}

int
vote(string str)
{
    int ok = 0, type;
    string the_name;

    if (TP->query_guild_member("Solamnian Knights"))
      ok = 3;
    if (TP->query_guild_member("Sentries of Solamnia"))
      ok = 1;
    if (TP->query_wiz_level())
      return 0;
    if (!ok)
      return 0;
    
    NF("Voting is not active currently.\n");
    if (!vote_active)
      return 0;
    
    the_name = TP->query_real_name();
    NF("You have already voted on this issue.\n");
    if (member_array(the_name, who_voted) >= 0)
      return 0;
    
    if (member_array(the_name, m_indexes(voted_once)) < 0)
      {
	  voted_once += ([ the_name:str ]);
	  write("Are you sure? Please vote one more time to confirm.\n");
	  return 1;
      }

    if (voted_once[the_name] != str)
      {
	  write("Your voting differed! Your vote was discarded.\n");
	  voted_once = m_delete(voted_once, the_name);
	  return 1;
      }

    voted_once = m_delete(voted_once, the_name);

    NF("You can only vote with 'aye' or 'nay'.\n");
    type = ok + TP->query_knight_level() - 2;
    if (str == "aye" || str == "yes" || str == "y")
      vote_counts[type]++;
    else if (str == "nay" || str == "no" || str == "n")
      vote_counts[type + 7]++;
    else
      return 0;
    write("You voted: " + C(str) + ".\n");
    say(QCTNAME(TP) + " votes at the voting box.\n");
    who_voted += ({ the_name });

    seteuid(getuid(TO));
    save_object(SAVE_FILE);
    return 1;
}

int
start_vote(string str)
{
    if (str != "vote")
      return 0;
    if (!TP->query_guild_member("Solamnian Knights") &&
	!TP->query_guild_member("Sentries of Solamnia") &&
	!TP->query_wiz_level())
      return 0;

    NF("There is already a voting going on.\n");
    if (vote_active)
      return 0;

    write("Please enter the issue to vote on.\n");
    clone_object(EDITOR)->edit();

    return 1;
}

void
done_editing(string txt)
{
    if (!txt || txt == "")
      {
	  write("Aborted.\n");
	  return;
      }
    vote_issue = txt;
    /*vote_caller = TP->query_name();*/
    vote_active = 1;
    write("New vote active.\n");
    who_voted = ({});
    vote_counts = ({ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 });
    end_time_vote = time() + VOTE_TIME;
    set_alarm(itof(end_time_vote - time()),0.0,"end_vote");
    seteuid(getuid(TO));
    save_object(SAVE_FILE);
}


void
end_vote()
{
    string txt = ("\n" +
		  ctime(time()) + "\n" +
		  vote_issue +
		  "Result:         Aye  Nay             Aye  Nay\n" +
		  /*"Black Sentries: " +
		  sprintf("%3i  %3i",vote_counts[0],vote_counts[7]) +
		  "   Sentries: " +
		  sprintf("%3i  %3i",vote_counts[1],vote_counts[8]) +
		  */
		  "\nBlack Knights:  " +
		  sprintf("%3i  %3i",vote_counts[2],vote_counts[9]) +
		  "   Squires:  " + 
		  sprintf("%3i  %3i",vote_counts[3],vote_counts[10]) +
		  "\nCrown:          " + 
		  sprintf("%3i  %3i",vote_counts[4],vote_counts[11]) +
		  "   Sword:    " + 
		  sprintf("%3i  %3i",vote_counts[5],vote_counts[12]) +
		  "\nRose:           " + 
		  sprintf("%3i  %3i",vote_counts[6],vote_counts[13]) + "\n");
    
    write_file(RESULTS_TO, txt);
    /*find_living("aridor")->catch_msg(txt);*/
    vote_active = 0;
    tell_room(E(TO),"A knight arrives.\n" +
	      "The knight empties the voting box and counts the votes.\n" +
	      "The knight writes the results down into the results book.\n" +
	      "The knight leaves again.\n");

    seteuid(getuid(TO));
    save_object(SAVE_FILE);
}

int
results()
{
    NF("What?\n");
    if (!TP->query_guild_member("Solamnian Knights") &&
	!TP->query_guild_member("Sentries of Solamnia") &&
	!TP->query_wiz_level())
      return 0;

    /*say(QCTNAME(TP) + " checks the voting results.\n");*/
    tail(RESULTS_TO);
    return 1;
}

