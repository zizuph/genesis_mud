/*
 * /d/Gondor/common/guild2/newnpc/qm.c
 * The Questmaster of Morgul Tower
 * By Finwe, May 2020
 *
 * Revision History:
 */

inherit "/std/monster";
inherit "/d/Gondor/common/lib/binbit";

#include "/d/Gondor/defs.h"
#include "qbits.h"
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define TMP_ASKED_FOR_TOUR  "_mm_asked_for_tour"
#define TOUR_OBJ_DIR       "/d/Gondor/common/guild2/obj/"

#define TOURS   ({  "Go find the Post Office of the Dark Tower.\n",\
                    "Go find the Bank of the Dark Tower\n",\
                    "Go find the Training Hall of the Dark Tower.\n",\
                    "Find Ghashdurub, the Master Weapon Smith of the " +\
                        "Morgul Army.\n",\
                })
/*
                    "Go find the corsair that is said to land with " +\
                    "his ship somewhere close to Pelargir. he hasn't sent " +\
                    "his report to the Tower.",\
                    
                    "I need information about the activity ships landing " +\
                    "in Pelargir. Go spy for me and visit the ship " +\
                    "captains that sail there, and ask for a report from them.",\

                })
*/
int           check_tour(object note, object tp);
int           accept_tour(string str);
void          do_ask_for_note(object tp);
string        quest_inform();
public int    check_remaining_quests(object who);


void
create_monster()
{
    int i;

    set_race_name("elf");

    set_name("menerial");
    set_adj("noble");
    set_adj("somber");
    set_short("noble somber elf");
    add_name("delegate");
    add_name("chief delegate");
    set_long("This is the QM_NAME of Green Oaks. She has smooth " +
        "skin and cheerful eyes, and is responsible for keeping track " +
        "of business affairs. Travellers may ask her for tasks, and " +
        "if she has any, she will give them out.\n");
    set_title("Car'imyr, Chief Delegate of Green Oaks");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);
    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable
    add_prop(LIVE_M_NO_ACCEPT_GIVE,0);

    for (i = 0; i < 5; i++)
        set_base_stat(i, 100 + random(25));

    set_chat_time(40+random(10));

    set_gender(G_MALE);
/*
    set_chat_time(60+random(60));
    add_chat("If you are looking for something to do, ask me.");
    add_chat("I love helping travellers.");
    add_chat("We do not see many troublemakers in Green Oaks.");
    add_chat("What can I help you with?");
    add_chat("Elves are marvelous creatures, I am sure you will agree.");
    add_chat("I have much work to do.");
    
    set_act_time(60+random(60));
    add_act("emote watches you.");
    add_act("emote paces the floor quietly.");
    add_act("emote smiles happily.");
    add_act("emote greets a visitor.");
*/
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
    if (present(TOUR_NOTE_PROP,tp))
        set_alarm(1.0, 0.0, &do_ask_for_note(tp));
    if (living(tp) && interactive(tp) && CAN_SEE(TO, tp) &&
        !(tp->query_met(query_real_name())))
        set_alarm(2.0 + 5.0 * rnd(), 0.0, &react_intro(tp));

    add_action(accept_tour, "accept");
}


void
return_object(object obj, object to)
{
    string  obname = OB_NAME(obj);

    if (obj->id("coin"))
        return;

    command("say I do not believe I need this. Thank-you though.");
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

    if (obj->id(TOUR_NOTE_PROP))
        set_alarm(0.5, 0.0, &check_tour(obj, from));
    else
        set_alarm(0.5, 0.0, &return_object(obj, from));
}


void
do_ask_for_note(object tp)
{
command("say Greetings again!");
command("say Have you completed the tour I gave you?");
command("say If you have, please give me the note."); 
command("smile "+tp->query_real_name());
}

void
reward_tour(object tp, int qno)
{
    int reward;

    set_bin_bits(TOUR_GROUP, TOUR_BIT_START, TOUR_BIT_NBR, tp, qno + 1);
    command("say Thank you. You finished that tour for me!");
    command("shake " + tp->query_real_name());


    switch(qno)
    {
        case PO_TOUR_NUM:       reward = 50; break;
        case BANK_TOUR_NUM:     reward = 50; break;
        case TRAIN_TOUR_NUM:    reward = 50; break;
        case SMITH_TOUR_NUM:    reward = 100; break;
//        case PO_TOUR_NUM:       reward = PO_TOUR_EXP; break;
//        case PIERS_TOUR_NUM:    reward = PIERS_TOUR_EXP; break;
//        case BOARD_TOUR_NUM:    reward = BOARD_TOUR_EXP; break;
    }

    
    tp->add_exp_quest(reward);
    log_file("mini", tp->query_cap_name()+" did Faerie tour "
      +qno+". " + ctime(time())+".\n");
    tell_object(tp,"You feel a little more experienced.\n");
}

void
check_tour(object note, object tp)
{
    if (note->query_player_name() != tp->query_real_name())
    {
        command("say This is not your tour note! Are you "
          + "trying to cheat?");
        command("glare "+tp->query_real_name());
        log_file("mini", tp->query_cap_name()+" tried to cheat on "
          + "a Faerie tour for "+CAP(note->query_player_name())
          + ". " + ctime(time())+".\n", 0);
        note->remove_object();
        return;
    }

    if (note->query_tour_no() == query_bin_bits(TOUR_GROUP, TOUR_BIT_START, TOUR_BIT_NBR, tp))
    {
        if (note->query_tour_done())
        {
            reward_tour(tp, note->query_tour_no());
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

    if (objectp(present(TOUR_NOTE_PROP, tp)))
    {
        command("peer " + tp->query_real_name());
        command("say But you already have a task that you did not solve yet!");
        return "";
    }

    qno = query_bin_bits(TOUR_GROUP, TOUR_BIT_START, TOUR_BIT_NBR, tp);
//write("DEBUG: Tour number " + qno + " and max tours: " + TOUR_MAX + "\n");
 
    if (qno > TOUR_MAX)

    {
//        command ("say DEBUG: SHORTER SAY");
        command("say Sorry, I have no more tasks for you, " + 
            tp->query_race_name()+". However, I have reports that there " +
            "are other towns and villages that have need of your help. " +
            "Some of what they tell me I will pass on to you:");
        command("grin happily");
        command("say In the land of Krynn, in the town of Solace, be sure " +
                    "and visit Tarshir. He has tasks and tours.");
        command("say In the land of Gont lives Thera. She lives in a farmhouse and could use your help.");
        command("say North of Thera, in Ten Alders lives the herbalist Ariel. She could use your help, too.");
        command("say Also, in the land of Krynn is the city of Palanthas. " +
            "Visit Leiden at the Silver Dragon Inn. He needs your help.");
        command("say In the land of Middle-earth, Carastur, the Lord " +
            "Councillor of Pelargir needs help.");
        command("say Also in the land of Middle-earth, in Minas Tirith " +
            "is Hunthor, the Master of Advice. He has several tours and " +
            "tasks. You must be good enough to enter the city to help " +
            "him though.");
        command("say In the land Terel is a gypsy camp. Visit Tecla, the " +
            "old fortune teller and she has tasks you can do.");
        command("say In the land of Cadu is a Mayor. Visit him because " +
            "he needs your help.");
        command("say In the land of Calia, visit the town of Argos. There, " +
            "in the park you will find Alexis. He has tours you may do.");
        command("emote furrows her brow thoughtfully.");
        command("say If you're a daring adventurer, there are some " +
            "dangerous tasks in the land of Kalad. In the Central district " +
            "is Hernan. He is in the Sage's office and needs help.");
        command("say Also, if you look around here, there are others " +
            "who need help, too.");
        return "";
    }

    command("say This is what you need to do:");
    tell_object(tp, TOURS[qno]);
    command("say If you want to do this task, type 'accept tour'");
    tp->add_prop(TMP_ASKED_FOR_TOUR, 1);
    command("smile");
    return "";

}

int
accept_tour(string str)
{
    int     qno;
    object  note,
            tp = TP;

//    if (str != "task" || str != "tour")
    if(str != "tour")
    {
        NFN("Accept what, the tour?");
        return 0;
    }

    if (objectp(present(TOUR_NOTE_PROP, tp)))
    {
        command("peer " + tp->query_real_name());
        command("say But you already have a task that you did not solve yet!");
        return 1;
    }

    if (!tp->query_prop(TMP_ASKED_FOR_TOUR))
    {
        command("say You have to ask for a task first!");
        return 1;
    }

    say(QCTNAME(TP)+" asks the QM_NAME for a task.\n",TP);
    qno = query_bin_bits(TOUR_GROUP, TOUR_BIT_START, TOUR_BIT_NBR, tp);

//write("DEBUG: Tour number " + qno + " " + TOUR_MAX + "\n");

    if (qno >= sizeof(TOURS))
    {
        return 1;
    }

    tp->remove_prop(TMP_ASKED_FOR_TOUR); // don't allow getting more notes
    command("say Great! Take this note as proof I sent you.");
    command("say When you have finished this task, come back to me " +
        "and I shall reward you.");
    note = clone_object(TOUR_OBJ_DIR + "tournote");
    note->set_tour_no(qno);
    note->set_task(TOURS[qno]);
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
query_tours()
{
    return TOURS;
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
    return (query_bin_bits(TOUR_GROUP, TOUR_BIT_START, TOUR_BIT_NBR, who)
            > TOUR_MAX);
} /* check_remaining_quests */