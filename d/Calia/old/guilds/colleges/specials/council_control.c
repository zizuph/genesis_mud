/*
 
  Control object for the Assembly (Council of the Colleges of Elemental Magic).
 
  This controls their administrative powers, and gives out information to
  guild code that may need it.

  By Bishop of Calia, July 2003.

 */

#include <macros.h>
#include "defs.h"

//One day's worth of seconds:
#define ONE_DAY 86400
//One week's worth of seconds:
#define ONE_WEEK 604800
 //Generic vote, no hardcoded results: 
#define VOTE_GENERIC 1
//Vote to expel a member:
#define VOTE_EXPEL 2
//Vote to approve a new member:
#define VOTE_ADDMEMBER 3
//Vote to add a new member to council:
#define VOTE_ADDCOUNCIL 4
//Vote to remove someone from council:
#define VOTE_REMCOUNCIL 5
//Vote to spell ban a member:
#define VOTE_SPELLBAN 6
//Vote to confine a member to the Tower:
#define VOTE_CONFINEMENT 7
//Vote to promote a member in rank:
#define VOTE_PROMOTE 8
//Vote to demote a member in rank:
#define VOTE_DEMOTE 9
//Vote to lift all punishments from someone:
#define VOTE_LIFTPUN 10
//These are used to store element used by a member in the member_list mapping:
#define FIRE 8
#define AIR 16
#define WATER 32
#define EARTH 64

//This is a mixed array of vote information. Each vote has the following 
//format -  0: int vote type, 1: string reason for vote, 2: string name
//of the target of the vote, 3: int time the vote ends, 4 int the
//current result of the vote (positive means Aye, negative Nay, 0 undecided),
//5 int four bits determining which councilmembers have voted.
mixed *pending_votes = ({});

mapping member_list = ([ ]);
mapping council_members = ([ ]);
mapping punishments = ([ ]);
mapping approved_applicants = ([ ]);

// Prototypes:
varargs int start_vote(int type, string reason, string vote_target);
void resolve_vote(int index);
void check_votes();
void add_member(string str, int bits);
void remove_member(string str);
int perform_vote(object voter, int index, string vote);
int query_council(string str);
int check_resolvable(int index);
int check_approved_applicant(string str);
int query_punishments(string str);
int query_rank(string str);
void cleanup_approved_applicants();
string list_agenda();


 /*
    Starts a vote.
    
    Args: object starter, int type of vote, (optional) string reason for vote 
        and (optional) name of the target of the vote.
        
    returns: 0 - success!
             1-X - failure for various reasons.

 */
varargs int
start_vote(object starter, int type, string reason, string vote_target)
{
    setuid();
    seteuid(getuid());
    
    if (!query_council(starter->query_name()) 
        && starter->query_name() != "Bishop")
    {
        return 1;
    }

    if (strlen(reason) > 50)
    {
        return 2;  
    }
    
    if (type == VOTE_GENERIC)
    {
        pending_votes += ({({type, reason, 0, time() + ONE_WEEK, 0, 0})});
        save_object(COLLEGE_LOGS + "council_data");
        return 0;
    }
    if (type == VOTE_EXPEL)
    {
        if (!member_list[vote_target])
        {
            return 3;
        }
        if (punishments[vote_target] & EXPELLED_BIT)
        {
            return 7;
        }   
             
        pending_votes += ({({type, reason, vote_target, 
            time() + ONE_WEEK, 0, 0})});
        save_object(COLLEGE_LOGS + "council_data");
        return 0;
    }
    if (type == VOTE_ADDMEMBER)
    {
        if (member_list[vote_target])
        {
            return 4;
        }
        
        pending_votes += ({({type, reason, vote_target, 
            time() + ONE_WEEK, 0, 0})});
        save_object(COLLEGE_LOGS + "council_data");
        return 0;
    }   
    if (type == VOTE_ADDCOUNCIL)
    {
        if (!member_list[vote_target])
        {
            return 3;
        }
        if (query_council(vote_target))
        {
            return 5;
        }
        if (member_list[vote_target] & APPRENTICE_LVL_BIT)
        {
            return 12;
        }
        
        pending_votes += ({({type, reason, vote_target, 
            time() + ONE_WEEK, 0, 0})});
        save_object(COLLEGE_LOGS + "council_data");
        return 0;
    } 
    if (type == VOTE_REMCOUNCIL)
    {
        if (!member_list[vote_target])
        {
            return 3;
        }
        if (!query_council(vote_target))
        {
            return 6;
        }
        
        pending_votes += ({({type, reason, vote_target, 
            time() + 2*ONE_WEEK, 0, 0})});
        save_object(COLLEGE_LOGS + "council_data");
        return 0;
    }
    if (type == VOTE_SPELLBAN)
    {
        if (!member_list[vote_target])
        {
            return 3;
        }
        if (punishments[vote_target] & SPELL_BANNED_BIT)
        {
            return 7;
        }
        
        pending_votes += ({({type, reason, vote_target, 
            time() + ONE_DAY, 0, 0})});
        save_object(COLLEGE_LOGS + "council_data");
        return 0;
    }
    if (type == VOTE_CONFINEMENT)
    {
        if (!member_list[vote_target])
        {
            return 3;
        }
        if (punishments[vote_target] & TOWER_CONFINED_BIT)
        {
            return 7;
        }
        
        pending_votes += ({({type, reason, vote_target, 
            time() + ONE_DAY, 0, 0})});
        save_object(COLLEGE_LOGS + "council_data");
        return 0;
    }
    if (type == VOTE_PROMOTE)
    {
        if (!member_list[vote_target])
        {
            return 3;
        }
        if (member_list[vote_target] & SCHOLAR_LVL_BIT)
        {
            return 8;
        }
        
        pending_votes += ({({type, reason, vote_target, 
            time() + ONE_DAY, 0, 0})});
        save_object(COLLEGE_LOGS + "council_data");
        return 0;
    } 
    if (type == VOTE_DEMOTE)
    {
        if (!member_list[vote_target])
        {
            return 3;
        }
        if (member_list[vote_target] & APPRENTICE_LVL_BIT)
        {
            return 9;
        }
        
        pending_votes += ({({type, reason, vote_target, 
            time() + ONE_DAY, 0, 0})});
        save_object(COLLEGE_LOGS + "council_data");
        return 0;
    }
    if (type == VOTE_LIFTPUN)
    {
        if (!member_list[vote_target])
        {
            return 3;
        }
        if (punishments[vote_target] == 0)
        {
            return 10;
        }
        
        pending_votes += ({({type, reason, vote_target, 
            time() + ONE_DAY, 0, 0})});
        save_object(COLLEGE_LOGS + "council_data");
        return 0;
    }                                       
    else
    {
        return 11;
    }
}


/*
   Determine if a vote can be safely resolved.
*/
int
check_resolvable(int index)
{
    int i = 0, j = 0;
    int num = pending_votes[index][5];
    
    if (strlen(council_members["fire"]))
    {
        i++;
        if (num & 1)
        {
            j++;
        }
    }
    if (strlen(council_members["air"]))
    {
        i++;
        if (num & 2)
        {
            j++;
        }
    }
    if (strlen(council_members["water"]))
    {
        i++;
        if (num & 4)
        {
            j++;
        }
    }
    if (strlen(council_members["earth"]))
    {
        i++;
        if (num & 8)
        {
            j++;
        }
    }
    
    if (i == 0 && pending_votes[index][4] == 0)
    {
        //This means there are no current council members and no votes. In such
        // a case, do not resolve the vote.
        return 0;
    }
           
    if (i - j == 0 || i - j < ABS(pending_votes[index][4]))
    {
        //This means not enough voters left to sway the vote.
        return 1;
    }
}
    

/*
    Checks what's going on with the votes. If any vote is past its deadline,
    resolve it. If all who can vote, have voted - resolve it. Also, if 
    further votes wouldn't change the outcome, resolve the vote.
*/
void
check_votes()
{
    int i = 0;

    if (!sizeof(pending_votes))
    {
        return;
    }
    
    while (i < sizeof(pending_votes))
    {
        if (time() - pending_votes[i][3] > 0)
        {
            resolve_vote(i);
        }
        else 
        if (check_resolvable(i))
        {
            resolve_vote(i);
        }
        else
        {
            i++;
        }
    }
}


/*
    Resolves a vote. The argument is the index in the pending_votes array
    which will be resolved.
*/
void
resolve_vote(int index)
{
    int i;
    mixed *this_vote = pending_votes[index];
    int result = this_vote[4];
    
    setuid();
    seteuid(getuid());

    if (!this_vote[0])
    {
        return;
    }
    
    if (this_vote[0] == VOTE_GENERIC)
    {
        if (result > 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to " + this_vote[1]+
                " was carried through by the Assembly on " + ctime(time())
                + ".\n");
        }
        else
        if (result == 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to " + this_vote[1]+ 
                " was split in the middle on " + ctime(time())
                + ".\n");            
        }
        else
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to " + this_vote[1]+ 
                " was denied by the Assembly on " + ctime(time())
                + ".\n");
        }
    }
    if (this_vote[0] == VOTE_EXPEL)
    {
        if (result > 0)
        {
            punishments[this_vote[2]] = punishments[this_vote[2]] | 
                EXPELLED_BIT;
            
            if (objectp(find_living(this_vote[2])))
            {
                find_living(this_vote[2])->check_council_status();
            }
            
                
            write_file(COLLEGE_LOGS + "voteresults", "Vote to expel " +
                capitalize(this_vote[2]) + " from the guild" +
                " was carried through by the Assembly on " + ctime(time())
                + ".\n");
        }
        else
        if (result == 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to expel " +
                capitalize(this_vote[2]) + " from the guild" +
                " was split in the middle on " + ctime(time())
                + ".\n");        
        }
        else
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to expel " +
                capitalize(this_vote[2]) + " from the guild" +
                " was denied by the Assembly on " + ctime(time())
                + ".\n");
        }
    }
    if (this_vote[0] == VOTE_ADDMEMBER)
    {
        if (result > 0)
        {
            approved_applicants[this_vote[2]] = time();
            write_file(COLLEGE_LOGS + "voteresults", "Vote to accept " +
                capitalize(this_vote[2]) + " as a new member" +
                " was carried through by the Assembly on " + ctime(time())
                + ".\n");
        }
        else
        if (result == 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to accept " +
                capitalize(this_vote[2]) + " as a new member" +
                " was split in the middle on " + ctime(time())
                + ".\n");
        }
        else
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to accept " +
                capitalize(this_vote[2]) + " as a new member" +
                " was denied by the Assembly on " + ctime(time())
                + ".\n");
        }
    }
    if (this_vote[0] == VOTE_ADDCOUNCIL)
    {
        if (result > 0)
        {
            if (member_list[this_vote[2]] & FIRE)
            {
                council_members["fire"] = this_vote[2];
            }
            else if (member_list[this_vote[2]] & AIR)
            {
                council_members["air"] = this_vote[2];
            }
            else if (member_list[this_vote[2]] & WATER)
            {
                council_members["water"] = this_vote[2];
            }
            else 
            {
                council_members["air"] = this_vote[2];
            }
            
            if (member_list[this_vote[2]] & MAGE_LVL_BIT)
            {
                //If he's not of scholar rank yet, promote him.
                member_list[this_vote[2]] = member_list[this_vote[2]] &
                    (~MAGE_LVL_BIT);
                member_list[this_vote[2]] = member_list[this_vote[2]] |
                    SCHOLAR_LVL_BIT;
            }
            
            if (objectp(find_living(this_vote[2])))
            {
                find_living(this_vote[2])->catch_tell("You were promoted" +
                    " to the office of Principal!\n");
            }
            
            write_file(COLLEGE_LOGS + "voteresults", "Vote to make " +
                capitalize(this_vote[2]) + " a Principal" +
                " was carried through by the Assembly on " + ctime(time())
                + ".\n");
        }
        else
        if (result == 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to make " +
                capitalize(this_vote[2]) + " a Principal" +
                " was split in the middle on " + ctime(time())
                + ".\n");      
        }
        else
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to make " +
                capitalize(this_vote[2]) + " a Principal" +
                " was denied by the Assembly on " + ctime(time())
                + ".\n");
        }
    }
    if (this_vote[0] == VOTE_REMCOUNCIL)
    {
        if (result > 0)
        {
            if (member_list[this_vote[2]] & FIRE)
            {
                council_members = m_delete(council_members, "fire");
            }
            else if (member_list[this_vote[2]] & AIR)
            {
                council_members = m_delete(council_members, "air");
            }
            else if (member_list[this_vote[2]] & WATER)
            {
                council_members = m_delete(council_members, "water");
            }
            else 
            {
                council_members = m_delete(council_members, "earth");
            }
                   
            if (objectp(find_living(this_vote[2])))
            {
                find_living(this_vote[2])->catch_tell("You were demoted" +
                    " from the office of Principal!\n");
            }                   
                    
            write_file(COLLEGE_LOGS + "voteresults", "Vote to depose " +
                capitalize(this_vote[2]) + " as Principal" +
                " was carried through by the Assembly on " + ctime(time())
                + ".\n");
        }
        else
        if (result == 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to depose " +
                capitalize(this_vote[2]) + " as Principal" +
                " was split in the middle on " + ctime(time())
                + ".\n");        
        }
        else
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to depose " +
                capitalize(this_vote[2]) + " as Principal" +
                " was denied by the Assembly on " + ctime(time())
                + ".\n");
        }
    }
    if (this_vote[0] == VOTE_SPELLBAN)
    {
        if (result > 0)
        {
            punishments[this_vote[2]] = punishments[this_vote[2]] | 
                SPELL_BANNED_BIT;
 
            if (objectp(find_living(this_vote[2])))
            {
                find_living(this_vote[2])->check_council_status();
            }
            
            write_file(COLLEGE_LOGS + "voteresults", "Vote to ban " +
                capitalize(this_vote[2]) + " from using spells" +
                " was carried through by the Assembly on " + ctime(time())
                + ".\n");
        }
        else
        if (result == 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to ban " +
                capitalize(this_vote[2]) + " from using spells" +
                " was split in the middle on " + ctime(time())
                + ".\n");     
        }
        else
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to ban " +
                capitalize(this_vote[2]) + " from using spells" +
                " was denied by the Assembly on " + ctime(time())
                + ".\n");
        }
    }
    if (this_vote[0] == VOTE_CONFINEMENT)
    {
        if (result > 0)
        {
            punishments[this_vote[2]] = punishments[this_vote[2]] | 
                TOWER_CONFINED_BIT;              
            
            if (objectp(find_living(this_vote[2])))
            {
                find_living(this_vote[2])->check_council_status();
            }
                             
            write_file(COLLEGE_LOGS + "voteresults", "Vote to confine " +
                capitalize(this_vote[2]) + " to the Marble Tower" +
                " was carried through by the Assembly on " + ctime(time())
                + ".\n");
        }
        else
        if (result == 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to confine " +
                capitalize(this_vote[2]) + " to the Marble Tower" +
                " was split in the middle on " + ctime(time())
                + ".\n");          
        }
        else
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to confine " +
                capitalize(this_vote[2]) + " to the Marble Tower" +
                " was denied by the Assembly on " + ctime(time())
                + ".\n");
        }
    }
    if (this_vote[0] == VOTE_PROMOTE)
    {
        if (result > 0)
        {
            i = member_list[this_vote[2]];
            if (i & APPRENTICE_LVL_BIT)
            {
                i = i & (~APPRENTICE_LVL_BIT);
                i = i | MAGE_LVL_BIT;
                member_list[this_vote[2]] = i;
            }
            else 
            if (i & MAGE_LVL_BIT)
            {
                i = i & (~MAGE_LVL_BIT);
                i = i | SCHOLAR_LVL_BIT;
                member_list[this_vote[2]] = i;
            }
            
            if (objectp(find_living(this_vote[2])))
            {
                find_living(this_vote[2])->check_council_status();
            }
            
            write_file(COLLEGE_LOGS + "voteresults", "Vote to promote " +
                capitalize(this_vote[2]) + " in rank" +
                " was carried through by the Assembly on " + ctime(time())
                + ".\n");
        }
        else
        if (result == 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to promote " +
                capitalize(this_vote[2]) + " in rank" +
                " was split in the middle on " + ctime(time())
                + ".\n");          
        }
        else
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to promote " +
                capitalize(this_vote[2]) + " in rank" +
                " was denied by the Assembly on " + ctime(time())
                + ".\n");
        }
    }
    if (this_vote[0] == VOTE_DEMOTE)
    {
        if (result > 0)
        {
            i = member_list[this_vote[2]];
            if (i & MAGE_LVL_BIT)
            {
                i = i & (~MAGE_LVL_BIT);
                i = i | APPRENTICE_LVL_BIT;
                member_list[this_vote[2]] = i;
            }
            else 
            if (i & SCHOLAR_LVL_BIT)
            {
                i = i & (~SCHOLAR_LVL_BIT);
                i = i | MAGE_LVL_BIT;
                member_list[this_vote[2]] = i;
            }
            
            if (objectp(find_living(this_vote[2])))
            {
                find_living(this_vote[2])->check_council_status();
            }
                        
            write_file(COLLEGE_LOGS + "voteresults", "Vote to demote " +
                capitalize(this_vote[2]) + " in rank" +
                " was carried through by the Assembly on " + ctime(time())
                + ".\n");
        }
        else
        if (result == 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to demote " +
                capitalize(this_vote[2]) + " in rank" +
                " was split in the middle on " + ctime(time())
                + ".\n");         
        }
        else
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to demote " +
                capitalize(this_vote[2]) + " in rank" +
                " was denied by the Assembly on " + ctime(time())
                + ".\n");
        }
    }
    if (this_vote[0] == VOTE_LIFTPUN)
    {
        if (result > 0)
        {
            punishments = m_delete(punishments, this_vote[2]);
            
            if (objectp(find_living(this_vote[2])))
            {
                find_living(this_vote[2])->check_council_status();
            }
                        
            write_file(COLLEGE_LOGS + "voteresults", "Vote to lift " +
                "punishments from " +  capitalize(this_vote[2]) + 
                " was carried through by the Assembly on " + ctime(time())
                + ".\n");
        }
        else
        if (result == 0)
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to lift " +
                "punishments from " +  capitalize(this_vote[2]) + 
                " was split in the middle on " + ctime(time())
                + ".\n");         
        }
        else
        {
            write_file(COLLEGE_LOGS + "voteresults", "Vote to lift " +
                "punishments from " +  capitalize(this_vote[2]) + 
                " was denied by the Assembly on " + ctime(time())
                + ".\n");
        }
    }

    pending_votes -= ({this_vote});
    save_object(COLLEGE_LOGS + "council_data");    
}


/*
    Perform the actual vote.
    
    Args: objectpointer to voter, int index in pending_votes we are voting on,
    string vote aye/nay.
    
    returns: 0 - success!
             1-X - failure for various reasons.
*/
int
perform_vote(object voter, int index, string vote)
{
    int branch = query_council(voter->query_name());
    mixed *this_vote;
    
    if (index >= sizeof(pending_votes))
    {
        return 1;
    }
    
    this_vote = pending_votes[index];    
    
    if(!branch && voter->query_name() != "Bishop")
    {
        return 2;
    }
    
    if (branch & this_vote[5])
    {
        return 3;
    }
    
    if (vote == "aye" || vote == "Aye")
    {
        pending_votes[index][4]++;
        pending_votes[index][5] = pending_votes[index][5] | branch;
        save_object(COLLEGE_LOGS + "council_data");
        check_votes();
        return 0;
    }
    else
    if (vote == "nay" || vote == "Nay")
    {
        pending_votes[index][4]--;
        pending_votes[index][5] = pending_votes[index][5] | branch;
        save_object(COLLEGE_LOGS + "council_data");      
        check_votes();
        return 0;
    }
    else
    {
        return 4;
    }
}

/*
    Check if str is a member of council. Return 1 if fire council, 2 if
    water council, 4 if air council and 8 if earth council. 0 if not a 
    councilmember.
 */
int
query_council(string str)
{

    if (council_members["fire"] == lower_case(str))
    {
        return 1;
    }
    if (council_members["water"] == lower_case(str))
    {
        return 2;
    }
    if (council_members["air"] == lower_case(str))
    {
        return 4;
    }
    if (council_members["earth"] == lower_case(str))
    {
        return 8;
    }
    
    return 0;            
}


/*
    This lists the current issues that are up for voting.

    Returns the list.
*/
string
list_agenda()
{
    int i;
    string str;
    string list = "";
 
    if (!sizeof(pending_votes))
    {
        list += "No votes are currently running.\n";
    }
    else
    {
        for (i = 0; i < sizeof(pending_votes); i++)
        {
            str = "";
            
            switch (pending_votes[i][0])
            {
                case VOTE_GENERIC:
                    str += "Vote to " + pending_votes[i][1] + ".";
                    break;
                case VOTE_EXPEL:
                    str += "Vote to expel " + capitalize(pending_votes[i][2])
                        + " from the guild.";
                    break;
                case VOTE_ADDMEMBER:
                    str += "Vote to approve " +capitalize(pending_votes[i][2])
                        + " for membership.";
                    break;
                case VOTE_ADDCOUNCIL:
                    str += "Vote to add " + capitalize(pending_votes[i][2])
                        + " to the Assembly.";
                    break;
                case VOTE_REMCOUNCIL:
                    str += "Vote to remove " + capitalize(pending_votes[i][2])
                        + " from the Assembly.";
                    break;
                case VOTE_SPELLBAN:
                    str += "Vote to ban " + capitalize(pending_votes[i][2])
                        + " from using spells.";
                    break;
                case VOTE_CONFINEMENT:
                    str += "Vote to confine " +capitalize(pending_votes[i][2])
                        + " to the Marble Tower.";
                    break;
                case VOTE_PROMOTE:
                    str += "Vote to promote " + 
                        capitalize(pending_votes[i][2]) + " in guild rank.";
                    break;
                case VOTE_DEMOTE:
                    str += "Vote to demote " + 
                        capitalize(pending_votes[i][2]) + " in guild rank.";
                    break;
                default:
                    str += "Vote to remove all punishments from " + 
                        capitalize(pending_votes[i][2]) + ".";
            }
            
            str += " Ends on " + ctime(pending_votes[i][3]) + ".";
            list += "-Matter " + (i+1) + ":\n" + break_string(str, 50, 5) + 
                ".\n";
        }
    }

    return list;
} 


/*
   This function determines whether someone with the name of str 
   has been approved by the Assembly for joining the guild.
   Returns 1 if that is the case, 0 otherwise..
 */
int 
check_approved_applicant(string str)
{
    if (approved_applicants[lower_case(str)])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/*
   Adds a new member to the guild. Argument str is the name of the person
   we are adding, bits contains information about his/her rank and element.

 */
void 
add_member(string str, int bits)
{
    setuid();
    seteuid(getuid());
    
    member_list[lower_case(str)] = bits;
    save_object(COLLEGE_LOGS + "council_data");          
}


/*
    Removes a member from the guild, argument str is name of the person.
 */
void 
remove_member(string str)
{
    setuid();
    seteuid(getuid());
    
    member_list = m_delete(member_list, lower_case(str));
    save_object(COLLEGE_LOGS + "council_data");          
}


/*
    This removes any approved applicants that have joined the guild, and
    revokes any approval made more than three weeks ago.
*/
void
cleanup_approved_applicants()
{
    int i = 0;
    string *apps_to_delete = ({ });
    string *applicants = m_indices(approved_applicants);
    
    while (i < sizeof(applicants))
    {
        if (member_list[applicants[i]])
        {
            apps_to_delete += ({applicants[i]});
        }
        else
        if (time() - approved_applicants[applicants[i]] > 3*ONE_WEEK)
        {
            apps_to_delete += ({applicants[i]});
        }

        i++;
    }
    
    while (sizeof(apps_to_delete))
    {
        approved_applicants = m_delete(approved_applicants, apps_to_delete[0]);
        apps_to_delete -= ({apps_to_delete[0]});
    }
    
    save_object(COLLEGE_LOGS + "council_data");  
}

/*
   This returns the punishments the member of name str is currently under.
*/
int 
query_punishments(string str)
{
    return punishments[lower_case(str)];
}

/*
   This returns the guild rank of the member with name str.
*/
int 
query_rank(string str)
{
    return (member_list[lower_case(str)]);
}
            
void
init_council()
{
    setuid();
    seteuid(getuid());
    restore_object(COLLEGE_LOGS + "council_data");
    
    set_alarm(0.1, 900.0, &check_votes());
    set_alarm(0.1, 0.0, &cleanup_approved_applicants());
}           
                
           