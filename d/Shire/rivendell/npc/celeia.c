/*
 * NPC for brooch quest, Celeia
 * By Finwe, june 1998
 */


#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Shire/rivendell/npc/elfmaker.h"

inherit "/d/Shire/rivendell/npc/elfmaker.c";
#include "/d/Shire/common/make_money.h"

// randomly places the brooch throughout the area
#define BROOCH_DEST ONE_OF_LIST(({ FOREST_DIR + "forest01",\
                                   FOREST_DIR + "forest12",\
                                   FOREST_DIR + "forest33",\
                                   FOREST_DIR + "forest58",\
                                   FOREST_DIR + "forest64",\
                                   FOREST_DIR + "forest83"}))

#define QUEST_NAME  "brooch"
#define ELF_WEP     RWEP_DIR
#define ELF_ARM     RARM_DIR
#define ELF_OBJ     ROBJ_DIR

void
create_elf()
{
    if(!IS_CLONE)
        return;

    set_type(GUARD);
    set_name("celeia");
    set_living_name("celeia");
    set_adj(({"sad","golden-haired"}));
    add_adj("elegant");
    set_race_name("elf");
    set_gender(G_FEMALE);
    set_long("This elf is fair like all the others of her race. " +
        "Her golden hair identifies her as a member of an " +
        "ancient elven family. Her ageless features hide many " +
        "of the travels she has seen during her long lifetime. " +
        "She seems to be upset.\n");
    set_elf_average(130);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 100*1000);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(LIVE_I_SEE_DARK, 20);
    add_prop("_ranger_m_no_disarm_drop", 1);
    add_prop("_brooch_quest_",1);
    //add_prop(LIVE_I_QUICKNESS, 10);

    add_subloc("_celia_quest_elf", TO);
    add_ask(({"brooch","quest","task","help"}),"@@ask_brooch");

    set_act_time(4);
    add_act("emote sobs softly.");
    add_act("emote sighs deeply.");
    add_act("emote wonders where it could be at.\n");
    arm_elf();
}


string
ask_brooch()
{
    object brooch;


    if (TP->query_prop("_brooch_quest_"))
    {
        command("say You know what you must do. What? You can't " +
            "help me after all?");
        command("sniff");
        command("cry");
        return "";
    }


    if (CHECK_QUEST(TP, QUEST_NAME))
    {
        command("say Thank you for your offer, but you have " +
            "already helped me.");
        return "";
    }

    command("say One day I was on patrol, watching the borders to");
    command("say see what the orcs were doing. We hastened back to");
    command("say make our reports to Elrond. While in the forest,");
    command("say I tripped and fell. As I reached out to break my");
    command("say fall, a branch ripped my cloak. On the cloak was");
    command("say a priceless brooch that has been handed down for");
    command("say generations. I didn't miss it until I returned");
    command("say to my home. When I went back to look for it, the");
    command("say brooch couldn't be found. If you find it and");
    command("say return it to me, it would mean so much to me. I");
    command("say will reward you for your efforts.");

    TP->add_prop("_brooch_quest_",1);
    command("say Good luck!");

    brooch = clone_object(ELF_OBJ + "brooch");
    brooch->move(BROOCH_DEST, 1);
    return "";

}

void 
test_quest(object player, object obj)
{

    if (!player->query_prop("_brooch_quest_"))
    {
        command("emote examines the " + obj->short() + " for a moment.");
        command("say I'm sure this " + obj->short() + " is worth something to " +
            "someone, but it is not what I am looking for.");
	return;
    }
    if (!REWARD_QUEST(player, QUEST_NAME))
    {
	command("say Thank you for your concern, but you have helped me before.");
	return;
    }
    command("gasp");
    command("say Oh, thank you! You have found my brooch!");
    command("say It has been in my family for many ages!");
    command("emote examines the brooch carefully.");
    command("emote face lights up.");
    command("say Oh my, the clasp broke. No wonder I lost it. I " +
        "will have to have that fixed.");
    command("say Take this as a reward for helping me.");
    player->remove_prop("_brooch_quest_");
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");

}

public void
give_back(object from, object obj)
{
    write("The elf gives it back to you.\n");
    obj->move(from);
    return;
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;
    if (obj->id("_brooch_quest_")) 
        set_alarm(5.0, 0.0, &test_quest(from, obj));        
    else
    {
        set_alarm(5.0,0.0, &give_back(from, obj));
        return;
    }
}

