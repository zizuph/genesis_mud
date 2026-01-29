/*
	* Local defines for path to Grey Mountains
	* Altrus, June 2005
	*
*/
 
// Root directory
#define GREY_DIR     	 "/d/Shire/greymount/"
 
// Object directories	
#define ARM_DIR          	(GREY_DIR + "arm/")
#define WEP_DIR         	(GREY_DIR + "wep/")
#define OBJ_DIR          	(GREY_DIR + "obj/")
#define NPC_DIR          	(GREY_DIR + "npcs/")
 
// Room directories
#define FOOT_DIR		(GREY_DIR + "foothills/")
#define DOOR_DIR		(GREY_DIR + "backdoor/")

// Base files
#define FOOT_BASE          	(FOOT_DIR + "desc_foothills.c")
#define PATH_BASE		(GREY_DIR + "base_path.c")
#define GREY_BASE		(GREY_DIR + "base_grey_path.c")
#define FIELD_BASE		(GREY_DIR + "base_field.c")
#define GREY_DESC		(FOOT_DIR + "desc_grey_path.c")
 
//#define ROOM_TELL_TIME     180
//#define NPC_TELL_TIME       	90
 
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