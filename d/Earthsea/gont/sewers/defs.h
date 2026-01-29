/*#include "../defs.h"/*/

#define SEWER_DIR         ("/d/Earthsea/gont/sewers/")


#define SEWER_ROOM_DIR    (SEWER_DIR + "room/")
#define SEWER_OBJ_DIR     (SEWER_DIR + "obj/")
#define SEWER_NPC_DIR     (SEWER_DIR + "npc/")
#define SEWER_WEP_DIR     (SEWER_DIR + "wep/")
#define SEWER_LIB_DIR     (SEWER_DIR + "lib/")
#define SEWER_LOG_DIR     (SEWER_DIR + "log/")
#define SEWER_ARM_DIR     (SEWER_DIR + "arm/")
#define DATA_DIR          (SEWER_DIR + "data/")
#define BC_MODULE         (SEWER_LIB_DIR + "broadcast_master")

/* Base files */
#define SEWER_ROOM_BASE   (SEWER_ROOM_DIR + "sewer_room_base")
#define MAIN_TUNNEL_BASE  (SEWER_ROOM_DIR + "main_tunnel_base")
#define SPOKE_TUNNEL_BASE (SEWER_ROOM_DIR + "spoke_tunnel_base")

/* Room directories */
#define SEWER_MAIN_TUNNEL (SEWER_ROOM_DIR + "main_tunnel/")
#define SEWER_SPOKE       (SEWER_ROOM_DIR + "sewer_spoke/")

/* NPC files */
#define SEWER_NPC         (SEWER_NPC_DIR  + "sewer_npc")

/* Defines for Broadcast Room Types */
#define ROOM_TYPE_UNKNOWN   0
#define ROOM_TYPE_STREET    1
#define ROOM_TYPE_ROOF      2
#define ROOM_TYPE_DOCK      3