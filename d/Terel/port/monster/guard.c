/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * guard.c
 *
 * A gate guard. Mortricia 921212
 * Modifed for the hunt assassin quest by Shinto 980725
 * */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";
#include "/d/Terel/include/quest_bits.h"

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#define ARM_DIR         PORT_DIR + "armour/"
#define WEP_DIR         PORT_DIR + "weapon/"
#define HUNTING_TREVIN "_i_hunting_trevin"
#define KILLED_TREVIN "_i_killed_trevin"
#define TALKED_TO_INNKEEP "_i_talked_innkeep"

#define ADJS            ({"brown", "grey", "dirty", "wet"})

#define ALIGN           -70



public string
reply_task()
{
    write_file("/d/Terel/port/log/ask_hunt",
        TP->query_name()+ " asked quest." + ctime(time()) + "\n");


    if (!TP->test_bit("Terel", QUEST_HAQ_GROUP, QUEST_HAQ_BIT))
    {
        if (TP->query_prop(HUNTING_TREVIN))
        {
            command("sigh");
            command("say I told you! Hunt down the tall wiry male human.");
            return "";
        }

        command("say There has been a murder, I need you to hunt down "+
                       "the killer.");
        command("say Another villager saw the assassin, he describes" +
                       " him as a tall wiry male human.");
        command("say The villager claims he headed north, by now he could be"+
                       " hiding out anywhere in Calathin or the Silver Forest.");
        command("say Find him, and bring him to justice and you will be well "+
                       "rewarded.");
        TP->add_prop(HUNTING_TREVIN, 1);
        return "";
    }
    return "say Hmm, I don't seem to have any more I need done.";
}

public string
reply_reward()
{

    if (!TP->query_prop(HUNTING_TREVIN))
    {
        command("say Reward for what? You aren't doing anything " +
            "for me.");
        return "";
    }

    if (!TP->query_prop(KILLED_TREVIN))
    {
        command("say I said hunt him down and kill him!");
        return "";

    }
    if(!TP->query_prop(TALKED_TO_INNKEEP))
    {
        command("say Good work, glad you got him!");
        TP->add_exp(QUEST_HAQ_EXP/2);
        TP->set_bit(QUEST_HAQ_GROUP, QUEST_HAQ_BIT);
        write("You feel more experienced!\n");
        say(QCTNAME(TP) + " has become more experienced.\n");
         write_file(QUEST_LOG, TP->query_name() +

            " cheated on the hunt assassin quest (" + ctime(time()) + ")\n");

        TP->remove_prop(KILLED_TREVIN);
        TP->remove_prop(HUNTING_TREVIN);
        return "";
    }

    TP->add_exp(QUEST_HAQ_EXP);
    TP->set_bit(QUEST_HAQ_GROUP, QUEST_HAQ_BIT);
    command("say You got him, thank the Star.");
    command("say You've done a good thing. Thank you very much.");
    write("You feel more experienced.\n");
    say(QCTNAME(TP) + " has become more experienced.\n");
    write_file(QUEST_LOG, TP->query_name() +
                   " solved the hunt assassin quest (" + ctime(time()) + ")\n");
    TP->remove_prop(KILLED_TREVIN);
    TP->remove_prop(HUNTING_TREVIN);
    return "";
}


void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name(({"guard","captain"}));
    set_name("guard");
    set_short("tall guard captain");
    set_long("It's a dark and tall gate guard. He normally stands at the " +
	     "gate in the fence.\n");

    set_adj(({"dark", "tall"}));
    set_race_name("human");
    set_gender(MALE);

    set_stats(({35, 35, 35, 30, 30, 35}));
    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(ALIGN);

    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_WEP_SWORD,    50);
    set_skill(SS_AWARENESS,    50);

    set_all_hitloc_unarmed(20);
    set_all_attack_unarmed(20, 20);

    add_ask(({"task", "quest", "tour", "job", "work"}),
        reply_task, 1);
    add_ask(({"reward", "for reward"}), reply_reward, 1);

    set_alarm(1.0, -1.0, "dress_me");
}

dress_me()
{
    object sword, cloak;
    string adj;

    FIX_EUID;
    adj = ADJS[random(sizeof(ADJS))];
    cloak = clone_object(ARM_DIR + "cloak");
    cloak -> set_short(adj + " cloak");
    cloak -> set_long("A " + adj + " cloak.\n");
    cloak -> set_adj(adj);
    cloak -> move(TO);
    command("wear cloak");

    sword = clone_object(WEP_DIR + "plain_sword");
    sword -> move(TO);
    command("wield sword");
}

