/*
 * Defines for Annuminas
 * -- Finwe, December 2001
 */

#define ANN_DIR         "/d/Shire/annuminas/"
#define ANN_NPC         (ANN_DIR + "monsters/")
#define ANN_WEP         (ANN_DIR + "wep/")
#define ANN_ARM         (ANN_DIR + "arm/")
#define ANN_OBJ         (ANN_DIR + "obj/")

/* base files */

/* miscellaneous defines */
#define ROOM_TELL_TIME  60+random(120)
#define NPC_TELL_TIME   90


// Sets up time defs for area.
#define LATE_NIGHT		0..3	/*12am-3am*/
#define EARLY_MORNING	4..7	/*4am-7am*/
#define MORNING			8..10	/*8am-10am*/
#define NOON			11..13	/*11am-1pm*/
#define AFTERNOON		14..17	/*2pm-5pm*/
#define EVENING			18..21	/*6pm-9pm*/
#define EARLY_NIGHT		22..24	/*10pm-12am*/