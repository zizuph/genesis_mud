#ifndef _SHIRE_DOMAIN_FILES_
#define _SHIRE_DOMAIN_FILES_

/* Define the std inherits */
#define SHIRE_ROOM      "/d/Shire/std/room" 
#define SHIRE_MONSTER   "/d/Shire/std/monster" 
#define SHIRE_CREATURE  "/d/Shire/std/creature"
#define SHIRE_DOOR      "/d/Shire/std/door" 
#define SHIRE_WORKROOM  "/d/Shire/std/workroom" 

/* Define the lib inherits */
#define HERB_SEARCH     "/d/Shire/lib/herbsearch" 
#define INN_LIB         "/d/Shire/lib/inn"  
#define AREA_ROOM       "/d/Shire/lib/area_room" 
#define HERBALIST_LIB   "/d/Shire/lib/herbalist" 
#define KILL_LOGGER     "/d/Shire/lib/kill_logger"
#define HUNT_SHADOW     "/d/Shire/lib/hunting_shadow"
#define LOOKOUT         "/d/Shire/lib/lookout_func"


/* Define important include files */
#define SKILLS_FILE      "/d/Shire/skills.h"
#define BITS_FILE        "/d/Shire/bits.h"
#define MONEY_FILE       "/d/Shire/common/make_money.h"
#define HOBBIT_FILE      "/d/Shire/hobbitmaker/hobbitmaker.h"
#define ORC_FILE         "/d/Shire/orcmaker/orcmaker.h"

/* Define important Shire files. */
#define HERB_MASTER       "/d/Shire/common/herbs/herb_master.c"
#define QUEST_MASTER      "/d/Shire/sys/global/quest_master"
#ifdef  CLOCK
#undef  CLOCK
#endif
#define CLOCK             "/d/Gondor/common/obj/clock"


// No more defines after this line.
#endif
