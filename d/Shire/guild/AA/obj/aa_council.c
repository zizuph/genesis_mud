#pragma no_clone
#pragma no_inherit
#pragma strict_types
#pragma save_binary

#include <std.h>
#include <macros.h>
#include <composite.h>
#include "/d/Shire/guild/AA/guild.h"

#define SAVE_FILE    (AA_DIR+"save_files/AA_COUNCIL")

#define AA_ACTIVITY_MAPPINGS  (AA_DIR+"obj/captain_activity_mappings")

#define MAX_LEADER_IDLE     1814400     
// 21 days * 60sec * 60min * 24 hours = 1814400 secs (21 days)

// TEST PARAMETER
//#define MAX_LEADER_IDLE     300

/*
 * Nonprivate functions:
 */
int is_ro(string name);

int is_captain(string name);

// NEW
int is_lieutenant(string name);

int is_council(string name);

private void check_leaders();

// NEW Nov 2019 - ACTIVITY LOGIC
void activity_meter();


/**********************************************************************
 * Global variables, they will be saved.
 */

private string *captain_list = ({ });
/*
 *   captain_list = ({ "name1", "name2", ... });
 */

// NEW
private string *lieutenant_list = ({});
/*
*   lieutenant_list = ({ "name1", "name2", ... });
*/

private string *ro_list = ({ });
/*
 *   ro_list = ({ "name1", "name2", ... });
 */

private mapping c_list = ([ ]);
/*
 *   c_list = ([ "name1":p1, "name2":p2, ... , "name5":p5 ]);
 */
private mapping c_dates = ([ ]);
/*
 *   c_dates = ([ num : ({ date, who }), ... ]);
 */
private mapping c_vote  = ([ ]);
/*
 *    c_vote = ([
 *      num : ({({"name1","vote",weight}), ({"name2","vote",weight}),...}),
 *      ...    ]);
 */
private mapping c_apply = ([ ]);
/*
 * c_apply = ([ num : ({"name1", "name2", ...}), ...]);
 */
 
 
/*
 * prototype
 */
private void check_council();
private void check_captain();

// NEW Nov 2019 - ACTIVITY LOGIC
int captain_activity;


// NEW Nov 2019 - ACTIVITY LOGIC
int
query_activity_meter_captain()
{
    return captain_activity;
}


/*
 * Function name: create
 * Description  : Function called when object is loaded
 */
void
create()
{
    int i;

    FIXEUID;
    if (!restore_object(SAVE_FILE))
    {
        captain_list = ({});

        // NEW
        lieutenant_list = ({});

        ro_list = ({});


        c_list = ([ ]);
        c_dates = ([ ]);
        c_vote  = ([ ]);
        c_apply = ([ ]);      
    }

    set_alarm(0.0, 0.0, check_council);

    //Council removal code - test
    set_alarm(0.0, 0.0, check_leaders);

    //set_alarm(0.0, 0.0, check_captain);
    
    // NEW Nov 2019 - ACTIVITY LOGIC
    // Drops 1 point every 150 minute - Nerull 2021
    set_alarm(0.0, 9000.0, &activity_meter());
}

/*
 * Function name: query_council
 * Returns:       List of names of councilmembers - capitalized
 */
string *
query_council()
{
    return m_indexes(c_list);
}


/*
* Function name: query_ro
* Returns:       List of names of councilmembers - capitalized
*/
/*string *
query_ro()
{
    return m_indexes(ro_list);
}*/

/*
 * Function name: query_applied
 * Returns:       List of names of applicants for council
 */
string *
query_applied()
{
    string *list = ({ });
    int i, *arr = m_indexes(c_apply);
    for (i=0 ; i<sizeof(arr) ; i++)
        list += c_apply[arr[i]];
    return list;
}


/*
 * Function name: is_captain
 * Arguments:     name - player name
 * Returns:       1 - 'name' is Captain
 *                0 - 'name' is not
 */
int
is_captain(string name)
{
    if (member_array(CAP(name), captain_list) != -1)
        return 1;
    return 0;
}


/*  NEW
* Function name: is_lieutenant
* Arguments:     name - player name
* Returns:       1 - 'name' is lieutenant
*                0 - 'name' is not
*/
int
is_lieutenant(string name)
{
    if (member_array(CAP(name), lieutenant_list) != -1)
        return 1;
    return 0;
}


/*
* Function name: is_ro
* Arguments:     name - player name
* Returns:       1 - 'name' is Captain
*                0 - 'name' is not
*/
int
is_ro(string name)
{
    if (member_array(CAP(name), ro_list) != -1)
        return 1;
    return 0;
}



// NEW
string 
query_captain()
{
    string s = "";
    mixed arr;
    int i;

    arr = captain_list;
    
    if (!sizeof(arr))
    {
        return s + "";
    }

    return s + break_string(COMPOSITE_WORDS(arr), 60, 0) + "";
}


// NEW
string
query_lieutenant()
{
    string s = "";

    mixed arr;
    int i;

    arr = lieutenant_list;

    if (!sizeof(arr))
    {
        return s + "";
    }

    return s + break_string(COMPOSITE_WORDS(arr), 60, 0) + "";
}


// NEW
int
no_captain()
{
    mixed arr;
    int i;

    arr = captain_list;

    if (!sizeof(arr))
    {
        return 1;
    }

    return 0;
}


// NEW
int
no_lieutenants()
{
    mixed arr;
    int i;

    arr = lieutenant_list;

    if (!sizeof(arr))
    {
        return 1;
    }

    return 0;
}


string
query_ro()
{
    string s = "";
    mixed arr;
    int i;

    arr = ro_list;

    if (!sizeof(arr))
    {
        return s + "";
    }

    return s + break_string(COMPOSITE_WORDS(arr), 60, 0) + "";
}


/*
 * Function name: is_ro
 * Arguments:     name - player name
 * Returns:       1 - 'name' is Recruitment Officer
 *                0 - 'name' is not
 */
/*int
is_ro(string name)
{
    if (member_array(CAP(name), ro_list) != -1)
        return 1;
    return 0;
}*/

/*
 * Function name: is_council
 * Arguments:     name - player name
 * Returns:       1 - 'name' is Council member
 *                0 - 'name' is not
 */
int
is_council(string name)
{
    if (member_array(CAP(name), query_council()) != -1)
        return 1;
    return 0;
}

/*
 * Function name: my_sort_function
 * Description:   Used for sorting of election results
 */
private int
my_sort_function(mixed a, mixed b)
{
    if (a[1] > b[1]) return -1;
    if (a[1] < b[1]) return 1;
    if (a[2] > b[2]) return -1;
    if (a[2] < b[2]) return 1;
    if (a[0] > b[0]) return -1;
    if (a[0] < b[0]) return 1;
    return 0;
}

/*
 * Function name: report_council
 * Description:   This function creates the report with council election
 *                results. (Now it is a file - in future will be a note
 *                on board.)
 * Arguments:     p - number of council position
 *                name - name of the winner of election
 *                report - list with names, votes, weights
 */
private void
report_council(int p, string name, mixed report)
{
    mixed rrr = sort_array(report, "my_sort_function");
    string s;
    int i;

    s = "It is my pleasure to announce that new councilmember no. "+p+" is:";
    s += "\n\n            "+name+"\n\n";
    s += "              Emissary of the Dark Lord\n\n\n";
    s += "P.S. Here are the results of voting:\n\n";
    s += " Candidate:                  Weight:  Votes:\n";
    s += "---------------------------------------------\n";
    for (i=0; i<sizeof(rrr); i++)
        s += sprintf(" %-30'.'s %3d %7d\n", rrr[i][0]+" ",
                                            rrr[i][1],
                                            rrr[i][2]);

    FIXEUID;
    (AA_VOTE_ROOM->get_board())->create_note("ELECTION RESULT", "Emissary", s);
}

/*
 * Function name: set_council
 * Description:   This function counts votes and select the winner of
 *                council elections for given position.
 * Arguments:     p - number of council position
 */
private void
set_council(int p)
{
    mixed arr, report = ({ });
    mixed best = ({ ({ "_dummy_", 0, 0 }) });
    int i,v,w;
    string name;

    if (member_array(p, m_indexes(c_vote)) == -1) return;

    for (1; sizeof(c_vote[p]); 1)
    {
        name = c_vote[p][0][1];
        arr = ({ });
        w = 0;
        v = 0;
        for (i=0; i<sizeof(c_vote[p]); i++)
            if (c_vote[p][i][1] == name)
            {
                arr += ({ c_vote[p][i] });
                w += c_vote[p][i][2];
                v++;
            }
        c_vote[p] -= arr;
        if (AA_RANKS_OBJ->aa_member(name))
        {
            report += ({ ({ name, w, v }) });
            if (w > best[0][1])
            {
                best = ({ ({ name, w, v }) });
            }
            else if (w == best[0][1])
            {
                if (v > best[0][2])
                {
                    best = ({ ({ name, w, v }) });
                }
                else if (v == best[0][2])
                    best += ({ ({ name, w, v }) });
            }
        }
    }
    arr = m_indexes(c_list);
    for (i=0; i<sizeof(arr); i++)
        if (c_list[arr[i]] == p)
            c_list = m_delete(c_list, arr[i]);
    c_vote = m_delete(c_vote, p);
    c_apply = m_delete(c_apply, p);
    i = random(sizeof(best)); /* if more, we choose winner randomly */
    if (best[i][0] != "_dummy_")
    {
        c_list += ([ best[i][0] : p ]);
        report_council(p, best[i][0], report); /* create report */
    }
}



/*
* Function name: check_leaders
* Description:   This function throws out of Idle captains and idle LT's.
*/
private void
check_leaders()
{
    mixed arr;
    mixed arr2;

    int i, x;

    /* throw non members out of the captain position */
    arr = captain_list;
    arr2 = lieutenant_list;


    for (i = 0; i < sizeof(arr); i++)
    {

        //Check if Captain is idle, remove if so
        int t = time() - MAX_LEADER_IDLE;

        int p = time();

        // If the player is in play, ignore boot.
        if (find_player(lower_case(arr[i])))
            return;


        int j = file_time(PLAYER_FILE(lower_case(arr[i])) + ".o");

        // DEBUG
        find_player("nerull")->catch_tell("Time playerfile: " + j
            + ".\nT               : "+p+".\n"
            +"TimeTime - idletime: " + t + ".\n");


        if (j < t)
        {
            // DEBUG
            find_player("nerull")->catch_tell("Captain "+arr[i]+" demoted "
            +"to regular soldier due to lack of activity.\n");

            captain_list -= ({ arr[i] });
        }
    }


    for (x = 0; x < sizeof(arr2); x++)
    {

        ///Check if Lieutenant is idle, remove if so
        int t2 = time() - MAX_LEADER_IDLE;

        int p2 = time();

        // If the player is in play, ignore boot.
        if (find_player(lower_case(arr2[x])))
            return;


        int j2 = file_time(PLAYER_FILE(lower_case(arr2[x])) + ".o");

        // DEBUG
        find_player("nerull")->catch_tell("Time playerfile: " + j2
            + ".\nT               : "+p2+".\n"
            +"TimeTime - idletime: " + t2 + ".\n");


        if (j2 < t2)
        {
            // DEBUG
            find_player("nerull")->catch_tell("Lieutenant "+arr[x]+" demoted "
            +"to regular soldier due to lack of activity.\n");

            lieutenant_list -= ({ arr2[x] });
        }
    }


    FIXEUID;
    save_object(SAVE_FILE);

    set_alarm(3600.0, 0.0, check_leaders);
}


/*
 * Function name: check_captain
 * Description:   This function throws out of captain non AA members
 *                (after they quit guild).
 */
private void
check_captain()
{
    mixed arr;
    int i;

    /* throw non members out of the captain position */
    arr = captain_list;

    for (i=0; i<sizeof(arr); i++)
        if ((!AA_RANKS_OBJ->aa_member(arr[i])) || AA_RANKS_OBJ->is_captain(arr[i]))
            captain_list -= ({ arr[i] });

    FIXEUID;
    save_object(SAVE_FILE);
    set_alarm(3600.0, 0.0, check_captain);
}


// NEW
/*
* Function name: check_lieutenant
* Description:   This function throws out of lieutenant non AA members
*                (after they quit guild).
*/
private void
check_lieutenant()
{
    mixed arr;
    int i;

    /* throw non members out of the captain position */
    arr = lieutenant_list;

    for (i = 0; i<sizeof(arr); i++)
        if ((!AA_RANKS_OBJ->aa_member(arr[i])) || AA_RANKS_OBJ->is_lieutenant(arr[i]))
            lieutenant_list -= ({ arr[i] });

    FIXEUID;
    save_object(SAVE_FILE);
    set_alarm(3600.0, 0.0, check_lieutenant);
}


/*
* Function name: check_ro
* Description:   This function throws out RO for non AA members
*                (after they quit guild).
*/
private void
check_ro()
{
    mixed arr;
    int i;

    /* throw non members out of the captain position */
    arr = ro_list;

    for (i = 0; i<sizeof(arr); i++)
        if ((!AA_RANKS_OBJ->aa_member(arr[i])) || AA_RANKS_OBJ->is_ro(arr[i]))
            ro_list -= ({ arr[i] });

    FIXEUID;
    save_object(SAVE_FILE);
    set_alarm(3600.0, 0.0, check_ro);
}


/*
 * Function name: check_council
 * Description:   This function throws out of council non AA members
 *                (after they quit guild), starts election for empty positions
 *                and puts in new councilmembers after election.
 */
private void
check_council()
{
    mixed arr, tmp;
    int i, j;

    /* throw non members out of RO */
    arr = ro_list;

    for (i=0; i<sizeof(arr); i++)
        if ((!AA_RANKS_OBJ->aa_member(arr[i])) || AA_RANKS_OBJ->lieut_cap(arr[i]) || is_council(arr[i]))
            ro_list -= ({ arr[i] });

    /* throw non members out of voting records */
    arr = m_indexes(c_vote);
    for (i=0; i<sizeof(arr); i++)
    {
        tmp = ({ });
        for (j=0; j<sizeof(c_vote[arr[i]]); j++)
            if (!AA_RANKS_OBJ->aa_member(c_vote[arr[i]][j][0]) ||
                !AA_RANKS_OBJ->aa_member(c_vote[arr[i]][j][1]))
                tmp += ({ c_vote[arr[i]][j] });
        c_vote[arr[i]] -= tmp;
    }

    /* throw non members out of application records */
    arr = m_indexes(c_apply);
    for (i=0; i<sizeof(arr); i++)
    {
        tmp = ({ });
        for (j=0; j<sizeof(c_apply[arr[i]]); j++)
            if (!AA_RANKS_OBJ->aa_member(c_apply[arr[i]][j]))
                tmp += ({ c_apply[arr[i]][j] });
        c_apply[arr[i]] -= tmp;
    }

    /* throw non members out of council */
    arr = m_indexes(c_list);
    for (i=0; i<sizeof(arr); i++)
      if (!AA_RANKS_OBJ->aa_member(arr[i]))
          c_list = m_delete(c_list, arr[i]);

    /* put in new councilmembers */
    arr = m_indexes(c_dates);
    for (i=0; i<sizeof(arr); i++)
    {
        if (c_dates[arr[i]][0]+WEEK+WEEK < time())
            set_council(arr[i]); /* elections are over, set council up */
        if (c_dates[arr[i]][0]+WEEK+WEEK+MONTH < time())
            c_dates = m_delete(c_dates, arr[i]); /* allow start elections */
    }
    /* start election for empty positions */
    arr = m_values(c_list);
    for (i=1; i<6; i++)
        if ((member_array(i, arr) == -1) &&
            ((member_array(i, m_indexes(c_dates)) == -1) ||
             ((c_dates[i][0]+WEEK < time()) && (!sizeof(c_apply[i])))
           ))
        {
            c_dates = m_delete(c_dates, i);
            c_vote = m_delete(c_vote, i);
            c_apply = m_delete(c_apply, i);
            c_vote += ([ i : ({ }) ]);
            c_apply += ([ i : ({ }) ]);
            c_dates += ([ i : ({ time(), "Emissary" }) ]);
        }

    FIXEUID;
    save_object(SAVE_FILE);
    set_alarm(3600.0, 0.0, check_council);
}


void
demote_leader(string name)
{
    name = CAP(name);
    
    captain_list -= ({ name });
    
    find_player("nerull")->catch_tell("Captain demoted "
    +"to regular soldier due to lack of activity.\n");
    
    // NEW Nov 2019 - ACTIVITY LOGIC
    AA_ACTIVITY_MAPPINGS->clean_captain_activity_gauge(name);
    
    FIXEUID;
    save_object(SAVE_FILE);
    

    lieutenant_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);

    if (member_array(name, ro_list) == -1)
    {
        return;
    }

    ro_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);

    return;
}


void
promote_captain(string name)
{

    name = CAP(name);

    if (!AA_RANKS_OBJ->aa_member(name))
    {
        write(name+" is not member of the army.\n");
        return;
    }

    /*if (member_array(name, captain_list) != -1)
    {
        write(name+" is already the Captain.\n");
        return;
    }*/

    
    captain_list += ({ name });
    sort_array(captain_list);
    FIXEUID;
    save_object(SAVE_FILE);
    write(name+" is now the new Captain of the Army of Angmar!\n");
    
    // NEW Nov 2019 - ACTIVITY LOGIC
    // The number of hours inactie before the capt is booted
    AA_ACTIVITY_MAPPINGS->set_captain_activity_gauge(name, 120);

    lieutenant_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);

    // We'll make sure the Captain is not part of the RO's.
    /*if (member_array(name, ro_list) == -1)
    {
        return;
    }*/

    ro_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    //write(name + " leaves the Recruitment Officers.\n");
    return;
}


void
demote_captain(string name)
{
    name = CAP(name);

    /*if (member_array(name, captain_list) == -1 || !this_player()->query_wiz_level())
    {
        write(name+" is not a Captain of the Army of Angmar.\n");
        return;
    }*/
    
    find_player("nerull")->catch_tell("Captain demoted "
    +"to regular soldier due to lack of activity.\n");

    captain_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    //write("You demoted "+name+" from the position of Captain in the Army of Angmar.\n");
    
    // NEW Nov 2019 - ACTIVITY LOGIC
    AA_ACTIVITY_MAPPINGS->clean_captain_activity_gauge(name);
    
    // NEW Nov 2019 - ACTIVITY LOGIC
    AA_ACTIVITY_MAPPINGS->set_captain_rejoin_cooldown(name, 1);

   /* lieutenant_list += ({ name });
    FIXEUID;
    save_object(SAVE_FILE);*/

    // We'll make sure the demoted Captain is not part of the RO's.
    /*if (member_array(name, ro_list) == -1)
    {
        return;
    }*/

    /*ro_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    //write(name + " leaves the Recruitment Officers.\n");*/

    return;
}


void
demote_captain_self(string name)
{
    name = CAP(name);

    captain_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    //write("You retire from the position of Captain in the Army of Angmar.\n");
    
    // NEW Nov 2019 - ACTIVITY LOGIC
    AA_ACTIVITY_MAPPINGS->clean_captain_activity_gauge(name);

    lieutenant_list += ({ name });
    FIXEUID;
    save_object(SAVE_FILE);

    // We'll make sure the demoted Captain is not part of the RO's.
    if (member_array(name, ro_list) == -1)
    {
        return;
    }

    ro_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    //write(name + " leaves the Recruitment Officers.\n");

    return;
}


void
demote_lieutenant_self(string name)
{
    name = CAP(name);

    lieutenant_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    
    if (member_array(name, ro_list) == -1)
    {
        return;
    }

    ro_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);

    return;
}


// NEW
void
promote_lieutenant(string name)
{

    name = CAP(name);

    if (!AA_RANKS_OBJ->aa_member(name))
    {
        write(name + " is not member of the army.\n");
        return;
    }

    /*if (member_array(name, lieutenant_list) != -1)
    {
        write(name + " is already a Lieutenant.\n");
        return;
    }*/

    lieutenant_list += ({ name });
    sort_array(lieutenant_list);
    FIXEUID;
    save_object(SAVE_FILE);
    write(name + " is now a Lieutenant of the Army of Angmar!\n");

    // We'll make sure the Lieutenant is not part of the RO's.
    /*if (member_array(name, ro_list) == -1)
    {
        return;
    }*/

    ro_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    //write(name + " leaves the Recruitment Officers.\n");
    return;
}


// NEW
void
demote_lieutenant(string name)
{
    name = CAP(name);

    /*if (member_array(name, lieutenant_list) == -1 || !this_player()->query_wiz_level())
    {
        write(name + " is not a Lieutenant of the Army of Angmar.\n");
        return;
    }*/

    lieutenant_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    write("You demoted " + name + " from the position of Lieutenant in the Army of Angmar.\n");

    // We'll make sure the demoted Lieutenant is not part of the RO's.
    /*if (member_array(name, ro_list) == -1)
    {
        return;
    }*/

    ro_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    //write(name + " leaves the Recruitment Officers.\n");

    return;
}


// NEW
void
promote_ro(string name)
{
    name = CAP(name);

    if (!AA_RANKS_OBJ->aa_member(name))
    {
        write(name + " is not member of the army.\n");
        return;
    }

    if (member_array(name, ro_list) != -1)
    {
        write(name + " is already a Recruitment Officer.\n");
        return;
    }

    ro_list += ({ name });
    sort_array(ro_list);
    FIXEUID;
    save_object(SAVE_FILE);
    write(name + " is now a Recruitment Officer of the Army of Angmar!\n");

    return;
}


// NEW
void
demote_ro(string name)
{
    name = CAP(name);

    /*if (member_array(name, ro_list) == -1)
    {
        write(name + " is not a Recruitment Officer of the Army of Angmar.\n");
        return;
    }*/

    ro_list -= ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    write("You demoted " + name + " from the position of Recruitment Officer of the Army of Angmar.\n");

    return;
}


void
apply_council(int p)
{
    string name = TP->query_name();
    int i, *ind;

    if (!AA_RANKS_OBJ->aa_member(name))
    {
        write("Only real soldiers can apply here.\n");
        return;
    }
    if (member_array(p, m_indexes(c_apply)) == -1)
    {
        write("No applications are taken for position no. "+p+" now.\n");
        return;
    }
    if (c_dates[p][0]+WEEK < time())
    {
        write("Sorry, application period is over.\n");
        return;
    }
    if ((member_array(name, m_indexes(c_list)) != -1) && (c_list[name] != p))
    {
        write("You can apply only for your own position.\n");
        return;
    }
    ind = m_indexes(c_apply);
    for (i=0; i<sizeof(ind); i++)
        if (member_array(name, c_apply[ind[i]]) != -1)
        {
            write("You have already applied for position no. "+ind[i]+".\n");
            return;
        }
    c_apply[p] += ({ name });
    FIXEUID;
    save_object(SAVE_FILE);
    write("You applied for council position no. "+p+".\n");
    return;
}


string
check_votes(string name)
{
    string vvv = "";
    mixed arr = m_indexes(c_vote);
    int i,j;

    for (i=0; i<sizeof(arr); i++)
        for (j=0; j<sizeof(c_vote[arr[i]]); j++)
            if (name == c_vote[arr[i]][j][0])
                vvv += c_vote[arr[i]][j][1]+" for council no. "+arr[i]+".\n";
    return vvv;
}


private void
priv_start_election(int p, string name)
{
    c_vote += ([ p : ({ }) ]);
    c_apply += ([ p : ({ }) ]);
    c_dates += ([ p : ({ time(), name }) ]);
    FIXEUID;
    save_object(SAVE_FILE);
}


void
start_election(int p)
{
    string name = TP->query_name();

    if(AA_RANKS_OBJ->lieut_cap(name))
    {
        if((member_array(p, m_indexes(c_dates)) != -1) &&
           (c_dates[p][0]+WEEK+WEEK+MONTH > time()))
        {
            write("Election for this position can be started after "+
                  ctime(c_dates[p][0]+WEEK+WEEK+MONTH)+".\n");
            return;
        }
        priv_start_election(p, name);
        write("You started election for council position no. "+p+".\n");
        return;
    }
    else if(is_council(name) && (c_list[name] == p))
    {
        if(member_array(p, m_indexes(c_vote)) != -1)
        {
            write("Election for this position are in proces.\n");
            return;
        }
        priv_start_election(p, name);
        write("You started election for council position no. "+p+".\n");
        return;
    }
    write("You can't start election for council position no. "+p+".\n");
}


void
vote_council(string name, int p)
{
    int i;

    if (!AA_RANKS_OBJ->aa_member(TP->query_name()))
    {
        write("Only members can vote here.\n");
        return;
    }
    if (member_array(p, m_indexes(c_vote)) == -1)
    {
        write("There is no voting for council position no. "+p+" now.\n");
        return;
    }
    if (c_dates[p][0]+WEEK > time())
    {
        write("We are still taking applications for this position.\n"+
              "You can vote after "+ctime(c_dates[p][0]+WEEK)+".\n");
        return;
    }
    if (c_dates[p][0]+WEEK+WEEK < time())
    {
        write("Sorry, the voting period is over.\n");
        return;
    }
    if (member_array(name, c_apply[p]) == -1)
    {
        write(name+" has not applied for council position no. "+p+".\n");
        return;
    }
    for (i=0; i<sizeof(c_vote[p]); i++)
        if (c_vote[p][i][0] == TP->query_name())
            c_vote[p] -= ({ c_vote[p][i] });
    c_vote[p] += ({ ({ TP->query_name(), name, AA_RANKS_OBJ->rank_no(TP)+2 }) });
    FIXEUID;
    save_object(SAVE_FILE);
    write("You voted for "+name+" for council position no. "+p+".\n");
    return;
}


void
withdraw_application()
{
    string name = TP->query_name();
    int i, *ind = m_indexes(c_apply);

    for (i=0; i<sizeof(ind); i++)
        if (member_array(name, c_apply[ind[i]]) != -1)
        {
            write("You withdraw your application for position no. "+ind[i]+".\n");
            c_apply[ind[i]] -= ({ name });
            FIXEUID;
            save_object(SAVE_FILE);
            return;
        }
    write("You have not applied for anything.\n");
}


/*
 * Function name: list_council_ro()
 * Returns:       What you get when you 'read plaque'.
 */
string
list_council_ro()
{
    //string s = "Councilmembers are:\n\n";
    string s = "Recruitment Officers are :\n\n";
    mixed arr;
    int i;

    //arr = query_council();
    arr = ro_list;
    for (i = 0; i < sizeof(arr); i++)
    {
    
        //s += "Position no. " + c_list[arr[i]] + " ............ " + arr[i] + "\n";

        arr = ro_list;
        s += "\n\n\nRecruitment Officers are:\n\n";
        
        if (!sizeof(arr))
        {
            s += "     ----\n";
        }

        //--------------------------------------------------------------
        arr = lieutenant_list;
        s += "\n\n\nThe Lieutenants of the Army of Angmar are:\n\n";

        if (!sizeof(arr))
        {
            s += "     ----\n";
        }   //return s + "     ----\n";
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        arr = captain_list;
        s += "\n\n\nThe Mighty Captain of the Army of Angmar is:\n\n";

        if (!sizeof(arr))
        {
            s += "     ----\n";
        }   //return s + "     ----\n";
        //--------------------------------------------------------------

        return s + break_string(COMPOSITE_WORDS(arr), 60, 5) + "\n";
    }
      
}


/*
 * Function name: ann_list
 * Returns:       What you get when you 'read list'.
 */
string
ann_list()
{
    string s = "";
    int i;
    int* arr = m_indexes(c_apply);

    for (i=0; i<sizeof(arr); i++)
    {
        if (c_dates[arr[i]][0]+WEEK > time())
        {
            s += c_dates[arr[i]][1]+": *APPLY* for council no. "+arr[i];
            s += ". End: "+ctime(c_dates[arr[i]][0]+WEEK)[4..18]+".\n";
            if (sizeof(c_apply[arr[i]]))
            {
                s += break_string("  Applicants:  "+
                          COMPOSITE_WORDS(c_apply[arr[i]]), 70, 5)+"\n";
            }
        }
        else if (c_dates[arr[i]][0]+WEEK+WEEK > time())
        {
            s += c_dates[arr[i]][1]+": *VOTE* for council no. "+arr[i];
            s += ". End: "+ctime(c_dates[arr[i]][0]+WEEK+WEEK)[4..18]+".\n";
            if (sizeof(c_apply[arr[i]]))
            {
                s += break_string("  Applicants:  "+
                          COMPOSITE_WORDS(c_apply[arr[i]]), 70, 5)+"\n";
            }
        }
    }
    return s;
}


void resign_as_council()
{
    string name = TP->query_name();

    if(member_array(name, m_indexes(c_list)) == -1)
    {
        write("You are not a council member.\n");
        return;
    }

    c_list = m_delete(c_list, name);
    FIXEUID;
    save_object(SAVE_FILE);

    write("You have resigned as council member.\n");
}


int 
remove_council_member(string str)
{
    if (!str)
    {
        write("Remove whom?\n");

        return 1;
    }

    //object comem = find_player(str);

    string nam = str;


    if (member_array(nam, m_indexes(c_list)) == -1)
    {
        write("Not a council member.\n");
        return 1;
    }

    c_list = m_delete(c_list, nam);
    FIXEUID;
    save_object(SAVE_FILE);

    write("You remove the council member.\n");
}


//////////////////// ACTIVITY LOGIC //////////////////////////////////////
// NEW Nov 2019 - ACTIVITY LOGIC



// NEW Nov 2019 - ACTIVITY LOGIC
// Activitymeter logic
void
activity_meter()
{
    string captain;
    
    // using already existing function that returns the captain string
    captain = query_captain();
    
    captain_activity = AA_ACTIVITY_MAPPINGS->query_captain_activity_gauge(captain);
    
    if (captain_activity > 0)
    {
        if (is_captain(captain) == 1)
        {
            captain_activity = captain_activity -1;
            
            if (captain_activity < 1)
            {
                captain_activity = 1;
            }
            
            AA_ACTIVITY_MAPPINGS->set_captain_activity_gauge(captain, captain_activity);
        }
    }

    if (is_captain(captain) == 1)
    {
        if (captain_activity < 5)
        {
            demote_captain(captain);
            
            AA_ACTIVITY_MAPPINGS->clean_captain_activity_gauge(captain);
        }
    }
    
    return;
}

