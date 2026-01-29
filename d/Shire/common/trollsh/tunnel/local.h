/*
 * Local defines for tunnels of the Trollshaws
 * Created by Finwe, August 2001
 *
 */
 
// Root directory
#define TS_DIR      "/d/Shire/common/trollsh/"
#define TUN_DIR     (TS_DIR + "tunnel/")
 
// Object directories
#define ARM_DIR            (TS_DIR + "arm/")
#define WEP_DIR            (TS_DIR + "weapon/")
#define OBJ_DIR            (TS_DIR + "obj/")
#define NPC_DIR            (TS_DIR + "npc/")
 
// Room directories

// Base files
#define TUNNEL_BASE            (TUN_DIR + "base_tunnel.c")
 
#define ROOM_TELL_TIME      180
#define NPC_TELL_TIME        90
#define DARK                add_prop(ROOM_I_LIGHT, -1);
#define LIGHT               add_prop(ROOM_I_LIGHT, 1);

 