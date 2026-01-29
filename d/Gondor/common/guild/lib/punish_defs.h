/* The defines for possible punishments. */
#define NO_PUNISH     0
#define REM_PUNISH    1
#define NOTRAIN       2
#define NOTRADE       3
#define NOACCESS      4
#define NOSKILLS      5
#define NOSPELLS      6
#define NOABILITIES   7
#define DEGRADE       8
#define REWARD        9
#define PUPILIZE     10
#define EXPULSION    11
#define BAN          12
#define OUTLAW       13
#define COMMEND      14

/* String descriptions of the possible punishments. */
#define PTYPE ({ "not punished", "cleared for punishments",\
        "no access to training", "no access to trading",\
        "no access to Ranger hideouts", "no use of Ranger skills",\
        "no use of Ranger magic", "no use of Ranger abilities",\
        "lowered guild-rank", "raised guild-rank", "demotion to pupil status",\
        "expulsion from the Rangers", "banning from the Rangers",\
        "being outlawed in Gondor", "a commendation" })

#define PUNISH_LOG   "/d/Gondor/log/rangerpunish"
#define RANKSTEP   5  /* Occ-stat steps per rank in punish/reward */

/* Skill-numbers used for punishment/reward handling (OLD_REWARDED,
 * OLD_PUNISHED, SS_PUNISHED, SS_REWARDED and SS_PUNISHMENT) are defined
 * in /d/Gondor/defs.h
 */
