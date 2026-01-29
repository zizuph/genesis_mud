/*
 * /d/Gondor/guilds/rangers/npc/taskmaster.c
 *
 * Gives out tasks and rewards tasks done for apprentice rangers.
 * Coded by Gwyneth
 * Modifications:
 *    Tigerlily, Nov. 2004: added task 8--warrior task, with
 *        rewards and add_asks
 * 
 *    Arman, Dec. 2018: fixed bug with potion task.
 */
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <math.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"


inherit RANGERS_NPC + "npc_ranger.c";

string give_task();
string reward_task();
string answer_apply();
string warg_reply();
string lair_reply();
string default_answer();


public void do_reward(string name, string amount, string reason);
public void introduce(object who);

static string *gIntro = ({});

#define RANGER_DEBUG(x)      find_player("arman")->catch_msg("[Ranger] " + x + "\n")

public void
create_ranger()
{
    set_living_name("lossefalme");
    set_title("the Legend of the Rangers of the Westlands");
    set_name("lossefalme");
    add_name("woman");
    set_adj(({"old", "stooped"}));
    add_name("taskmistress");
    /* Do not remove this name. It's necessary for other things. */
    add_name("taskmaster");
    remove_name("man");
    set_long("This old Ranger has led a long and difficult " +
        "life judging by the deeply etched lines on her forehead and " +
        "her intense gaze giving the impression that she is " +
        "very wise. In her aging years, she has retired to " +
        "the life of a teacher. Her job here is to assign " +
        "tasks to apprentices, and handle their applications " +
        "to companies. Perhaps she could teach you a few things.\n");
    
    set_gender(G_FEMALE);
    set_skill(SS_BRAWLING,    80 + random(10));
    set_skill(SS_HEARING,     60 + random(10));
    set_skill(SS_HERBALISM,   96);
    set_skill(SS_AWARENESS,   87);
    set_skill(SS_WEP_POLEARM, 85);
    set_skill(SS_DEFENCE,     65);
    set_skill(SS_PARRY,       48);
    set_stats(({ 125, 125, 130, 169, 168, 125 }));
    set_base_stat(SS_OCCUP, 200);
    set_hp(10000);
    add_prop(CONT_I_WEIGHT, 61578);
    add_prop(CONT_I_HEIGHT, 198);
    add_prop(CONT_I_VOLUME, 70000);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    add_ask(({"tasks", "task"}), &give_task());
    add_ask(({ "reward", "finished", "finished task", "done"}),
        &reward_task());
    add_ask(({"applying", "company", "companies", "apply to company",
              "applying to company"}), &answer_apply());
    add_ask(({"beast", "about beast", "warg", "great white warg", 
        "white warg", "beast of sauron", "beast of Sauron",
        "evil beast of sauron"}), &warg_reply());
    add_ask(({"mountains", "foothills of the White Mountains",
        "foothills", "white mountains", "White Mountains",
        "lair", "about lair"}), &lair_reply());
    set_default_answer("You are met with silence.\n");
   
    arm_me();
}

string
default_answer()
{
    command(one_of_list( ({"say Pardon me?", "scratch", "shrug unknow",
        "say I haven't a clue.", "say Why don't you ask someone else."}) ));
    return "";
}

string
answer_apply()
{
    set_alarm(1.0, 0.0, &command("say This is how it shall " +
        "be. You must prove yourself by accomplishing " +
        "a few tasks that demonstrate your abilities as a " +
        "ranger."));
    set_alarm(3.0, 0.0, &command("say When the tasks " +
        "have been completed and you have grown as an apprentice, " +
        "you will need to be sanctioned by a full ranger " +
        "from the company where you want to apply."));
    set_alarm(4.0, 0.0, &command("say Then you will be able to apply " +
        "to a company, either the grey or the green."));
    set_alarm(5.0, 0.0, &command("say If you are voted " +
        "in by the membership of the North or Ithilien, " +
        "the next step is for you to find the company hideout."));
    set_alarm(7.0, 0.0, &command("say While in the " +
        "presence of a witness who is a full ranger " +
        "and member of the company you wish to join, " +
        "who will attest to your worthiness to become a ranger, " +
        "you will take the oath to join the company."));
    set_alarm(9.0, 0.0, &command("say Take heed! Thy path " +
        "will not be easy, and it will be full of peril, whichever " +
        "you should choose."));
    return "";
}
string
warg_reply()
{
    command("say We have received a report that an evil beast " +
        "of Sauron has come down from the north and has set up " +
        "his lair somewhere in the foothills of the White Mountains.");
    set_alarm(2.0, 0.0, &command("say One of our scouts set off a month ago to " +
        "check on this report, but he has not returned."));
    set_alarm(3.0, 0.0, &command("sigh"));
    set_alarm(4.0, 0.0, &command("say I fear the worst for him."));
    set_alarm(6.0, 0.0, &command("say The reports say that it was a warg, " +
        "white with evil red eyes and long yellow fangs."));
    return "";
}

string
lair_reply()
{
    set_alarm(0.0, 0.0, &command("say They say the beast has its " +
        "lair somewhere in the foothills of the White Mountains, " +
        "possibly in a cave there."));
    set_alarm(2.0, 0.0, &command("sigh"));
    set_alarm(4.0, 0.0, &command("say He is terrorizing the farmers " +
        "nearby!"));
    return "";
}

string
give_task()
{
    environment()->start_task(this_player()->query_real_name());
    return "";
}

string
reward_task()
{
    int num, task;
    string name;

    name = TP->query_real_name();
    task = TP->query_prop(RANGER_I_TASK);
    num = environment()->query_done(TP);

    switch(num)
    {
    case 0:
        return "";

    case 1:
        // Completed minimum requirements
        set_alarm(1.0, 0.0, &do_reward(name, "moderately", 
            "completing task number " + LANG_NUM2WORD(task)));
        MANAGER->increment_task_number(name);
        break;

    case 2:
        // Extra good job on the task
        set_alarm(1.0, 0.0, &do_reward(name, "moderately",
            "completing task number " + LANG_NUM2WORD(task)));
        set_alarm(1.1, 0.0, &do_reward(name, "slightly",
            "doing extra well on task number " + LANG_NUM2WORD(task)));
        MANAGER->increment_task_number(name);
        break;

    default:
        // Biggest reward for last task.
        set_alarm(1.0, 0.0, &do_reward(name, "moderately",
            "completing task number " + LANG_NUM2WORD(task)));
        set_alarm(1.1, 0.0, &do_reward(name, "moderately",
            "doing extra well on task number " + LANG_NUM2WORD(task)));
        MANAGER->increment_task_number(name);
        TP->remove_prop(RANGER_I_SUCCESS_CURE);
        break;
    }

    TP->remove_prop(RANGER_I_TASK);
    environment()->reset_task(task);

    return "";
}

public void
do_reward(string name, string amount, string reason)
{
    environment()->reward_task(name, amount, reason);
}

void
enter_inv(object ob, object from)
{
    string name, team_name, herb, potion, *potions;
    object teammate;

    ::enter_inv(ob, from);

    if (!objectp(from))
        return;

    name = from->query_real_name();

    if (ob->id("_animal_meat") && from->query_prop(RANGER_I_TASK) == COOK_TASK)
    {
        // Roasting task object
        if (ob->query_prop(RANGER_S_ROASTED) == name)
        {
            set_alarm(1.0, 0.0, &command("say Nice job on the roast!"));
            from->remove_prop(RANGER_I_TASK);
            from->remove_prop(RANGER_O_ROASTED);

            if (present("ashes", environment()) ||
              present("campfire", environment()))
            {
                set_alarm(1.6, 0.0, &command("emote looks around."));
                set_alarm(1.8, 0.0, &command("grumble disappoint"));
                set_alarm(1.9, 0.0, &command("extinguish campfire"));
                set_alarm(2.0, 0.0, &command("kick ashes"));
                set_alarm(2.1, 0.0, &command("say But you didn't clean " +
                    "up after yourself. Oh well, I'll reward you anyways."));
                set_alarm(2.2, 0.0, &do_reward(name, "moderately",
                    "completing task number two"));
                MANAGER->increment_task_number(name);
            }
            else
            {
                set_alarm(1.6, 0.0, &command("say And you even cleaned up " +
                    "after yourself! Good job!"));
                set_alarm(1.7, 0.0, &do_reward(name, "moderately",
                    "completing task number two"));
                set_alarm(1.8, 0.0, &do_reward(name, "slightly",
                    "doing extra well on task number two"));
                MANAGER->increment_task_number(name);
            }

            environment()->reset_task(COOK_TASK);
        }
        else
        {
            set_alarm(1.0, 0.0, &command("say Hmmm, I'm not sure you " +
                "did this all by yourself! I'm afraid I can't reward you."));
        }
    }
    else if (strlen(ob->query_herb_name()) &&
      from->query_prop(RANGER_I_TASK) == HERB_TASK)
    {
        herb = TASK_HERBS[NAME_TO_RANDOM(name, TASK_RANDOM,
            sizeof(TASK_HERBS))];

        // Herb task object
        if (ob->query_herb_name() == herb)
        {
            set_alarm(1.0, 0.0, &command("say Very nice specimen of " +
                herb + "!"));
            from->remove_prop(RANGER_I_TASK);
            set_alarm(1.3, 0.0, &do_reward(name, "moderately",
                 "completing task number five"));

            if (!ob->query_dried())
            {
                set_alarm(1.2, 0.0, &command("say An extra reward " +
                    "for getting it fresh!"));
                set_alarm(1.3, 0.0, &do_reward(name, "slightly",
                    "doing extra well on task number five"));
            }
            else
                set_alarm(1.2, 0.0, &command("say It would have been " +
                    "better fresh, but I'll still reward you a little."));

            MANAGER->increment_task_number(name);
            environment()->reset_task(HERB_TASK);
        }
        else
        {
            set_alarm(1.0, 0.0, &command("say So you know what an " +
                "herb is. This one, however, is not " + herb + "."));
            set_alarm(1.2, 0.0, &command("put " + OB_NAME(ob)));
        }
    }
    else if (strlen(ob->query_potion_name()) &&
      from->query_prop(RANGER_I_TASK) == POTION_TASK)
    {
        // Potion task object
        if (ob->query_prop(RANGER_S_MADE_POTION) == name)
        {
            if (ob->query_strength() > 17)
            {
                if (!from->query_prop(RANGER_S_POTION))
                    potions = ({});
                else
                    potions = from->query_prop(RANGER_S_POTION);

                potion = ob->query_potion_name();
                if (member_array(potion, potions) != -1)
                {
                        set_alarm(0.5, 0.0, &command("quaff potion"));
                        set_alarm(1.0, 0.0, &command("say Nice potion, but " +
                            "you already gave me " + 
                            LANG_ADDART(potion) + "."));
                }
                else
                {
                    set_alarm(0.5, 0.0, &command("quaff potion"));
                    set_alarm(1.0, 0.0, &command("say Good job on the " +
                        ob->query_potion_name() + "!"));
                    potions += ({ potion });
                    from->add_prop(RANGER_S_POTION, potions);

/*
                    if (member_array("avarywalme potion", potions) != -1 &&
                      member_array("este potion", potions) != -1 &&
                      member_array("wenya potion", potions) != -1)
*/
                    if (member_array("avarywalme", potions) != -1 &&
                      member_array("este", potions) != -1 &&
                      member_array("wenya", potions) != -1)
                    {
                        from->remove_prop(RANGER_I_TASK);
                        from->remove_prop(RANGER_S_POTION);
                        set_alarm(1.2, 0.0, &do_reward(name, "moderately",
                             "completing task number six"));
                        MANAGER->increment_task_number(name);
                        environment()->reset_task(POTION_TASK);
                    }
                }
            }
            else
            {
                set_alarm(0.5, 0.0, &command("quaff potion"));
                set_alarm(1.0, 0.0, &command("say I think you'd " +
                    "better work on your technique. Please mix " +
                    "a strong or powerful " + ob->query_potion_name() +
                    " for your reward."));
            }
        }
        else
        {
            set_alarm(1.0, 0.0, &command("say What do you think " +
                "you're doing trying to pawn off someone else's " +
                "work for your own?"));
            set_alarm(1.2, 0.0, &command("put " + OB_NAME(ob)));
        }
    }
    else if (ob->query_prop(RANGER_I_RABBIT) &&
      from->query_prop(RANGER_I_TASK) == TRACK_TASK)
    {
        set_alarm(1.0, 0.0, &command("say Excellent! That was " +
            "a tricky task!"));
        from->remove_prop(RANGER_I_TASK);
        from->remove_prop(RANGER_I_RABBIT);
        set_alarm(1.2, 0.0, &do_reward(name, "moderately",
            "completing task number three"));
        MANAGER->increment_task_number(name);
        environment()->reset_task(TRACK_TASK);
    }
    else if (ob->id("_Ranger_Task_Eight_Proof") &&
      from->query_prop(RANGER_I_TASK) == WARRIORS_TASK)
    {
        team_name = from->query_prop(WARG_S_TEAM);
        if (!strlen(team_name))
        {
            command("frown");
            command("say You need to kill the warg " +
                "with a Ranger teammate.");
            command("say How did you get this fang?");
            from->remove_prop(RANGER_I_TASK);
            from->remove_prop(WARG_S_TEAM);
            environment()->reset_task(WARRIORS_TASK);
            ob->remove_object();
            command("emote throws the fang away into the " +
                "bushes.");
            return;
        }
        teammate = present(team_name, environment(TO));
        if (!objectp(teammate))
        {            
            command("say Where is your teammate?");
            command("peer");
            command("say If you can't follow instructions, you " +
                "won't make much of a ranger!");
            ob->remove_object();
            from->remove_prop(RANGER_I_TASK);
            from->remove_prop(WARG_S_TEAM);
            environment()->reset_task(WARRIORS_TASK);
            command("emote throws the fang away into the " +
                "bushes.");
            return;
        }
        set_alarm(1.0, 0.0, &command("say Excellent! That was " +
            "a dangerous task! You have proven your bravery."));
        from->remove_prop(RANGER_I_TASK);
        from->remove_prop(WARG_S_TEAM);
        teammate->remove_prop(WARG_S_TEAM);
        set_alarm(1.2, 0.0, &do_reward(name, "moderately",
            "completing the warrior task"));
        set_alarm(1.2, 0.0, &do_reward(team_name, "moderately",
            "assisting " + capitalize(name) + " to finish " +
            "the warrior task"));
        MANAGER->increment_task_number(name);
        environment()->reset_task(WARRIORS_TASK);
        return;
    }
    else if (ob->id("coin"))
    {
        set_alarm(0.4, 0.0, &command("frown"));
        set_alarm(1.2, 0.0, &command("say What are you trying to do? " +
            "Bribe me?"));
        set_alarm(1.6, 0.0, &command("emote looks indignant."));
    }
    else
    {
        // Not a task object
        set_alarm(1.0, 0.0, &command("put " + OB_NAME(ob)));
    }
}

/* 
 * Function name: greet
 * Description:   This function makes the npc do a greeting to people it
 *                already knows and to fellow npc's. It is possible to
 *                redefine, note however that it should never contain an
 *                'introduce myself' command.
 * Arguments:     object who - the living that introduced to me
 *
 */                   
public void
greet(object who)
{
    // He won't greet an enemy! 
    if (member_array(who, query_enemy(-1)) > -1) 
    { 
        command("glare " + OB_NAME(who)); 
    } 
    else if (!objectp(query_attack())) 
    {  
        command("nod briefly " + OB_NAME(who)); 
    } 
} 

/* 
 * Function name:   introduce 
 * Description:     This function makes the npc do an introduction to a 
 *                  player that has not been introed to it earlier. The 
 *                  function may be redefined to create variety. 
 * Arguments:       object who - the living that introduced to me 
 * 
 */

public void 
introduce(object who)
{
    if (who->query_race_name() == "goblin")
    {
        command("peer suspiciously " + OB_NAME(who));
        command("rsay Be gone, foul creature!");
        return;
    }

    // she won't intro to an enemy 
    if (member_array(who, query_enemy(-1)) > -1) 
    { 
        command("kick " + OB_NAME(who)); 
    } 
    else 
    { 
        command("introduce myself to " + OB_NAME(who)); 
        command("hail " + OB_NAME(who)); 
    } 
} 

