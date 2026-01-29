#include "/d/Khalakhor/sys/paths.h"

/* Global coords for Abhainn Ruith. */
#define VILLAGE_COORDS ({1, 1});

/* A few path shortcuts. */
#define VILLAGE  S_EAST + "rannoch/village/"
#define ROOM     VILLAGE + "room/"
#define NPC      VILLAGE + "npc/"
#define OBJ      VILLAGE + "obj/"
#define ARM      VILLAGE + "arm/"
#define WEP      VILLAGE + "wep/"

/* Arrays with coords for certain groups of rooms */
#define WALL_COORDS ({"0,8","0,9","0,10","1,7","2,6","3,6",\
                      "4,6","6,6","6,7","13,1","14,1","15,1",\
                      "16,1","17,2","17,3",})
#define RIVERBANK_COORDS ({"7,6","7,7","9,5","9,6","9,7","9,8",\
                           "10,4","11,3","12,2","13,1",})
#define WALKWAY_WEST_COORDS ({"0,10","1,10","2,10","3,10","4,10",\
                              "4,9","5,9","6,9","7,8","7,7",})
#define WALKWAY_EAST_COORDS ({"11,10","12,10","13,9","14,9",\
                              "14,10","15,11","16,11","16,10",\
                              "17,9","17,8",})
#define MAIN_ROAD_COORDS ({"9,7","10,7","11,7","12,7","13,7",\
                           "14,7","15,7","16,7","17,7","18,7",\
                           "10,6","11,5","12,5","13,4","14,3",\
                           "15,2","16,1",})
#define MARKETPLACE_COORDS ({"3,7","3,8","3,9","4,7","4,9",\
                             "5,7","5,8","5,9",})
#define OTHER_BUSY_COORDS ({"0,9","1,9","2,9","2,10","3,10",\
                            "6,7","6,8","7,7","8,7","15,6",\
                            "15,8","15,9",})