/* Palanthas Adventurer's Guild from Teth's '96 Solace adv_guild.
 * Mortis 12.2005
 * Finish descs, skills, etc.
 *
 * Completed operational basics and added donation box.
 * Mortis 09.2014
 *
 * Reduced number of skills trained. It exceeded the maximum for
 * an adventurers guild of 400 levels of skills
 * Arman 12.2017
 */

#include <macros.h>
#include <ss_types.h>
#include "../local.h"
#include CLOCKH

inherit MONKS_ROOMBASE;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

/* Global variables */

object abox;

string
query_to_jail()
{
    return "southwest";
}

/* Prototypes */

public void 
set_up_skills();


public void
reset_palan_room()
{
/*    if (!gTrainer)
    {
        gTrainer = clone_object(LIV + "mbarista");
        gTrainer->move(TO);
    }*/
}

public void
create_palan_room()
{
    set_short("Palanthas Adventurer's Guild Tower");
    set_long("In the lower level of a tower that is both tidy and well-"
    + "equipped. A rack in one corner carries some training equipment, "
    + "while several ropes hang from the ceiling. There is a table in the "
    + "far end of the room. A series of elevated planks occupies the "
    + "northeast alcove. If the trainer is present, she may help you <learn> "
    + "or <improve> skills for a fee. You may also <meditate> here to see "
    + "how your abilities are progressing as well as refocus experience "
    + "on them.\n");

    add_item(({"wall","walls","floor"}),"This portion of the " +
        "room is made of polished wood, but there's nothing interesting " +
        "about it.\n");
    add_item(({"room","training hall","hall"}),"This room is furnished " +
        "for the intent of training people.\n");
    add_item(({"table"}), "The table contains training things. They're "
    + "pretty good.\n");
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
    add_item(({"rings","iron rings"}), "They seem to be made of blackened " +
        "iron, and their only use is to suspend the ropes.\n");

    add_exit(NOBLE + "ser4","southwest","@@remove_medi_props@@", 0);

    abox = clone_object(MONKS + "obj/adv_guild_box");
    abox->move(TO);
   
    create_skill_raise();
    set_up_skills();
   
    reset_palan_room();
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
    init_guild_support();
    add_action("gs_meditate","meditate");
    add_action("do_climb", "climb");
    add_action("do_walk","walk");
    add_action("do_study","study");
    init_skill_raise();
    ::init();
}

public int
do_climb(string str)
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

public int
do_walk(string str)
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

public int
do_study(string str)
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
    write("You kneel and start thinking about the sound of one hand "
    + "clapping until you're fairly sure you're meditating. You peek "
    + "around to see if anyone sees how awesome you're doing. Now that "
    + "you're meditating, you can <estimate> your physical and mental "
    + "abilities as well as <set> which ones to focus your future "
    + "experience on. When you are done, you can <rise>.\n");
   
    say(QCTNAME(TP) + " kneels and looks like they're meditating. "
    + C(HE(TP)) + " peeks around with one eye open to see if anyone "
    + "is watching " + HIM(TP) + " to see how awesome " + HE(TP)
    + "'s doing.\n");
}


public int
gs_hook_rise()
{
    write("You open your eyes and hop back up on your feet ready to do "
    + "anything of which you're capable!\n");

    say(QCTNAME(TP) + " opens " + HIS(TP) + " eyes and hops back to "
    + HIS(TP) + " feet.\n");
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
    sk_add_train(SS_ACROBAT,"maneuver acrobatically",0,0,20);
    sk_add_train(SS_ALCHEMY,"mix potions and poultices",0,0,20);
    sk_add_train(SS_ANI_HANDL,"handle and train animals",0,0,30);
    sk_add_train(SS_APPR_MON,"appraise friends and foes",0,0,30);
    sk_add_train(SS_APPR_OBJ,"appraise objects",0,0,30);
    sk_add_train(SS_APPR_VAL,"appraise values",0,0,30);
    sk_add_train(SS_AWARENESS,"be perceptive and watchful",0,0,30);
    sk_add_train(SS_BLIND_COMBAT,"fight in the dark or blind",0,0,20);
    sk_add_train(SS_CLIMB,"climb up and down",0,0,30);
    sk_add_train(SS_FR_TRAP,"find and remove traps",0,0,20);
    sk_add_train(SS_HERBALISM,"find and recognize herbs",0,0,20);
    sk_add_train(SS_LANGUAGE,"understand linguistics",0,0,30);
    sk_add_train(SS_RIDING,"ride creatures that carry you",0,0,20);
    sk_add_train(SS_SWIM,"swim",0,0,30);
    sk_add_train(SS_TRADING,"get better prices at shops",0,0,30);
    // sk_add_train(SS_ELEMENT_FIRE,"use fire magic",0,0,20);
    // sk_add_train(SS_ELEMENT_WATER,"use water magic",0,0,20);
    // sk_add_train(SS_ELEMENT_EARTH,"use earth magic",0,0,20);
    // sk_add_train(SS_ELEMENT_AIR,"use air magic",0,0,20);
    // sk_add_train(SS_ELEMENT_LIFE,"use life magic",0,0,20);
    // sk_add_train(SS_ELEMENT_DEATH,"use death magic",0,0,20);
    // sk_add_train(SS_HIDE,"hide yourself or items",0,0,20);
    // sk_add_train(SS_HUNTING,"find food in the wild",0,0,30);
    // sk_add_train(SS_LOC_SENSE,"recognize the surroundings",0,0,30);
    // sk_add_train(SS_OPEN_LOCK,"open locks",0,0,20);
    // sk_add_train(SS_PICK_POCKET,"steal things from people",0,0,20);
    // sk_add_train(SS_SNEAK,"sneak unseen",0,0,20);
    // sk_add_train(SS_SPELLCRAFT,"use arcane or divine magic",0,0,20);
    // sk_add_train(SS_TRACKING,"track people's movements outside",0,0,30);
    // sk_add_train(SS_UNARM_COMBAT,"fight without weapons",0,0,30);
    // sk_add_train(SS_WEP_AXE,"fight with axes",0,0,30);
    // sk_add_train(SS_WEP_CLUB,"fight with clubs",0,0,30);
    // sk_add_train(SS_WEP_KNIFE,"fight with knives",0,0,30);
    // sk_add_train(SS_WEP_POLEARM,"fight with polearms like halberds",0,0,30);
    // sk_add_train(SS_WEP_SWORD,"fight with swords",0,0,30);
    // sk_add_train(SS_DEFENCE,"use defensive maneuvers",0,0,20);
}

public int
sk_improve(string sk)
{
/*    if (!(present("carl", this_object())))    
    {
        write("Without the trainer, it is impossible to train here.\n");
        return 1;
    }*/
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
    notify_fail("This adventurer's guild can teach you nothing further in "
    + "this skill. If you are interested in improving it further, seek out "
    + "a racial, occupational, layman, or craft guild that specializes in "
    + "it.\n");
    return 0;
}

