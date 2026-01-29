#ifndef _TEMPLAR_DEFS
#define _TEMPLAR_DEFS

/**
 * Louie 2004
 * Stolen from WoHS
 */
 
#include "/d/Krynn/common/defs.h"

/*
 * Various Guild Defines
 */
#define GUILDMASTERS            ({ "louie" })
#define GUILD_NAME              "Templars of Takhisis"
#define GUILD_STYLE             "fighter"
#define GUILD_OBJ_NAME          "Templars of Takhisis item"
#define GUILD_SAP_OB_NAME       "sap_ob"
#define GUILD_TAX               12
#define WARRIOR_GUILD_TAX       12
#define TEMPLAR_GUILD_TAX       16
#define GUILD_MIN_ALIGN          0
#define GUILD_WARN_ALIGN         -300
#define GUILD_MAX_LEVEL          20
#define GUILD_SAP_PROP           "_templar_sap_prop"
#define SS_GUILD_ATTACK_SKILL    108600
#define SS_GUILD_SAP_SKILL       108602
#define SS_GUILD_DEFEND_SKILL    108601

#define TEMPLAR_SAP_RESET        "_templar_sap_reset"
#define TEMPLAR_ATTACK_PREP      "_templar_attack_prep"
#define TEMPLAR_ATTACK_RESET     "_templar_attack_reset"

//These numbers high, in case a remove_prop
//doesn't work correctly.  The actual times are a little
//more random (13-17 instead of 15, etc)
#define SAP_IMMUNE_TIME         360
#define SAP_RESET_TIME          140
#define ATTACK_RESET_TIME       30
#define ATTACK_PREP_TIME        15

#define TEMPLAR_RANK_BETRAYER    -1
#define TEMPLAR_RANK_WARRIOR     0
#define TEMPLAR_RANK_KNIGHT      1
#define TEMPLAR_RANK_OFFICER     2
#define TEMPLAR_RANK_LORD        3


/*
 * Paths
 */ 
#define PATH                    ("/d/Krynn/guilds/templar/")
#define LOG                     ("templar/")
#define TEMPLAR_BOARD           ("/d/Krynn/guilds/templar/log/board")
#define SAVE_PATH               ("/d/Krynn/guilds/templar/save/")
#define JOINED                  (LOG + "joined")
#define LEFT                    (LOG + "left")
#define PROBLEMS                (LOG + "problems")
#define ROOM                    (PATH + "room/")
#define STD                     (PATH +"std/")
#define GUILD_IR                 (STD + "i_room_base")
#define GUILD_OR                 (STD + "o_room_base")
#define NPC                     (PATH + "npc/")
#define OBJ                     (PATH + "obj/")
#define LIB                     (PATH + "lib/")
#define GUILD_SHADOW            (OBJ + "shadow")
#define GUILD_CMDSOUL           (OBJ + "cmdsoul")
#define TOBJ                    (ROOMS + "obj/")


/* 
 * Files 
 */
#define ADMIN                   (ROOM + "admin")
#define SHIELD_AURA             (OBJ + "shield_aura")
#define SAP_OB                  (OBJ + "sap_ob")
#define SAP_STUN_OB             (OBJ + "sap_stun_ob")


#endif /* _TEMPLAR_DEFS */

