#define THIS_DIR        "/d/Emerald/telberin/" 
#define CASTLE_DIR      THIS_DIR + "castle/"
#define HOUSE_DIR       THIS_DIR + "house/"
#define OUT_DIR         THIS_DIR + "outskirts/"
#define ARM_DIR         THIS_DIR + "arm/"
#define WEP_DIR         THIS_DIR + "wep/"
#define OBJ_DIR         THIS_DIR + "obj/"
#define NPC_DIR         THIS_DIR + "npc/"
 
#define AVENUE_DIR      THIS_DIR + "avenue/"
#define AVENUE          AVENUE_DIR +  "avenue_base.c"
#define INNER_AVE       AVENUE_DIR + "avenue_inner_base.c"
 
#define LROAD           THIS_DIR + "road/"
#define LAKEROAD        LROAD + "road_base.c"
 
// defs for leah road to chapel
#define LEROAD          THIS_DIR + "road/"
#define LEAHROAD        LEROAD + "leroad_base.c"

#define NPC_HANDLER     THIS_DIR + "telberin_npc_handler"
#define LOAD_HANDLER    catch(call_other(NPC_HANDLER, "??"))
#define IS_CARRIAGE_STOP "_is_carriage_stop_room"
