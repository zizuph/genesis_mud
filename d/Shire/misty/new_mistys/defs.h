/*
 * Local defines for Misty Mountains
 * Created by Finwe, September 2004
 *
 */

// Root directory
#define MM_DIR              "/d/Shire/misty/new_mistys/"

// Directories
#define ARM_DIR             (MM_DIR + "arm/")
#define WEP_DIR             (MM_DIR + "wep/")
#define MM_LOG_DIR          (MM_DIR + "log/")
#define PATH_DIR            (MM_DIR + "rooms/paths/")
#define CAVE_DIR            (MM_DIR + "rooms/caves/")
#define ORCMAKER_DIR        ("/d/Shire/orcmaker/")
#define ORC_OBJ             (ORCMAKER_DIR + "obj/")

// Base files
#define PATH_BASE           (MM_DIR + "base_path.c")
#define MT_BASE             (MM_DIR + "base_mt.c")
#define BASE_COMMON         (MM_DIR + "base_common.c")
#define ROOM_TELL_TIME      180
#define NPC_TELL_TIME        90

// Sets up time defs for area.
#define LATE_NIGHT           0..3    /*12am-3am*/
#define EARLY_MORNING        4..7    /*4am-7am*/
#define MORNING              8..11    /*8am-10am*/
#define NOON                12..13    /*11am-1pm*/
#define AFTERNOON           14..17    /*2pm-5pm*/
#define EVENING             18..21    /*6pm-9pm*/
#define EARLY_NIGHT         22..24    /*10pm-12am*/


