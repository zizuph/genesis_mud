/* Guild.h */

#include <formulas.h>
#include "local.h"

#define GUILDMASTERS  ({"Morrigan","Aridor","Teth"})

/* SET THIS TO 1 TO SWITCH TO THE NEW KNIGHTS!!!!! */
#define NEW_KNIGHTS   1
/* SET THIS TO 1 to SWITCH TO THE NEW LAYMAN SENTRIES!!!!! */
#define NEW_LAYMAN    1

#define GUILD_NAME    "Solamnian Knights"
#define GUILD_NAME_CLERIC "Solamnian Knight Clerics"
#if NEW_LAYMAN
#define GUILD_NAME_LAY    "Sentries of Solamnia"
#else
#define GUILD_NAME_LAY    "Solamnian Knights"
#endif
#define BOOKPATH      VDIR + "book/"
#define MEDALPATH     OBJ + "medal"
#define O_SHADOW      OBJ + "occ_shadow"
#define L_SHADOW      OBJ + "lay_shadow"
#define CLERIC_SHADOW OBJ + "cleric_shadow"
#define KNIGHT_SOUL   OBJ + "solamnian_soul"

#define SPELL_OBJ       TDIR + "spells/knight_spells_base"
#define SWORD_SPELL_OBJ TDIR + "spells/sword_spells"
#define ROSE_SPELL_OBJ  TDIR + "spells/rose_spells"
#define SPELL_OB_NAME "solamnian_spells"

#define CONCLAVE_CMD  OBJ + "conclave_cmd"
#define CONCLAVE_OBJ  "knight_conclave_command_object"
#define NON_KN_AWD_ID "non_knight_award"
#define NON_KN_AWD_OB OBJ + NON_KN_AWD_ID

#define KNIGHT_LOG     TDIR + "log/"
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
/*
#define KNIGHT_I_BASH        "_knight_i_bash"
#define KNIGHT_I_KICK        "_knight_i_kick"
*/

#define KEEPKEY         02321111
#define GARDKEY         02322222
#define GARDKEY2        02333333

#define ADMIN           TDIR + "admin.c"
#define ENTRANCE        VDIR + "outkeep"
#define START_ROOM      VDIR + "startroom"

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

#define RATE            16/*18*/
/*this number must be carefully reconsidered for the changes in the guild!!!*/
#define SS_LEVEL0       (RATE * 1 / 4)    /*  4 */
#define SS_LEVEL1       (RATE * 2 / 4)    /*  9 */
#define SS_LEVEL2       (RATE * 5 / 4)    /* 22 */
#define SS_LEVEL3       (RATE * 8 / 4)    /* 36 */
#define SS_LEVEL4       (RATE * 10 / 4)   /* 45 */
#define SS_LEVEL5       (RATE * 12 / 4)   /* 54 */
#define SS_LEVEL6       (RATE * 15 / 4)   /* 67 */
#define SS_LEVEL7       (RATE * 17 / 4)   /* 76 */
#define SS_LEVEL8       (RATE * 18 / 4)   /* 81 */
#define SS_LEVEL9       (RATE * 19 / 4)   /* 85 */
#define SS_LEVEL10      (RATE * 20 / 4)   /* 90 */
#define SS_LEVEL11      (RATE * 23 / 4)   /*103 */
#define SS_LEVEL12      (RATE * 30 / 4)   /*135 */
#define SS_LEVEL13      (RATE * 40 / 4)   /*180 */

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

#define TAX        ({ 0, 25, 10, 16, 16, 16, 0 })
#define LAY_TAX    ({ 0,  0,  0,  0, 10,  9, 0 })
#define MAX_TRAIN  ({ 0,  0, 50, 90, 90, 90, 0 })

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
"Master Warrior", \
"Lady Warrior", \
"High Lady" })

#define CROWN_TITLES  ({ "Untitled Crown Knight", \
"Squire of Crown", \
"Defender of Crown", \
"Knight of Crown", \
"Scepter Knight", \
"Shield Knight", \
"Shield of Crown", \
"Lord of Shield", \
"Lord of Crown", \
"Master Warrior", \
"Lord Warrior", \
"High Warrior" })

#define FSWORD_TITLES ({ "Untitled Sword Knight", \
"Novice of Swords", \
"Knight of Swords", \
"Blade Knight", \
"Knight Clerist", \
"Abess of Swords", \
"Elder of Swords", \
"Master of Swords", \
"Lady of Swords", \
"Master Clerist", \
"Lady Clerist", \
"High Clerist" })

#define SWORD_TITLES ({ "Untitled Sword Knight", \
"Novice of Swords", \
"Knight of Swords", \
"Blade Knight", \
"Knight Clerist", \
"Abott of Swords", \
"Elder of Swords", \
"Master of Swords", \
"Lord of Swords", \
"Master Clerist", \
"Lord Clerist", \
"High Clerist" })

#define FROSE_TITLES ({ "Untitled Rose Knight", \
"Novice of Roses", \
"Knight of Tears", \
"Knight of Mind", \
"Knight of Roses", \
"Keeper of Roses", \
"Master of Roses", \
"Archknight", \
"Lady of Roses", \
"Master of Justice", \
"Lady of Justice", \
"High Justice" })

#define ROSE_TITLES ({ "Untitled Rose Knight", \
"Novice of Roses", \
"Knight of Tears", \
"Knight of Mind", \
"Knight of Roses", \
"Keeper of Roses", \
"Master of Roses", \
"Archknight", \
"Lord of Roses", \
"Master of Justice", \
"Lord of Justice", \
"High Justice" })

#if NEW_LAYMAN
#define KNIGHT_LAY_TITLES  ({ "Solamnian Knight", \
  "Black Sentry of Solamnia", \
  "Sentry of Solamnia", \
  "Sentry of Solamnia", \
  "Sentry of Solamnia", \
  "Sentry of Solamnia" })
#else
#define KNIGHT_LAY_TITLES  ({ "Solamnian Knight", \
  "Black Squire of Solamnia", \
  "Squire of Solamnia", \
  "Sentry of Solamnia", \
  "Sentry of Solamnia", \
  "Sentry of Solamnia" })
#endif

#if NEW_LAYMAN
#define SENTRY_M_TITLES ({ "an Untitled Sentinel", \
  "a Sentinel", \
  "a Scout", \
  "a Crown Guardsman", \
  "a Crown Patrolsman", \
  "a Crown Trustkeeper", \
  "a Sword Trustkeeper", \
  "a Sword Avenger", \
  "a Sword Protector", \
  "a Rose Avenger", \
  "a Rose Protector", \
  "the High Sentinel" }) /* high sentinel is NOT used*/

#define SENTRY_F_TITLES ({ "an Untitled Sentinel", \
  "a Sentinel", \
  "a Scout", \
  "a Crown Guardswoman", \
  "a Crown Patrolswoman", \
  "a Crown Trustkeeper", \
  "a Sword Trustkeeper", \
  "a Sword Avenger", \
  "a Sword Protector", \
  "a Rose Avenger", \
  "a Rose Protector", \
  "the High Sentinel" })
  /* high sentinel is NOT used, possibly allow more sublevels,
              dunno if this is easily possible.
  */
#else
#define SENTRY_TITLES ({ "an Untitled Squire", \
  "a Beginner Squire", \
  "a Travelled Squire", \
  "a Well Studied Squire", \
  "a Loyal Squire", \
  "a Crown Squire", \
  "an Experienced Crown Squire", \
  "a Sword Squire", \
  "an Experienced Sword Squire", \
  "a Rose Squire", \
  "an Elder Squire", \
  "an Elder Squire" })
#endif


#define WIMPY_LIMIT ({ 99,60,60,40,30,20,10 })
#define WIMPY_LIMIT2 ({ 10, 8, 6, 5, 4, 3, 2, 1, 0, -2, -4, -4, -4 })

#define SS_RESCUE  67530
#define SS_KATTACK 67531
/*
#define SS_KICK    67532
*/
#ifndef SS_BLOCK
#define SS_BLOCK   67533
#endif
#define KNIGHT_SKILL_DESC  ({"rescue", "kattack", "", "weapon form"})
/* Removed "kick",
 * we need the "" however to prevent bugs since the skill number are not consecutive anymore
 */
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
/* #define IN_B_LIST(str, remove) (ADMIN)->in_banish_list(str, remove)
 * #define REM_B_LIST(str)        (ADMIN)->remove_from_list(str)
 * #define IN_P_LIST(str, remove) (POBJ)->in_prestige_list(str, remove)
 */
#define DISGRACE(ob, reason)   (ADMIN)->perform_disgrace(ob, "paladine", reason,0)
#define BANISH(ob, reason)     (ADMIN)->perform_banishment(ob, "paladine", reason,0)
#define KILLED(killer, killed) (ADMIN)->killed_logging(killer, killed)
#define LEAVE(ob)              (ADMIN)->leave(ob)

              /*  2H  POL PAR DEF SW KN CL AX LA AM AO AH TR HU AW*/
#define SKILLS ({ 20, 1, 23, 24, 0, 3, 4, 2, 109, 100, 101, 105, 107, \
                  108, 110, \
                  SS_RESCUE, SS_KATTACK, \
                  SS_BLOCK, SS_PRESTIGE_ACC, SS_PRESTIGE_ST, \
                  SS_CHARITY, SS_DISGRACED})

/*
#define F_CKICK_HIT(ob, ob2) ob->query_skill(SS_KICK) * \
 ob->query_stat(SS_DEX) - \
 ob2->query_stat(SS_DEX) * 10

#define F_CKICK_PEN(ob, ob2) F_PENMOD(ob->query_stat(SS_STR) / 4, \
 2 * ob->query_skill(SS_KICK) / 3) + 10

#define CKICK_HIT 300

#define F_BASH_HIT(ob, ob2) ob->query_stat(SS_DIS) * \
 ob->query_skill(SS_BASH) - \
 ob2->query_stat(SS_DIS) * 10

#define F_BASH_PEN(ob, ob2) F_PENMOD(ob->query_stat(SS_STR) / 3, \
 3 * ob->query_skill(SS_BASH) / 4) + 20

#define BASH_HIT 800
*/

/* Formulas to the cmd_soul */

#define F_RESCUE(ob, ob2) ob->query_stat(SS_DIS) + ob->query_stat(SS_DEX) - \
                      ob2->query_stat(SS_WIS) + \
                      ob->query_skill(SS_RESCUE) * ob->query_skill(SS_RESCUE) * \
                      ob->query_skill(SS_RESCUE) / 400

#define RESCUE_HIT 200

