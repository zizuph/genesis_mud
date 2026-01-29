/* Stralle @ Genesis 011230
 *
 * The standard PoT npc.
 *
 *  Remembering encounters is based on the Shadow Union std npc by Cirion.
 *
 * Features:
 *  o Versatile busy states
 *  o Remembering encounters with livings
 *  o Notifying a random logged in member when attacked
 *  o Notifying logged in members when killed
 *
 *  Revisions:
 *    Lucius, Aug 2016:  Fixed issues with greeted flag not being set properly
 *
 */
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../../guild.h"
#include "../../spells.h"
#include "npc.h"
#include DL_CLOCK
#include <files.h>
#include <language.h>
#include <macros.h>
#include <composite.h>
#include <money.h>

inherit AM_FILE

/* Undef this to have the npc not react to wizards when it shouldn't
 */
#undef TEST
#undef KRYNN_BUGGY

/* "name" : ({ (int)known, (int)when, (int)greeted, (string)shortdesc,
 *             (string)longdesc })
 */
private mapping gMet = ([ ]);
int gBusy = 0, gPriest = 1;
/*
 */

/* Function name: set_busy
 * Description:   Sets a busy state in the npc. The npc can be busy
 *                in several different ways why an argument of B_*
 *                is necessary.
 * Arguments:     int state - the busy state to set to on
 */
void
set_busy(int state)
{
    gBusy |= state;
}

/* Function name: unset_busy
 * Description:   Unsets the previously set busy state. Refer to
 *                set_busy for more information.
 * Arguments:     int state - the busy state to set to off
 */
void
unset_busy(int state)
{
    gBusy &= ~(state);
}

/* Function name: query_busy
 * Description:   Checks if the npc is busy. Refer to set_busy for
 *                for more information
 * Arguments:     int state - the busy state to check
 * Returns:       int - 1/0, true or not.
 */
int
query_busy(int state)
{
    return !(!(gBusy & state));
}

/* Function name: meet_living
 * Description:   Called from init_living() to register a living we
 *                encounter as met.
 * Arguments:     object who - who we met
 */
void
meet_living(object who)
{
    int known, greeted, x;
    string *list, oldest;
    
    if (!CAN_SEE(TO, who) || !CAN_SEE_IN_ROOM(TO))
        return;

#ifndef TEST
    if ((who->query_wiz_level()) ||
        wildmatch("*jr", who->query_real_name()))
        return;
#endif

    if (gMet[who->query_real_name()])
    {
        if (gMet[who->query_real_name()][M_KNOWN])
            known = 1;
        if (gMet[who->query_real_name()][M_GREETED])
            greeted = 1;
    }

    if (who->query_guild_name_occ() == GUILD_NAME)
        known = 1;
    
    gMet[who->query_real_name()] = allocate(M_SIZEOF);
    gMet[who->query_real_name()][M_KNOWN] = known;
    gMet[who->query_real_name()][M_WHEN] = time();
    gMet[who->query_real_name()][M_TIME] = CLOCK->query_estimate_time_of_day_string();
    gMet[who->query_real_name()][M_GREETED] = greeted;
    gMet[who->query_real_name()][M_SHORT] = who->query_nonmet_name();
    gMet[who->query_real_name()][M_LONG] = who->long(TO);

    /* We can only remember a set number of encounters
     * Do FIFO on the list
     */
    if (m_sizeof(gMet) > MAX_REMEMBER)
    {
        list = m_indices(gMet);
        for (x = 0, oldest = list[MAX_REMEMBER] ; x < (MAX_REMEMBER + 1) ;
            x++)
        {
            if (gMet[list[x]][M_WHEN] < gMet[oldest][M_WHEN])
                oldest = list[x];
        }
        
        gMet = m_delete(gMet, oldest);
    }
}

mapping
debug()
{
    return gMet;
}

int
query_met_living(string who)
{
    return (pointerp(gMet[who]) && gMet[who][M_KNOWN] ? 1 : 0);
}

string *
present2past_tense(string desc, string who)
{
    string *arr;
    int x;

    desc = implode(explode(desc, " is wearing "), " wore ");
    desc = implode(explode(desc, " is wielding "), " wielded ");
    desc = implode(explode(desc, " wears "), " wore ");
    desc = implode(explode(desc, " is "), " was ");
    desc = implode(explode(desc, " has "), " had ");
    desc = implode(explode(desc, " looks "), " looked ");
    desc = implode(explode(desc, " seems "), " seemed ");
    desc = implode(explode(desc, " are "), " were ");
    desc = implode(explode(desc, " presenting "), " who presented ");
    desc = implode(explode(desc, " bears "), " bore ");
    arr = explode(desc, "\n");

    if (!gMet[who][M_KNOWN])
        for (x = sizeof(arr) - 1 ; x >= 0 ; x--)
            if (wildmatch("*" + who + "*", lower_case(arr[x])))
                arr = exclude_array(arr, x, x);

    return arr;                
}

/* Function name: parse_name
 * Description:   Parses a string and returns a name of someone we have met.
 *                For instance 'stralle', 'blue-eyed human', etc
 * Arguments:     string who - the name or [parts of] shortdesc to parse
 * Returns:       string - the name of the person or 0 if not met
 */
string
parse_name(string who)
{
    string *arr, *arr2, *tmp;
    int x, y, size, size2, flag;

    if (gMet[who] && gMet[who][M_KNOWN])
        return who;
    
    arr = m_indices(gMet);
    arr2 = explode(who, " ");
    size2 = sizeof(arr2);
    
    for (x = 0, size = sizeof(arr) ; x < size ; x++)
    {
        tmp = explode(gMet[arr[x]][M_SHORT], " ");
        for (y = 0, flag = 1 ; y < size2 ; y++)
        {
            if (member_array(arr2[y], tmp) < 0)
            {
                flag = 0;
            }
        }
        
        if (flag)
            return arr[x];
    }
    
    return 0;
}

int
sort_when_met(string a, string b)
{
    /* We want reverse order */
    if (gMet[a][M_WHEN] < gMet[b][M_WHEN])
        return 1;
    else if (gMet[a][M_WHEN] > gMet[b][M_WHEN])
        return -1;
    else
        return 0;
}

void
list_met(object asker)
{
    string *list;
    int x, size;

    /* Should only happen if called from outside our environment.
     */
    if (!m_sizeof(gMet))
    {
        command("psay I have yet to meet anyone today.");
        return;
    }

    list = sort_array(m_indices(gMet), "sort_when_met");
    for (x = 0, size = sizeof(list) ; x < size ; x++)
    {
        if (list[x] == asker->query_real_name())
            list[x] = "you";
        else if (gMet[list[x]][M_KNOWN])
            list[x] = capitalize(list[x]);
        else
            list[x] = LANG_ADDART(gMet[list[x]][M_SHORT]);
    }

    if (sizeof(list) == 1)
        command("psay Today I have only met " + list[0] + ".");
    else
        command("psay Today I have met " + COMPOSITE_WORDS(list) + ".");
}

string
desc_time(string who)
{
    return gMet[who][M_TIME];
}

string
desc_when(string who)
{
    switch ((time() - gMet[who][M_WHEN]) / 60)
    {
        case 0..2:
            return "just now";
            break;
        case 3..5:
            return "very recently";
            break;
        case 6..10:
            return "quite recently";
            break;
        case 11..20:
            return "fairly recently";
            break;
        case 21..30:
            return "recently";
            break;
        case 31..45:
            return "a little while ago";
            break;
        case 46..120:
            return "a while ago";
            break;
        case 121..180:
            return "some time ago";
            break;
        default:
            return "a long time ago";
            break;
    }
}

varargs void
delayed_desc_met(object asker, string *arr, int round = 0)
{
    if (environment(asker) != environment())
    {
        command("mumble something about busy people.");
        unset_busy(B_SPEAKING);
        return;
    }

    if (round < sizeof(arr))
    {
        command(arr[round]);
        set_alarm(1.0 + itof(random(3)), 0.0,
            &delayed_desc_met(asker, arr, round + 1));
    }
    else
        unset_busy(B_SPEAKING);
}
        
void
desc_met(object asker, string who)
{
    string name, *descs, *arr;
    int x, size;
    
    if (!m_sizeof(gMet))
    {
        command("psay I have yet to meet anyone today.");
        return;
    }

    name = parse_name(who);
    if (!name)
    {
        command("psay I do not recall meeting any " + who + " today.");
        return;
    }

    descs = present2past_tense(gMet[name][M_LONG], name);
    arr = ({"psay It was " + desc_time(name) + " when " + desc_when(name) +
        " I met this person."});

    for (x = 0, size = sizeof(descs) ; x < size ; x++)
    {
        if (!(x % 4))
            arr += ({ ({"ponder", "think the encounter.", "scratch", "brood",
                "hmm"})[random(sizeof(5))] });

        arr += ({ "psay " + descs[x] });
    }
    
    arr += ({ "psay That is all I can remember." });
    arr += ({ "psay I hope this has been useful." });

    set_busy(B_SPEAKING);
    
    set_alarm(1.0, 0.0, &delayed_desc_met(asker, arr));
}

void
unset_priest()
{
    gPriest = 0;
}

void
update_spells()
{
    present(MEDALLION_ID, TO)->update_spells();
}

void
clone_ingredients()
{
    if (TO->query_skill(PS_SPELLS) & PTELL_ID)
        MONEY_MAKE(20, "copper")->move(TO);
}

void
clone_guild_items()
{
    clone_object(POTSHADOW)->add_occ_shadow(TO);
    if (gPriest)
        set_alarm(4.0, 0.0, &update_spells());
}

void
arm_me()
{
    setuid();
    seteuid(getuid(this_object()));

    if (gPriest)
    {
        clone_ingredients();
        clone_guild_items();
    }
}

void
unseen_hook()
{
    command("say What? Who's there?");
}

void
do_greet(object who)
{
    if (!objectp(who))
        return;

    string name = who->query_real_name();

    /* The player could go back and forth several times, spawning
     * several trigs and he could have left.
     */
    if ((environment(TO) != environment(who) || !CAN_SEE(TO, who)) ||
        (gMet[name] && gMet[name][M_GREETED]))
        return;
        
    command("pgreet " + OB_NAME(who));

    if (gMet[name])
	gMet[name][M_GREETED] = 1;
}

/* Function name: create_pot_monster
 * Description:   The create function. As create_krynn_monster is nomask
 *                use this one instead
 */
void
create_pot_monster()
{
}

/* Function name: create_krynn_monster
 * Description:   Sets certain predefaults and postdefaults.
 */
nomask void
create_krynn_monster()
{
    add_name("priest");
    set_introduce(1);
    
    set_skill(PS_SPELLS, PTELL_ID);
    
    create_pot_monster();

    set_dont_answer_unseen(1);
    
    add_ask(" [to] [list] 'people' / 'met' / 'encountered' / 'encounters' ",
        "answer_met", 2);
    add_ask(" [to] 'describe' [the] %s ", "answer_met", 2);
}

public void
init_living()
{
    ::init_living();

    /* Register TP as met to us. We must do this as first thing or
     * we will not greet members amongst others.
     */
    meet_living(TP);

    /* Automagically add this npc as known to our members and greet them
     */
    if (TP->query_guild_name_occ() == GUILD_NAME && interactive(TP))
    {
	string name = TP->query_real_name();

        if (TO->query_real_name() != "priest")
            TP->add_introduced(this_object()->query_real_name());

        if (gMet[name] && !gMet[name][M_GREETED])
            set_alarm(1.0 + itof(random(5)), 0.0, &do_greet(TP));
    }
}

#ifdef KRYNN_BUGGY
/* Someone has seen fit to comment out the following in the
 * /d/Krynn/std/monster file...
 */
/* 
 * Function name: catch_question
 * Description:   This function is called in each living being someone asks a
 *                question to.
 * Arguments:     question - The question as put
 */
public void
catch_question(string question)
{
    int i,j;
    mixed ret_arr, arg1, arg2, arg3, arg4, arg5;
    
    if (dont_answer_unseen && (!TP->check_seen(this_object()) ||
        !CAN_SEE_IN_ROOM(this_object())))
    {
        set_alarm(itof(random(3) + 1), 0.0, "unseen_hook");
        return;
    }
    
    if (query_busy(B_SPEAKING))
    {
        command("say to " + OB_NAME(TP) + " Please don't interrupt me!");
        return;
    }

    if (query_attack())
    {
        command("gaze annoyedly " + OB_NAME(TP));
        return;
    }

    i = strlen(question);
    if (question[i - 1] == "."[0] || question[i - 1] == "?"[0])
        question = extract(question, 0, i - 2);
    
    posed_question = lower_case(question);

//    return ::catch_question(posed_question);
    
    for (i = 0; i < sizeof(ask_arr); i++)
        if (member_array(posed_question, ask_arr[i][0]) >= 0)
        {
            set_alarm(itof(random(4)), 0.0, &answer_question(
                  ({ ask_arr[i][1], TP }), ask_arr[i][2] ));
            return;
        }

    for (i = 0; i < sizeof(ask_arr); i++)
        for(j = 0; j < sizeof(ask_arr[i][0]); j++)
            if (parse_command(posed_question, environment(), ask_arr[i][0][j],
                arg1, arg2, arg3, arg4, arg5))
            {
                set_alarm(itof(random(4)), 0.0, &answer_question(
                       ({ ask_arr[i][1], TP, arg1,
                          arg2, arg3, arg4, arg5}), ask_arr[i][2] ));
                return; 
            }

    /* If the question cannot be answered, log the question */
    log_file("asks",ctime(time())[4..15] + " " +
        TP->query_name() +
        " asked "+ file_name(TO) +
        ": " + question + "\n",200000);

    if (default_answer)
        set_alarm(itof(random(4)), 0.0, 
            &answer_question(({ default_answer }), 0 )); 
    else
        return ::catch_question(posed_question);

}

/*
 * Function name: answer_question
 * Description:   This function is called after a short delay when this mobile
 *                wants to react to a question
 * Arguments:     An array ({ string msg, int cmd })
 */
public void
answer_question(mixed arr, int cmd)
{
    object env;
    string str;

    arr += ({ 0,0,0,0,0,0,0 }); /* make sure the array is long enough */

    if ((env = environment(this_object())) == environment(TP) ||
        env == TP ||
        (not_here_func &&
            call_other(this_object(), not_here_func, TP)))
    {
        if (cmd == 2)
        {
            str = call_other(this_object(), arr[0], arr[1],
                arr[2], arr[3], arr[4], arr[5], arr[6]);
            command(str);
        }
        else
        {
            str = this_object()->check_call(arr[0], TP);

            if (cmd)
                command(str);
            else if (atoi(str) == 0)
                tell_object(TP,str);
        }
    }
}
#else
 
/* Function name: catch_question
 * Description:   Redefined to implement busy states
 * Arguments:     string question - the question posed
 */
public void
catch_question(string question)
{
    if (query_busy(B_SPEAKING))
    {
        command("say to " + OB_NAME(TP) + " Please don't interrupt me!");
        return;
    }

    if (query_attack())
    {
        command("gaze annoyedly " + OB_NAME(TP));
        return;
    }
    
    return ::catch_question(question);
}
#endif

/* Function name: answer_met
 * Description:   Answers questions about encounters
 * Arguments:     object asker - who asked us
 *                string who   - who to ask about if any
 * Returns:       string - the string to write on the socket
 */
varargs string
answer_met(object asker, string who)
{
    /* Don't answer non-members
     */
    if (TP->query_guild_name_occ() != GUILD_NAME &&
        member_array(TP->query_real_name(),
        SECURITY->query_guild_masters("pot")) < 0)
    {
        answer_question(({ query_default_answer() }), 0);
        return "";
    }

    /* There is a three second delay from which the npc is cloned til
     * he has the necessary soul to use the command psay
     */
    if (member_array(GUILD_CMDSOUL, query_cmdsoul_list()) < 0)
    {
        command("say to " + OB_NAME(TP) + " You have caught me in a " +
            "bad moment. Please allow me just a blink of an eye to " +
            "compose myself.");
        return "";
    }

    /* No who signifies the asker wants a list of the ones this npc
     * has met
     */
    if (!who)
    {
        list_met(asker);
        return "";
    }

    desc_met(asker, who);
    return "";
}

mixed
oke_to_move(string exit)
{
    if (query_busy(B_WAITING) || query_busy(B_SPEAKING))
        return 0;
    
    return ::oke_to_move(exit);
}

/* Function name: do_introduce
 * Description:   Do the actual introduction. Called by an alarm
 *                from react_introduce
 * Arguments:     string who - who introduced if any
 */
void
do_introduce(string who)
{
    if (who)
        command("introduce me to " + who);
    else
        command("introduce me");
    
    unset_busy(B_WAITING);
}

/* Function name: react_introduce
 * Description:   Called whenever someone introduces in our environment
 * Arguments:     mixed who - who introduced if any
 */
varargs void
react_introduce(string who)
{
    if (!strlen(who) || !present(who, environment()))
        return;

    set_busy(B_WAITING);
    
    if (query_introduce())
        set_alarm(2.0, 0.0, &do_introduce(who));

    if (gMet[who] && !gMet[who][M_KNOWN])
        gMet[who][M_KNOWN] = 1;
}

/* Function name: desc_surrounding
 * Description:   Modifies the short desc of a room for use in speach.
 *                Removes the capitalisation of the first word and adds
 *                a 'by' or 'the' before the desc when suited or if
 *                not called by attacked_by() and if where == environment()
 *                changes the short desc to 'right here'.
 * Arguments:     object where - what room, default where the npc stands
 * Returns:       string - the modified short desc.
 */
varargs string
desc_surrounding(object where = environment())
{
    string *common_art = ({ "a", "an", "the" });
    string *common_prep = ({ "up", "on", "at", "in", "outside",
        "inside", "above", "below", "beside", "under" });
    string *arr, short_desc = where->short();
    
    if (short_desc)
    {
        arr = explode(short_desc + " ", " ");
        if (member_array(lower_case(arr[0]), common_art) >= 0)
        {
            short_desc = "by " + lower_case(arr[0]) + " " +
                implode(arr[1..sizeof(arr) - 1], " ");
        }
        else if (member_array(lower_case(arr[0]), common_prep) >= 0)
        {
            short_desc = "by the " + lower_case(arr[0]) + " " +
                implode(arr[1..sizeof(arr) - 1], " ");
        }
        else
        {
            short_desc = lower_case(arr[0]) + " " +
                implode(arr[1..sizeof(arr) - 1], " ");
        }
    }
    else
    {
        short_desc = "in a non-descript place";
    }

    switch (calling_function())
    {
        case "attacked_by":
            return short_desc;
            break;
        default:
            if (where != environment())
                return short_desc;
            else
                return "right here";

            break;
    }
}

/* Function name: desc_living
 * Description:   Npcs know everyone which is why we need this pseudo
 *                met/nonmet routine
 * Arguments:     object who - who to check
 */
string
desc_living(object who)
{
    if (gMet[who->query_real_name()] && gMet[who->query_real_name()][M_KNOWN])
        return who->query_name();
    else
        return LANG_ADDART(who->query_nonmet_name());
}

/* Function name: attacked_by
 * Description:   Called when we are attacked.
 * Arguments:     object attacker - the one who attacked us
 */
void
attacked_by(object attacker)
{
    object *priests = filter(users(), &operator(==)(GUILD_NAME) @
        &->query_guild_name_occ());
    
    if (sizeof(priests))
        command("cast ptell " +
            priests[random(sizeof(priests))]->query_real_name() + " Help! " +
            "I am under attack by " + desc_living(attacker) + " " +
            desc_surrounding() + "!");

    attacker->add_prop(NERAKA_I_ATTACKED_TEMPLE, 1);
    ::attacked_by(attacker);
}

#ifdef 0
int
check_health()
{
    return (100 * query_hp()) / query_max_hp();
}

void
check_status()
{
    /* He would require ingredients and should really npcs show off
     * spells in a rather secretive guild? The future will decide.
     */
    if ((!query_attack() && check_health() < 100) || check_health() <= 17)
        command("pheal");

    // heal some mana :)
    add_mana(25);
}
#endif

int
filter_death(object ob)
{
    if (ob->query_guild_name_occ() == GUILD_NAME &&
        ob->query_priest_level() >= GUILD_LEVEL_PRIEST &&
        present(MEDALLION_ID, ob))
        return 1;

    return 0;
}

/* Function name: do_die
 * Description:   Handles death
 * Arguments:     object killer - the one who killed us
 */
void
do_die(object killer)
{
    object ob;

    seteuid(getuid());
    
    if (ob = present(MEDALLION_ID))
    {
        command("emote clutches " + HIS(TO) + " " + LANG_SHORT(ob) +
            ", a pale expression on " + HIS(TO) + " face.\n");
        filter(users(), filter_death)->catch_tell("Your medallion " +
            "twitches suddenly. A feeling of loss enters your mind " +
            "briefly.\n");
    }

    A_KILL_LOG("pot/npckills", capitalize(TO->query_real_name()), killer);
    
    ::do_die(killer);
}
