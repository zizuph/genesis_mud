/*
 *   defs.h
 * 
 * Main definitions file for the Eldoral undead
 * tunnel system.
 *
 * Baldacin@Genesis, Sep 2003
 */

#include "../defs.h"

#define ROOMS     (TUNNEL + "rooms/")
#define TUN_NPCS  (TUNNEL + "npcs/")
#define TUN_ARMOURS (TUNNEL + "armours/")
#define TUN_OBJECTS (TUNNEL + "objects/")
#define TUN_WEAPONS (TUNNEL + "weapons/")
#define TUN_DOORS   (TUN_OBJECTS + "doors/")
#define UNDERGROUND (ROOMS + "underground/")

#define HIMSELF(x)    ((x)->query_objective() + "self")
#define ONE_OF(x)     ((x)[random(sizeof(x))])

// Key Codes for the Underground Tunnel Gates
#define GATE_ONE_KEY    "_underground_tunnel_gate_one_key"
#define GATE_TWO_KEY    "_underground_tunnel_gate_two_key"
#define GATE_THREE_KEY  "_underground_tunnel_gate_three_key"
#define GATE_FOUR_KEY   "_underground_tunnel_gate_four_key"
