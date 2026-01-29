/*
 * AA Ranking object
 *
 *
 * Modification 2007.07.02 Novo: Fixed sorting function
 *              2009.04.16 Petros: Fixed update_rank when someone leaves
 *                                 and rejoins.
*/
#pragma no_clone
#pragma no_inherit
#pragma strict_types
#pragma save_binary

#include <std.h>
#include <macros.h>
#include "../guild.h"

#define SAVE_FILE    (AA_DIR+"save_files/AA_RANKS")

/* by this we lower rank_stat of all members every boot */
#define LOWER_ALL    5
/* this is max allowed rising of rank_stat per boot */
#define MAX_JUMP    50
/* bonus for having rank - makes ranks more stable */
#define RANK_BONUS   100


/*
 * Nonprivate functions:
 */
void remove_entry(string name); // remove entry (player left guild...)
string update_rank(object who); // updates entry, returns rank
string *query_players_with_rank(string rank); // returns list of names with this rank
//string *query_players_with_rank_no(int i); // Footman = 0 ... Captain = 6


// NEW
//string *query_players_with_rank_no(int i); // Footman = 0 ... Lieutenant = 6


string *query_players_with_rank_no(int i); // Footman = 0 ... Lieutenant = 6

string *query_aa_members(); // Returns list of names of members

string captain;

string ro;

// NEW
string lieutenant;

//private string *captain_list = ({});

int aa_member(string name);

int is_lieutenant(string name);
int is_ro(string name);
int is_captain(string name);
int lieut_cap(string name);

int rank_no(object who);


//private static string *Ranks = ({ "Footman", "Standard Bearer", "Corporal",
  //                       "Sergeant", "Warrant Officer", "Lieutenant", "Captain" });


// NEW
private static string *Ranks = ({ "Footman", "Standard Bearer", "Lance Corporal",
	"Corporal", "Sergeant", "Master Sergeant", "Master Sergeant" });

// OLD
//private static string *Ranks = ({ "Footman", "Standard Bearer", "Corporal",
  //                       "Sergeant", "Master Sergeant", "Warrant Officer", "Lieutenant"});

// NEW
private static int *Factors = ({ 1, 3, 6, 9, 15, 20, 1 });

//private static int *Factors = ({ 1, 3, 6, 10, 16, 25, 1 });
private static int *Stat_levels = ({ 0, 200, 400, 650, 900, 1200, 1400 });

/*
 * Army has fixed structure and so number of positions available
 * depends on number of members. This limits number of position from
 * the top. Note that one position for every level is always available
 * Here are top limits:
 *
 *  Footmen         - no restrictions
 *  Standard Bearer - (sum of members) / Factors[1]
 *  Corporal        - (sum of members) / Factors[2]
 *  Sergeant        - (sum of members) / Factors[3]
 *  Warrant Officer - (sum of members) / Factors[4]
 *  Lieutenant      - (sum of members) / Factors[5]
 *  Captain/Lt      - 1
 *
 *----------------- New ranknames------------------
 *<<  Footmen         - no restrictions
 *  Standard Bearer - (sum of members) / Factors[1]
 *  Lance Corporal  - (sum of members) / Factors[2]
 *  Corporal        - (sum of members) / Factors[3]
 *  Sergeant        - (sum of members) / Factors[4]
 *  Master Sergeant - (sum of members) / Factors[5]
 *  Warrant Officer - 1  >>
 *-------------------------------------------------
 *
 *
 *
 *  note (sum of members) is only up to a given level
 *
 * This rank system should be more exciting for players - in order to
 * get better rank (if there is no place available) one have to be better
 * then other player on that level which will result in promotion of this
 * one and demotion of other one.
 */

/*
 * The index to the Name_rank mapping is the name and it will return
 * rank of player.
 *
 *  mapping Name_rank = ([ "name" : "rank", ... ]);
 *
 * The index to the Rank_name_stat mapping is rank and it will return an
 * array of arrays containing name of the player with this rank and his stat
 * that determines the rank.
 *
 * mapping Rank_name_stat = ([
 *       "rank1" : ({ ({"name1","stat1"}),({"name2","stat2"}),...}),
 *       "rank2" : ({ ({"name3","stat3"}),({"name3","stat3"}),...}),
 *           ...             ]);
 *
 * The index to the Name_rank mapping is the name and it will return
 * time when rank stat was last updated.
 *
 * mapping Name_time = ([ "name" : time_updated, ... ]);
 */

/*
 * Global variables, they will be saved.
 */
private mapping Name_rank      = ([ ]);
private mapping Rank_name_stat = ([ ]);
private mapping Name_time = ([ ]);
private int recalculated_rank_time;

/*
 * Prototypes
 */
private static void recalculate_ranks();

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
        Name_rank      = ([ ]);
        Rank_name_stat = ([ ]);
        Name_time = ([ ]);
        for (i = 0; i < sizeof(Ranks); i++)
            Rank_name_stat += ([ Ranks[i] : ({ }) ]);
    }
    for (i=0; i<sizeof(Ranks); i++)
        if(!Rank_name_stat[Ranks[i]])
            Rank_name_stat[Ranks[i]] = ({ });
    set_alarm(0.0, 0.0, recalculate_ranks);
}

/*
 * Function name: set_new_rank
 * Arguments:     names - string array of names
 *                new_rank - string
 *                old_rank - string
 * Description  : changes ranks for all names from old_rank to new_rank
 */
private static void
set_new_rank(string *names, string new_rank, string old_rank)
{
    int i, s;
    mixed old_rank_name_stat = Rank_name_stat[old_rank];

    s = sizeof(names);
    for (i = 0; i < s; i++)
        Name_rank[names[i]] = new_rank;

    s = sizeof(old_rank_name_stat);
    for (i = 0; i < s; i++)
        if(member_array(old_rank_name_stat[i][0], names) != -1)
        {
            Rank_name_stat[new_rank] += ({ old_rank_name_stat[i] });
            Rank_name_stat[old_rank] -= ({ old_rank_name_stat[i] });
        }
}

/*
 * Function name: rank_demote_council
 * Description  : We demote council members (no W.O or LT.) ant those
 *                who applied for council.
 */
private static void
rank_demote_council()
{
    string *names, *council;
    int i, j, s, r = sizeof(Ranks);
    FIXEUID;
    council = AA_COUNCIL_OBJ->query_council() + AA_COUNCIL_OBJ->query_applied();
    for (i = r-1; i > r-3; i--)
    {
        names = ({ });
        s = sizeof(Rank_name_stat[Ranks[i]]);
        for (j = 0; j < s; j++)
            if (member_array(CAP(Rank_name_stat[Ranks[i]][j][0]), council) != -1)
                names += ({ Rank_name_stat[Ranks[i]][j][0] });
        set_new_rank(names, Ranks[r-3], Ranks[i]);
    }
}

/*
 * Function name: lower_all_stats
 * Description  : We lower all stats so not logging players are not on top
 */
private static void
lower_all_stats()
{
    string *names;
    int i, j, s;

    for (i=0; i<sizeof(Ranks); i++)
        for (j = 0; j < sizeof(Rank_name_stat[Ranks[i]]); j++)
        {
            Rank_name_stat[Ranks[i]][j][1] -= LOWER_ALL;
            if (Rank_name_stat[Ranks[i]][j][1] < 0)
                Rank_name_stat[Ranks[i]][j][1] = 0;
        }
}

/*
 * Function name: demote_for_low_stat
 * Description  : We demote everyone who lost somehow stats
 */
private static void
demote_for_low_stat()
{
    string *names;
    int i, j, s;

    for (i = sizeof(Ranks)-1; i > 0; i--)
    {
        names = ({ });
        s = sizeof(Rank_name_stat[Ranks[i]]);
        for (j = 0; j < s; j++)
            if (Rank_name_stat[Ranks[i]][j][1] < Stat_levels[i])
                names += ({ Rank_name_stat[Ranks[i]][j][0] });
        set_new_rank(names, Ranks[i-1], Ranks[i]);
    }
}

/*
 * Function name: promote_for_high_stat
 * Description  : Now we promote eneryone with stat high enough
 */
private static void
promote_for_high_stat()
{
    string *names;
    int i, j, s;

    for (i = 0; i < sizeof(Ranks)-1; i++)
    {
        names = ({ });
        s = sizeof(Rank_name_stat[Ranks[i]]);
        for (j = 0; j < s; j++)
            if (Rank_name_stat[Ranks[i]][j][1] > Stat_levels[i+1])
                names += ({ Rank_name_stat[Ranks[i]][j][0] });
        set_new_rank(names, Ranks[i+1], Ranks[i]);
    }
}

/*
 * Function name: how_many_to_remove
 * Arguments    : rank - rank (string)
 * Returns      : how much more names is on this level then it should be or
 *                -1 - this should never happen!
 */
private static int
how_many_to_remove(string rank)
{
    int i, num_of_all, num, num2;

    if (rank == Ranks[sizeof(Ranks)-1])
    {
        if (sizeof(Rank_name_stat[rank]))
            return (sizeof(Rank_name_stat[rank]) - 1);
        return 0;
    }
    num_of_all = 0;
    for (i = 0; i < sizeof(Ranks); i++)
    {
        num = sizeof(Rank_name_stat[Ranks[i]]);
        num_of_all += num;
        if (rank == Ranks[i])
        {
            if (num < 2)
                return 0;
            num2 = num - (num_of_all / Factors[i]);
            if (num2 == num)
                num2--;
            num = num2;
            if (num < 1)
                return 0;
            return num;
        }
    }
    return -1; // should never happen
}

private int
my_sort_function(mixed a, mixed b)
{
    return a[1]-b[1];
}

/*
 * Function name: demote_no_place
 * Description  : we may have promoted too many...
 */
private static void
demote_no_place()
{
    int i, j, r;
    string *names;
    for (i = sizeof(Ranks)-1; i > 0; i--)
    {
        Rank_name_stat[Ranks[i]] = sort_array(Rank_name_stat[Ranks[i]],
            my_sort_function);
        names = ({ });
        r = how_many_to_remove(Ranks[i]);
        if (r>0)
        {
            for (j = 0; j < r; j++)
                names += ({ Rank_name_stat[Ranks[i]][j][0] });
            set_new_rank(names, Ranks[i-1], Ranks[i]);
        }
    }
}

/*
 * Function name: remove_entry
 * Description  : Removes name from record (player left guild...)
 * Argument     : name (string)   name to be removed
 */
void
remove_entry(string name)
{
    int i;
    string rank;
    mixed tmp, tmp2 = ({ });

    /***  check if this name has a record  ***/
    if(member_array(name, m_indices(Name_rank)) == -1) return;
    rank = Name_rank[name];
    tmp = Rank_name_stat[rank];
    Name_rank = m_delete(Name_rank, name);

    for(i = 0; i < sizeof(tmp); i++)
        if(tmp[i][0] != name)
            tmp2 += ({ tmp[i] });

    Rank_name_stat[rank] = tmp2;
    FIXEUID;
    save_object(SAVE_FILE);
}

public void start_five()
{ demote_no_place(); FIXEUID; save_object(SAVE_FILE); }
public void start_four()
{ rank_demote_council(); set_alarm(0.0, 0.0, start_five); }
public void start_three()
{ promote_for_high_stat(); set_alarm(0.0, 0.0, start_four); }
public void start_two()
{ demote_for_low_stat(); set_alarm(0.0, 0.0, start_three); }
public void start_one()
{ lower_all_stats(); set_alarm(0.0, 0.0, start_two); }

/*
 * Function name: recalculate_ranks
 * Description  : It removes nonexistant and idle players and
 *                once a day updates ranks.
 */
public void
recalculate_ranks()
{
    string *names, rank;
    int i, s;

    /*** first remove nonexistant players ***/
    FIXEUID;
    names = m_indices(Name_rank) + m_indices(Name_time);
    s = sizeof(names);
    for(i = 0; i < s; i++)
    {
        if(!SECURITY->exist_player(names[i]) || SECURITY->query_wiz_level(names[i]) ||
           (explode(names[i]+"#", "jr#")[0]+"jr" == names[i]))
        {
            remove_entry(names[i]);
            Name_time = m_delete(Name_time, names[i]);
        }
    }
    /*** now remove players with zero AA stat (idle too long) ***/
    names = ({ });
    rank = Ranks[0];
    s = sizeof(Rank_name_stat[rank]);
    for(i = 0; i < s; i++)
        if(Rank_name_stat[rank][i][1] == 0)
            names += ({ Rank_name_stat[rank][i][0] });
    for(i = 0; i < sizeof(names); i++)
        remove_entry(names[i]);

    set_alarm(2000.0, 0.0, recalculate_ranks);
    if(time() < recalculated_rank_time + DAY)
        return; // really recalculate rank only once a day
    recalculated_rank_time = time();

    /*** finally sort them all out ***/
    set_alarm(0.0, 0.0, start_one);
}

private void set_time_updated(string name)
{
    Name_time[name] = time();
}

private int
query_time_updated(string name)
{
    if (member_array(name, m_indexes(Name_time)) == -1)
        return -DAY;
    return Name_time[name];
}

/*
 * Function name: update_rank
 * Description  : This function should be called every time when player
 *                logs in. It updates player stat and returns his present
 *                rank.
 */
string
update_rank(object who)
{
    string rank, name = who->query_real_name();
    int aa_stat, i, s;

    FIXEUID;
    if(!name)
        return "Servant";
    if((aa_stat = who->query_aa_stat()) < 1)
    {
        set_time_updated(name);
        remove_entry(name);
        return "Servant";
    }

    for(i = 0; i < sizeof(Ranks); i++)
        if(!Rank_name_stat[Ranks[i]])
            Rank_name_stat[Ranks[i]] = ({ });

    if(member_array(name, m_indices(Name_rank)) == -1)
    {
        Name_rank += ([ name : Ranks[0] ]);
        Rank_name_stat[Ranks[0]] += ({ ({ name, MIN(MAX_JUMP, aa_stat) }) });
    }
    else
    {
        if (query_time_updated(name) > time() - DAY)
            return Name_rank[name];

        rank = Name_rank[name];
        s = sizeof(Rank_name_stat[rank]);
        for(i = 0; i < s; i++)
            if(name == Rank_name_stat[rank][i][0])
            {
                Rank_name_stat[rank][i][1] =
                    (member_array(rank, Ranks)>=0 ? RANK_BONUS : 0 ) +
                     MIN(aa_stat, Rank_name_stat[rank][i][1] + MAX_JUMP);
                i = s;
            }
    }
    /* save the new values */
    set_time_updated(name);
    save_object(SAVE_FILE);
    return Name_rank[name];
}

/*
 * Function name: query_players_with_rank
 * Description  : Returns list of names with this rank
 */
string *
query_players_with_rank(string rank)
{
    string *names = ({ });

	
    int i;

	// captain name (string)
	captain = AA_COUNCIL_OBJ->query_captain();

	// NEW
	lieutenant = AA_COUNCIL_OBJ->query_lieutenant();

	// NEW
	ro = AA_COUNCIL_OBJ->query_ro();

	captain = lower_case(captain);

	// NEW
	lieutenant = lower_case(lieutenant);

	// NEW
	ro = lower_case(ro);
	

    if(member_array(rank, Ranks) == -1) return ({ });

	for (i = 0; i < sizeof(Rank_name_stat[rank]); i++)
	{
		names += ({ Rank_name_stat[rank][i][0] });
	}
       

	// We remove the captain from the list.
	names -= ({ captain });

	// NEW
	// We remove the lieutenant from the list.
	names -= ({ lieutenant });

	// NEW
	// We remove the ro from the list.
	//names -= ({ ro });

    return names;
}

/*
 * Function name: query_players_with_rank_no
 * Description  : Returns list of names with rank of given number
 *                Footman = 0 ... LT = 6
 */
string *
query_players_with_rank_no(int i)
{
    if(i<0 || i>6) return ({ });
    return query_players_with_rank(Ranks[i]);
}

/*
 * Function name: query_aa_members
 * Description:   Returns list of names of members
 */
string *
query_aa_members()
{
    return m_indexes(Name_rank);
}

/*
 * Function name: aa_member
 * Arguments:     name - player name
 * Returns:       1 - 'name' is member of AA
 *                0 - 'name' is not member
 */
int
aa_member(string name)
{
    if (member_array(LOW(name), m_indexes(Name_rank)) == -1)
        return 0;
    return 1;
}


//------------------------------------------------------------------------------

/*
 * Function name: is_lieutenant
 * Arguments:     name - player name
 * Returns:       1 - 'name' is Lieutenent
 *                0 - 'name' is not
 */
/*int
is_lieutenant(string name)
{
    if (member_array(LOW(name), query_players_with_rank_no(5)) != -1)
        return 1;
    return 0;
}*/

/*
 * Function name: is_captain
 * Arguments:     name - player name
 * Returns:       1 - 'name' is Captain
 *                0 - 'name' is not
 */
/*int
is_captain(string name)
{
    if (member_array(LOW(name), query_players_with_rank_no(6)) != -1)
        return 1;
    return 0;
}*/

/*
 * Function name: lieut_cap
 * Arguments:     name - player name
 * Returns:       1 - 'name' is Capt. or Lieutenent
 *                0 - 'name' is not
 */
/*int
lieut_cap(string name)
{
    if (is_lieutenant(name) || is_captain(name)) return 1;
    return 0;
}*/



/* OLD
 * Function name: is_lieutenant
 * Arguments:     name - player name
 * Returns:       1 - 'name' is Lieutenent
 *                0 - 'name' is not
 */
/*int
is_lieutenant(string name)
{
    if (member_array(LOW(name), query_players_with_rank_no(6)) != -1)
        return 1;
    return 0;
}*/




// NEW---------------------------------
/*
* Function name: is_ro
* Arguments:     name - player name
* Returns:       1 - 'name' is Captain
*                0 - 'name' is not
*/
int
is_ro(string name)
{
	if (AA_COUNCIL_OBJ->is_ro(name)) return 1;
	return 0;
}
//-------------------------------------


// NEW---------------------------------
/*
* Function name: is_lieutenant
* Arguments:     name - player name
* Returns:       1 - 'name' is Captain
*                0 - 'name' is not
*/
int
is_lieutenant(string name)
{
	if (AA_COUNCIL_OBJ->is_lieutenant(name)) return 1;
	return 0;
}
//-------------------------------------


/*
 * Function name: is_captain
 * Arguments:     name - player name
 * Returns:       1 - 'name' is Captain
 *                0 - 'name' is not
 */
int
is_captain(string name)
{
	if (AA_COUNCIL_OBJ->is_captain(name)) return 1;
	return 0;
}

/*
 * Function name: lieut_cap
 * Arguments:     name - player name
 * Returns:       1 - 'name' is Capt. or Lieutenent
 *                0 - 'name' is not
 */
int
lieut_cap(string name)
{
    //if (is_lieutenant(name) || AA_COUNCIL_OBJ->is_captain(name)) return 1;

	// NEW
	if (AA_COUNCIL_OBJ->is_lieutenant(name) || AA_COUNCIL_OBJ->is_captain(name)) return 1;

    return 0;
}

//-----------------------------------------------------------------------


/*
 * Function name: rank_no
 * Argument:      who - object we want to know rank of
 * Returns:       Rank number of 'who' (Footman=0,...,Captain=6).
 <<<<* Returns:       Rank number of 'who' (Footman=0,...,LT=6).>>>>
 */
int
rank_no(object who)
{
    return member_array(who->query_rank(), Ranks);
}

