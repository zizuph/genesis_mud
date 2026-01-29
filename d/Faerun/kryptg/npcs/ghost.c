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

#define FOUND_BONES     "_found_bones"
#define CAN_SACRIFICE   (TP->add_prop(FOUND_BONES, 1))

// bit defs for each bone
#define BONE_HEAD    1
#define BONE_SPINE   2
#define BONE_LARM    4
#define BONE_RARM    8
#define BONE_LLEG   16
#define BONE_RLEG   32
#define DONE        (BONE_HEAD|BONE_SPINE|BONE_LARM|BONE_RARM|BONE_LLEG|BONE_RLEG)

int alarm_id;
// keeps track of what players have what bones
string *visitors;
int *bitm;

int alarm_id;
//void play_msg(object player, int stage);
//void convert_dwarf();

void create_monster()
{
    int i;

    visitors = ({});
    bitm = ({});

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
    
    restore_object("/d/Faerun/kryptg/npcs/visitors");

}
