/*
 * Filename:    adv_guild.c
 * Description  Solace Adventurer's Guild
 *
 * Coded by Teth, April 28, 1996
 *
 * Revision history:
 */

#include "../local.h"
#include <macros.h>
#include <ss_types.h>

inherit SOLINROOM;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

/* Global variables */

object gTrainer;

/* Prototypes */

public void
set_up_skills();


public void
reset_solace_room()
{
    if (!gTrainer)
    {
        gTrainer = clone_object(NPC + "sasha.c");
        gTrainer->move(TO);
    }
}

public void
create_solace_room()
{
    set_short("The House of Adventurers");
    set_long("Nestled within a tree, this small training hall is " +
        "both tidy and well-equipped. A rack in one corner carries " +
        "some training equipment, while several ropes hang from the " +
        "ceiling. The table in the far end of the room has items upon " +
        "its surface. A series of elevated planks occupies the northeast " +
        "alcove. If the trainer is present, she may help you learn or " +
        "improve skills for a fee. You may also <meditate> here, and " +
        "enter a state of bliss.\n");

    add_item(({"wall","walls","floor"}),"This portion of the " +
        "room is made of polished wood, but there's nothing interesting " +
        "about it.\n");
    add_item(({"room","training hall","hall"}),"This room is furnished " +
        "for the intent of training people.\n");
    add_item("rack","The rack in the corner is made of a plain, but " +
        "polished wood. It carries a fair sum of training equipment.\n");
    add_item(({"equipment","training equipment"}),"Situated on the rack " +
        "are blunt wooden weapons, of no value other than training.\n");
    add_item(({"blunt weapons","blunt wooden weapons","wooden weapons"}),
        "Swords and polearms are the only two weapon types in the rack. " +
        "They are made for training purposes only, so it would be " +
        "pointless to try and take them.\n");
    add_item(({"ropes","several ropes","rope"}),"These ropes hang from " +
        "the ceiling, perhaps 4 metres high. They are most likely used " +
        "to help train climbing. You may be able to climb them.\n");
    add_item("ceiling","The ceiling is not special in any way, other than " +
        "the iron rings that suspend the ropes.\n");
    add_item(({"rings","iron rings"}),"They seem to be made of blackened " +
        "iron, and their only use is to suspend the ropes.\n");
    add_item(({"table","surface","table surface"}),"The surface of the " +
        "table has several complicated-looking mechanisms resting " +
        "upon it.\n");
    add_item(({"items","mechanisms","complicated-looking mechanisms"}),
        "Looking more closely, you can tell that these items are " +
        "disassembled locks, in various states. They are however, chained " +
        "down.\n");
    add_item(({"locks","disassembled locks"}),"These locks are used to " +
        "train people how to open locks, and to understand the mechanisms " +
        "inside. Studying the locks might be interesting.\n");
    add_item(({"series of elevated planks","planks","elevated planks"}),
        "These elevated planks seem to be used to train people how to move " +
        "silently, and thus sneak better. Underneath the planks is a " +
        "detailed sound-making apparatus. You might be able to test your " +
        "sneaking abilities by walking on the planks.\n");
    add_item(({"detailed apparatus","sound-making apparatus","apparatus"}),
        "Depending on which plank the trainee walks on, the apparatus " +
        "seems to be constructed such that it will make a sound if the " +
        "person isn't cautious enough.\n");

    add_exit(ROOMS + "bridge_walk25","northwest","@@remove_medi_props");

    create_skill_raise();
    set_up_skills();

    reset_solace_room();
}


public int
remove_medi_props()
{
    TP->remove_prop(LIVE_I_MEDITATES);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
}


public void
init()
{
    object ob;
    if (ob = present("tour1", TP))
      ob->set_arr("advguild");
    init_guild_support();
    add_action("gs_meditate","meditate");
    add_action("do_climb", "climb");
    add_action("do_walk","walk");
    add_action("do_study","study");
    init_skill_raise();
    ::init();
}

public int do_climb(string str)
{
    int skl;
    if ((str=="ropes")||(str=="rope")||(str=="up rope")||(str=="up ropes"))
    {
        skl = TP->query_skill(SS_CLIMB);
        if (skl > 45)
        {
            say(QCTNAME(TP) + " effortlessly climbs up the rope and " +
                "back down again.\n");
            write("You effortlessly climb up the rope and back down " +
                "again.\n");
            return 1;
        }

        if (skl <=45 && skl >20)
        {
            say(QCTNAME(TP) + " climbs up and down the rope with some " +
                "effort.\n");
            write("You climb up and down the rope with some effort.\n");
            return 1;
        }

        if (skl <=20 && skl >2)
        {
            say(QCTNAME(TP) + " strains and struggles, but manages to " +
                "climb up and down the rope!\n");
            write("With strenuous effort, you manage to climb up and " +
                "down the rope!\n");
            return 1;
        }

        if (skl <=2)
        {
            say(QCTNAME(TP) + " tries with much effort, but is unable to " +
                "climb up the rope.\n");
            write("As much as you struggle, you are unable to climb " +
                "up the rope!\n");
            return 1;
         }
    }
    NF("Climb what?\n");
    return 0;
}

public int do_walk(string str)
{
    int skl;
    if ((str=="planks")||(str=="on planks"))
    {
        skl = TP->query_skill(SS_SNEAK);
        if (skl >= 30)
        {
             say(QCTNAME(TP) + " silently walks over every plank.\n");
             write("You silently walk over every plank.\n");
             return 1;
        }
        if (skl < 30 && skl >= 10)
        {
             say(QCTNAME(TP) + " makes creaking noises while walking on " +
                 "a few of the planks.\n");
             write("Some of the planks make creaking noises as you walk " +
                 "on them.\n");
             return 1;
        }
        if (skl < 10 && skl > 1)
        {
            say(QCTNAME(TP) + " walks on a few planks noiselessly, but " +
                "that doesn't happen very often.\n");
            write("You manage to walk on a few of the planks without " +
                "making any noise, but you are by no means perfect.\n");
            return 1;
        }
        if (skl <= 1)
        {
            say(QCTNAME(TP) + " makes creaking noises on the planks with " +
                "every single step made.\n");
            write("Every single step you make emits a noise.\n");
            return 1;
        }
     }
     NF("Walk on what?\n");
     return 0;
}

public int do_study(string str)
{
    int skl;
    if ((str == "locks")||(str == "disassembled locks"))
    {
        skl = TP->query_skill(SS_OPEN_LOCK);
        if (skl > 20)
        {
            say(QCTNAME(TP) + " scoffs at the locks on the table, " +
                "apparently thinking them too simple.\n");
            write("You scoff at the simplicity of the locks.\n");
            return 1;
        }
        if (skl <= 20 && skl > 9)
        {
            say(QCTNAME(TP) + " looks challenged, but also " +
                "appears reasonably confident, while investigating the " +
                "locks on the table.\n");
            write("You are challenged by the locks, but are able to " +
                "master most of them.\n");
            return 1;
        }
        if (skl <= 9 && skl > 3)
        {
            say(QCTNAME(TP) + " shows some understanding of the " +
                "mechanics, but by no means comprehends " +
                "everything about the locks on the table.\n");
            write("You are able to understand the basic principles of " +
                "the locks, but you can't fathom the intricacies.\n");
            return 1;
        }
        if (skl <= 3)
        {
            say(QCTNAME(TP) + " looks confused while examining the " +
                 "locks on the table.\n");
             write("You are bedazzled by the mechanics of the locks.\n");
             return 1;
        }
    }
    NF("Study what?\n");
    return 0;
}


public void
gs_hook_start_meditate()
{
    write("You start to concentrate solely upon your own mind and you " +
        "block off all your senses. A feeling of peace enters your inner " +
        "being, and somehow you see everything anew with a clarity and " +
        "precision that was unavailable to you before, yet you also know " +
        "that it is all in your mind. You feel at one with your body, able "+
        "to <estimate> your abilities with confidence. As well, you are " +
        "able to exert such control on your body that you can <set> which " +
        "abilities you are going to concentrate on in the future. To " +
        "leave these depths, you must <rise>.\n");

    say(QCTNAME(TP) + " enters into a trance and slowly kneels " +
        "down. " + C(PRONOUN(TP)) + " falls into a deep trance and " +
        "seems lost to the physical world around " + OBJECTIVE(TP) + ".\n");
}


public int
gs_hook_rise()
{
    write("The sense of peace leaves you as your consciousness stirs. " +
        "Physical reality assaults your senses, and the feeling that " +
        "you've never really seen things clearly before leaves you. Now, " +
        "you must prepare yourself for whatever the future brings you.\n");

    say(QCTNAME(TP) + " blinks once or twice as " + PRONOUN(TP) + " is " +
        "brought back to physical reality. " + QCTNAME(TP) + " then rises " +
        "and prepares to face the adventures ahead.\n");
}


public void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
}


public void
set_up_skills()
{
    sk_add_train(SS_ANI_HANDL,"handle and train animals",0,0,30);
    sk_add_train(SS_APPR_MON,"appraise friends and foes",0,0,30);
    sk_add_train(SS_APPR_OBJ,"appraise objects",0,0,30);
    sk_add_train(SS_CLIMB,"climb up and down",0,0,30);
    sk_add_train(SS_DEFENCE,"use defensive maneuvers",0,0,20);
    sk_add_train(SS_WEP_CLUB,"fight with a club",0,0,20);
    sk_add_train(SS_LOC_SENSE,"recognize the surroundings",0,0,30);
    sk_add_train(SS_OPEN_LOCK,"open locks",0,0,20);
    sk_add_train(SS_WEP_POLEARM,"fight with a polearm",0,0,15);
    sk_add_train(SS_SNEAK,"sneak unseen",0,0,15);
    sk_add_train(SS_SWIM,"swim",0,0,30);
    sk_add_train(SS_WEP_SWORD,"fight with a sword",0,0,30);
}

public int
sk_improve(string sk)
{
    if (!(present("sasha", this_object())))
    {
        write("Without the trainer, it is impossible to train here.\n");
        return 1;
    }
    return ::sk_improve(sk);
}

public int
sk_query_max(int snum)
{
    int *skills_available_here;
    mixed skval;

    skills_available_here = sk_query_train();

    if(member_array(snum, skills_available_here) == -1)
        return 0;

    if (!mappingp(sk_default))
        return 0;
    skval = sk_trains[snum];
    if (sizeof(skval)>2)
        return skval[2];
    else return 0;
}


public int
sk_hook_improved_max(string skill)
{
    notify_fail("Somehow you feel that Sasha is unable to give " +
        "you more training in that skill. You'll have to seek another.\n");
    return 0;
}

