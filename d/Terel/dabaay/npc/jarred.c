/*
 * This is an NPC named "Jared Head".  He is called by stumble.c, and exists
 * to serve and watch over the Stumble Inn. 
 *
 * Jan 2021 - Lucius - Commented out set_living_name
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <const.h>
#include <ss_types.h>
inherit "/std/act/action";
inherit "/std/act/seqaction";
#include "/d/Terel/include/quest_bits.h"

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#define HUNTING_TREVIN "_i_hunting_trevin"
#define KILLED_TREVIN "_i_killed_trevin"
#define TALKED_TO_INNKEEP "_i_talked_innkeep"

public string
reply_task()
{
    write_file("/d/Terel/dabaay/log/ask_hunt",
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

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    if (!IS_CLONE)
	return;

    ::create_monster();
    set_name("jarred");
//    set_living_name("jarred");    
    set_race_name("halfling");
    set_adj(({"curly-haired","lazy"}));
    set_long(
        "He is a lazy-looking curly-haired halfling, that manages "+
        "the Stumble Inn.\n");

    default_config_npc(70);
    set_all_hitloc_unarmed(35);
    set_skill(SS_DEFENCE,      60);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_UNARM_COMBAT, 70);

    set_gender(G_MALE);
    add_prop(LIVE_I_QUICKNESS, 50);
    add_prop(LIVE_I_ALWAYSKNOWN, 1);

    add_prop(OBJ_M_NO_ATTACK,"He is much to helpful to want to do that.\n");

    add_ask(({"job", "work", "task", "quest", "help"}),
        reply_task, 1);
    add_ask(({"reward me","reward"}), reply_reward, 1);

}

