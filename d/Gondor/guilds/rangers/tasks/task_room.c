/*
 * /d/Gondor/guilds/rangers/tasks/task_room.c
 *
 * The room where apprentices can get tasks and be rewarded for them.
 *
 * Coded by Gwyneth
 * Updated by Tigerlily, Nov. 2, 2004:
 *     Added task #8
 *     Added test for sanction to apply
 *     Also updated taskmaster.c for task 8 (used in conjunction 
 *         with this room.
 *
 * Updated by Toby, 2007-03-26:
 *     Added a prop for the rabbit cloning with a delay on 6 hours
 *     before new clone. This to support the long up-times of the game.
 */
inherit "/d/Gondor/std/room.c";

/*
#define STILLTESTING 1
*/

#include "../rangers.h"
#include "/d/Gondor/defs.h"

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <math.h>
#include <stdproperties.h>


#define COMPANY_APP_OK 1
#define MAX_TASK 8
#define RECRUITER_OFFICE (RANGERS_HQ_DIR + "recruiter_office.c")

static object gTaskmaster;
static string *gNames = ({ "", "", "", "", "", "", "", "" });
static int gBusy = 0;
public int i_clone_rabbit;
public void reset_task(int task);


void
reset_room()
{
    int i;
    ::reset_room();

//check on tasks--if players working on tasks have left the realms,
//reset them

    for (i= 0; i < sizeof(gNames); i++ )
    {
        if (strlen(gNames[i]))
        {
            if (!objectp(find_player(gNames[i])))
            {
                gNames[i] = "";
            }
        }
    }
    if (!objectp(gTaskmaster))
    {
        gTaskmaster = clone_object(RANGERS_NPC + "taskmaster");
        gTaskmaster->move_living("humming a song", TO);
    }
}

/*
 * Function name: allowed_pass
 * Description  : Only allows those who have been assigned the task
 *                through the exit.
 * Arguments    : int task - the task number
 * Returns      : 0 for allowed, 1 for not allowed
 */
public int
allowed_pass(int task)
{
    if (TP->query_wiz_level() || TP->query_prop(RANGER_I_RABBIT) ||
      TP->query_real_name() == gNames[task - 1])
        return 0;

    write("You are not allowed there right now.\n");
    return 1;
}

void
create_gondor()
{
    set_short("just west of the Ranger Headquarters");
    set_long("You're just west of the Ranger Headquarters " +
        "in a small clearing. To your north lies a small hut " +
        "where the very ill can rest in comfort and quiet. " +
        "A small path to the west leads into the Druedain " +
        "forest. It looks overgrown and untravelled.\n");

    add_item(({ "headquarters", "ranger headquarters" }),
        "The Ranger Headquarters is east and leads into its " +
        "post office.\n");
    add_item(({ "hut", "small hut" }), "A heavy cloth curtain " +
        "covers the windowless hut to the north. It appears to " +
        "be a single room.\n");
    add_item(({ "curtain", "cloth curtain", "heavy cloth curtain",
        "heavy curtain" }), "The curtain looks like it's fairly " +
        "effective at keeping the cold out when closed, while " +
        "it lets fresh air in when it's open.\n");
    add_item(({ "clearing", "small clearing", "ground" }),
        "The ground is covered with short grass and dirt. A " +
        "charred area shows evidence of many past campfires.\n");
    add_item(({ "grass", "short grass" }), "It appears to be " +
        "thriving in the rich soil.\n");
    add_item(({ "soil", "rich soil", "dirt" }), "The soil is " +
        "rich and brown.\n");
    add_item(({ "path", "small path" }), "It leads into a little " +
        "visited part of the Druedain forest.\n");
    add_item(({ "forest", "druedain forest", "Druedain forest" }),
        "The forest grows dense and dark to the west. It is " +
        "filled with many species of tree, all of which seem " +
        "threatening to any who may pass beneath their boughs.\n");
    add_item(({ "tree", "trees" }), "There are many species of " +
        "tree growing in the Druedain, and all of them seem tall " +
        "and majestic. It is plain that no axe has cut this wood " +
        "for many an Age.\n");


    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TRACKTASK_DIR + "track_task1", "west",
        &allowed_pass(TRACK_TASK));
    add_exit(RANGERS_TASK + "poison_room", "north",
        &allowed_pass(CURE_TASK));
    add_exit(RANGERS_HQ_DIR + "post", "east");

    reset_room();
}


/* Function name: reset_clone_rabbit
 * Description  : Resets the timer on cloning the rabbit
 *                Fix due to long uptimes
 */
public void
reset_clone_rabbit()
{
   i_clone_rabbit = 1;
}


/*
 * Function name: clone_rabbit
 * Description  : Clones the rabbit, begins his run and makes him
 *                temporarily invisible.
 */
public void
clone_rabbit()
{
    if(i_clone_rabbit)
    {
        object rabbit = clone_object(RANGERS_NPC + "rabbit");

        rabbit->move_living("M", this_object());
        rabbit->start_run("west");

        i_clone_rabbit = 0;
        // 6hrs reset before cloning again
        set_alarm(4320.0, 0.0, &reset_clone_rabbit());
    }
        
}

/*
 * Function name: query_task
 * Description  : Returns the task number the apprentice must complete.
 * Arguments    : string name - the name to inquire about
 * Returns      : See description
 */
int
query_task(string name)
{
    return MANAGER->query_task_number(name) + 1;
}

public void
setup_poison(string name)
{
    (RANGERS_TASK + "poison_room")->set_helper(name);
}

/*
 * Function name: start_task
 * Description  : Called by the taskmaster when she's asked for a new task.
 *                It assigns a new task to an Apprentice Ranger.
 * Arguments    : string name - the name of the apprentice
 */
public void
start_task(string name)
{
    int task, jtime;
    string herb;

    if (!strlen(name))
        return;

    if (!present(gTaskmaster))
    {
        write("The taskmaster is not present.\n");
        return;
    }

    if (!APPRENTICE_MEMBER(TP))
    {
        gTaskmaster->command("say I only teach apprentices, I'm sorry.\n");
        return;
    }

    task = query_task(name);
    if (task > MAX_TASK)
    {
        gTaskmaster->command("say I have no more tasks for you " +
            "at this time. Perhaps you should ask about applying " +
            "to a company?");  
        return;
    }

    if (!strlen(gNames[task - 1]) &&
      gNames[task - 1] != TP->query_real_name() &&
      objectp( find_player( lower_case(gNames[task - 1]) ) ))
    {
        set_alarm(1.2, 0.0, &gTaskmaster->command("say I do have a task, " +
            "but someone else is already working on it right now."));
        set_alarm(1.5, 0.0, &gTaskmaster->command("say Please come back " +
            "later."));
        return;
    }

    TP->add_prop(RANGER_I_TASK, task);
    switch(task)
    {
    case 1:
        // Build a fire
        gNames[task - 1] = TP->query_real_name();
        set_alarm(1.2, 0.0, &gTaskmaster->command("say Ahh, your first " +
            "task!"));
        set_alarm(1.5, 0.0, &gTaskmaster->command("say It is important " +
            "for a Ranger to know how to survive in the wild. To begin " +
            "with, build a very large fire for me all by yourself."));
        set_alarm(1.9, 0.0, &gTaskmaster->command("say Ask me for your " +
            "reward when you have a fire for me."));
        break;
    case 2:
        // Gather and cook some game
        set_alarm(1.2, 0.0, &gTaskmaster->command("say For your second " +
            "task, we'll continue with wilderness survival skills."));
        set_alarm(1.5, 0.0, &gTaskmaster->command("say Hunt down some " +
            "game and return here to roast it for me. Give it to me " +
            "when you're done, and don't forget to " +
            "clean up after yourself!"));
        break;
    case 3:
        // Track an npc through forest
        if (gNames[task - 1] == TP->query_real_name())
        {
            if(i_clone_rabbit)
            {
               set_alarm(2.0, 0.0, &tell_room(this_object(), QCTNAME(gTaskmaster) +
                   " puts a fluffy brown rabbit on the ground, as you have seen before, " +
                   " and nudges him to the west.\n"));
               set_alarm(2.1, 0.0, &clone_rabbit());
               set_alarm(0.6, 0.0, &gTaskmaster->command("say Track down that " +
                   "rabbit and bring it back to me. Don't dawdle along the way!"));
             }
             else
               set_alarm(0.6, 0.0, &gTaskmaster->command("say Track down that " +
                   "rabbit... Yes, that you must do. But for now rest a little " +
                   "while, as my rabbit does. Or did you find him?"));

            return;
        }

        gNames[task - 1] = TP->query_real_name();
        set_alarm(0.8, 0.0, &reset_clone_rabbit());
        set_alarm(1.6, 0.0, &gTaskmaster->command("say This third task " +
            "concludes your wilderness survival tasks."));
        set_alarm(3.0, 0.0, &tell_room(this_object(), QCTNAME(gTaskmaster) +
            " puts a fluffy brown rabbit on the ground and nudges him " +
            "to the west.\n"));
        set_alarm(3.1, 0.0, &clone_rabbit());
        set_alarm(4.5, 0.0, &gTaskmaster->command("say Track down that " +
            "rabbit and bring it back to me. Don't dawdle along the way!"));
        break;
    case 4:
        // Gather spells
        set_alarm(1.2, 0.0, &gTaskmaster->command("say For your fourth " +
            "task, you will discover the magic of the Rangers."));
        set_alarm(1.5, 0.0, &gTaskmaster->command("say Come back " +
            "and ask me for your reward when you have discovered two " +
            "Ranger spells."));
        break;
    case 5:
        // Find a fresh herb from random preset list
        herb = TASK_HERBS[NAME_TO_RANDOM(name, TASK_RANDOM,
            sizeof(TASK_HERBS))];

        set_alarm(1.2, 0.0, &gTaskmaster->command("say Rangers live off " +
            "the land and make full use of the herbs they can find."));
        set_alarm(1.5, 0.0, &gTaskmaster->command("emote ponders which " +
            "herb to assign."));
        set_alarm(1.7, 0.0, &gTaskmaster->command("say Find " + 
            LANG_ADDART(herb) + " for me, preferably fresh."));
        break;
    case 6:
        // Mix the three potions, non-watery
        set_alarm(1.2, 0.0, &gTaskmaster->command("say Rangers use herbs " +
            "for their spells, but sometimes a potion is handy when you're " +
            "just too weak to cast a spell."));
        set_alarm(1.6, 0.0, &gTaskmaster->command("say Demonstrate that " +
            "you know how to make the three potions that we specialize in, " +
            "the stronger the better!"));
        break;
    case 7:
        // Cleanse an npc
        if (gNames[task - 1] == TP->query_real_name())
        {
            set_alarm(1.2, 0.0, &gTaskmaster->command("say One of our " +
                "Rangers has just come back from a mission, but he is " +
                "poisoned. I'm afraid he will die if you don't see him " +
                "through this."));
            set_alarm(1.7, 0.0, &gTaskmaster->command("say You'll find the " +
                "Ranger in the small cabin to the north."));
            set_alarm(2.3, 0.0, &gTaskmaster->command("say Now, please " +
                "hurry!"));
            return;
        }
        gNames[task - 1] = TP->query_real_name();
        set_alarm(1.2, 0.0, &gTaskmaster->command("say So you need " +
            "another task?"));
        set_alarm(1.5, 0.0, &gTaskmaster->command("say You've come at " +
            "just the right time!"));
        set_alarm(2.3, 0.0, &gTaskmaster->command("say One of our " +
            "Rangers has just come back from a mission, but he is " +
            "poisoned. I'm afraid he will die if you don't see him " +
            "through this."));
        set_alarm(2.8, 0.0, &gTaskmaster->command("say You'll find the " +
            "Ranger in the small cabin to the north."));
        set_alarm(1.0, 0.0, &setup_poison(TP->query_real_name()));
            (RANGERS_TASK + "poison_room")->reset_room();
   
        break;
    case 8:
        jtime = MANAGER->query_apprentice_join_time(TP->query_real_name());
#ifndef STILLTESTING
/*
        if (jtime > time() || jtime == -1)
        {
            set_alarm(0.0, 0.0, &gTaskmaster->command("say I think you " +
                "need to study longer as an apprentice. This task requires " +
                "courage and knowledge of the ways of a Ranger."));
            return;
            break;
        }
*/
#endif
        // Task to team with ranger
        if (gNames[task - 1] == TP->query_real_name())
        {
            set_alarm(0.0, 0.0, &gTaskmaster->command("say You must " +
                "find and kill the beast of Sauron, and remember, " +
                "do not go alone or unprepared!"));
            return;
        }
        gNames[task - 1] = TP->query_real_name();
        set_alarm(1.0, 0.0, &gTaskmaster->command("say Your " +
            "final task as an apprentice will test all of your " +
            "skills and bravery."));
        set_alarm(3.0, 0.0, &gTaskmaster->command("say It is most " +
            "dangerous, and you must not embark on it alone or " +
            "unprepared."));
        set_alarm(6.0, 0.0, &gTaskmaster->command("say Reports have " +
            "come to us from the foothills of the White Mountains about " +
            "some new devilry of Sauron's! There is a great beast that " +
            "is ravaging the area!"));
        set_alarm(9.0, 0.0, &gTaskmaster->command("say You will need "+
            "to team with a Ranger from Arnor or Ithilien."));
        set_alarm(11.0, 0.0, &gTaskmaster->command("say With the " +
            "assistance of your teammate, you and one full ranger only, " +
            "you must find and kill the beast. As proof, bring me " +
            "one of its fangs!"));
        set_alarm(16.0, 0.0, &gTaskmaster->command("say Return to me " +
            "with the fang, accompanied by the Ranger teammate who " +
            "assisted you!"));
        break;
    default:
        gTaskmaster->command("say I have no other tasks " +
            "for you at this time.");
        break;
    }

    return;
}

/*
 * Function name: query_done
 * Description  : Tests if some of the tasks are done.
 * Arguments    : object tp - the player who has been assigned the task.
 * Returns      : 1 if it's done, 0 if it's not
 */
public int
query_done(object tp)
{
    int task;
    object task_item;

    if (!objectp(tp))
        return 0;

    task = tp->query_prop(RANGER_I_TASK);

    switch(task)
    {
    case 1:
        task_item = tp->query_prop(RANGER_O_FIRE_TASK);
        /* Fire doesn't exist or isn't in this room. */
        if (!objectp(task_item) || !present(task_item, TO))
            return 0;

        if (!task_item->query_lit())
        {
            gTaskmaster->command("say It's just a stack of wood!");
            return 0;
        }

        if (task_item->determine_size() == "very large")
        {
            gTaskmaster->command("say Great job! Such a very large fire!");
            return 2;
        }

        gTaskmaster->command("say Not as large as you could have built it, " +
            "but it's sufficient.");
        return 1;

    case 2:
    case 3:
        // Rewarding done through giving the item.
        break;

    case 4:
        task_item = present("ranger_spell_book", tp);
        if (!objectp(task_item))
        {
            gTaskmaster->command("say But you don't even have your " +
                "spellbook, much less any Ranger spells!");
            return 0;
        }

        if (tp->query_ranger_has_virtues())
        {
            int num_spells = 0;
            foreach (object spell : tp->query_spellobjs())
            {
                if (spell->is_ranger_virtue_spell() &&
                    spell->query_spell_can_be_learned(tp))
                {
                    num_spells++;
                }
            }
            if (num_spells >= 2)
            {
                gTaskmaster->command("say Great job! You've gotten a " +
                    "spellbook and at least two spells.");
                return 1;
            }
        }

        if (m_sizeof(task_item->query_spell_map()) >= 2)
        {
            gTaskmaster->command("say Great job! You've gotten a " +
                "spellbook and at least two spells.");
            return 1;
        }

        gTaskmaster->command("say You've got your spellbook, but " +
            "you don't have two spells yet. Keep looking!");
        gTaskmaster->command("smile encourag");
        return 0;

    case 5:
    case 6:
        // Rewarding done through giving the item.
        break;

    case 7:
        if (tp->query_prop(RANGER_I_SUCCESS_CURE))
        {
            gTaskmaster->command("say You cured him! Wonderful!");
            gTaskmaster->command("nod encouragingly");
            return 3;

        }
        if (tp->query_prop(RANGER_I_FAILED_CURE))
        {
            gTaskmaster->command("emote wipes away a tear from his eyes.");
            gTaskmaster->command("say He died! I can't reward you, I'm " +
                "sorry.");
            return 0;
        }

        gTaskmaster->command("say You haven't cured him yet.");
        return 0;
    case 8:
        // reward is done through giving item
/*

        gTaskmaster->command("say Congratulations on finishing " +
            "your last task!" );
        gTaskmaster->command("say Your next step is to be sanctioned " +
            "by a Ranger from the company to which you want to apply.");
        gTaskmaster->command("say Then you may 'apply north/ithilien' " +
            "to request membership in a company if it has been " +
            "at least two weeks since you joined.");
        gTaskmaster->command("say It will take one week from the time " +
            "you apply for the members of the company to decide if " +
            "they want you to join them or not. You must apply before " +
            ctime(MANAGER->query_apprentice_time(TP->query_real_name())) +
            ".");
*/

    default:
        return 0;
    }

    gTaskmaster->command("say Just give it to me.");
    return 0;
}

/*
 * Function name: reward_task
 * Description  : Rewards an apprentice for completing a task.
 *                Does not increment the task.
 * Arguments    : string name - the name of the apprentice
 *                string amount - slightly or moderately
 *                string reason - the reason for the reward
 */
public void
reward_task(string name, string amount, string reason)
{
    if (!strlen(name) || !strlen(amount) || !strlen(reason))
        return;

    MANAGER->reward_ranger(name, amount);
    MANAGER->rlog("apprentice", "The taskmaster rewarded " +
        capitalize(name) + " " + amount + " for " + reason);
    find_player(name)->catch_tell("You have been rewarded " +
        amount + " for " + reason + "!\n");
    return;
}

/*
 * Function name: reset_task
 * Description  : Resets the task so someone else can try it.
 * Arguments    : int task - the task number to reset
 */
public void
reset_task(int task)
{
    int i, size;
    string *contents = get_dir(TRACKTASK_DIR);

    if (intp(task) && task >= FIRE_TASK && task <= WARRIORS_TASK)
        gNames[task - 1] = "";

    // Resets all the tracks in the track task.
    if (task == TRACK_TASK)
        for (i = 0, size = sizeof(contents); i < size; i++)
            find_object(TRACKTASK_DIR + contents[i])->remove_prop(ROOM_S_DIR);
}

/*
 * Function name: apply
 * Description  : Allows an apprentice to apply to a company
 *                when they've completed all tasks.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 for success, 0 for failure
 */
public int
apply(string str)
{
    string company, name, recruiter_name, recruiter_company;
    int jtime;

    name = TP->query_real_name();

#ifndef COMPANY_APP_OK
    if (APPRENTICE_MEMBER(TP) && query_task(name) > 7)
    {
        gTaskmaster->command("say You must complete a final apprentice " +
            "task. I will post a note on the board when it is ready.");
        notify_fail("Applications are not being accepted to the companies " +
            "at this time.\n");
        return 0;
    }
#endif
// else
    // check recruiter office--must be loaded
    if (!objectp(find_object(RECRUITER_OFFICE)))
    {
        RECRUITER_OFFICE->teleledningsanka();
        if (!objectp(find_object(RECRUITER_OFFICE)))
        {
            notify_fail("There is a bug in the application process. " +
                "Please log a bug message or send a mail to the " +
                "guildmaster.\n");
            return 0;
        }
    }
    recruiter_name = find_object(RECRUITER_OFFICE)->query_sanction(name);
    if (!strlen(recruiter_name))
    {
        notify_fail("You need to be sanctioned by a mature ranger " +
            "from the company that you wish to join.\n");
        return 0;
    }

    recruiter_company = find_object(MANAGER)->query_ranger_company(recruiter_name);
    if (!strlen(recruiter_company))
    {
        notify_fail("Your recruiter no longer belongs to a " +
            "Ranger company. You must be resanctioned.\n");
        return 0;
    }
    if (!strlen(str))
    {
        notify_fail("Apply [to] Ithilien or the North?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "[to] [the] %w", company))
    {
        notify_fail("Apply [to] Ithilien or the North?\n");
        return 0;
    }
    company = lower_case(company);
    if (company != recruiter_company)
    {
        notify_fail("You cannot apply to the " + capitalize(company) +
            " company. You can only apply to the company " +
            "where you were sanctioned.\n");
       return 0;
    }

    if (!APPRENTICE_MEMBER(TP) || query_task(name) <= WARRIORS_TASK)
    {
        notify_fail("Only apprentices who've completed all tasks " +
            "may apply.\n");
        return 0;
    }


    jtime = MANAGER->query_apprentice_join_time(name);

#ifndef STILLTESTING
    if (jtime > time() || jtime == -1)
    {
        notify_fail("I think you need more time as an apprentice.\n");
        return 0;
    }
#endif


    name = TP->query_real_name();
    if (MANAGER->query_voted_out(name, company))
    {
        notify_fail("You have already been denied membership " +
            "in that company.\n");
        return 0;
    }

    switch(company)
    {
    case "ithilien":
        if (MEMBER_VOTE_ITH->query_vote(name))
        {
            notify_fail("You have already applied to Ithlien.\n");
            return 0;
        }

        MEMBER_VOTE_ITH->start_vote(name);
        write("You apply to join Ithilien. You will be voted in or out by " +
             extract(ctime(time() + ELECTION_TIME_OUT), 4, -9) + ". "+ 
             "After you have been voted in, you will need to find " +
             "the Ithilien hideout and be accompanied by a witness " +
             "in order to be promoted to full ranger.\n");
        return 1;

    case "north":
        if (MEMBER_VOTE_NOR->query_vote(name))
        {
            notify_fail("You have already applied to the North.\n");
            return 0;
        }

        MEMBER_VOTE_NOR->start_vote(name);
        write("You apply to join the North. You will be voted in or out by " +
             extract(ctime(time() + ELECTION_TIME_OUT), 4, -9) + ". " +
             "After you have been voted in, you will need to find " +
             "the hideout of the Rangers of the North and be " +
             "accompanied by a witness in order to be promoted " +
             "to full ranger.\n");
        return 1;

    default:
        notify_fail("Apply [to] 'Ithilien' or the 'North'?\n");
        return 0;
    }

}

/*
 * Function name: init
 * Description  : Calls parent init and adds the 'apply' verb to
 *                the commands one can use when entering the room.
 */
public void
init()
{
    ::init();

    add_action(apply, "apply");
}

public void 
reset_busy()
{ 
    gBusy = 0; 
}

/*
 * Function name: return_ob
 * Description  : Return weapons and armours to the player who
 *                dropped them.
 * Arguments    : object who - the player who dropped it
 *                object ob - the object dropped
 */
public void
return_ob(object who, object ob)
{
    if (!present(ob))
        return;

    if (!present(who))
        return;

    if (present(gTaskmaster))
    {
        if (!gBusy)
        {
            gTaskmaster->command("say This isn't an armoury! Go " +
                "put that in the racks where it belongs!");
            set_alarm(0.7, 0.0, &gTaskmaster->command("mumble"));
            gBusy = 1;
            set_alarm(0.5, 0.0, &reset_busy());
        }

        who->catch_tell(gTaskmaster->query_The_name(who) +
            " picks up your carelessly dropped " + ob->query_name() +
            " and returns it to you.\n");
        tell_room(QCTNAME(gTaskmaster) + " picks up the carelessly " +
            "dropped " + ob->query_name() + " and returns it to " +
            QTNAME(who) + ".\n", who);
        ob->move(who, 1);
    }
    else
    {
        reset_room();
        return_ob(who, ob);
    }
}

/*
 * Function name: enter_inv
 * Description  : We don't want this becoming the apprentice
 *                storage room. If it's armour or weapons,
 *                have the janitor clean up.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob))
        return;

    if (!objectp(from) || !query_interactive(from))
        return;

    if (ob->check_armour() || ob->check_weapon())
        if (present(from))
            set_alarm(3.0, 0.0, &return_ob(from, ob));

    return;
}

int
query_ranger_room()
{
    return 1;
}
