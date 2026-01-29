
/* local.h for kalaman 3/3/97 
 * definitions for dungeon and poor district added 2011
 */

#ifndef KALAMAN_DEF
#define KALAMAN_DEF

#define KPATH    "/d/Ansalon/kalaman"
#define KROOM    KPATH + "/room/"
#define CITY     KPATH + "/city/"
#define WALL     KPATH + "/wall/"
#define KOBJ     KPATH + "/obj/"
#define KWEAPON  KOBJ + "weapon/"
#define KARMOUR  KOBJ + "armour/"
#define KNPC     KPATH + "/living/"
#define KLOG     KPATH + "/log/"
#define PLAINS   "/d/Ansalon/estwilde/plains/"
#define SEWERS   KPATH + "/sewers"
#define SROOM    SEWERS + "/rooms/"
#define SOBJ     SEWERS + "/obj/"
#define SNPC     SEWERS + "/living/"
#define DUNGEON  KPATH + "/dungeon"
#define DOBJ     DUNGEON + "/obj/"
#define DROOM    DUNGEON + "/rooms/"
#define DNPC     DUNGEON + "/living/"
#define POOR     KPATH + "/poor"
#define PROOM    POOR  + "/rooms/"

#define STDDOOR "/d/Ansalon/std/door"
#define NORMAL_BOARD KLOG + "boards/normal"
#define BOGUS_KEY "7110000"
#define KALAMAN_OUT KPATH + "/std/o_room_base"
#define KALAMAN_IN KPATH + "/std/i_room_base"
#define DUNGEON_IN DUNGEON + "/std/dungeon_base"
#define SEWER_IN SEWERS + "/std/kalaman_sewers"
#define CITY_OUT KPATH + "/std/city_out_base"
#define KALAMAN_NOBUY   "_kalaman_no_buy"


/* Kalaman Master Server */
#define KMASTER (KPATH + "/std/kalaman_master")
#define DMASTER (KMASTER)

/* Status definitions for kalaman_master.c (master server) */
#define S_DSLEEP   "dungeon_guards_sleep"
#define S_DDOOR1   "dungeon_guard_door"
#define S_DDOOR2   "dungeon_area2_door"
#define S_DGRATE   "dungeon_grate"
#define S_WGRATE   "well_grate"
#define S_GWELL    "garden_well"
#define S_TDRAPERY "thief_drapery"
#define S_MAINGATE "dungeon_main_gate"

#ifndef ENV
#define ENV(x) environment(x)
#endif

#define SOLPLAINS "/d/Krynn/solamn/eplains/rooms/eplain-24-2-K"

#endif KALAMAN_DEF
