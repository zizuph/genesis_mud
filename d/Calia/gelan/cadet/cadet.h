
/* 
   ~Calia/gelan/cadet/cadet.h 

   This is the defs file for the Cadets of Gelan guild

   Coded by Maniac@Genesis, March 1997 

   Copyright (C) Miguel Leith 1997
*/ 

#ifndef GELAN_CADET_DEFS
#define GELAN_CADET_DEFS

#define GELAN_SCHOOL_CONNECT "/d/Calia/gelan/rooms/school"

#define GC_DIR "/d/Calia/gelan/cadet/"
#define GC_HELP_DIR (GC_DIR + "help/")

/* admin defs */ 
#define GC_GUILD_NAME "Cadets of Gelan" 
#define GC_GUILD_TYPE "layman"
#define GC_GUILD_STYLE "fighter" 
#define GC_GUILD_TAX 12
#define GC_GM_NAME "Xorfin"

#define GC_GROUP 3 
#define GC_BIT 0 
#define GC_BIT2 1 
#define GC_DOM "Calia" 

#define CADET_I_CONFIRM_LEAVE "_cadet_i_confirm_leave" 
#define CADET_AS_BRAWL_WITH "_cadet_as_brawl_with" 
#define CADET_AS_DUEL_WITH "_cadet_as_duel_with" 
#define CADET_AS_ASK_QUARTER "_cadet_as_ask_quarter" 
#define CADET_AS_GRANT_QUARTER "_cadet_as_grant_quarter" 

#define CADETS_CAN_BRAWL(c1, c2) \
 ((member_array(c1->query_real_name(), \
                c2->query_prop(CADET_AS_BRAWL_WITH)) > -1) && \
  (member_array(c2->query_real_name(), \
                c1->query_prop(CADET_AS_BRAWL_WITH)) > -1)) 

#define CADETS_CAN_DUEL(c1, c2) \
 ((member_array(c1->query_real_name(), \
                c2->query_prop(CADET_AS_DUEL_WITH)) > -1) && \
  (member_array(c2->query_real_name(), \
                c1->query_prop(CADET_AS_DUEL_WITH)) > -1)) 

/* object defs */ 
#define GC_FRIEND_NPC "/d/Calia/gelan/cadet/friend_npc"
#define GC_SHOES (GC_DIR + "cadet_shoes") 
#define GC_SHOES_ID "_gc_shoes_id" 
#define GC_RING_ID "_gc_ring_id" 
#define GC_NOTEBOOK_ID "_gc_notebook_id" 
#define GC_GUILDMASTER (GC_DIR + "guildmaster")
#define GC_GM_UNIFORM (GC_DIR + "gm_uniform") 
#define GC_GM_WEAPON (GC_DIR + "gm_weapon")
#define GC_GRADUATE_SHADOW (GC_DIR + "graduate_shadow")
#define GC_GRADUATE_SOUL (GC_DIR + "graduate_soul")
#define GC_BOARD (GC_DIR + "cadet_board")
#define GC_PUSHUP_OB (GC_DIR + "cadet_pushup_ob")
#define GC_JOIN_INFO (GC_DIR + "cadet_join_info.txt")
#define GC_COMMAND_INFO (GC_DIR + "cadet_command_info.txt")
#define GC_BOARD_NOTES (GC_DIR + "notes/")
#define GC_SHADOW (GC_DIR + "cadet_shadow") 
#define GC_SOUL (GC_DIR + "cadet_soul")
#define GC_ATTACK_DESC "/d/Calia/std/attack_desc"
#define GC_RACK (GC_DIR + "cadet_rack")
#define GC_GR_SUPPORT (GC_DIR + "gr_support")

/* Boolean checks */ 
#define IS_GELAN_CADET(pl) (pl->query_guild_name_lay() == GC_GUILD_NAME) 
#define IS_GRADUATE(pl) (pl->query_prop(GC_RING_ID))
#define IS_CADET_FRIEND(pl) (pl->query_gelan_cadet_friend_npc())  

/* Primary and secondary weapon defs */ 
#define GC_SKILL_PRIMARY_WEAPON 114030 
#define GC_SKILL_SECONDARY_WEAPON 114031 

#define SS_CADET_DROPROOM_POINTS 114032
#define SS_CADET_DONK_BAN 114033
#define GC_DONK_BAN_DURATION (3 * 24 * 3600)

#define GC_MAX_LEVEL_PRIMARY_WEAPON 50
#define GC_MAX_LEVEL_SECONDARY_WEAPON 45

#define GC_SELECTED_NOTHING 0
#define GC_SELECTED_SWORD 1 
#define GC_SELECTED_POLEARM 2 
#define GC_SELECTED_AXE 3 
#define GC_SELECTED_KNIFE 4 
#define GC_SELECTED_CLUB 5
#define GC_SELECTED_UNARMED 6

#define GC_NAME_SELECTED_MAP \
    ([  "sword" : GC_SELECTED_SWORD, \
        "polearm" : GC_SELECTED_POLEARM, \
        "axe" : GC_SELECTED_AXE, \
        "knife" : GC_SELECTED_KNIFE, \
        "club" : GC_SELECTED_CLUB, \
        "unarmed" : GC_SELECTED_UNARMED ])


/* Title defs */ 
#define GC_SELECTED_TITLE_MAP \
    ([  GC_SELECTED_NOTHING : "", \
        GC_SELECTED_SWORD : "Sword", \
        GC_SELECTED_POLEARM : "Polearm", \
        GC_SELECTED_AXE : "Axe", \
        GC_SELECTED_KNIFE : "Knife", \
        GC_SELECTED_CLUB : "Club", \
        GC_SELECTED_UNARMED : "Fistfighter" ])

#define GC_LEVEL_GRADUATE "Learned"

#define GC_LEVEL_TITLE_ARR \
 ({ "Initiate", "Junior", "Regular", "Advanced", "Senior", GC_LEVEL_GRADUATE })

#define GC_NUM_LEVEL_TITLES 6
#define GC_BASE_TITLE "Cadet of Gelan"


/* stat requirement defs */ 
#define GC_MAX_AVG_STAT 86
#define GC_WARN_AVG_STAT 77

#define GC_AVG_STAT_EXPEL(tp) (tp->query_average_stat() > GC_MAX_AVG_STAT)
#define GC_AVG_STAT_CAN_JOIN(tp) (!GC_AVG_STAT_EXPEL(tp))

#define GC_AVG_STAT_WARN(tp) \
                (tp->query_average_stat() > GC_WARN_AVG_STAT) 


/* room defs */ 
#define GC_ROOMS GC_DIR
#define GC_TRAINROOM (GC_ROOMS+"cadet_trainroom") 
#define GC_STARTROOM (GC_ROOMS+"cadet_startroom") 
#define GC_MESSROOM (GC_ROOMS+"cadet_mess") 
#define GC_BOARDROOM (GC_ROOMS+"cadet_boardroom") 
#define GC_POSTROOM (GC_ROOMS+"cadet_post") 
#define GC_COMMONROOM (GC_ROOMS+"cadet_commonroom") 
#define GC_DROPROOM (GC_ROOMS+"cadet_droproom") 


/* attack special defs */ 
#define GC_DONK_PREP_TIME 4 
#define GC_DONK_RECOVER_TIME 12

#define GC_DONK_STATE_START 0 
#define GC_DONK_STATE_PREPARE 1
#define GC_DONK_STATE_RECOVER 2

/* save related defs */ 
#define GC_SAVE (GC_DIR + "gc_save")

#define GC_CADET_REGFILE(p) (GC_DIR + "cadets/registry/" + \
                             p[0..0] + "/" + p)

#define GC_CADET_GAMELEV_DIR (GC_DIR + "cadets/gamelevel/")
#define GC_CADET_GUILDLEV_DIR (GC_DIR + "cadets/guildlevel/")
#define GC_CADET_WEAPON_DIR (GC_DIR + "cadets/weapon/")
#define GC_CADET_RACE_DIR (GC_DIR + "cadets/race/")
#define GC_CADET_GENDER_DIR (GC_DIR + "cadets/gender/")
#define GC_CADET_ADJ1_DIR (GC_DIR + "cadets/adj1/")
#define GC_CADET_ADJ2_DIR (GC_DIR + "cadets/adj2/")
#define GC_CADET_PICTURE_DIR (GC_DIR + "cadets/pictures/")
#define GC_RACK_DIR (GC_DIR + "racks/")

#define GC_CADET_WEP(p) (read_file(GC_CADET_REGFILE(p)))

#define GC_CADET_PICTURE(p) (GC_CADET_PICTURE_DIR + \
                             p[0..0] + "/" + p)

#define GC_CADET_INFO_SAVE(p) (GC_DIR+"cadets/save/" + \
                               p[0..0] + "/" + p)

#define GC_GRADUATE_REGFILE(p) (GC_DIR + "graduates/registry/" + \
                                p[0..0] + "/" + p)

#define GC_GRADUATE_GAMELEV_DIR (GC_DIR + "graduates/gamelevel/")
#define GC_GRADUATE_WEAPON_DIR (GC_DIR + "graduates/weapon/")
#define GC_GRADUATE_RACE_DIR (GC_DIR + "graduates/race/")
#define GC_GRADUATE_GENDER_DIR (GC_DIR + "graduates/gender/")
#define GC_GRADUATE_ADJ1_DIR (GC_DIR + "graduates/adj1/")
#define GC_GRADUATE_ADJ2_DIR (GC_DIR + "graduates/adj2/")
#define GC_GRADUATE_PICTURE_DIR (GC_DIR + "graduates/pictures/")

#define GC_GRADUATE_WEP(p) (read_file(GC_GRADUATE_REGFILE(p)))

#define GC_GRADUATE_PICTURE(p) (GC_GRADUATE_PICTURE_DIR + \
                                p[0..0] + "/" + p) 

#define GC_GRADUATE_INFO_SAVE(p) (GC_DIR+"graduates/save/" + \
                                  p[0..0] + "/" + p) 

#define GC_MAX_WEAPON_RACK_POINTS 1700
#define GC_MAX_ARMOUR_RACK_POINTS 1300
#define GC_MAX_MISC_RACK_POINTS 1000 

#endif
