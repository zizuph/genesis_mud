/*
 * Quest NPC for haunted citadel of Kryptgarden
 * by Finwe, August, 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";
inherit "/lib/unique";

#define QUEST_NAME_PROP "_citadel_quest"
#define MIN_HP 2500
// props for when mort gives part of life to dwarf for conversion

#define FOUND_BONES     "_found_bones"
#define CAN_SACRIFICE   (TP->add_prop(FOUND_BONES, 1))

int alarm_id;
void play_msg(object player, int stage);
void convert_dwarf();

void create_monster()
{
    int i;

    set_race_name("ghost");
//    set_name("ghost");
    add_name("_insect_quest_npc");
    set_adj("shadowy");
    set_adj("dwarf");
    add_name("undead");
    set_short("shadowy dwarf ghost");

    set_long("This is a " + query_short() + " and has been dead for unknown ages. He looks like he was tortured and probably died a terrible death. The ghost still has a regal look about him and looks around nervously.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_NO_BODY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK,10);
    add_prop(LIVE_I_UNDEAD, 15);
    add_prop(OBJ_M_NO_ATTACK,"He floats out of your reach.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK,1);


    set_alignment(0);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_gender(G_MALE);

            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 120 + random(25));
    set_base_stat(5, 100);

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

   /* Actions */
    set_act_time(5);
    set_chat_time(5);

    add_chat("We were once a proud race.");
    add_chat("Those insect people are evil.");
    add_chat("Have you come to cleanse the citadel for my people?");
    add_chat("If you are brave, I could use your help.");
    add_chat("I will rest peacefully once our citadel is purged of this evil.");
    add_chat("Only the bravest come here now.");

    add_act("sigh deep");
    add_act("emote looks forlornly");
    add_act("emote looks away wistfully.");
    add_act("emote looks around nervously.");
    add_act("emote floats around the room forlornly.");
    add_act("emote stops and listens intently to something.");

    set_mm_in(" floats in.");

    add_ask(({"task","help","quest"}),VBFC_ME("give_task"));
}


string give_task()
{


    if(TP->test_bit(DOMAIN, CITADEL_QUEST_GROUP, CITADEL_QUEST_BIT))
    {
	    command("say I thank you for your concern, but you have already helped me.");
	    return "";
    }

    if (TP->query_prop(QUEST_NAME_PROP))
    {
	    command("sigh sadly");
	    command("say Did I misjudge you? Was this task too much for you? I hope not.");
        command("say Please gather a spine, a head bone, a left and right arm bone, and a left and right leg bone for me.");
        command("say When you have gathered them, please come back here and ask for your reward.");
        command("sob");
	    return "";
    }
// check if player has enough HP to do quest.
    if(TP->query_max_hp()> MIN_HP && TP->query_hp()>(MIN_HP/2))
    {
        command("sigh sadly");
        command("Thank you for you ");
        command("say It happened many ages ago, so long ago I barely remember. Ages ago dwarves lived in the forest and were content with our lives. We were prosperous and traded with everyone but one day a swarm of insect-like creatures attacked us. They overwhelmed us and the forest and destroyed everyone there.");
        command("sniff sadly");
        command("say Our strongest warriors raced here but were quickly overwhelmed. Their queen came sacrificed the rest of us throughout the citadel. I was cursed by her, and remain here. Please help me defeat her.");
        command("say To start, I need you to gather the bones of those who were sacrificed. Please find me a spine bone. In order to break the curse, I will need a portion of your life.");
        command("say When you have found the bone and are ready to help me, return here and give the bone.");

        TP->add_prop(QUEST_NAME_PROP,1);
        return "";
    }
    else
    {
        command("sniff sadl");
        command("say I'm sure you could probably help me, but if you were to, you'd die, and I can't bear to think of that!");
        return "";
    }
}

void
failed_give(object obj,object from)
{

    command("say I have no need for such things.");
    write(TO->query_The_name(from)+" gives it back to you.\n");
    obj->move(from);
    return;
}

void reject_bone(string str, object obj, object from)
{
    command("say Ack! This " + str + " looks like it was stolen from a corpse! That won't do me any good!");
    command("say When you have properly found a " + str + ", come back to me.");
//    write(TO->query_The_name(from)+" gives it back to you.\n");
//    obj->move(from);
    command("drop bone");
    return;
}

// gives out tasks for the bones



void
give_head_task(object player)
{
    command("emote examines the spine bone carefully.");
    command("say Outstanding!");
    player->add_prop(OK_SPINE,1);
    player->remove_prop(FOUND_SPINE);
    command("say Next I need the head bone.");
    return;
}

void
give_larm_task(object player)
{
    command("emote examines the head bone carefully.");
    command("say Very good!");
    player->add_prop(OK_HEAD,1);
    player->remove_prop(FOUND_HEAD);
    command("say Next I need the left-arm bone.");
    return;
}

void
give_rarm_task(object player)
{
    command("emote examines the left-arm bone carefully.");
    command("say This is very good!");
    player->add_prop(OK_LARM,1);
    player->remove_prop(FOUND_LARM);
    command("say Next I need the right-arm bone.");
    return;
}

void
give_lleg_task(object player)
{
    command("emote examines the right-arm bone carefully.");
    command("say This bone looks like it was chewed on.");
    player->add_prop(OK_RARM,1);
    player->remove_prop(FOUND_RARM);
    command("say Next I need the left-leg bone.");
    return;
}

void
give_rleg_task(object player)
{
    command("emote examines the left-leg bone carefully.");
    command("say This bone looks like it was chewed on.");
    player->add_prop(OK_LLEG,1);
    player->remove_prop(FOUND_LLEG);
    command("say Last of all, I need the right-leg bone.");
    return;
}

void
give_bones_found(object player)
{
    string bone_msg = "";
    command("emote examines the right-leg bone carefully.");
    command("say Thank you for finding these bones!");
    player->add_prop(OK_RLEG,1);
    player->remove_prop(FOUND_RLEG);

//check to see that all the bones were found
    if(!TP->query_prop(OK_HEAD))
    {
        bone_msg = "head bone";
    }

    if(!TP->query_prop(OK_SPINE))
    {
        if(bone_msg == "")
            bone_msg = "spine bone";
        else
            bone_msg = bone_msg + ", spine bone";
    }

    if(!TP->query_prop(OK_LARM))
    {
        if(bone_msg == "")
            bone_msg = "left-arm bone";
        else
            bone_msg = bone_msg + ", left-arm bone";
    }


    if(!TP->query_prop(OK_RARM))
    {
        if(bone_msg == "")
            bone_msg = "right-arm bone";
        else
            bone_msg = bone_msg + ", right-arm bone";
    }

    if(!TP->query_prop(OK_RLEG))
    {
        if(bone_msg == "")
            bone_msg = "right-leg bone";
        else
            bone_msg = bone_msg + ", right-leg bone";
    }

    if(!TP->query_prop(OK_LLEG))
    {
        if(bone_msg == "")
            bone_msg = "left-leg bone";
        else
            bone_msg = bone_msg + ", left-leg bone";
    }

    if(bone_msg != "")
    {
        command("say You haven't found all the bones I need. These are what you are missing: " + bone_msg + ". When you have found them, please return here.\n");
        return;
    }

    CAN_SACRIFICE;

    command("say Now, before I can restore them, I need a portion of your life to finish the spell. If you agree to this, then <sacrifice life> and I shall continue. ");
    return;
}

public void
enter_inv(object obj, object from)
{
    string str;

    ::enter_inv(obj, from);
    if (!living(from))
	    return;

    if (obj->id(SPINE))
    {
        if(TP->query_prop(FOUND_SPINE))
        {
	        set_alarm(2.0,0.0, &give_head_task(from));
	        return;
         }
         else
         {
            set_alarm(2.0,0.0, &reject_bone("spine", obj, from));
            return;
         }
    }

    if (obj->id(HEAD))
    {
        if(TP->query_prop(FOUND_HEAD))
        {
	        set_alarm(2.0,0.0, &give_larm_task(from));
	        return;
         }
         else
         {
            set_alarm(2.0,0.0, &reject_bone("head bone", obj, from));
            return;
         }
    }

    if (obj->id(LARM))
    {
        if(TP->query_prop(FOUND_LARM))
        {
	        set_alarm(2.0,0.0, &give_rarm_task(from));
	        return;
         }
         else
         {
            set_alarm(2.0,0.0, &reject_bone("left arm bone", obj, from));
            return;
         }
    }

    if (obj->id(RARM))
    {
        if(TP->query_prop(FOUND_RARM))
        {
	        set_alarm(2.0,0.0, &give_lleg_task(from));
	        return;
         }
         else
         {
            set_alarm(2.0,0.0, &reject_bone("right arm bone", obj, from));
            return;
         }
    }

    if (obj->id(LLEG))
    {
        if(TP->query_prop(FOUND_LLEG))
        {
	        set_alarm(2.0,0.0, &give_rleg_task(from));
	        return;
         }
         else
         {
            set_alarm(2.0,0.0, &reject_bone("right leg bone", obj, from));
            return;
         }
    }

    if (obj->id(RLEG))
    {
        if(TP->query_prop(FOUND_RLEG))
        {
	        set_alarm(2.0,0.0, &give_bones_found(from));
	        return;
         }
         else
         {
            set_alarm(2.0,0.0, &reject_bone("right leg bone", obj, from));
            return;
         }
    }

    set_alarm(1.5, 0.0, &failed_give(obj,from));
    return;
}

int sacrifice_life(string str)
{
    str = lower_case(str);

    if(str !="life")
    {
        notify_fail("Sacrifice, your life?\n");
        return 0;
    }

    if(TP->test_bit(DOMAIN, CITADEL_QUEST_GROUP, CITADEL_QUEST_BIT))
    {
	    command("say I thank you for your concern, but you have already helped me.");
	    return 1;
    }

    if(!TP->query_prop(FOUND_BONES))
    {
        command("say You haven't found the bones yet. Find the spine bone first, bring it to me, and I'll tell you what to do next.");
        return 1;
    }

    set_alarm(1.0,0.0, &play_msg(TP, 0));
    TP->heal_hp(-MIN_HP);

// clean up player now
    TP->remove_prop(OK_HEAD);
    TP->remove_prop(OK_SPINE);
    TP->remove_prop(OK_LARM);
    TP->remove_prop(OK_RARM);
    TP->remove_prop(OK_LLEG);
    TP->remove_prop(OK_RLEG);
    TP->remove_prop(QUEST_NAME_PROP);

    QUEST_LOG_FILE(CITADEL_QUEST_LNG, CITADEL_QUEST_EXP);

    return 1;
}


void
init_living()
{
    ::init_living();
    add_action("sacrifice_life", "sacrifice");
}


void
play_msg(object player, int stage)
{
    float time;

    switch (stage)
    {
        case 0:
            TP->catch_msg("The ghost stretches forth his hand towards you.\n");
            tell_room(ENV(TP), "The " + query_short() + " stretches his hand out.\n", TP);
            time = 1.0;
            break;
        case 1:
            TP->catch_msg("You fall to the ground in utter pain. Strange colors dance before your eyes as you see your life begin to flow out of you.\n");
            tell_room(ENV(TP),QCTNAME(TP)+ " falls to the ground and writhes in pain.\n", TP);
            time = 3.0;
            break;
        case 2:
            TP->catch_msg("The pain intensifies and you black out from it.\n");
            tell_room(ENV(TP), CAP(HE_SHE(TP))+ " suddenly stops moving and seems to age before your eyes. Strange colors seem to suddenly float up from the body and envelope the ghost.\n", TP);
            time = 4.0;
            break;
        case 3:
            TP->catch_msg("The pain seems to ease slightly. A deep fog seems to cloud your awareness.\n");
            tell_room(ENV(TP), "The " + query_short() + " seems to collapse in on itself.\n", TP);
            time = 4.0;
            break;
        case 4:
            TP->catch_msg("Somewhere in your awareness you sense a flash of light and the fog begins to dissapate.\n");
            tell_room(ENV(TP), "Suddenly, there is a flash of light, and standing before you is a dwarf king.\n", TP);
            time = 3.0;
            break;
        case 5:
            TP->catch_msg("You wake from the fog, feeling weak and disoriented.\n");
            tell_room(ENV(TP), QCTNAME(TP)+ " begins to stir and awakes.\n", TP);
            time = 3.0;
            break;
        default:
            TP->catch_msg("Standing before you is a dwarf king, fully restored and mortal again.\n");
            tell_room(ENV(TP), CAP(HE_SHE(TP))+ " stands up and looks around.\n", TP);
            tell_object(TP,"You feel more experienced!\n");
            say(QCTNAME(TP) + " was rewarded.\n");

            TP->set_bit(CITADEL_QUEST_GROUP, CITADEL_QUEST_BIT);
            TP->add_exp_quest(CITADEL_QUEST_EXP);
            convert_dwarf();
        return;
    }
    set_alarm(time, 0.0, &play_msg(TP, ++stage));
    return;
}

void convert_dwarf()
{
    TO->set_short("tall regal dwarf");
    TO->set_long("This is an ancient dwarf king. He looks regal and recently reborn. The dwarf is stout looking and was once a ruler of race in Kryptgarden Forest. He looks anxious to run away and spread the good news of his rebirth and who aided him.\n");
    TO->set_race_name("dwarf");
    command("say I thank you greatly for your help! I cannot believe someone like yourself would be willing to sacrfice your life to aid me!!\n");
    command("say I must run and muster my kind to come back and and regain what was taken from us so many ages ago. As I travel, I will tell of your deeds to all I meet!\n");
    command("emote flourishes a bow and runs away.\n");
    remove_object();
    return;
}
