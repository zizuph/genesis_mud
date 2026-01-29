/*
 *  /d/Emerald/common/guild/aod/defs.h
 *
 *  These are the definitions for the Army of Darkness guild.
 */

#define     GUILD_NAME            "Army of Darkness"
#define     GUILD_STYLE           "fighter"
#define     GUILD_TAX_OCC         28
#define     GUILD_TAX_RACE        10

#define     RACE_GUILD_NAME       GUILD_NAME
#define     RACE_GUILD_TAX        5

#define     NUM_OFFICER           "Headhunter General"
#define     NUM_OFFICER_SHORT     "General"
#define     SPH_OFFICER           "Black Corporal"
#define     SPH_OFFICER_SHORT     "Corporal"

#define     AOD_DIR              ("/d/Emerald/common/guild/aod/")
#define     AOD_OBJ_DIR          (AOD_DIR + "obj/")
#define     AOD_LOG_DIR          (AOD_DIR + "log/")
#define     AOD_SAVE_DIR         (AOD_LOG_DIR + "member_save/")
#define     AOD_ROOM_DIR         (AOD_DIR + "rooms/")
#define     AOD_OBJ_DIR          (AOD_DIR + "obj/")
#define     AOD_SHAD_DIR         (AOD_DIR + "shadow/")
#define     AOD_NPC_DIR          (AOD_DIR + "npc/")
#define     AOD_LIB_DIR          (AOD_DIR + "lib/")
#define     AOD_WEP_DIR          (AOD_DIR + "wep/")
#define     AOD_ARM_DIR          (AOD_DIR + "arm/")
#define     AOD_DOC_DIR          (AOD_DIR + "doc/")
#define     AOD_TROPHY_DIR       (AOD_LOG_DIR + "trophy_save/")
#define     AOD_CHAMBER_DIR      (AOD_LOG_DIR + "chamber_save/")
#define     AOD_LUNCH_DIR        (AOD_LOG_DIR + "lunch_save/")
#define     AOD_DECAP_DIR        (AOD_LOG_DIR + "decap_save/")
#define     AOD_OGG_DIR          (AOD_LOG_DIR + "ogg_save/")

#define     AOD_SHADOW           (AOD_DIR + "aod_shadow")
#define     AOD_RACE_SHADOW      (AOD_DIR + "race_shadow")
#define     AOD_MASTER           (AOD_OBJ_DIR + "master")
#define     TROPHY_MASTER        (AOD_OBJ_DIR + "trophy_master")
#define     CHAMBER_MASTER       (AOD_OBJ_DIR + "chamber_master")
#define     DECAP_MASTER         (AOD_OBJ_DIR + "decapitation_master")
#define     AOD_LUNCH_MASTER     (AOD_OBJ_DIR + "lunch_master")
#define     AOD_OGG_MASTER       (AOD_OBJ_DIR + "ogg_master")
#define     METAL_MASTER         (AOD_OBJ_DIR + "metal_master")
#define     REPOSITORY_FILE      "aod_repository"
#define     MILESTONE_FILE       (AOD_DIR + "milestones.txt")
#define     LUNCH_FILE           "free_lunch"
#define     AOD_CMDSOUL          (AOD_DIR + "cmdsoul")
#define     AOD_EMBLEM           (AOD_OBJ_DIR + "sack")
#define     AOD_RACE_EMBLEM      (AOD_OBJ_DIR + "belt")
#define     AOD_POST             (AOD_ROOM_DIR + "post")
#define     AOD_STARTLOC         (AOD_ROOM_DIR + "start")
#define     AOD_TRAINING         (AOD_LIB_DIR + "training_module")
#define     DTELL_MOD            (AOD_LIB_DIR + "darkling_tell")

#define     AOD_DECAPITATED_PROP ("_aod_decapitated_prop")
#define     AOD_WIELD_PROP       ("_aod_wield_prop")
#define     AOD_WEAR_PROP        ("_aod_wear_prop")
#define     AOD_STOMP_PROP       ("_aod_stomp_prop")
#define     AOD_I_CRUSH_STATUS   ("_aod_i_crush_status")
#define     AOD_I_STOMP_PROP     ("_aod_i_stomp_prop")
#define     AOD_JUST_KICKED      ("_aod_just_kicked_prop")

#define     AOD_EMBLEM_ID        (GUILD_NAME + " emblem")
#define     AOD_RACE_EMBLEM_ID   ("_aod_race_emblem")
#define     AOD_NPC              ("_aod_npc")
#define     AOD_FORGED_ITEM      ("_aod_forged_item")
#define     AOD_CORPSE_WEAPON_ID ("_aod_corpse_weapon")
#define     AOD_RACK_ITEM        ("_aod_rack_item")
#define     AOD_OGRESTOMP_EFFECT ("_aod_ogrestomp_effect")
#define     AOD_FORGE_NORM       "Forge-Normal"
#define     AOD_FORGE_MAGIC      "Forge-Magic"

#define     AOD_UNWORTHY         10
#define     AOD_WORTHY           100
#define     ELECTION_INTERVAL    864000
#define     NOT_YET_ASSIGNED     "Unassigned!"

#define     CON_FACTOR           0.3
#define     STR_FACTOR           0.5
#define     INT_FACTOR           0.5
#define     WIS_FACTOR           0.5
#define     DEX_FACTOR           0.1
#define     HEIGHT_FACTOR        300
#define     WEIGHT_FACTOR        600000
#define     SPEED_FACTOR         100
#define     AC_FACTOR            30
#define     FIST_FACTOR          3

#define     AOD_SPEED_CAP        200
#define     AOD_AC_CAP           40
#define     AOD_FIST_CAP         30

#define     AOD_HUMAN            0
#define     AOD_ELF              1
#define     AOD_HOBBIT           2
#define     AOD_DWARF            3
#define     AOD_GNOME            4
#define     AOD_RACEREWARD       25000

/* The skill number for the guild's special skills.
 */
#define SS_AOD_WALLOP            132010
#define SS_AOD_PBLOCK            132011

/* Definitions used in the training rooms */
#define     NPC  this_object()->trainer_present()
#define     MIND_JUICE_MESSAGE "The " + NPC + " bellows:" \
                                + " Hmmm ... brain too dumb. You drink" \
                                + " more mind juice. Then more improve!"

#define     IS_OGRE(x)     ((x)->query_guild_name_occ() == GUILD_NAME ||\
                            (x)->id(AOD_NPC))
#define     AOD_GENERAL(x) (AOD_MASTER->get_info(REPOSITORY_FILE, \
                            "GENERAL") == (x)->query_real_name())
#define     AOD_CORPORAL(x) (AOD_MASTER->get_info(REPOSITORY_FILE, \
                            "CORPORAL") == (x)->query_real_name())

#define     TELL_G(x) (find_living("gorboth")->catch_tell("DEBUG: "+(x)+"\n"))
#define     CHAMBER_INFO(x,y) (CHAMBER_MASTER->set_info("guests", (x), (y)))
#define     DARKLING_TELL(x)  (DTELL_MOD->darkling_tell((x), this_player(), "xyzzyX"))
#define     OGG_TELL(x)       (DTELL_MOD->darkling_tell((x), this_player(), "ogg"))
#define     GENERAL_AWOL      (AOD_MASTER->get_info("General_Awol"))

/* No definitions beyond this line. */
