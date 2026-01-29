/*
 * Macro defines for the internal Earthsea terrain system and
 * Mudlib system
 * Ckrik 9/2003
 *
 * Make sure there are no errors in this file if you edit it.
 */

#include <stdproperties.h>
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

#define BEACH  \
     add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SALTBEACH); \
     add_prop(ROOM_I_TYPE, ROOM_BEACH); \
     add_prop(ROOM_I_IS, 1); \
     add_prop(ROOM_I_LIGHT, 1);
#define BAY \
     add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_BAY); \
     add_prop(ROOM_I_TYPE, ROOM_IN_WATER); \
     add_prop(ROOM_I_IS, 1); \
     add_prop(ROOM_I_LIGHT, 1);
#define SEA \
     add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_OCEAN); \
     add_prop(ROOM_I_TYPE, ROOM_IN_WATER); \
     add_prop(ROOM_I_IS, 1); \
     add_prop(ROOM_I_LIGHT, 1);
#define UNDER_SEA \
     add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_UNDERSEA); \
     add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER); \
     add_prop(ROOM_I_IS, 1); \
     add_prop(ROOM_I_LIGHT, 0);
#define FOREST  \
     add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST); \
     add_prop(ROOM_I_IS, 1); \
     add_prop(ROOM_I_LIGHT, 1);
#define MEADOW  \
     add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_PLAIN); \
     add_prop(ROOM_I_IS, 1); \
     add_prop(ROOM_I_LIGHT, 1);
#define FIELD  \
     add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FIELD); \
     add_prop(ROOM_I_IS, 1); \
     add_prop(ROOM_I_LIGHT, 1);
#define STREET  \
     add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_STREET); \
     add_prop(ROOM_I_IS, 1); \
     add_prop(ROOM_I_LIGHT, 1);
#define INSIDE  \
     add_prop(ROOM_I_IS, 1); \
     add_prop(ROOM_I_INSIDE, 1); \
     add_prop(ROOM_I_LIGHT, 1);
