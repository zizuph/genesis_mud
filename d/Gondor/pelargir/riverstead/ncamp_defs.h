/*
 * ncamp_defs.h
 *
 * Definitions for Anduin Orc Invasion.
 *
 * These are the defines for an area designed for so-called "newbies".
 * The scenario is a small settlement of Gondorian farmers along the
 * western bank of the Anduin under attack by a band of orcs who have
 * crossed the river. This is intended to be a place where small players
 * can go to slay evil or good (or both) NPCs and gain some combat
 * experience, reasonable equipment, money, etc. As such, players above
 * a certain stataverage will not be able to access the area.
 *
 * Coded by Alto, 24 September 2002
 *
 * Modification log:
 * Date     Name    Modification
 * 6-6-17   Alto    Raised STAT_MAX to 200 to allow larger mortals
 *                  to enter. With the addition of the Genesis tutorial
 *                  area, newbies were too big to enter after completing 
 *                  the tutorial.
 */
 
#ifndef NEWBIECAMP_DEFINITIONS
#define NEWBIECAMP_DEFINITIONS
 
/* To guard against redefinitions, do not add definitions before this line.
 */
 
/* Values
 */
#define STAT_MAX             200
 

/* Directories.
 */
 
#define NCAMP_DIR            "/d/Gondor/pelargir/riverstead/"

#define NCAMP_OBJ            NCAMP_DIR          + "obj/"
#define NCAMP_ROOM           NCAMP_DIR          + "room/"
#define NCAMP_NPC            NCAMP_DIR          + "npc/"
#define NCAMP_ARM            NCAMP_DIR          + "arm/"
#define NCAMP_WEP            NCAMP_DIR          + "wep/"
#define NCAMP_LIB            NCAMP_DIR          + "lib/"
#define NCAMP_QUEST          NCAMP_DIR          + "quest/"
#define NCAMP_LOG            NCAMP_LIB          + "log/"

/* Log files.
 */
 
#define NCAMP_KILL_LOG       NCAMP_LOG          + "ncampkills"


/* Properties.
 */

#define NCAMP_NO_ATTACK         "_ncamp_no_attack"
#define NCAMP_ATTACK_LOWER      "_ncamp_attack_lower"
#define NCAMP_ATTACK_UPPER      "_ncamp_attack_upper"


/* Macros.
 */

#define WIZARD            this_player()->query_wiz_level()
#define GOODIE            this_player()->query_alignment() >= 0
#define BADDIE            this_player()->query_alignment() < 0
#define STAT_AVE          this_player()->query_average_stat()
#define NO_ATTACK         this_player()->query_prop(NCAMP_NO_ATTACK)
#define ATTACK_LOWER      this_player()->query_prop(NCAMP_ATTACK_LOWER)
#define ATTACK_UPPER      this_player()->query_prop(NCAMP_ATTACK_UPPER)


/* To guard against redefinition, put all defs above this line.
 */
#endif NEWBIECAMP_DEFINITIONS
