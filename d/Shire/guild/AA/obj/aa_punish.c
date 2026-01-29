#pragma no_clone
#pragma no_inherit
#pragma strict_types
#pragma save_binary

#include <std.h>
#include <macros.h>
#include "../guild.h"

#define PERCENT     30
#define SAVE_FILE   (AA_DIR+"save_files/AA_PUNISH")

/*************************************************************************
 * Prototypes
 */
private void beating_on_head(object tp);
private void rejecting_from_army(object tp);
private void executing(object tp);
private void check_punish();
/**********************************************************************
 * Global variables, they will be saved.
 */
private mapping To_be_punished  = ([ ]);
/*
 *  To_be_punished = ([ name : ({ p1, p2, ... }), ... ]);
 */
private mapping Punished        = ([ ]);
/*
 *  Punished = ([ name : ({ ({ p, time }), ... }), ... ]);
 */
private mapping Punish  = ([ ]);
/*
 *   Punish = ([
 *       "name"+"#"+p : ({ ({"name1",vote}), ({"name2",vote}),...}),
 *      ...   ]);
 */
private mapping Dates = ([ ]);
/*
 *  Dates = ([ "name"+"#"+p : ({ date, who }), ... ]);
 */

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
        To_be_punished = ([ ]);
        Punished = ([ ]);
        Punish = ([ ]);
        Dates  = ([ ]);
    }
    set_alarm(0.0, 0.0, check_punish);
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
    string s = "Result of voting on punishment no. "+p+" for "+name+":\n\n";
    if (yes > no)
        s += "        "+name+" will be punished!\n\n";
    else
        s += "        "+name+" will NOT be punished!\n\n";
    s += "                  Emissary of the Dark Lord\n\n";
    s += "P.S. Results of voting:\n\n";
    s += "      Voted: "+ayes+" yes,  "+ano+" no";
    if ((ayes != yes) || (ano != no))
        s += "      Counted: "+yes+" yes,  "+no+" no";
    s += ".\n";
    FIXEUID;
    (AA_VOTE_ROOM->get_board())->create_note("VOTING RESULT", "Emissary", s);
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

    if (member_array(str, m_indexes(Punish)) == -1) return;

    arr = explode(str, "#");
    name = arr[0];
    p = atoi(arr[1]);

    /* first expected number of votes */
    expected = 5; /* council - O.K... they may be counted twice but... */
    expected += sizeof(AA_RANKS_OBJ->query_players_with_rank_no(6));
    expected += sizeof(AA_RANKS_OBJ->query_players_with_rank_no(5));
    if(p > 1)
        expected += sizeof(AA_RANKS_OBJ->query_players_with_rank_no(4));
    if(p > 2)
        expected += sizeof(AA_RANKS_OBJ->query_players_with_rank_no(3));
    if(p > 3)
        expected += sizeof(AA_RANKS_OBJ->query_players_with_rank_no(2));
    if(p > 4)
        expected += sizeof(AA_RANKS_OBJ->query_players_with_rank_no(1));

    expected = (expected * PERCENT) / 100;
    yes = 0; no = 0; ayes = 0; ano = 0;

    /* count all votes */
    for (i=0; i<sizeof(Punish[str]); i++)
    {
        if(Punish[str][i][1] == "yes")
        {
           ayes++;
        }
        else ano++;
    }
    if (sizeof(Punish[str]) >= expected) /* all votes count */
    {
        yes = ayes;
        no = ano;
    }
    if (yes == no) /* only votes of council count */
    {
        yes = 0;
        arr = AA_COUNCIL_OBJ->query_council();
        for (i=0; i<sizeof(Punish[str]); i++)
            if (member_array(Punish[str][i][0], arr) != -1)
                if (Punish[str][i][1] == "yes")
                    yes++;
        no = 5 - yes;
    }

    report_punish(name, p, sizeof(Punish[str]), yes, no, ayes, ano);

    if (yes > no)
    {
        if(member_array(name, m_indexes(To_be_punished)) == -1)
        {
            To_be_punished += ([ name : ({ p }) ]);
        }
        else if(member_array(p, To_be_punished[name]) == -1)
            To_be_punished[name] += ({ p });

        FIXEUID;
        save_object(SAVE_FILE);
    }
    Punish = m_delete(Punish, str);
}

/*
 * Function name: check_punish
 * Description:   Checks if voting is over (to set_punish) and if player
 *                can be punished again.
 *                Check variables for records containing nonmembers and
 *                throws them out.
 */
private void
check_punish()
{
    mixed arr, tmp;
    int i, j;

    arr = m_indexes(To_be_punished);
    for (i=0; i<sizeof(arr); i++)
        if (!sizeof(To_be_punished[arr[i]]) || !AA_RANKS_OBJ->aa_member(arr[i]))
            To_be_punished = m_delete(To_be_punished, arr[i]);
    arr = m_indexes(Punished);
    for (i=0; i<sizeof(arr); i++)
        if (!sizeof(Punished[arr[i]]) || !AA_RANKS_OBJ->aa_member(arr[i]))
            Punished = m_delete(Punished, arr[i]);
    arr = m_indexes(Punish);
    for (i=0; i<sizeof(arr); i++)
    {
        if (!AA_RANKS_OBJ->aa_member(explode(arr[i], "#")[0]))
        {
            Punish = m_delete(Punish, arr[i]);
        }
        else
        {
            tmp = ({ });
            for (j=0; j<sizeof(Punish[arr[i]]); j++)
                if (!AA_RANKS_OBJ->aa_member(Punish[arr[i]][j][0]))
                    tmp += ({ Punish[arr[i]][j] });
            Punish[arr[i]] -= tmp;
        }
    }
    arr = m_indexes(Dates);
    for (i=0; i<sizeof(arr); i++)
    {
        if (Dates[arr[i]][0]+WEEK < time())
            set_punish(arr[i]);
        if (Dates[arr[i]][0]+MONTH < time())
            Dates = m_delete(Dates, arr[i]);
        if (!AA_RANKS_OBJ->aa_member(explode(arr[i], "#")[0]))
            Dates = m_delete(Dates, arr[i]);
    }

    FIXEUID;
    save_object(SAVE_FILE);
    set_alarm(3600.0, 0.0, check_punish);
}

/*
 * Function name: ann_list
 * Returns:       announcements about punishments
 */
string
ann_list()
{
    string n, p, s = "";
    int i;
    mixed arr = m_indexes(Punish);

    for (i=0; i<sizeof(arr); i++)
        if (Dates[arr[i]][0]+WEEK > time())
        {
            n = explode(arr[i], "#")[0];
            p = explode(arr[i], "#")[1];
            s += Dates[arr[i]][1]+": *VOTE* on punishment "+p+" for "+n;
            s += ". End: "+ctime(Dates[arr[i]][0]+WEEK)[4..18]+".\n";
        }
    return s;
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
        Punished[tp->query_name()] -= ({ ({ p, t }) });
        return;
    }
    tp->add_prop(AA_PUN, 1);
    if ((p>1) && (t+TEN_DAYS > time()))
        tp->add_prop(AA_PUN, 2);
    if ((p>2) && (t+WEEK > time()))
        tp->add_prop(AA_PUN, 3);
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
    To_be_punished[name] -= ({ p });
    if (p == 4) beating_on_head(tp);
    if (p < 5)
    {
        make_old_punishment(tp, ({ p, time() }) );
        if(member_array(name, m_indexes(Punished)) == -1)
            Punished[name] = ({  });
        Punished[name] += ({ ({ p, time() }) });
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
    if (member_array(name, m_indexes(Punished)) != -1)
        for (i=0; i<sizeof(Punished[name]); i++)
            make_old_punishment(tp, Punished[name][i]);

    /* now check new punishments and do them too... */
    if (member_array(name, m_indexes(To_be_punished)) != -1)
        for (i=0; i<sizeof(To_be_punished[name]); i++)
            make_new_punishment(tp, To_be_punished[name][i]);
}

/*
 * Function name:
 * Description:
 * Arguments:
 */
private void
executing(object tp)
{
    FIXEUID;
    tell_room(ENV(tp),
        "Suddenly, the terrible visage of a burning Lidless Red Eye fills"
      + " the entire area, and a deep and penetrating voice speaks: DIE!\n");
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
    FIXEUID;
    (AA_DIR+"rooms/chapel")->do_leave(tp);
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

    FIXEUID;

    tp->catch_msg("\n"
      + "Suddenly, the terrible visage of a burning Lidless Red Eye fills"
      + " the entire area, and a deep and penetrating voice speaks: WRETCH,"
      + " RECEIVE YOUR DUE REWARD!\n"
      + "\nMany angry warriors jump at you "+
        "and beat you with their nasty clubs...\n"+
        "Fortunatelly you lose consciousness so you don't feel every hit.\n\n"+
        "When you wake up you notice that you have terrible headache "+
        "and that you feel less skillful.\n\n");
    tell_room(ENV(tp), "\n"
      + "Suddenly, the terrible visage of a burning Lidless Red Eye fills"
      + " the entire area, and a deep and penetrating voice speaks: WRETCH,"
      + " RECEIVE YOUR DUE REWARD!\n"
      + "\nMany angry warriors jump at "+
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

string
check_votes(string name)
{
    string vvv = "";
    mixed arr = m_indexes(Punish);
    int i,j;

    for (i=0; i<sizeof(arr); i++)
        for(j=0; j<sizeof(Punish[arr[i]]); j++)
            if(name == Punish[arr[i]][j][0])
                vvv += Punish[arr[i]][j][1]+" on punishment no. "+
                       explode(arr[i],"#")[1]+" for "+explode(arr[i],"#")[0]+".\n";
    return vvv;
}

void
start_punish(string name, int p)
{
    if (!AA_RANKS_OBJ->lieut_cap(TP->query_name()) &&
        !AA_COUNCIL_OBJ->is_council(TP->query_name()))
    {
        //write("Only Captain, Lieutenants and Final Judges can propose punishment.\n");
        write("Only Captain, Lieutenants, Warrant Officers and Final Judges can propose punishment.\n");
        return;
    }

    name = CAP(name);
    if (!AA_RANKS_OBJ->aa_member(name))
    {
        write(name+" is not member of the army.\n");
        return;
    }
    if ((p < 1) || (p > 6))
    {
        write("There is no punishment no. "+p+".\n");
        return;
    }
    if((member_array(name+"#"+p, m_indexes(Dates)) != -1) &&
       (Dates[name+"#"+p][0]+MONTH > time()))
    {
        write("This punishment can't be proposed again till "+
              ctime(Dates[name+"#"+p][0]+MONTH)+".\n");
        return;
    }
    Punish += ([ name+"#"+p : ({ }) ]);
    Dates += ([ name+"#"+p : ({ time(), TP->query_name() }) ]);
    FIXEUID;
    save_object(SAVE_FILE);
    write("You proposed to punish "+name+" with punishment no. "+p+".\n");
    return;
}

int
can_vote_pun(object who, int p)
{
}

void
vote_punish(string name, int p, string v)
{
    int i,r;

    if (member_array(name+"#"+p, m_indexes(Punish)) == -1)
    {
        write("There is no voting on punishment no. "+p+" for "+name+".\n");
        return;
    }
    if (Dates[name+"#"+p][0]+WEEK < time())
    {
        write("I am sorry. Voting period is over.\n");
        return;
    }
    if ((v != "yes") && (v != "no"))
    {
        write("You can vote only 'yes' or 'no' here.\n");
        return;
    }
    FIXEUID;
    r = AA_RANKS_OBJ->rank_no(TP);
    if (AA_COUNCIL_OBJ->is_council(TP->query_name()) || (r > 4) ||
        ((r > 3) && (p > 1)) || ((r > 2) && (p > 2)) ||
        ((r > 1) && (p > 3)) || ((r > 0) && (p > 4)) )
    {
        for (i=0; i<sizeof(Punish[name+"#"+p]); i++)
            if (Punish[name+"#"+p][i][0] == TP->query_name())
            {
                Punish[name+"#"+p] -= ({ Punish[name+"#"+p][i] });
                Punish[name+"#"+p] += ({ ({TP->query_name(), v}) });
                save_object(SAVE_FILE);
                write("You changed your vote on punishment no. "+p+" for "+
                      name+" to '"+v+"'.\n");
                return;
            }

        Punish[name+"#"+p] += ({ ({TP->query_name(), v}) });
        save_object(SAVE_FILE);
        write("You voted '"+v+"' on punishment no. "+p+" for "+name+".\n");
        return;
    }
    write("You have no right to vote on this punishment.\n");
}

