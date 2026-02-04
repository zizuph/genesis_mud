/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * farm2_farmer.c
 * Tomas  -- Nov. 1999
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
#include "/d/Terel/include/quest_bits.h"
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#define ARM_DIR         CALATHIN_DIR + "farms/armour/"
#define WEP_DIR         CALATHIN_DIR + "farms/weapon/"
#define ASKED_FARM2_CROW "_i_asked_crow"
#define KILLED_CROW "_i_killed_crow"
#define FOUND_THE_BEAR "_i_found_bear"


public string
reply_task()
{
    write_file("/d/Terel/calathin/log/killed_the_farm2_crow",
        TP->query_name()+ " asked quest." + ctime(time()) + "\n");


    if (!TP->test_bit("Terel", QUEST_KCQ_GROUP, QUEST_KCQ_BIT))
    {
        if (TP->query_prop(ASKED_FARM2_CROW))
        {
            command("sigh");
            command("say I told you! Kill the crow, I dont know how, just do it.");
            return "";
        }
        command("say The crows are eating us out of house and home!");
        command("say I'd kill them myself, but the crows keep flying out of reach.");
        command("say Find a way, then kill the crow and you will be well "+
           "rewarded.");
        TP->add_prop(ASKED_FARM2_CROW, 1);
        return "";
    }
    return "say Hmm, no killing the crow is all I needed. Check back later, perhaps " +
       "i'll have something else for you to do later on.";
}

public string
reply_reward()
{

    if (!TP->query_prop(ASKED_FARM2_CROW))
    {
        command("say Reward for what? You aren't doing anything " +
            "for me.");
        return "";
    }

    if (!TP->query_prop(KILLED_CROW))
    {
        command("say The crows are still stealing from my farm, " +
           "you've done nothing to help me yet!");
        return "";

    }
    if(!TP->query_prop(FOUND_THE_BEAR))
    {
        command("say Good work, you have done a great service for my family!");
        TP->add_exp(QUEST_KCQ_EXP/2);
        TP->set_bit(QUEST_KCQ_GROUP, QUEST_KCQ_BIT);
        write("You feel more experienced!\n");
        say(QCTNAME(TP) + " has become more experienced.\n");
         write_file(QUEST_LOG, TP->query_name() +
            " cheated on the kill crow quest (" + ctime(time()) + ")\n");

        TP->remove_prop(KILLED_CROW);
        TP->remove_prop(FOUND_THE_BEAR);
        TP->remove_prop(ASKED_FARM2_CROW);
       return "";
    }

    TP->add_exp(QUEST_KCQ_EXP);
    TP->set_bit(QUEST_KCQ_GROUP, QUEST_KCQ_BIT);
    command("say You got him, nice work!");
    command("say You've saved our farm, Thank you!.");
    write("You feel more experienced.\n");
    say(QCTNAME(TP) + " has become more experienced.\n");
    write_file(QUEST_LOG, TP->query_name() +
       " solved the kill crow quest (" + ctime(time()) +")\n");
    TP->remove_prop(KILLED_CROW);
    TP->remove_prop(FOUND_THE_BEAR);
    TP->remove_prop(ASKED_FARM2_CROW);
   return "";
}


void
create_monster()
{
    set_name("farmer");
    set_short("farmer");
    set_long("The old farmer looks like she has a problem on her hands.\n");
    set_adj(({"frustrated", "old"}));
    set_race_name("human");
    set_gender(1);

    set_stats(({100, 100, 100, 100, 100, 100}));
    SET_MAX_HP;
    SET_MAX_MANA;

    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_AWARENESS,    50);

    set_all_hitloc_unarmed(50);
    set_all_attack_unarmed(50, 50);

    add_ask(({"task", "quest", "tour", "job", "work"}),
        reply_task, 1);
    add_ask(({"reward", "for reward"}), reply_reward, 1);

     dress_me();
}
void dress_me()
{
    seteuid(getuid(this_object()));

    clone_object(CALATHIN_DIR+"farms/weapon/rake")->move(TO);
    command("wield rake");
    clone_object(CALATHIN_DIR+"/farms/armour/dress")->move(TO);
    clone_object(CALATHIN_DIR+"/farms/armour/shoes")->move(TO);
    clone_object(CALATHIN_DIR+"/farms/armour/overcoat")->move(TO);
    clone_object(CALATHIN_DIR+"/farms/armour/hat")->move(TO);
    command("wear all");
}
