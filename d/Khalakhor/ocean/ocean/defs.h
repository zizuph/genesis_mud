/*
 * Khalakhor sea definitions
 * Tapakah, 10/2021
 */

#ifndef KHALAKHOR_OCEAN_DEFS
#include "/d/Krynn/std/boats/std_boat_defs.h"
#define KHALAKHOR_OCEAN_DEFS 1

#define MAP_HANDLER                "/d/Ansalon/std/map_map"

#define KHALAKHOR_SEA "/d/Khalakhor/ocean/"
#define ROOM          KHALAKHOR_SEA + "room/"
#define LIVING        KHALAKHOR_SEA + "living/"
#define ROOM_BASE     KHALAKHOR_SEA + "sea-base"
#define PLACER        KHALAKHOR_SEA + "sea-placer"
#define SEA_SECTOR    KHALAKHOR_SEA + "sea-sector"
#define SAILING_BASE  KHALAKHOR_SEA + "sailing"
#define MAP_DATA_FILE KHALAKHOR_SEA + "sea-map.txt"
#define SAILING_LIB   KHALAKHOR_SEA + "lib"
#define SAILING_PIER  KHALAKHOR_SEA + "pier"
#define SINK_ROOM     ROOM          + "sink-room"

#define DEFAULT_BLOCK_MSG           "You feel lost...\n"

#define MAP_SIZE_X 34
#define MAP_SIZE_Y 33

#define NEIGHBOURS (["west": "Calia", "north": "Kalad", \
                     "east": "Terel", "south": "Earthsea" ])

#ifndef TP
#define TP this_player()
#define TPQN this_player()->query_name()
#define TO this_object()
#define NF(x)    notify_fail(x)
#define NF0(x) { notify_fail(x); return 0; }
#endif

#define NORMAL_DIFFICULTY          0
#define TRICKY_DIFFICULTY          30
#define ROUGH_SEAS_DIFFICULTY      51
#define HIGH_SEAS_DIFFICULTY       76
#define IMPOSSIBLE_SEAS_DIFFICULTY 91

#define BAILE_ASHLAGH_LANDING "/d/Khalakhor/se_speir/lohrayn/ashlagh/room/pier-mariners"
#define BAILE_ASHLAGH_ENTRY "/d/Khalakhor/ocean/room/sea-30-29-b"

#define CADU_LANDING "/d/Khalakhor/inisi/roke/nyreese/cadu_pier-mariners"
#define CADU_ENTRY "/d/Khalakhor/ocean/room/sea-9-27-c"

#define CARISCA_LANDING "/d/Khalakhor/inisi/roke/carisca/pier-mariners"
#define CARISCA_ENTRY "/d/Khalakhor/ocean/room/sea-5-30-r"

#define DAENBRAIGH_LANDING "/d/Khalakhor/n_speir/daenbraigh/room/pier-0-15"
#define DAENBRAIGH_ENTRY "/d/Khalakhor/ocean/room/sea-16-8-n"

#define DRUID_LANDING "/d/Khalakhor/sw_speir/forest/room/landing-10-10"
#define DRUID_ENTRY "/d/Khalakhor/ocean/room/sea-14-14-w"

#define GALAITH_LANDING "/d/Khalakhor/inisi/galaith/pier/pier-mariners"
#define GALAITH_ENTRY "/d/Khalakhor/ocean/room/sea-3-13-g"

#define HAMMERHANDS_LANDING "/d/Khalakhor/se_speir/steppe/room/landing-26-13"
#define HAMMERHANDS_ENTRY "/d/Khalakhor/ocean/room/sea-26-12-e"

#define LUCKY_LANDING "/d/Khalakhor/inisi/leprechaun/room/pier-60-60"
#define LUCKY_ENTRY "/d/Khalakhor/ocean/room/sea-8-6-l"

#define PORTMACDUNN_LANDING "/d/Khalakhor/ship/macdunn/pier6"
#define PORTMACDUNN_ENTRY "/d/Khalakhor/ocean/room/sea-23-18-e"

#define SAMORGAN_LANDING "/d/Khalakhor/sw_speir/samorgan/pier/pie1306"
#define SAMORGAN_ENTRY "/d/Khalakhor/ocean/room/sea-14-21-w"

#define WASTELANDS_LANDING "/d/Khalakhor/n_speir/wastes/room/landing-30-2"
#define WASTELANDS_ENTRY "/d/Khalakhor/ocean/room/sea-22-1-n"

#define SPARKLE_CONNECTION "/d/Sparkle/area/sea/room/sparkle_sea-12-1-n.c"

#define KHALAKHOR_MAX_BOATS_IN_ROOM 30
#define SAILING_OPEN 1
// #define SAILING_SKILL 143020
#endif
