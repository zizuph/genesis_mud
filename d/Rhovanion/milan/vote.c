#pragma no_inherit
#pragma strict_types

inherit "/d/Rhovanion/lib/room";

#include <std.h>
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

#define BOARD_NAME  "/d/Rhovanion/common/boards/shield_club_vote"
#define SAVE_FILE   (THIS_DIR+"S_C_VOTES")
#define TITLE_FILE  (THIS_DIR+"s_c_titles")
#define WEEK        (7*86400)
#define TEN_DAYS    864000
#define MONTH       (30*86400)
#define TITLES      ({ "Footman", "Standard Bearer", \
                       "Corporal", "Sergeant", "Warrant Officer", \
                       "Lieutenant", "Captain" })
#define PERCENT     30

/**********************************************************************
 * Global variables, they will be saved.
 */
private mapping to_be_punished  = ([ ]);
/*
 *  to_be_punished = ([ name : ({ p1, p2, ... }), ... ]);
 */
private mapping punished        = ([ ]);
/*
 *  punished = ([ name : ({ ({ p, time }), ... }), ... ]);
 */
private mapping punish  = ([ ]);
/*
 *   punish = ([
 *       "name"+"#"+p : ({ ({"name1",vote}), ({"name2",vote}),...}),
 *      ...   ]);
 */
private mapping dates = ([ ]);
/*
 *  dates = ([ "name"+"#"+p : ({ date, who }), ... ]);
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

/*************************************************************************
 * Prototypes
 */
private void beating_on_head(object tp);
private void rejecting_from_army(object tp);
private void executing(object tp);


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
 * Function name: aa_member
 * Arguments:     name - player name
 * Returns:       1 - 'name' is member of AA
 *                0 - 'name' is not member
 */
int
aa_member(string name)
{
    string n, *arr;

    n = LOW(name);
    arr = TITLE_FILE->query_members();
    if (member_array(n, arr) == -1)
        return 0;
    return 1;
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
    if (member_array(LOW(name),
                     TITLE_FILE->query_players_with_title(TITLES[5])) != -1)
        return 1;
    if (member_array(LOW(name),
                     TITLE_FILE->query_players_with_title(TITLES[6])) != -1)
        return 1;
    return 0;
}

/*
 * Function name: my_sort_function
 * Description:   Used for sorting of election results
 */
int
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
    s += "                               Dark Lord\n\n\n"; 
    s += "P.S. Here are the results of voting:\n\n";
    s += " Candidate:                  Weight:  Votes:\n";
    s += "---------------------------------------------\n";
    for (i=0; i<sizeof(rrr); i++)
        s += sprintf(" %-30'.'s %3d %7d\n", rrr[i][0]+" ",
                                            rrr[i][1],
                                            rrr[i][2]);

    seteuid(getuid());
    write_file(THIS_DIR+"Council."+p, s);
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
        if (aa_member(name))
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
 * Function name: check_council
 * Description:   This function throws out of council non AA members
 *                (after they quit guild), starts election for empty positions
 *                and puts in new councilmembers after election.
 */
void
check_council()
{
    int i;
    mixed arr;

    /* throw non members out of council */
    arr = m_indexes(c_list);
    for (i=0; i<sizeof(arr); i++)
      if (!aa_member(arr[i])) c_list = m_delete(c_list, arr[i]);

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
            c_dates += ([ i : ({ time(), "Dark Lord" }) ]);
        }

    /* save new variables */
    seteuid(getuid());
    save_object(SAVE_FILE);
}

/*
 * Function name: report_punish
 * Description:   This function creates the report with punishment voting
 *                results. (Now it is a file - in future will be a note
 *                on board.)
 * Arguments:     name - name of player to be punished
 *                p - number of punishment
 *                voted - how many voted
 *                yes - counted 'yes'
 *                no - counted 'no'
 *                ayes - all voted 'yes'
 *                ano - all voted 'no'
 */
private void
report_punish(string name, int p, int voted, int yes, int no, int ayes, int ano)
{
    string s;

    s = "Result of voting on punishment no. "+p+" for "+name+":\n\n";
    if (yes > no)
    {
        s += "        "+name+" will be punished!\n\n";
    }
    else
        s += "        "+name+" will NOT be punished!\n\n";
    s += "                                    Dark Lord\n\n";
    s += "P.S. Results of voting:\n\n";
    s += "      Voted: "+ayes+" yes,  "+ano+" no";
    if ((ayes != yes) || (ano != no))
        s += "      Counted: "+yes+" yes,  "+no+" no";
    s += ".\n";

    seteuid(getuid());
    write_file(THIS_DIR+"Pun_"+name+"_"+p, s);
}

/*
 * Function name: set_punish
 * Description:   This function counts votes and decides on punishment
 * Arguments:     str - in format 'name#x' ('name' of player 'x' num of pun.)
 */
private void
set_punish(string str)
{
    mixed arr;
    string name;
    int i,yes,no,ayes,ano,p,expected;

    if (member_array(str, m_indexes(punish)) == -1) return;

    arr = explode(str, "#");
    name = arr[0];
    p = atoi(arr[1]);

    /* first expected number of votes */
    expected = 5; /* council - O.K... they may be counted twice but... */
    expected += sizeof(TITLE_FILE->query_players_with_title(TITLES[6]));
    expected += sizeof(TITLE_FILE->query_players_with_title(TITLES[5]));
    if(p > 1)
        expected += sizeof(TITLE_FILE->query_players_with_title(TITLES[4]));
    if(p > 2)
        expected += sizeof(TITLE_FILE->query_players_with_title(TITLES[3]));
    if(p > 3)
        expected += sizeof(TITLE_FILE->query_players_with_title(TITLES[2]));
    if(p > 4)
        expected += sizeof(TITLE_FILE->query_players_with_title(TITLES[1]));

    expected = (expected * PERCENT) / 100;
    yes = 0; no = 0; ayes = 0; ano = 0;

    /* count all votes */
    for (i=0; i<sizeof(punish[str]); i++)
    {
        if(punish[str][i][1] == "yes")
        {
           ayes++;
        }
        else ano++;
    }
    if (sizeof(punish[str]) >= expected) /* all votes count */
    {
        yes = ayes;
        no = ano;
    }
    if (yes == no) /* only votes of council count */
    {
        yes = 0;
        arr = m_indexes(c_list);
        for (i=0; i<sizeof(punish[str]); i++)
            if (member_array(punish[str][i][0], arr) != -1)
                if (punish[str][i][1] == "yes")
                    yes++;
        no = 5 - yes;
    }

    report_punish(name, p, sizeof(punish[str]), yes, no, ayes, ano);

    if (yes > no)
    {
        if(member_array(name, m_indexes(to_be_punished)) == -1)
        {
            to_be_punished += ([ name : ({ p }) ]);
        }
        else if(member_array(p, to_be_punished[name]) == -1)
            to_be_punished[name] += ({ p });

        seteuid(getuid());
        save_object(SAVE_FILE);
    }
    punish = m_delete(punish, str);
}

/*
 * Function name: check_punish
 * Description:   Checks if voting is over (to set_punish) and if player
 *                can be punished again.
 */
void
check_punish()
{
    int i;
    mixed arr;

    arr = m_indexes(dates);
    for (i=0; i<sizeof(arr); i++)
    {
        if (dates[arr[i]][0]+WEEK < time())
            set_punish(arr[i]);
        if (dates[arr[i]][0]+MONTH < time())
            dates = m_delete(dates, arr[i]);
    }
    seteuid(getuid());
    save_object(SAVE_FILE);
}

/*
 * Function name: check_variables
 * Description:   Check mappings for records containing nonmembers and 
 *                throws them out.
 */
private void
check_variables()
{
    mixed arr, tmp;
    int i, j;

    arr = m_indexes(to_be_punished);
    for (i=0; i<sizeof(arr); i++)
        if (!sizeof(to_be_punished[arr[i]]) || !aa_member(arr[i]))
            to_be_punished = m_delete(to_be_punished, arr[i]);
    arr = m_indexes(punished);
    for (i=0; i<sizeof(arr); i++)
        if (!sizeof(punished[arr[i]]) || !aa_member(arr[i]))
            punished = m_delete(punished, arr[i]);
    arr = m_indexes(punish);
    for (i=0; i<sizeof(arr); i++)
        if (!aa_member(explode(arr[i], "#")[0]))
        {
            punish = m_delete(punish, arr[i]);
        }
        else
        {
            tmp = ({ });
            for (j=0; j<sizeof(punish[arr[i]]); j++)
                if (!aa_member(punish[arr[i]][j][0]))
                    tmp += ({ punish[arr[i]][j] });
            punish[arr[i]] -= tmp;
        }
    arr = m_indexes(dates);
    for (i=0; i<sizeof(arr); i++)
        if (!aa_member(explode(arr[i], "#")[0]))
            dates = m_delete(dates, arr[i]);
    arr = m_indexes(c_vote);
    for (i=0; i<sizeof(arr); i++)
    {
        tmp = ({ });
        for (j=0; j<sizeof(c_vote[arr[i]]); j++)
            if (!aa_member(c_vote[arr[i]][j][0]) ||
                !aa_member(c_vote[arr[i]][j][1]))
                tmp += ({ c_vote[arr[i]][j] });
        c_vote[arr[i]] -= tmp;
    }
    arr = m_indexes(c_apply);
    for (i=0; i<sizeof(arr); i++)
    {
        tmp = ({ });
        for (j=0; j<sizeof(c_apply[arr[i]]); j++)
            if (!aa_member(c_apply[arr[i]][j]))
                tmp += ({ c_apply[arr[i]][j] });
        c_apply[arr[i]] -= tmp;
    }

    seteuid(getuid());
    save_object(SAVE_FILE);
}

/*
 * Function name: reset_room
 */
void
reset_room()
{
    object cleaner;

    check_variables();
    check_council();
    check_punish();

    seteuid(getuid());
    cleaner = clone_object("/std/monster");
    cleaner->set_name("guild_cleaner");
    cleaner->set_base_stat(SS_STR, 350);
    cleaner->set_base_stat(SS_DEX, 10);
    cleaner->set_base_stat(SS_CON, 150);
    cleaner->set_base_stat(SS_WIS, 10);
    cleaner->set_base_stat(SS_INT, 10);
    cleaner->set_base_stat(SS_DIS, 30);
    cleaner->set_pname("trolls");
    cleaner->set_race_name("troll");
    cleaner->set_adj(({"huge", "clumsy"}));
    cleaner->set_short("huge clumsy troll");
    cleaner->add_prop(LIVE_I_NEVERKNOWN, 1);
    cleaner->move(TO, 1);
    tell_room(TO, QCNAME(cleaner)+" arrives.\n");
    cleaner->command("get all");
    cleaner->command("sigh");
    cleaner->command("s");
    cleaner->command("e");
    cleaner->command("drop all");
    cleaner->command("w");
    cleaner->command("n");
    cleaner->command("say I have my orders... Keep this place tidy!");
    tell_room(TO, QCNAME(cleaner)+" leaves.\n");
    cleaner->remove_object();
}

/*
 * Function name: create_room
 */
void
create_room()
{
    object board;

    set_short("Court room of Army of Angmar");
    set_long("This is the court room of Army of Angmar. On the wall you "+
             "see the silver plaque, sign, the announcement list and the "+
             "list of punishments.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_item(({"punishments","list of punishments"}),"All possible punishments "+
                            "are listed here.\n");
    add_item(({"list","announcement list"}), "Here you may find interesting "+
                            "announcements regarding army-life.\n");
    add_item("sign", "It is quite plain with some instructions on it.\n");
    add_item(({"plaque","silver plaque"}), "A very nice silver plaque indeed. "+
                       "It has something engraved on it and it looks rather "+
                       "important.\n");
    add_cmd_item(({"punishments","list of punishments"}), "read", "@@pun_list");
    add_cmd_item(({"list","announcement list"}), "read", "@@ann_list");
    add_cmd_item("sign", "read", "@@sign");
    add_cmd_item(({"plaque","silver plaque"}), "read", "@@plaque");

    add_exit(THIS_DIR+"priv","south");
    add_exit(THIS_DIR+"library","east");
    add_exit(THIS_DIR+"council","north","@@block_exit");

    seteuid(getuid());
    restore_object(SAVE_FILE);

    board = clone_object("/d/Rhovanion/lib/board");
    board->set_board_name(BOARD_NAME);
    board->set_remove_str("You are not able to delete any messages.\n");
    board->set_num_notes(20);
    board->move(TO, 1);

    reset_room();
}

/*
 * Function name: block_exit
 * Description:   Block out not councilmember, Lieutenant or Captain.
 * Returns:       1 - Not alow to enter
 *                0 - Alow enter
 */
int
block_exit()
{
    if (lieut_cap(TP->query_name())) return 0;  /* Lieutenant or Captain */
    if (member_array(TP->query_name(), m_indexes(c_list)) != -1) return 0;

    write("Only Captain, Lieutenants and councilmembers are allowed.\n");
    return 1;
}

/*
 * Function name: pun_list
 * Returns:       What you get when you 'read punishments'.
 */
string
pun_list()
{
    return "THE LIST OF PUNISHMENTS\n\n"+
           "      1. Ban from training for 2 weeks\n"+
           "      2. Lowering effectivity of specials for 10 days + above\n"+
           "      3. Disallowing specials for 1 week + above\n"+
           "      4. Beating on the head (loosing skills) + above\n"+
           "      5. Extermination\n"+
           "      6. Rejecting from Army + beating on the head\n";
}

/*
 * Function name: ann_list
 * Returns:       What you get when you 'read list'.
 */
string
ann_list()
{
    string s,n,p;
    int i;
    mixed arr;

    s = "BEGINING OF ANNOUNCEMENTS...\n";
    arr = m_indexes(c_apply);
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
    s += "\n";
    arr = m_indexes(punish);
    for (i=0; i<sizeof(arr); i++)
        if (dates[arr[i]][0]+WEEK > time())
        {
            n = explode(arr[i], "#")[0];
            p = explode(arr[i], "#")[1];
            s += dates[arr[i]][1]+": *VOTE* on punishment "+p+" for "+n;
            s += ". End: "+ctime(dates[arr[i]][0]+WEEK)[4..18]+".\n";
        }
    return s+"...END OF ANNOUNCEMENTS\n";
}

/*
 * Function name: sign
 * Returns:       What you get when you 'read sign'.
 */
string
sign()
{
    return "Available commands:\n"+
      "  To suggest punishment no. <num> for <name> use:\n"+
      "     'punish <name> <num>'\n"+
      "  To vote/change vote on punishment no. <num> for <name> use:\n"+
      "     'vote punish <name> <num> <yes/no>'\n"+
      "  To start election for council position no. <num> use:\n"+
      "     'council <num>'\n"+
      "  To apply for council position no. <num> use:\n"+
      "     'apply for council <num>'\n"+
      "  To withdraw application for council position use:\n"+
      "     'withdraw application'\n"+
      "  To vote/change vote for <name> for council position no. <num> use:\n"+
      "     'vote council <num> <name>'\n"+
      "  To check your votes use:\n"+
      "     'check votes'\n\n";
}

/*
 * Function name: plaque
 * Returns:       What you get when you 'read plaque'.
 */
string
plaque()
{
    string s = "Councilmembers are:\n\n";
    mixed arr = m_indexes(c_list);
    int i;

    for (i=0; i<sizeof(arr); i++)
      s += "Position no. "+c_list[arr[i]]+" ............ "+arr[i]+"\n";
    return s+"\n";
}

/*
 * Function name: rank_no
 * Argument:      who - object we want to know rank of
 * Returns:       Rank number of 'who' (Footman=0,...,Captain=6).
 */
int
rank_no(object who)
{
    return member_array(who->query_s_c_level(), TITLES);
}

/*
 * Function name: ok_punish
 * Description:   Decide if it is O.K. to propose punishment
 * Argument:      name - name of player to punish
 *                p - number of punishment
 * Returns:       0 - not allowed to propose punishment
 *                1 - allowed.
 */
int
ok_punish(string name, int p)
{
    string str = name+"#"+p;

    if (member_array(str, m_indexes(dates)) != -1)
    {
        if (dates[str][0]+WEEK > time())
        {
            write("This punishment is currently beeing voted on.\n");
            return 0;
        }
        if (dates[str][0]+MONTH > time())
        {
            write("This punishment can't be proposed again till "+
                  ctime(dates[str][0]+MONTH)+".\n");
            return 0;
        }
    }
    return 1;
}

/*
 * Function name: ok_council
 * Description:   Decide if it is O.K. to start elections for council
 * Argument:      p - number of council position
 * Returns:       0 - not allowed
 *                1 - allowed.
 */
int
ok_council(int p)
{
    if (member_array(p, m_indexes(c_dates)) != -1)
    {
        if (c_dates[p][0]+WEEK > time())
        {
            write("Applications for this position are accepted now.\n");
            return 0;
        }
        if (c_dates[p][0]+WEEK+WEEK > time())
        {
            write("Now is the voting on this position.\n");
            return 0;
        }
        if (c_dates[p][0]+WEEK+WEEK+MONTH > time())
        {
            write("This position can be voted on after "+
                  ctime(c_dates[p][0]+WEEK+WEEK+MONTH)+".\n");
            return 0;
        }
    }
    return 1;
}

/*
 * Function name: ok_resign
 * Description:   Decide if it is O.K. to resign on council
 * Argument:      p - number of council position
 * Returns:       0 - not allowed
 *                1 - allowed.
 */
int
ok_resign(int p)
{
    if (member_array(p, m_indexes(c_dates)) != -1)
    {
        if (c_dates[p][0]+WEEK > time())
        {
            write("Applications for this position are accepted now.\n");
            return 0;
        }
        if (c_dates[p][0]+WEEK+WEEK > time())
        {
            write("Now is the voting on this position.\n");
            return 0;
        }
    }
    c_dates = m_delete(c_dates, p);
    return 1;
}

/*
 * Function name: can_punish
 * Description:   Decide if player can propose punishment
 * Argument:      who - player trying to propose it
 * Returns:       0 - not allowed
 *                1 - allowed.
 */
int
can_punish(object who)
{
    if (lieut_cap(who->query_name())) return 1;  /* Lieutenant or Captain */
    if (member_array(who->query_name(), m_indexes(c_list)) != -1) return 1;
    return 0;
}

/*
 * Function name: can_council
 * Description:   Decide if player can start council election
 * Argument:      who - player trying to do it
 * Returns:       0 - not allowed
 *                1 - allowed.
 */
int
can_council(object who, int p)
{
    string name = who->query_name();

    if (lieut_cap(who->query_name()) && ok_council(p)) return 1;
    /* for any case update council first */
    if (member_array(name, m_indexes(c_list)) != -1)
        check_council();
    if ((member_array(name, m_indexes(c_list)) != -1) && (c_list[name] == p)
        && ok_resign(p))
        return 1;
    return 0;
}

/*
 * Function name: can_vote_pun
 * Description:   Decide if player can vote on punishment
 * Argument:      who - player trying to do it
 *                p - number of punishment
 * Returns:       0 - not allowed
 *                1 - allowed.
 */
int
can_vote_pun(object who, int p)
{
    int r = rank_no(who);

    if (member_array(who->query_name(), m_indexes(c_list)) != -1) return 1;
    if (r > 4) return 1;
    if ((r > 3) && (p > 1)) return 1;
    if ((r > 2) && (p > 2)) return 1;
    if ((r > 1) && (p > 3)) return 1;
    if ((r > 0) && (p > 4)) return 1;
    return 0;
}

/*
 * Function name: init
 * Description:   adds commands to player in this room
 */
void
init()
{
    ::init();
    add_action("punish","punish");     /* propose a punishment on someone */
    add_action("council","council");   /* start election for a council    */
    add_action("apply","apply");       /* apply for council position      */
    add_action("withdraw","withdraw"); /* withdraw application            */
    add_action("vote","vote");         /* vote on punishment or council   */
    add_action("check","check");       /* check your votes                */ 
}

/****************************************************************************
 *
 *   NOW COMES FUNCTIONS THAT HANDLE COMMANDS
 *
 ****************************************************************************/
int
check(string str)
{
    string *vvv = ({ });
    string name,p,tpname = TP->query_name();
    mixed arr;
    int i,j;

    if (str != "votes")
    {
        NF("Check what?\n");
        return 0;
    }

    arr = m_indexes(c_vote);
    for (i=0; i<sizeof(arr); i++)
        for (j=0; j<sizeof(c_vote[arr[i]]); j++)
            if (tpname == c_vote[arr[i]][j][0])
                vvv += ({ c_vote[arr[i]][j][1]+" for council no. "+
                          arr[i]+".\n" });
    arr = m_indexes(punish);
    for (i=0; i<sizeof(arr); i++)
    {
        name = explode(arr[i], "#")[0];
        p = explode(arr[i], "#")[1];
        for(j=0; j<sizeof(punish[arr[i]]); j++)
            if(tpname == punish[arr[i]][j][0])
                vvv += ({ punish[arr[i]][j][1]+" on punishment no. "+p+
                          " for "+name+".\n" });
    }
    if (!sizeof(vvv))
    {
        write("You have not voted on anything.\n");
    }
    else
    {
        write("You have voted:\n");
        for(i=0; i<sizeof(vvv); i++)
            write(vvv[i]);
    }
    return 1;
}

int
punish(string str)
{
    string name;
    int p;

    if ((!str) || (sscanf(str, "%s %d", name, p) != 2))
    {
        NF("Proper syntax is:\n"+
           "  'punish <name> <num>'\n"+
           "where <num> is a number of punishment.\n");
        return 0;
    }
    if (!can_punish(TP))
    {
        write("You can't propose a punishment.\n");
        return 1;
    }
    name = CAP(name);
    if (!aa_member(name))
    {
        write(name+" is not member of the army.\n");
        return 1;
    }
    if ((p < 1) || (p > 6))
    {
        write("There is no punishment no. "+p+".\n");
        return 1;
    }
    if (!ok_punish(name, p))
        return 1;    /* message was generated with test */
    punish += ([ name+"#"+p : ({ }) ]);
    dates += ([ name+"#"+p : ({ time(), TP->query_name() }) ]);
    write("You proposed to punish "+name+" with punishment no. "+p+".\n");
    seteuid(getuid());
    save_object(SAVE_FILE);
    return 1;
}

int
council(string str)
{
    int p;

    if (!str)
    {
        NF("Syntax: 'council <num>'\n");
        return 0;
    }
    p = atoi(str);
    if ((p < 1) || (p > 5))
    {
        NF("Proper syntax is: 'council <num>'\n"+
           "where <num> is number of position in council (1-5) "+
           "you want to start election for.\n");
        return 0;
    }
    if (!can_council(TP, p))
    {
        write("You can't start election for council position no. "+p+".\n");
        return 1;
    }
    c_vote += ([ p : ({ }) ]);
    c_apply += ([ p : ({ }) ]);
    c_dates += ([ p : ({ time(), TP->query_name() }) ]);
    write("You started election for council position no. "+p+".\n");
    seteuid(getuid());
    save_object(SAVE_FILE);
    return 1;
}

int
apply(string str)
{
    string name = TP->query_name();
    int p, i, *ind;

    if (!aa_member(name))
    {
        NF("Only members can apply here.\n");
        return 0;
    }
    if ((!str) || (sscanf(str, "for council %d", p) != 1))
    {
        NF("Syntax is: 'apply for council <num>'\n");
        return 0;
    }
    if (member_array(p, m_indexes(c_apply)) == -1)
    {
        write("No applications are taken for position no. "+p+" now.\n");
        return 1;
    }
    if (c_dates[p][0]+WEEK < time())
    {
        write("Sorry, application period is over.\n");
        return 1;
    }
    if ((member_array(name, m_indexes(c_list)) != -1) && (c_list[name] != p))
    {
        write("You can apply only for your own position.\n");
        return 1;
    }
    ind = m_indexes(c_apply);
    for (i=0; i<sizeof(ind); i++)
        if (member_array(name, c_apply[ind[i]]) != -1)
        {
            write("You have already applied for position no. "+ind[i]+".\n");
            return 1;
        }
    c_apply[p] += ({ name });
    write("You applied for council position no. "+p+".\n");
    seteuid(getuid());
    save_object(SAVE_FILE);
    return 1;
}

int
withdraw(string str)
{
    string name = TP->query_name();
    int i, *ind = m_indexes(c_apply);

    if (str != "application")
    {
        NF("Withdraw what?\n");
        return 0;
    }
    for (i=0; i<sizeof(ind); i++)
        if (member_array(name, c_apply[ind[i]]) != -1)
        {
            write("You withdraw your application for position no. "+
                  ind[i]+".\n");
            c_apply[ind[i]] -= ({ name });
            seteuid(getuid());
            save_object(SAVE_FILE);
            return 1;
        }
    write("You have not applied for anything.\n");
    return 1;
}

int
vote_council(string name, int p)
{
    int i;

    if (member_array(p, m_indexes(c_vote)) == -1)
    {
        write("There is no voting for council position no. "+p+" now.\n");
        return 1;
    }
    if (c_dates[p][0]+WEEK > time())
    {
        write("We are still taking applications for this position.\n"+
              "You can vote after "+ctime(c_dates[p][0]+WEEK)+".\n");
        return 1;
    }
    if (c_dates[p][0]+WEEK+WEEK < time())
    {
        write("Sorry, the voting period is over.\n");
        return 1;
    }
    if (member_array(name, c_apply[p]) == -1)
    {
        write(name+" has not applied for council position no. "+p+".\n");
        return 1;
    }
    for (i=0; i<sizeof(c_vote[p]); i++)
        if (c_vote[p][i][0] == TP->query_name())
        {
            c_vote[p] -= ({ c_vote[p][i] });
            c_vote[p] += ({ ({ TP->query_name(), name, rank_no(TP)+2 }) });
            write("You changed your vote on council position no. "+p+
                  " to "+name+".\n");
            seteuid(getuid());
            save_object(SAVE_FILE);
            return 1;
        }

    c_vote[p] += ({ ({ TP->query_name(), name, rank_no(TP)+2 }) });
    write("You voted for "+name+" for council position no. "+p+".\n");
    seteuid(getuid());
    save_object(SAVE_FILE);
    return 1;
}

int
vote_punish(string name, int p, string v)
{
    int i;

    if (member_array(name+"#"+p, m_indexes(punish)) == -1)
    {
        write("There is no voting on punishment no. "+p+" for "+name+".\n");
        return 1;
    }
    if (!can_vote_pun(TP, p))
    {
        write("You have no right to vote on this punishment.\n");
        return 1;
    }
    if (dates[name+"#"+p][0]+WEEK < time())
    {
        write("I am sorry. Voting period is over.\n");
        return 1;
    }
    if ((v != "yes") && (v != "no"))
    {
        write("You can vote only 'yes' or 'no' here.\n");
        return 1;
    }
    for (i=0; i<sizeof(punish[name+"#"+p]); i++)
        if (punish[name+"#"+p][i][0] == TP->query_name())
        {
            punish[name+"#"+p] -= ({ punish[name+"#"+p][i] });
            punish[name+"#"+p] += ({ ({TP->query_name(), v}) });
            write("You changed your vote on punishment no. "+p+" for "+
                  name+" to '"+v+"'.\n");
            seteuid(getuid());
            save_object(SAVE_FILE);
            return 1;
        }

    punish[name+"#"+p] += ({ ({TP->query_name(), v}) });
    write("You voted '"+v+"' on punishment no. "+p+" for "+name+".\n");
    seteuid(getuid());
    save_object(SAVE_FILE);
    return 1;
}

int
vote(string str)
{
    string name, v;
    int p;

    if (!aa_member(TP->query_name()))
    {
        NF("Only members can vote here.\n");
        return 0;
    }
    if (!str)
    {
        NF("Try vote something.\n");
        return 0;
    }
    if (sscanf(str, "council %d %s", p, name) == 2)
        return vote_council(CAP(name), p);
    if (sscanf(str, "punish %s %d %s", name, p, v) == 3)
        return vote_punish(CAP(name), p, v);
   
    NF("Proper syntax is:\n"+
       "     'vote punish <name> <num> <yes/no>'\n"+
       "or:  'vote council <num> <name>'\n");
    return 0;
}

/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

/*
 * Function name: make_old_punishment
 * Description:   This function sets up punishments that last for a while.
 * Arguments:     tp - object to be punished
 *                p_time - ({ pun_number, time_it_started })
 */
private void
make_old_punishment(object tp, mixed p_time)
{
    int p = p_time[0];
    int t = p_time[1];

    if (t+WEEK+WEEK < time())
    {
        punished[tp->query_name()] -= ({ ({ p, t }) });
        return;
    }
    tp->add_prop(S_C_PUN, 1);
    if ((p>1) && (t+TEN_DAYS > time()))
        tp->add_prop(S_C_PUN, 2);
    if ((p>2) && (t+WEEK > time()))
        tp->add_prop(S_C_PUN, 3);
}

/*
 * Function name: make_new_punishment
 * Description:   This is to set punishment for the first time and also
 *                to execute punishments that do not last for some time.
 * Arguments:     tp - object to be punished
 *                p - punishment number
 */
private void
make_new_punishment(object tp, int p)
{
    string name = tp->query_name();

    tp->catch_msg("You are being punished by punishment no. "+p+".\n");
    to_be_punished[name] -= ({ p });
    if (p == 4) beating_on_head(tp);
    if (p < 5)
    {
        make_old_punishment(tp, ({ p, time() }) );
        if(member_array(name, m_indexes(punished)) == -1)
            punished[name] = ({  });
        punished[name] += ({ ({ p, time() }) });
        return;
    }
    if (p == 5) executing(tp);
    if (p == 6) rejecting_from_army(tp);
}

/*
 * Function name: set_up_punishments
 * Description:   This function is called from AA shadow when player logs in.
 *                If he is to be punished then proper procedure follows.
 * Arguments:     tp - object we want to set punishments for
 */
void
set_up_punishments(object tp)
{
    string name = tp->query_name();
    int i;

    /* first check old punishments and set them up... */
    if (member_array(name, m_indexes(punished)) != -1)
        for (i=0; i<sizeof(punished[name]); i++)
            make_old_punishment(tp, punished[name][i]);

    /* now check new punishments and do them too... */
    if (member_array(name, m_indexes(to_be_punished)) != -1)
        for (i=0; i<sizeof(to_be_punished[name]); i++)
            make_new_punishment(tp, to_be_punished[name][i]);
}

/*
 * Function name:
 * Description:
 * Arguments:
 */
private void
executing(object tp)
{
    seteuid(getuid());
    write_file(THIS_DIR+"PUNISH_LOG", tp->query_name()+" executed. "+
                                    ctime(time())+"\n");
    tp->catch_msg("Suddenly Dark Lord appears and smashes your "+
                  "head to the pulp.\n");
    tell_room(ENV(tp), "Suddenly Dark Lord appears and smashes "+QTNAME(tp)+
                       "'s head to the pulp.\n", tp);
    tp->heal_hp(-10-tp->query_hp());
    tp->do_die(TO);
}

/*
 * Function name:
 * Description:
 * Arguments:
 */
private void
rejecting_from_army(object tp)
{
    seteuid(getuid());
    write_file(THIS_DIR+"PUNISH_LOG", tp->query_name()+" rejected from army. "+
                                    ctime(time())+"\n");
    (THIS_DIR+"chapel")->do_leave(tp);
}

/*
 * Function name:
 * Description:
 * Arguments:
 */
private void
beating_on_head(object tp)
{
    int *skills, i;

    seteuid(getuid());
    write_file(THIS_DIR+"PUNISH_LOG", tp->query_name()+" beated on head. "+
                                    ctime(time())+"\n");

    tp->catch_msg("\nSuddenly Dark Lord appears and points at you.\n"+
        "Dark Lord says: Punnish "+HIM(tp)+
        "!!!\n"+"\nMany angry warriors jump at you "+
        "and beat you with their nasty clubs...\n"+
        "Fortunatelly you lose consciousness so you don't feel every hit.\n\n"+
        "When you wake up you notice that you have terrible headache "+
        "and that you feel less skillful.\n\n");
    tell_room(ENV(tp), "\nSuddenly King Angmar appears and points at "+
        QTNAME(tp)+".\n"+
        "King Angmar says: Punnish "+HIM(tp)+
        "!!!\n"+"\nMany angry warriors jump at "+
        QTNAME(tp)+" and beat "+HIM(tp)+" with their nasty clubs...\n"+
        QCTNAME(tp)+" is soon knocked down but the cruel warriors continue "+
        "beating "+HIM(tp)+", aiming mainly for "+HIS(tp)+" head.\n"+
        "After they are satisfied they leave, leaving "+
        QTNAME(tp)+" laying on the floor...\n\n"+
        "After a long time "+QTNAME(tp)+" regains his sense and touches "+HIS(tp)+
        " sore head. "+CAP(HE(tp))+" sure regrets what "+HE(tp)+
        " has done!\n\n", tp);
    tp->set_max_headache(MAX(1000, tp->query_max_headache()));
    tp->set_headache(tp->query_max_headache());

    skills = tp->query_all_skill_types();
    for (i=0; i<sizeof(skills); i++)
    {
        if ((skills[i]<1000) || (skills[i]==138000) || (skills[i]==138001))
        {
            tp->set_skill(skills[i], tp->query_skill(skills[i]) - random(20));
            if (tp->query_skill(skills[i]) < 1) tp->remove_skill(skills[i]);
        }
    }
}

