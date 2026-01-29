#ifndef DOCK_DEFS
#define DOCK_DEFS

#define DOCK_DIR       "/d/Emerald/docks/"
#define DOCK_NPC_DIR   (DOCK_DIR + "npc/")
#define CERAL_ROOM     (DOCK_DIR + "ceral_room")
#define DOCK_ROOM      (DOCK_DIR + "dock_room")
#define DOCK_PATH_ROOM (DOCK_DIR + "dock_path_room")
#define PAV_PATH_ROOM  (DOCK_DIR + "pav_path_room")
#define PAV_ROOM       (DOCK_DIR + "pavilion_room")
#define DOCK_DOOR_OBJ  (DOCK_DIR + "obj/gate")
#define SHIP_MGR       (DOCK_DIR + "ship_mgr")
#define DIRECTION_MGR  (DOCK_DIR + "direction_mgr")

#define TELBERIN_LINE  	   ("Telberin")
#define SPARKLE_LINE   	   ("Sparkle")
#define FAERIE_LINE    	   ("Faerie")
#define TEREL_LINE     	   ("Terel")
#define AVENIR_LINE    	   ("Avenir")
#define GOLDEN_ISLAND_LINE ("Golden Island")
#define NORTH_SHORE_LINE   ("North Shore")

#define STATUS_UNKNOWN  0
#define STATUS_DOCKED   1
#define STATUS_UNDOCKED 2

// Define this as true if the ticketing agents should be in the pavilion
#define AGENT_PRESENT 0
#define PUB_OPEN      0
#define PO_OPEN       1
#define PAVILION_OPEN 1

#endif
