/* Vingaard Keep Adventurer's Guild
 * by Teth, Jan 2, 1997
 */

#include "../local.h"
#include <macros.h>
#include <ss_types.h>

inherit IN_BASE;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

/* Global variables */

object gTrainer;

/* Prototypes */

public void 
set_up_skills();


public void
reset_vin_room()
{
    if (!gTrainer)
    {
        gTrainer = clone_object(VNPC + "talia.c");
        gTrainer->move(TO);
    }
}

public void
create_vin_room()
{
    set_short("Vingaard Keep Militia Training Area");
    set_long("In this rectangular room, residents and friendly visitors " +
        "to Vingaard Keep are able to learn or improve some basic " +
        "skills when there is a trainer present. Fine sand can be seen " +
        "in one corner of the room. Standing upright against one wall " +
        "is a rack containing training equipment. A set of mats " +
        "occupies some space in a quiet area. There is an exit to the " +
        "south, leading back to the street.\n");

    AI(({"wall","walls","floor"}),"This portion of the room is made of " +
        "dreary grey stone, so that interest can be focussed on the " +
        "tasks at hand.\n");
    AI(({"dreary stone","grey stone","dreary grey stone","stone"}),
        "The grey stone is most likely granite.\n");
    AI("rack","The rack in the corner is made of a plain, but " +
        "polished wood. It carries a fair sum of training equipment.\n");
    AI(({"equipment","training equipment"}),"Situated on the rack " +
        "are blunt wooden weapons, of no value other than training.\n");
    AI(({"blunt weapons","blunt wooden weapons","wooden weapons"}),
        "Swords, axes and knives are the only three weapon types in the " +
        "rack. They are made for training purposes only, so it would be " +
        "pointless to try and take them.\n");
    AI(({"mats","set of mats"}),"The mats appear to be a place where you "+
        "can <meditate> and appraise your physical and mental " +
        "faculties.\n");
    AI(({"sand","fine sand"}),"The fine sand in the corner appears to be "+
        "used to test trainee's abilities to track. You might be able " +
        "to study it further.\n");
    AI(({"tracks","tracks in the sand"}),"The tracks are made to aid " +
        "trainees in assessing their ability to track.\n");
    add_search(({"sand","fine sand"}),2,KROBJECT + "sand_grain", -20);

    AE(VROOM + "ws1","south","@@remove_medi_props");
   
    create_skill_raise();
    set_up_skills();
   
    reset_vin_room();
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
    add_action("do_study","study");
    init_skill_raise();
    ::init();
}

public int do_study(string str)
{
    int skl;
    if ((str == "sand")||(str == "fine sand"))
    {
        skl = TP->query_skill(SS_TRACKING);
        if (skl > 70)
        {
            say(QCTNAME(TP) + " scoffs at the tracks in the sand, " + 
                "apparently thinking them too easy to read.\n");
            write("You scoff at the ease at which you are able to " +
                "read the tracks.\n");
            return 1;
        }

        if (skl <= 70 && skl > 50)
        {
            say(QCTNAME(TP) + " smiles confidently when studying the " +
                "tracks in the sand.\n");
            write("You smile confidently when studying the tracks in " +
                "the sand, knowing you are fully able to read them.\n");
            return 1;
        }

        if (skl <= 50 && skl > 20)
        {
            say(QCTNAME(TP) + " looks challenged, but also " +
                "appears reasonably confident, while investigating the " +
                "tracks in the sand.\n");
            write("You are challenged by the tracks, but are able to " +
                "understand and read most of them.\n");
            return 1;
        }
        if (skl <= 20 && skl > 5)
        {
            say(QCTNAME(TP) + " shows some understanding of the " +
                "patterns, but by no means comprehends " +
                "everything about the tracks in the sand.\n");
            write("You are able to understand the basic principles of " +
                "the tracks, but you can't fathom the intricacies.\n");
            return 1;
        }
        if (skl <= 5)
        {
            say(QCTNAME(TP) + " looks confused while examining the " +
                 "tracks in the sand.\n");
             write("You are befuddled by the tracks in the sand.\n");
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
    sk_add_train(SS_WEP_AXE,"fight with an axe",0,0,30);
    sk_add_train(SS_WEP_KNIFE,"fight with a knife",0,0,30);
    sk_add_train(SS_TRACKING,"track",0,0,30);
    sk_add_train(SS_WEP_SWORD,"fight with a sword",0,0,30);
    sk_add_train(SS_UNARM_COMBAT,"fight unarmed",0,0,20);
    sk_add_train(SS_BLIND_COMBAT,"fight blind",0,0,20);
}

public int
sk_improve(string sk)
{
    int playeralign;

    if (!(present("talia", this_object())))    
    {
        write("Without the trainer, it is impossible to train here.\n");
        return 1;
    }
    playeralign = TP->query_alignment();
    if ((playeralign < 0 ) || (TP->query_prop(I_WAS_EVIL)))
    {
        write("The trainer states: We don't train those of your ilk " +
            "here.\n");
        if (!TP->query_prop(I_WAS_EVIL))
        TP->add_prop(I_WAS_EVIL, 1);
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
    notify_fail("Somehow you feel that Talia is unable to give " +
        "you more training in that skill. You'll have to seek another.\n");
    return 0;
}

