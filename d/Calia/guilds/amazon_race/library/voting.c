inherit "/std/room";
#include <composite.h>
#include <language.h>
#include <time.h>
#include "../defs.h"

mapping gVotes = ([]);
mapping gVotings = ([ ]);


mixed tally_votes(int number);
string get_remaining_time(int i);
void remove_object() { save_object(VOTE_SAVE); ::remove_object();}
mapping query_votings(){ return gVotings; }

void
create_room()
{
    set_short("Voting server");
    set_long("Voting server.\n");
    
    restore_object(VOTE_SAVE);    
}

void
create_new_vote(object target, object presenter)
{
    string applicant_name = target->query_real_name();
	string presenter_name = presenter->query_real_name();
	string desc = "Should we allow "+capitalize(applicant_name)+
		" to join our ranks?";
    
    gVotes += ([ (sizeof(m_indexes(gVotes))+1) : ({((86400 * VOTE_EXPIRE) + time()),
		   desc, presenter_name, applicant_name}) ]);
    gVotings += ([ sizeof(m_indexes(gVotes)) :([]) ]);

    save_object(VOTE_SAVE);
}

int
vote_info(int i, string requester)
{
    if (gVotes[i])
    {
		write("Description: "+gVotes[i][VDESC]+"\n");
		write("Sponsor: "+gVotes[i][VPRESENTER]+"\n");
        write("Yes: "+tally_votes(i)[0]+
			 " No: "+tally_votes(i)[1]+
		     " Abstain: "+tally_votes(i)[2]+".\n\n");
		if (member_array(requester, m_indexes(gVotings[i])) != -1)
		{
		    write("You have casted your vote for '"+gVotings[i][requester]+
			  "' on this vote.\n");
		}
		else
			write("You have not yet casted your vote for this vote.\n");
        return 1;
    }
    
    return 0;
}

int
remove_vote(int i)
{
    if (gVotes[i])
	{
		gVotes = m_delete(gVotes, i); // Remove the vote
		gVotings = m_delete(gVotings, i); // Remove the votings
		save_object(VOTE_SAVE);
        return 1;
    }        
    return 0;
}

mixed
tally_votes(int number)
{
    int i;
    string *votings = m_values(gVotings[number]);
    mapping votes = ([ "yes":0, "no":0, "abstain":0, ]);
    
    for (i=0;i < sizeof(votings);i++)
    {
	if (votings[i] == "yes")
	    votes["yes"]++;
	if (votings[i] == "no")
	    votes["no"]++;	
	if (votings[i] == "abstain")
	    votes["abstain"]++;	
	    
    }
    return ({votes["yes"], votes["no"], votes["abstain"]});
}

string
get_remaining_time(int i)
{
    int tim = (gVotes[i][VTIME] - time());
    
    if (tim < 0)
       return "-ENDED-";
    return TIME2STR(tim, 2);
}

string
validate_vote(int number, string value, string name, int new = 1)
{
    string *yes_v     = ({"yes","aye","yae"});
    string *no_v      = ({"no","nay","nae"});
    string *abstain_v = ({"pass","abstain"});

    /* First we'll fix so all variations of 'yes'
	   logs as yes and all variations of 'no' as no
    */
	if (member_array(value, yes_v) != -1)
        value = "yes";
    if (member_array(value, no_v) != -1)
        value = "no";
    if (member_array(value, abstain_v) != -1)
        value = "abstain";

	if (!gVotes[number])
		return "That vote does not exist.\n";
	/* Check if the player already voted */
    if (new && member_array(name, m_indexes(gVotings[number])) != -1)
	    return "You already voted on that vote.\n";

    if (value != "yes" && value != "no" && value != "abstain")
        return "You may only vote yes, no or abstain.\n";

	return "";
}

void
add_voting(int number, string value, string name)
{
    if (gVotings[number])
	    gVotings[number] += ([ name:value ]);
	else
		gVotings[number] = ([ name:value ]);
	save_object(VOTE_SAVE);
}

void
change_voting(int number, string value, string name)
{
    if (gVotings[number][name])
	{
	    gVotings[number][name] = value;
		save_object(VOTE_SAVE);
		return;
    }
	else
	{
	    write("You havnt voted for that vote yet.\n");		    
		return;
	}		
}

void
list_votes()
{
    int i;
    int *votes = m_indexes(gVotes);

    write(" ------------------------------ \n");
    write("| Num | Applicant  | Remaining |\n");
    write("|-----+------------+-----------|\n");        
    for (i=0;i < sizeof(votes);i++)
    {
        write(sprintf("| %-3d | %-10s |%9s |\n", 
          (i+1), gVotes[(i+1)][VAPPLICANT], 
          get_remaining_time(i+1)));
     
    }
    write(" ------------------------------ \n");
}