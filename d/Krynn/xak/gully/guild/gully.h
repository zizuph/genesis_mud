/* Guild.h */

#include "../local.h"
#include <formulas.h>

#define GUILDMASTERS  ({"Morrigan","Aridor"})

#define GUILD_NAME    "Solamnian Knights"

#define MEDALPATH     KOBJ + "medal"
#define O_SHADOW      KOBJ + "occ_shadow"
#define KNIGHT_SOUL   KOBJ + "solamnian_soul"

#define CONCLAVE_CMD  KOBJ + "conclave_cmd"
#define CONCLAVE_OBJ  "knight_conclave_command_object"
#define NON_KN_AWD_ID "non_knight_award"
#define NON_KN_AWD_OB KOBJ + NON_KN_AWD_ID

#define KNIGHT_LOG     KDIR + "log/"
#define SPONSOREDPATH  KNIGHT_LOG + "sponsorlist"
#define JOINPATH       KNIGHT_LOG + "joined"
#define GUIDANCEPATH   KNIGHT_LOG + "guidance"
#define BANISHPATH     KNIGHT_LOG + "banished"
#define PRESTIGEPATH   KNIGHT_LOG + "prestige"
#define LEAVEPATH      KNIGHT_LOG + "left"
#define ADMIN_FILE     KNIGHT_LOG + "admin"
#define ARMSOLD        KNIGHT_LOG + "armsold"
#define KNIGHT_ALL_LOG KNIGHT_LOG + "allactions"
#define PRESTIGE_FILE  KNIGHT_LOG + "pre"
#define KILL_LOG       KNIGHT_LOG + "kills"
#define APPOINT_FILE KLOG + "appoint"
#define APPOINT_LOG KLOG + "appointments"
#define POSITIONS ({ "Warden", "Swordmaster", "General", "Eastern_Commander", "Southern_Commander" })

#define CHARITY_FILE         KNIGHT_LOG + "box"
#define CHARITY_FILELOW      KNIGHT_LOG + "boxlow"
#define CHARITY_FILEMED      KNIGHT_LOG + "boxmed"
#define CHARITY_FILEHIGH     KNIGHT_LOG + "boxhigh"

#define ARM_PROP             "_from_solamnian_drop_room_"
#define CHAR_OBJ             "_k_charity_object"
#define CHAR_WHO_GAVE        "_k_charity_who_gave"
#define CHARITY_LOG          KNIGHT_LOG + "char"
#define CHAR_PRES(val)       (val / 10)

#define KNIGHT_I_DEVOTION    "_knight_i_devotion"

#define GARDKEY         02322222
#define GARDKEY2        02333333

#define ADMIN           KDIR + "admin/admin.c"

/* Some identification macros for handy use */
#define IS_CONCLAVE(x)    ((ADMIN)->is_conclave(x->query_real_name()))
#define IS_GRANDMASTER(x) ((ADMIN)->is_grandmaster(x->query_real_name()))
#define IS_HIGH_KNIGHT(x) ((x)->query_knight_sublevel() == 11)

#define ENTRANCE        VROOM + "gate"
#define START_ROOM      VROOM + "startroom"

#define ALIGN_WARNING   150

#define SS_DBROSE       15
#define SS_DSQUIRE      30
#define SS_DCROWN       45
#define SS_DSWORD       65
#define SS_DROSE        85
#define SS_USQUIRE      25
#define SS_UCROWN       35
#define SS_USWORD       55
#define SS_UROSE        75
#define SS_USROSE       90

#define RATE            15/*18*/
/*this number must be carefully reconsidered for the changes in the guild!!!*/
#define SS_LEVEL0       (RATE * 1 / 4)
#define SS_LEVEL1       (RATE * 3 / 4)
#define SS_LEVEL2       (RATE * 6 / 4)
#define SS_LEVEL3       (RATE * 9 / 4)
#define SS_LEVEL4       (RATE * 12 / 4)
#define SS_LEVEL5       (RATE * 15 / 4)
#define SS_LEVEL6       (RATE * 18 / 4)
#define SS_LEVEL7       (RATE * 21 / 4)
#define SS_LEVEL8       (RATE * 24 / 4)
#define SS_LEVEL9       (RATE * 27 / 4)
#define SS_LEVEL10      (RATE * 30 / 4)
#define SS_LEVEL11      (RATE * 33 / 4)
#define SS_LEVEL12      (RATE * 36 / 4)
#define SS_LEVEL13      (RATE * 40 / 4)

#define K_LEVEL_ARRAY   ({ SS_LEVEL0, SS_LEVEL1, SS_LEVEL2, SS_LEVEL3, \
        SS_LEVEL4, SS_LEVEL5, SS_LEVEL6, SS_LEVEL7, \
        SS_LEVEL8, SS_LEVEL9, SS_LEVEL10, SS_LEVEL11, \
        SS_LEVEL12, SS_LEVEL13 })

#define L_BROSE         1
#define L_SQUIRE        2
#define L_CROWN         3
#define L_SWORD         4
#define L_ROSE          5
#define L_SROSE         6

#define L_0 0
#define L_1 1
#define L_2 2
#define L_3 3
#define L_4 4
#define L_5 5
#define L_6 6
#define L_7 7
#define L_8 8
#define L_9 9
#define L_10 10
#define L_11 11
#define L_12 12

#define TAX        ({ 0, 25, 12, 18, 18, 18, 0 })
#define MAX_TRAIN  ({ 0,  0, 50, 100, 100, 100, 0 })

#define KNIGHT_TITLES  ({ "Solamnian Knight", \
        "Knight of the Black Rose", \
        "Squire of Solamnia", \
        "Knight of the Crown", \
        "Knight of the Sword", \
        "Knight of the Rose" })

/* Note black knights have no set of titles */
#define SQUIRE_TITLES ({ "Untitled Squire", \
        "Failing Squire of Solamnia", \
        "Lacking Squire of Solamnia", \
        "Squire of Solamnia", \
        "Sworn Squire of Solamnia", \
        "Determined Squire of Solamnia", \
        "Practiced Squire of Solamnia", \
        "Dedicated Squire of Solamnia", \
        "Faithful Squire of Solamnia", \
        "Loyal Squire of Solamnia", \
        "Noble Squire of Solamnia", \
        "Noble Squire of Solamnia" })

#define FCROWN_TITLES  ({ "Untitled Crown Knight", \
        "Squire of Crown", \
        "Defender of Crown", \
        "Knight of Crown", \
        "Scepter Knight", \
        "Shield Knight", \
        "Shield of Crown", \
        "Lady of Shield", \
        "Lady of Crown", \
        "Master Warrior of Solamnia", \
        "Lady Warrior of Solamnia", \
        "High Warrior of Solamnia" })

#define CROWN_TITLES  ({ "Untitled Crown Knight", \
        "Squire of Crown", \
        "Defender of Crown", \
        "Knight of Crown", \
        "Scepter Knight", \
        "Shield Knight", \
        "Shield of Crown", \
        "Lord of Shield", \
        "Lord of Crown", \
        "Master Warrior of Solamnia", \
        "Lord Warrior of Solamnia", \
        "High Warrior of Solamnia" })

#define FSWORD_TITLES ({ "Untitled Sword Knight", \
        "Novice of Swords", \
        "Knight of Swords", \
        "Blade Knight", \
        "Knight Clerist", \
        "Abess of Swords", \
        "Elder of Swords", \
        "Master of Swords", \
        "Lady of Swords", \
        "Master Clerist of Solamnia", \
        "Lady Clerist of Solamnia", \
        "High Clerist of Solamnia" })

#define SWORD_TITLES ({ "Untitled Sword Knight", \
        "Novice of Swords", \
        "Knight of Swords", \
        "Blade Knight", \
        "Knight Clerist", \
        "Abbot of Swords", \
        "Elder of Swords", \
        "Master of Swords", \
        "Lord of Swords", \
        "Master Clerist of Solamnia", \
        "Lord Clerist of Solamnia", \
        "High Clerist of Solamnia" })

#define FROSE_TITLES ({ "Untitled Rose Knight", \
        "Novice of Roses", \
        "Knight of Tears", \
        "Knight of Mind", \
        "Knight of Roses", \
        "Keeper of Roses", \
        "Master of Roses", \
        "Archknight of the Rose", \
        "Lady of Roses", \
        "Master Justice of Solamnia", \
        "Lady Justice of Solamnia", \
        "High Justice of Solamnia" })

#define ROSE_TITLES ({ "Untitled Rose Knight", \
        "Novice of Roses", \
        "Knight of Tears", \
        "Knight of Mind", \
        "Knight of Roses", \
        "Keeper of Roses", \
        "Master of Roses", \
        "Archknight of the Rose", \
        "Lord of Roses", \
        "Master Justice of Solamnia", \
        "Lord Justice of Solamnia", \
        "High Justice of Solamnia" })

#define GRANDMASTER_TITLE ({ "Grand Master of the Knights of Solamnia", \
			     "Grand Master of the Knights of Solamnia", \
			     "Grand Master of the Knights of Solamnia" })
/* ({ male, female, neuter }) title. identical for now. */

#define WIMPY_LIMIT ({ 99,60,60,40,30,20,10 })
#define WIMPY_LIMIT2 ({ 10, 8, 6, 5, 4, 3, 2, 1, 0, -2, -4, -4, -4 })

#define SS_RESCUE  67530
#define SS_KATTACK 67531
#ifndef SS_BLOCK
#define SS_BLOCK   67532
#endif
#define KNIGHT_SKILL_DESC  ({"rescue", "kattack", "block"})

#define SKILL_OB "/lib/skill_raise"

#define SS_PRESTIGE_ACC 108111  /* Krynn is domain#8 */
#define SS_PRESTIGE_ST  108112  /* Krynn is domain#8 */
#define SS_CHARITY      108113  /* Krynn is domain#8 */
#define SS_DISGRACED    108119  /* Krynn is domain#8 */
#define SS_ARMOURER     108120  /* Krynn is domain#8 */

#define SECONDS_IN_2_DAYS 172800

#define GUILD_GROUP 1
#define MEMBER_BIT 0
#define BANISH_BIT 1
#define LAYMAN_BIT 2

#define MEMBER(ob)     ob->test_bit("Krynn", GUILD_GROUP, MEMBER_BIT)
#define LAYMAN(ob)     ob->test_bit("Krynn", GUILD_GROUP, LAYMAN_BIT)
#define BANISHED(ob)   ob->test_bit("Krynn", GUILD_GROUP, BANISH_BIT)

#define SPONSORED(player)      (ADMIN)->check_squirelist(player) /*player should be a string*/
#define SPONSOR(player)        (ADMIN)->check_knightlist(player) /*player should be a string*/
#define KNIGHT_SQUIRE(player)  (ADMIN)->get_knight_squire(player) /*player should be a object*/
#define SQUIRE_KNIGHT(player)  (ADMIN)->get_squire_knight(player) /* and a string is returned */
#define DISGRACE(ob, reason)   (ADMIN)->perform_disgrace(ob, "paladine", reason,0)
#define BANISH(ob, reason)     (ADMIN)->perform_banishment(ob, "paladine", reason,0)
#define KILLED(killer, killed) (ADMIN)->killed_logging(killer, killed)
#define LEAVE(ob)              (ADMIN)->leave(ob)

/*  2H POL PAR DEF SW CL LA AW  */
#define SKILLS ({ 20, 1, 22, 23, 24, 0, 4, 109, 110, \
        SS_RESCUE, SS_KATTACK, SS_BLOCK, SS_PRESTIGE_ACC, \
        SS_PRESTIGE_ST, SS_CHARITY, SS_DISGRACED})


/* Formulas to the cmd_soul */

#define F_RESCUE(ob, ob2) ob->query_stat(SS_DIS) + ob->query_stat(SS_DEX) - \
ob2->query_stat(SS_WIS) + \
ob->query_skill(SS_RESCUE) * ob->query_skill(SS_RESCUE) * \
ob->query_skill(SS_RESCUE) / 400

#define RESCUE_HIT 200
