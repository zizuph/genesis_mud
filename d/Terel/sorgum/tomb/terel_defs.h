   
/* metaprat - 920622 - just a suggestion ;) - change at will */
/* modification by dust: added property ROOM_HAS_WATER */
/* modified by cedric: changed prop ROOM_HAS_WATER to  
 * "_obj_i_contain_water", the mudlib-implemented standard */
/* Silvoria definitions file   */

#define DOMAINDIR   "/d/Terel/"
#define TERELDIR    DOMAINDIR + "common/"
#define MOUNTDIR    TERELDIR + "mountains/"
#define VALLEYDIR   TERELDIR + "valley/"
#define TOWNDIR     TERELDIR + "town/"
#define HOUSEDIR    TOWNDIR + "houses/"
#define FORESTDIR   TERELDIR + "forest/"
#define NPCSDIR     TERELDIR + "npcs/"
#define OBJSDIR     TERELDIR + "objs/"
#define MANSION     TERELDIR + "town/mansion/"
#define ENCHANT     TERELDIR + "enchanted/"
#define GARDEN      MANSION + "grd/"
#define CRTYARD     MANSION + "crt/"
#define BASEMENT    MANSION + "base/"
#define GRAVEYARD   MANSION + "grv/"
#define SECOND      MANSION + "sec/"
#define LIBRARY     MANSION + "lib/"
#define LEGION      MANSION + "leg/"
#define BASE        BASEMENT
#define PORT     TERELDIR + "port/"
#define SHIP       PORT + "ship/"
#define NPORT    TERELDIR + "n_port/"
/* Suggested connection locations between areas.   */
/* (eg, FORESTS may lead to TOWNN, and vice versa) */
/* (any connections mentioned below are entirely   */
/*  hypothetical).                                 */

#define ENTR_FOREST_N FORESTDIR + "forest23"
#define ENTR_FOREST_S FORESTDIR + "road1"
#define ENTR_FOREST_E FORESTDIR + "forest00"
#define ENTR_FOREST_W FORESTDIR + "forest00"

#define ENTR_MOUNT_N  MOUNTDIR + "mount00"
#define ENTR_MOUNT_S  MOUNTDIR + "mount00"
#define ENTR_MOUNT_E  MOUNTDIR + "mount00"
#define ENTR_MOUNT_W  MOUNTDIR + "mount00"

#define ENTR_VALL_N   VALLEYDIR + "valley00"
#define ENTR_VALL_S   VALLEYDIR + "valley00"
#define ENTR_VALL_E   VALLEYDIR + "valley00"
#define ENTR_VALL_W   VALLEYDIR + "valley00"

#define ENTR_TOWN_N   TOWNDIR + "silv_n3_1"
#define ENTR_TOWN_S   TOWNDIR + "silv06_6"
#define ENTR_TOWN_E   TOWNDIR + "silv12_4"
#define ENTR_TOWN_W   TOWNDIR + "silv01_5"

#define MECIENDIR   DOMAINDIR + "mecien/"
#define VADERDIR    DOMAINDIR + "vader/" 
#define JANUSDIR    DOMAINDIR + "janus/"
#define METAPRATDIR DOMAINDIR + "metaprat/"
#define OMDIR       DOMAINDIR + "om/"
#define AZIREONDIR  DOMAINDIR + "azireon/"
#define NAPTUREDIR    DOMAINDIR + "napture/"
#define CEDRICDIR     DOMAINDIR + "cedric/"
#define DUSTDIR     DOMAINDIR + "dust/"
#define MORTRICIADIR DOMAINDIR + "mortricia/"
#define REDHAWKDIR   DOMAINDIR + "redhawk/"
#define ELDERONDIR  DOMAINDIR + "elderon/"
#define JORLDIR  DOMAINDIR + "jorl/"
#define SORGUMDIR  DOMAINDIR + "sorgum/"

/* 
 * I propose we all add handy little macros here. -Cedric
 */
#define TCM(message) this_player()->catch_msg(message)

/* Additional properties
 * ROOM_HAS_WATER: means that you can fill the bucket with
 *                 water here (by dust)
 */

#define ROOM_HAS_WATER	"_obj_i_contain_water"

/* Quest-definitions:
 * QUEST_xxx_GROUP : group for quest bit (0..4)
 * QUEST_xxx_BIT : bit number
 * QUEST_xxx_EXP : exp points given for this quest
 */

#define QUEST_LOG		"/d/Terel/common/quest_log"
/* fire-quest in caves */
#define QUEST_FIRE_GROUP	0
#define QUEST_FIRE_BIT		0
#define QUEST_FIRE_EXP		2000
/* balance-quest (riddle) */
#define QUEST_BAL_GROUP		0
#define QUEST_BAL_BIT		1
#define QUEST_BAL_EXP		2000
/* red-death-quest (dangerous) */
#define QUEST_DEATH_GROUP	0
#define QUEST_DEATH_BIT		2
#define QUEST_DEATH_EXP		4000
/* maze-quest (colored rooms) */
#define QUEST_MAZE_GROUP	0
#define QUEST_MAZE_BIT		3
#define QUEST_MAZE_EXP          4000
/* Child Quest (bring Jeffrey home) */
#define QUEST_CHILD_GROUP          0
#define QUEST_CHILD_BIT            4
#define QUEST_CHILD_EXP            1000
/* The quests _G1_ to _G7_ are handled by the fortune teller in
 * the gyspy camp
 */
/* The hat quest */
#define QUEST_G1_GROUP  0
#define QUEST_G1_BIT    5
#define QUEST_G1_EXP    100
/* The beard quest */
#define QUEST_G2_GROUP  0
#define QUEST_G2_BIT    6
#define QUEST_G2_EXP    500
/* The belt quest */
#define QUEST_G3_GROUP  0
#define QUEST_G3_BIT    7
#define QUEST_G3_EXP    1000
/* The juggle quest */
#define QUEST_G4_GROUP  0
#define QUEST_G4_BIT    8
#define QUEST_G4_EXP    1000
/* The tight-rope quest */
#define QUEST_G5_GROUP  0
#define QUEST_G5_BIT    9
#define QUEST_G5_EXP    2000
/* The magic quest */
#define QUEST_G6_GROUP  0
#define QUEST_G6_BIT    10
#define QUEST_G6_EXP    16500
/* The spooky quest */
#define QUEST_G7_GROUP  0
#define QUEST_G7_BIT    11
#define QUEST_G7_EXP    10000
/* The Sacrifice Quest, by Vader */
#define QUEST_SAC_GROUP  0
#define QUEST_SAC_BIT    12
#define QUEST_SAC_EXP    10000
/* Porcia-quest (also yellow hint for door quest) */
#define QUEST_POR_GROUP 0
#define QUEST_POR_BIT	13
#define QUEST_POR_EXP   3000
/* Thane quest part 1: find sword, tear tapestry      	Cedric */
#define QUEST_TH1_GROUP	0
#define QUEST_TH1_BIT	14
#define QUEST_TH1_EXP	5000
/* Thane quest part 2: kill the Dark One 		Cedric */
#define QUEST_TH2_GROUP	0
#define QUEST_TH2_BIT	15
#define QUEST_TH2_EXP	5000
/* Mystic Order Quest,  by Mecien  */
#define QUEST_MOQ_GROUP   0
#define QUEST_MOQ_BIT   16
#define QUEST_MOQ_EXP    8000
/* big zodiac quest */
#define QUEST_ZOD_GROUP 0
#define QUEST_ZOD_BIT 17
#define QUEST_ZOD_EXP 70000
/* chisel quest in mines */
#define QUEST_CHI_GROUP 0
#define QUEST_CHI_BIT 18
#define QUEST_CHI_EXP 5000
/* witch quest, by Janus and Mortricia */
#define QUEST_WIT_GROUP 0
#define QUEST_WIT_BIT 19
#define QUEST_WIT_EXP 15000
/* The following quests are all located at Janus area
   and handled by the master Gardener. */
/* Bring the cat back quest by Janus */
#define QUEST_JJ1_GROUP 1
#define QUEST_JJ1_BIT 0
#define QUEST_JJ1_EXP 1600
/* Bracelet quest, by Janus */
#define QUEST_JJ2_GROUP 1
#define QUEST_JJ2_BIT 1
#define QUEST_JJ2_EXP 10000
/* Kill the bug queen quest, by Janus */
#define QUEST_JJ3_GROUP 1
#define QUEST_JJ3_BIT 2
#define QUEST_JJ3_EXP 20000
/* Kill the evil dragon in Ribos, by Vader */
#define QUEST_RIB_GROUP 1
#define QUEST_RIB_BIT 3
#define QUEST_RIB_EXP 40000
/* Find the map of Legion Dungeons Quest, by Redhawk */
#define QUEST_RR1_GROUP 1
#define QUEST_RR1_BIT 4
#define QUEST_RR1_EXP 1500
/* Legion dungeons quest 2 (only testing) by Redhawk */
#define QUEST_RR2_GROUP 1
#define QUEST_RR2_BIT 5
#define QUEST_RR2_EXP 2000

/* The vote_room puzzle quest, by Sorgum */
#define QUEST_SS1_GROUP 1
#define QUEST_SS1_BIT 6
#define QUEST_SS1_EXP 10000
   
/* END OF DEF FILE */


