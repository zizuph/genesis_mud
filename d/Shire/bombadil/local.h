/*
 * Defines for Tom Bombadil
 * -- Finwe, December 2001
 */

#define TOM_DIR         "/d/Shire/bombadil/"
#define ROOMS_DIR       (TOM_DIR + "rooms/")
#define VAL_DIR         "/d/Shire/downs/valley/"
#define OBJ_DIR         (TOM_DIR + "obj/")
#define WEP_DIR         (TOM_DIR + "wep/")
#define ARM_DIR         (TOM_DIR + "arm/")
#define NPC_DIR         (TOM_DIR + "npc/")

// base files
#define CLEAR_BASE      (TOM_DIR + "base_clearing.c")
#define INSIDE_BASE     (TOM_DIR + "base_inside.c")        
#define WITHY_BASE      (TOM_DIR + "base_withy.c")
#define HOUSE_BASE      (TOM_DIR + "base_house.c")
#define PICK_LILIES     (TOM_DIR + "pick_lilies.c")

// miscellaneous defines
#define ROOM_TELL_TIME  90+random(30)
#define NPC_TELL_TIME   90

// props
#define PARALYZED               "_bombadil_paralyze_"
#define LILY_PROP               "_shire_lily_"
#define QUEST_LILY_PROP         "_shire_find_lily_quest_"
#define FEATHER_PROP            "_shire_pheasant_feather_"
#define QUEST_FEATHER_PROP      "_shire_get_tom_feather_quest_"

// Sets up time defs for area.
#define LATE_NIGHT		0..3	/*12am-3am*/
#define EARLY_MORNING           4..7	/*4am-7am*/
#define MORNING			8..10	/*8am-10am*/
#define NOON			11..13	/*11am-1pm*/
#define AFTERNOON		14..17	/*2pm-5pm*/
#define EVENING			18..21	/*6pm-9pm*/
#define EARLY_NIGHT		22..24	/*10pm-12am*/