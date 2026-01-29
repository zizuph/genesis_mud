/*
 * Local defines for Anduin
 * Created by Finwe, June 2001
 *
 */
 
// Root directory
#define ANDUIN_DIR      "/d/Shire/anduin/"
 
// Object directories
#define ARM_DIR            (ANDUIN_DIR + "arm/")
#define WEP_DIR            (ANDUIN_DIR + "wep/")
#define OBJ_DIR            (ANDUIN_DIR + "obj/")
#define NPC_DIR            (ANDUIN_DIR + "npcs/")
 
// Room directories
#define WEST_DIR           (ANDUIN_DIR + "west/")
#define EAST_DIR           (ANDUIN_DIR + "east/")

// Base files
#define VALE_BASE           (ANDUIN_DIR + "base_vale.c")
#define BASE_HOUSE          (ANDUIN_DIR + "base_house.c")
 
#define ROOM_TELL_TIME      180
#define NPC_TELL_TIME        90
 
// Sets up time defs for area.
#define LATE_NIGHT		0..3	/*12am-3am*/
#define EARLY_MORNING	4..7	/*4am-7am*/
#define MORNING			8..10	/*8am-10am*/
#define NOON			11..13	/*11am-1pm*/
#define AFTERNOON		14..17	/*2pm-5pm*/
#define EVENING			18..21	/*6pm-9pm*/
#define EARLY_NIGHT		22..24	/*10pm-12am*/

/*
#ifndef GONDOR_HERB_DIR
#define GONDOR_HERB_DIR  "/d/Gondor/common/herbs/"
#endif
#ifndef SHIRE_HERB_DIR
#define SHIRE_HERB_DIR   "/d/Shire/common/herbs/"
#endif
#ifndef KRYNN_HERB_DIR
#define KRYNN_HERB_DIR   "/d/Krynn/common/herbs/"
#endif
*/