/*
 * Example questmaster for bit quests
 * based on /d/Sparkle/area/faerie/npcs/qm.c
 * By Finwe, June 2017
 */

inherit "/std/monster";
inherit "/d/Gondor/common/lib/binbit";

#include "../defs.h"
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define TMP_ASKED_FOR_QUEST  "_example_asked_for_quest"

#define QUESTS  ({  "Find Curly, the NPC.\n", \
                    "Find Thomas, the NPC.\n", \
                    "Find Fred, the NPC.\n", \
                    "Find Larry, the NPC.\n", \
                })

int           check_quest(object note, object tp);
int           accept_quest(string str);
void          do_ask_for_note(object tp);
string        quest_inform();
public int    check_remaining_quests(object who);


void
create_monster()
{
    int i;

    set_race_name("elf");

    set_name("georgette");
    set_adj("noble");
    set_adj("somber");
    set_short("noble somber elf");
    add_name("delegate");
    add_name("chief delegate");
    set_long("This is Georgette. She likes shiny items. Travellers may " +
        "ask her for tasks, and if she has any, she will give them out.\n");


    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);
    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable
    add_prop(LIVE_M_NO_ACCEPT_GIVE,0);

    for (i = 0; i < 5; i++)
        set_base_stat(i, 100 + random(25));

    set_chat_time(40+random(10));

    set_gender(G_FEMALE);

    set_chat_time(60+random(60));
    add_chat("If you are looking for something to do, ask me.");
    add_chat("I love helping travellers.");
    

    add_ask( ({ "tour", "tours", "about tour", "about tours",
                "for tour", "for tours",

                "task", "tasks", "about task", "about tasks",
                "for task", "for tasks",

                "quest", "quests", "about quest", "about quests",
                "for quest", "for quests",

                "job", "jobs", "about job", "about jobs",
                "for job", "for jobs",

                "help", "about help", "for help" }),
        quest_inform);
}


void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
    command("say to " + TP->query_real_name() + " Nice to meet ya!");
    command("shake " + TP->query_real_name() );
}

void
react_intro(object tp)
{
    if (!present(tp, ENV(TO)))
    {
        command("shrug");
        return;
    }
    /* we can be called in response to intro or out of init,
     * so check to be sure we don't intro twice
     */
    command("introduce me to "+tp->query_real_name());
    command("say Welcome to Faerie!");
    return;
}


void
init_living()
{
    object  tp = TP;

    ::init_living();
    if (present(QUEST_NOTE_PROP,tp))
        set_alarm(1.0, 0.0, &do_ask_for_note(tp));
    if (living(tp) && interactive(tp) && CAN_SEE(TO, tp) &&
        !(tp->query_met(query_real_name())))
        set_alarm(2.0 + 5.0 * rnd(), 0.0, &react_intro(tp));

    add_action(accept_quest, "accept");
}


void
return_object(object obj, object to)
{
    string  obname = OB_NAME(obj);

    if (obj->id("coin"))
        return;

    command("say I do not believe I need this. Thank you though.");
    command("give "+obname+" to "+to->query_real_name());
    if (present(obname, TO))
        command("drop "+obname);
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from) || !objectp(obj) || !living(from))
        return;

    if (obj->id(QUEST_NOTE_PROP))
        set_alarm(0.5, 0.0, &check_quest(obj, from));
    else
        set_alarm(0.5, 0.0, &return_object(obj, from));
}


void
do_ask_for_note(object tp)
{
command("say Greetings again!");
command("say Have you completed the quest I gave you?");
command("say If you have, please give me the note."); 
command("smile "+tp->query_real_name());
}

void
reward_quest(object tp, int qno)
{
    int reward;

    set_bin_bits(QUEST_GROUP, QUEST_BIT_START, QUEST_BIT_NBR, tp, qno + 1);
    command("say Thank you. You finished that quest for me!");
    command("shake " + tp->query_real_name());


    switch(qno)
    {
        case FRED_QUEST_NUM:    reward = FRED_QUEST_EXP; break;
        case LARRY_QUEST_NUM:   reward = LARRY_QUEST_EXP; break;
        case THOMAS_QUEST_NUM:  reward = THOMAS_QUEST_EXP; break;
        case CURLY_QUEST_NUM:   reward = CURLY_QUEST_EXP; break;
    }

    
    tp->add_exp_quest(reward);
/*
    log_file("mini", tp->query_cap_name()+" did Faerie tour "
      +qno+". " + ctime(time())+".\n");
*/
    tell_object(tp,"You feel a little more experienced.\n");
}

void
check_quest(object note, object tp)
{
    if (note->query_player_name() != tp->query_real_name())
    {
        command("say This is not your quest note! Are you "
          + "trying to cheat?");
        command("glare "+tp->query_real_name());
/*
        log_file("mini", tp->query_cap_name()+" tried to cheat on "
          + "a Faerie tour for "+CAP(note->query_player_name())
          + ". " + ctime(time())+".\n", 0);
*/
        note->remove_object();
        return;
    }
write("query_quest_done: " + note->query_quest_done());

    if (note->query_quest_no() == query_bin_bits(QUEST_GROUP, QUEST_BIT_START, QUEST_BIT_NBR, tp))
    {
        if (note->query_quest_done())
        {
            reward_quest(tp, note->query_quest_no());
            note->remove_object();
        }
        else
        {
            command("say But you haven't finished the task yet!");
            command("say Oh well--if you decide to try again, "
                  + "you're welcome to ask.");
            note->remove_object();
        }
        return;
    }
    command("say You were not supposed to do that one--"
          + "have you been cheating?");
    command("glare "+tp->query_real_name());
    note->remove_object();
}

string quest_inform()
{
    int     qno;
    object  tp = TP;
    string  qstr;

    if (objectp(present(QUEST_NOTE_PROP, tp)))
    {
        command("peer " + tp->query_real_name());
        command("say But you already have a task that you did not solve yet!");
        return "";
    }

    qno = query_bin_bits(QUEST_GROUP, QUEST_BIT_START, QUEST_BIT_NBR, tp);
write("DEBUG: Tour number " + qno + " and max tours: " + QUEST_MAX + "\n");

    if (qno > QUEST_MAX)

    {
//        command ("say DEBUG: SHORTER SAY");
        command("say Thank you for your help. That's all folks!");

        return "";
    }

    command("say This is what you need to do:");
    tell_object(tp, QUESTS[qno]);
    command("say If you want to do this task, type 'accept task'");
    tp->add_prop(TMP_ASKED_FOR_QUEST, 1);
    command("smile");
    return "";

}

int
accept_quest(string str)
{
    int     qno;
    object  note,
            tp = TP;

//    if (str != "task" || str != "tour" || str != "quest" str != "job")
    if(str != "task")
    {
        NFN("Accept what?");
        return 0;
    }

    if (objectp(present(QUEST_NOTE_PROP, tp)))
    {
        command("peer " + tp->query_real_name());
        command("say But you already have a task that you did not solve yet!");
        return 1;
    }

    if (!tp->query_prop(TMP_ASKED_FOR_QUEST))
    {
        command("say You have to ask for a task first!");
        return 1;
    }

    say(QCTNAME(TP)+" asks the questmaster for a task.\n",TP);
    qno = query_bin_bits(QUEST_GROUP, QUEST_BIT_START, QUEST_BIT_NBR, tp);

//write("DEBUG: Tour number " + qno + " " + TOUR_MAX + "\n");

    if (qno >= sizeof(QUESTS))
    {
        return 1;
    }

    tp->remove_prop(TMP_ASKED_FOR_QUEST); // don't allow getting more notes
    command("say Great! Take this note as proof I sent you.");
    command("say When you have finished this task, come back to me " +
        "and I shall reward you.");
    note = clone_object(OBJ_DIR + "quest_note");
    note->set_quest_no(qno);
    note->set_task(QUESTS[qno]);
    note->set_player_name(TP->query_real_name());
    if ((note->move(TP)))
    {
        command("say Hmm, it looks like you are carrying too much. In " +
            "that case, I'll drop the note on the ground so you can pick " +
            "it up.");
        note->move(ENV(TO));
    }
    return 1;
}

string *
query_quests()
{
    return QUESTS;
}


/*
 * Function name:        check_remaining_quests
 * Description  :        does the player have any remaining quests
 *                       to solve with this npc?
 * Arguments    :        object who - the player to check
 * Returns      :        int 1 - all complete, 0 - more needed
 */
public int
check_remaining_quests(object who)
{
    return (query_bin_bits(QUEST_GROUP, QUEST_BIT_START, QUEST_BIT_NBR, who)
            > QUEST_MAX);
} /* check_remaining_quests */