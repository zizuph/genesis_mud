/*
 * Local defines for the new Gobo caves
 * Created by Tijgen
 *9/13/02
 */

#include "/d/Shire/sys/defs.h"

 
// Root directory
#define CAVES_DIR      "/d/Shire/misty/new_goblin_caves/"
 
// Object directories
#define ARM_DIR            (CAVES_DIR + "armours/")
#define WEP_DIR            (CAVES_DIR + "weapons/")
#define OBJ_DIR            (CAVES_DIR + "objects/")
#define NPC_DIR            (CAVES_DIR + "npcs/")
  
// Room directories
#define ROOMS_DIR           (CAVES_DIR + "rooms/")
#define FOOD_DIR            (CAVES_DIR + "food/")
#define COURIER_DIR         (CAVES_DIR + "messengers/")


// Base files
#define CAVES_BASE           (CAVES_DIR + "cave_base.c")
#define GOBLIN_BASE          (NPC_DIR + "goblin_base")
#define ROOM_TELL_TIME      180
#define NPC_TELL_TIME        90
 
// Sets up time defs for area.
#define LATE_NIGHT              0..3    /*12am-3am*/
#define EARLY_MORNING           4..7    /*4am-7am*/
#define MORNING                 8..10   /*8am-10am*/
#define NOON                    11..13  /*11am-1pm*/
#define AFTERNOON               14..17  /*2pm-5pm*/
#define EVENING                 18..21  /*6pm-9pm*/
#define EARLY_NIGHT             22..24  /*10pm-12am*/

