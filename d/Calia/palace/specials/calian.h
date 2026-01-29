#define GUILD_NAME "Calian warrior's guild"
#define IS_CALIAN_WARRIOR(pl) (pl->is_calian_warrior())
#define IS_CALIAN_TRAINEE(pl) (pl->is_calian_trainee())
#define IS_CALIAN_FOLLOWER(pl) (pl->is_calian_follower())
#define GUILD_TYPE "occupational"
#define GUILD_STYLE "fighter"
#define SS_SWARM 114000
#define SS_MOVE_BEHIND 114001
#define SS_MAUL 114005
#define MAUL_SAVE "/d/Calia/palace/texts/maul_save"
#define MAUL_CONTROL "/d/Calia/palace/rooms/light/maul_room"

// Defines for Branches
#define CALIAN_BRANCH_WARRIOR   0
#define CALIAN_BRANCH_TRAINEE  1
#define CALIAN_BRANCH_FOLLOWER 2

// Calian Follower (applicant) Defines
#define CALIAN_FOLLOWER_TAX 10
#define CALIAN_FOLLOWER_MAX_MB 50
#define CALIAN_FOLLOWER_MAX_SWARM 50
#define CALIAN_FOLLOWER_MAX_MAUL 0
#define CALIAN_FOLLOWER_MAX_SWORD 50
#define CALIAN_FOLLOWER_MAX_POLEARM 50
#define CALIAN_FOLLOWER_MAX_THC 40
#define CALIAN_FOLLOWER_MAX_PARRY 40
#define CALIAN_FOLLOWER_MAX_DEFENCE 50
#define CALIAN_FOLLOWER_MAX_RIPOSTE 0

// Calian Trainee Defines
#define CALIAN_TRAINEE_TAX 18
#define CALIAN_TRAINEE_MAX_MB 70
#define CALIAN_TRAINEE_MAX_SWARM 70
#define CALIAN_TRAINEE_MAX_MAUL 70
#define CALIAN_TRAINEE_MAX_SWORD 65
#define CALIAN_TRAINEE_MAX_POLEARM 65
#define CALIAN_TRAINEE_MAX_THC 45
#define CALIAN_TRAINEE_MAX_PARRY 55
#define CALIAN_TRAINEE_MAX_DEFENCE 55
#define CALIAN_TRAINEE_MAX_RIPOSTE 70

// Calian Warrior Defines
#define CALIAN_WARRIOR_TAX    23
#define CALIAN_WARRIOR_MAX_MB 100
#define CALIAN_WARRIOR_MAX_SWARM 100
#define CALIAN_WARRIOR_MAX_MAUL 100
#define CALIAN_WARRIOR_MAX_SWORD 90
#define CALIAN_WARRIOR_MAX_POLEARM 90
#define CALIAN_WARRIOR_MAX_THC 65
#define CALIAN_WARRIOR_MAX_PARRY 75
#define CALIAN_WARRIOR_MAX_DEFENCE 75
#define CALIAN_WARRIOR_MAX_RIPOSTE 100

#define CALIAN_RACK_POINTS 114006
#define SS_SWARM_KNOWLEDGE 114007
#define SS_MAUL_KNOWLEDGE 114008
#define SS_CALIAN_RIPOSTE_SKILL 114009
#define CALIAN_RACK_POINTS_MEDALLION_GLASS -100000
#define CALIAN_RACK_POINTS_MEDALLION_BROKEN -250000
#define OBJ_I_ZERO_RACK_POINTS "_obj_i_zero_rack_points"
#define OBJ_I_BEEN_DONATED_BY_CALIAN "_obj_i_been_donated_by_calian"
#define RACK_WEP_OK(tohit, pen) (((tohit + pen) < 50) ? 0 : 1)  
#define RACK_ARM_OK(ac) ((ac < 20) ? 0 : 1)   
#define F_RACK_AVG_STAT(avg) \
         ((avg < 60) ? 60 : ((avg > 140) ? 140 : avg)) 
#define F_RACK_POINTS_WEP(tohit, pen, avg) ((3 * tohit * pen * pen) / avg)  
#define F_RACK_POINTS_ARM(ac, avg) ((ac * ac * ac) / (avg * 2) )  
#define NUM_MEDALLION_TINTS 18
#define MEDALLION_TINTS \
({ "pale green", "faded green", "light green", \
   "leaf green", "forest green", "emerald green", \
   "pale red", "faded red", "light red", \
   "flaming red", "sunset red", "ruby red", \
   "pale blue", "faded blue", "light blue", \
   "rich blue", "sky blue", "sapphire blue" })

#define SWARM_MANA 2
#define SWARM_FATIGUE 2
#define MAUL_MANA 4
#define MAUL_FATIGUE 4
#define SWARM_DELAY 10
#define SWARM_PREP_TIME 3
#define SWARM_EXEC_TIME 7
#define MAUL_PREP_TIME 4
#define MAUL_EXEC_TIME 16
#define MAUL_ATTACK_DELAY 5.0
#define MOVE_BEHIND_DELAY 1
#define MB_NO_ATTACKED_TIME 5
#define CALIAN_I_LAST_MBD_BY_AT_TIME "_calian_i_last_mbd_by_at_time"
#define CALIAN_I_SWARM_STATE "_calian_i_swarm_state"
#define CALIAN_I_MAUL_STATE "_calian_i_maul_state"
#define CALIAN_I_LAST_ATTACK_TIME "_calian_i_last_attack_time"
#define PRE_PREPARE 0
#define PREPARING 1
#define READY 2
#define JUST_SWARMED 3
#define JUST_MAULED 3
#define CALIAN_I_JUST_MOVED_BEHIND "_calian_i_just_moved_behind"
#define CALIAN_S_TEAM_TITLE "_calian_s_team_title"

#define PROJECT_PREP_TIME 1

/* Calian options */ 


#define CALIAN_OPTIONS 114004

#define CALOPT_SEE_SPECIALS 1
#define CALOPT_DISMEMBER 2
#define CALOPT_TITLE_NORMAL 4
#define CALOPT_TITLE_SPECIAL 8
#define CALOPT_TITLE_MIXED 16
#define CALOPT_RACK_CLUB 32

#define CALIAN_I_WEARING_INSIGNIA "_calian_i_wearing_insignia"
#define MEDALLION_MIN_ALIGN 1
#define MEDALLION_ID "Calia_medallion"

