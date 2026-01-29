#ifndef _TERRAIN_H_
#define _TERRAIN_H_

// PLEASE NOTE - THIS FILE IS OBSOLETE
// USE terrain.h for composite defines of mudlib terrain types!

// Put the prop in the larger include file.
#define ROOM_I_TERRAIN_TYPE   "_room_i_terrain_type"

// What defines.
#define TERRAIN_OUTSIDE    536870912

// Origin defines.
#define TERRAIN_NATURAL    268435456

// Medium defines.
#define TERRAIN_UNDERWATER 134217728

// Freedom of movement defines.
#define TERRAIN_OPENSPACE   67108864

// Where defines.
#define TERRAIN_INAIR       33554432
#define TERRAIN_ONWATER     16777216
#define TERRAIN_UNDERGROUND  8388608

// Water defines.
#define TERRAIN_WATERFLOW    4194304

// Terrain has defines.
#define TERRAIN_SALTYWTR     2097152
#define TERRAIN_FRESHWTR     1048576
#define TERRAIN_TREE          524288
#define TERRAIN_WET           262144
#define TERRAIN_ROCK          131072
#define TERRAIN_SAND           65536
#define TERRAIN_SOIL           32768
#define TERRAIN_HUMID          16384
#define TERRAIN_LAVA            8192
#define TERRAIN_ICE             4096
#define TERRAIN_CLUTTER         2048
#define TERRAIN_PLANT           1024
#define TERRAIN_MUD         (TERRAIN_WET | TERRAIN_SOIL)

// Terrain size defines.
#define TERRAIN_LARGE            512

//Terrain topography defines.
#define TERRAIN_ROUGH            256
#define TERRAIN_STEEP            128

// Population defines.
#define TERRAIN_CROWDED           64

// Light level defines.
#define TERRAIN_SHADY             32
#define TERRAIN_SUNLIGHT          16

// Domicile defines.
#define TERRAIN_RESIDENCE          8

// Dead defines.
#define TERRAIN_HASDEAD            4

// Boat defines.
#define TERRAIN_ONBOAT             2


// Simple combination of two defines, out and inside, natural and artificial.
#define TERRAIN_OUTNAT       (TERRAIN_OUTSIDE | TERRAIN_NATURAL)
#define TERRAIN_INNAT        (TERRAIN_NATURAL)
#define TERRAIN_OUTART       (TERRAIN_OUTSIDE)
#define TERRAIN_INART        1

// The useful underwater defines.
#define TERRAIN_WATERONUND   (TERRAIN_OUTNAT | TERRAIN_UNDERWATER | \
                              TERRAIN_WET | TERRAIN_HUMID)
#define TERRAIN_WATERIAUND   (TERRAIN_INART | TERRAIN_UNDERWATER | \
                              TERRAIN_WET | TERRAIN_HUMID)

// The combination of four basic defines.
#define TERRAIN_FREEOUTNAT   (TERRAIN_OUTNAT | TERRAIN_OPENSPACE)
#define TERRAIN_CONFOUTNAT   (TERRAIN_OUTNAT)
#define TERRAIN_FREEINNAT    (TERRAIN_INNAT | TERRAIN_OPENSPACE)
#define TERRAIN_CONFINNAT    (TERRAIN_INNAT)
#define TERRAIN_FREEOUTART   (TERRAIN_OUTART | TERRAIN_OPENSPACE)
#define TERRAIN_CONFOUTART   (TERRAIN_OUTART)
#define TERRAIN_FREEINART    (TERRAIN_INART | TERRAIN_OPENSPACE)
#define TERRAIN_CONFINART    (TERRAIN_INART)
#define TERRAIN_FREEWON      (TERRAIN_WATERONUND | TERRAIN_OPENSPACE)  
#define TERRAIN_CONFWIA      (TERRAIN_WATERIAUND)

// Air defines.
#define TERRAIN_SKY          (TERRAIN_INAIR | TERRAIN_FREEOUTNAT)
#define TERRAIN_FLIGHTSPACE  (TERRAIN_INAIR | TERRAIN_FREEINNAT)
#define TERRAIN_FLIGHTINSIDE (TERRAIN_INAIR | TERRAIN_FREEINART)

// Water defines.
#define TERRAIN_OPENWATER    (TERRAIN_FREEOUTNAT | TERRAIN_ONWATER | \
                              TERRAIN_WET | TERRAIN_HUMID)

#define TERRAIN_SALTWATER    (TERRAIN_OPENWATER | TERRAIN_SALTYWTR)
#define TERRAIN_OCEAN        (TERRAIN_SALTWATER | TERRAIN_ROUGH | \
                              TERRAIN_LARGE)
#define TERRAIN_UNDERSEA     (TERRAIN_FREEWON | TERRAIN_LARGE | \
                              TERRAIN_SALTYWTR | TERRAIN_SHADY)
#define TERRAIN_SALINELAKE   (TERRAIN_SALTWATER | TERRAIN_LARGE)
#define TERRAIN_BAY          (TERRAIN_SALTWATER | TERRAIN_LARGE)

#define TERRAIN_FRESHWATER   (TERRAIN_OPENWATER | TERRAIN_FRESHWTR)

#define TERRAIN_LAKE         (TERRAIN_FRESHWATER | TERRAIN_ROUGH | \
                              TERRAIN_LARGE)
#define TERRAIN_UNDERLAKE    (TERRAIN_FREEWON | TERRAIN_LARGE | \
                              TERRAIN_FRESHWTR | TERRAIN_SHADY)
#define TERRAIN_POND         (TERRAIN_FRESHWATER)
#define TERRAIN_RIVER        (TERRAIN_FRESHWATER | TERRAIN_LARGE | \
                              TERRAIN_WATERFLOW | TERRAIN_ROUGH)
#define TERRAIN_STREAM       (TERRAIN_FRESHWATER | TERRAIN_WATERFLOW)
#define TERRAIN_WATERFALL    (TERRAIN_FRESHWATER | TERRAIN_WATERFLOW | \
                              TERRAIN_ROUGH)
#define TERRAIN_INWELL       (TERRAIN_CONFINART | TERRAIN_ONWATER | \
                              TERRAIN_FRESHWTR | TERRAIN_SHADY)

// Land defines.
#define TERRAIN_WILDERNESS   (TERRAIN_OUTNAT)

#define TERRAIN_FLATLAND     (TERRAIN_WILDERNESS | TERRAIN_LARGE | \
                              TERRAIN_OPENSPACE)
#define TERRAIN_PLAIN        (TERRAIN_FLATLAND | TERRAIN_SOIL | \
                              TERRAIN_PLANT)
#define TERRAIN_MOOR         (TERRAIN_PLAIN | TERRAIN_HUMID | \
                              TERRAIN_ROCK)
#define TERRAIN_GLACIER      (TERRAIN_FLATLAND | TERRAIN_ICE | \
                              TERRAIN_ROUGH)
#define TERRAIN_TUNDRA       (TERRAIN_FLATLAND | TERRAIN_ICE | \
                              TERRAIN_PLANT)
#define TERRAIN_DESERT       (TERRAIN_FLATLAND | TERRAIN_SAND | \
                              TERRAIN_ROUGH)
#define TERRAIN_SCRUB        (TERRAIN_DESERT | TERRAIN_PLANT)
#define TERRAIN_BADLAND      (TERRAIN_DESERT | TERRAIN_PLANT | \
                              TERRAIN_ROCK | TERRAIN_SHADY)
#define TERRAIN_WASTELAND    (TERRAIN_DESERT | TERRAIN_ROCK)

#define TERRAIN_ROCKLAND     (TERRAIN_WILDERNESS | TERRAIN_ROUGH | \
                              TERRAIN_LARGE | TERRAIN_ROCK | TERRAIN_SHADY)
#define TERRAIN_MOUNTAIN     (TERRAIN_ROCKLAND | TERRAIN_STEEP | \
                              TERRAIN_SUNLIGHT) 
#define TERRAIN_HILL         (TERRAIN_ROCKLAND | TERRAIN_SOIL | \
                              TERRAIN_PLANT | TERRAIN_OPENSPACE)
#define TERRAIN_CLIFF        (TERRAIN_ROCKLAND | TERRAIN_STEEP)
#define TERRAIN_VOLCANO      (TERRAIN_ROCKLAND | TERRAIN_LAVA | \
                              TERRAIN_STEEP)

#define TERRAIN_COASTLAND    (TERRAIN_WILDERNESS | TERRAIN_PLANT | \
                              TERRAIN_OPENSPACE | TERRAIN_WET | \
                              TERRAIN_HUMID)
#define TERRAIN_LAKESHORE    (TERRAIN_COASTLAND | TERRAIN_FRESHWTR | \
                              TERRAIN_ROCK)
#define TERRAIN_COAST        (TERRAIN_COASTLAND | TERRAIN_SALTYWTR | \
                              TERRAIN_ROCK | TERRAIN_ROUGH)
#define TERRAIN_RIVERBANK    (TERRAIN_COASTLAND | TERRAIN_FRESHWTR | \
                              TERRAIN_SOIL | TERRAIN_SAND)
#define TERRAIN_SALTBEACH    (TERRAIN_COASTLAND | TERRAIN_SALTYWTR | \
                              TERRAIN_SAND)
#define TERRAIN_FRESHBEACH   (TERRAIN_COASTLAND | TERRAIN_FRESHWTR | \
                              TERRAIN_SAND)

#define TERRAIN_WETLAND      (TERRAIN_WILDERNESS | TERRAIN_LARGE | \
                              TERRAIN_WET | TERRAIN_HUMID | \
                              TERRAIN_ROUGH | TERRAIN_PLANT)
#define TERRAIN_SWAMP        (TERRAIN_WETLAND | TERRAIN_TREE | \
                              TERRAIN_SOIL | TERRAIN_SHADY | \
                              TERRAIN_FRESHWTR)
#define TERRAIN_MARSH        (TERRAIN_WETLAND | TERRAIN_OPENSPACE | \
                              TERRAIN_SOIL | TERRAIN_FRESHWTR)
#define TERRAIN_BOG          (TERRAIN_WETLAND | TERRAIN_OPENSPACE | \
                              TERRAIN_FRESHWTR)

#define TERRAIN_WOODS        (TERRAIN_WILDERNESS | TERRAIN_TREE | \
                              TERRAIN_SOIL | TERRAIN_PLANT)
#define TERRAIN_THICKET      (TERRAIN_WOODS | TERRAIN_ROUGH)
#define TERRAIN_BUSH         (TERRAIN_WOODS | TERRAIN_OPENSPACE)
#define TERRAIN_FOREST       (TERRAIN_WOODS | TERRAIN_ROUGH | \
                              TERRAIN_LARGE)
#define TERRAIN_JUNGLE       (TERRAIN_FOREST | TERRAIN_HUMID)
#define TERRAIN_MIXEDWOOD    (TERRAIN_FOREST | TERRAIN_SHADY | \
                              TERRAIN_SUNLIGHT)
#define TERRAIN_CONIFEROUS   (TERRAIN_FOREST | TERRAIN_SHADY)
#define TERRAIN_DECIDUOUS    (TERRAIN_FOREST | TERRAIN_SUNLIGHT)

//Underground defines.
#define TERRAIN_UGNAT        (TERRAIN_UNDERGROUND | TERRAIN_INNAT | \
                              TERRAIN_ROCK | TERRAIN_SHADY)
#define TERRAIN_NCAVETUNNEL  (TERRAIN_UGNAT | TERRAIN_ROUGH)
#define TERRAIN_NCAVE        (TERRAIN_UGNAT | TERRAIN_ROUGH | \
                              TERRAIN_OPENSPACE)
#define TERRAIN_NCAVELAKESH  (TERRAIN_NCAVE | TERRAIN_FRESHWTR | \
                              TERRAIN_WET | TERRAIN_HUMID)
#define TERRAIN_NCAVEMAGMA   (TERRAIN_NCAVE | TERRAIN_LAVA)
#define TERRAIN_UGART        (TERRAIN_UNDERGROUND | TERRAIN_INART | \
                              TERRAIN_SHADY)
#define TERRAIN_MINE         (TERRAIN_UGART | TERRAIN_ROCK | \
                              TERRAIN_ROUGH)
#define TERRAIN_ARTOPENING   (TERRAIN_UGART | TERRAIN_OPENSPACE)
#define TERRAIN_ARTOPENLAVA  (TERRAIN_ARTOPENING | TERRAIN_LAVA)

// Some artificial defines.
#define TERRAIN_HALL         (TERRAIN_INART)
#define TERRAIN_ROAD         (TERRAIN_FREEOUTART | TERRAIN_PLANT)
#define TERRAIN_BRIDGE       (TERRAIN_FREEOUTART | TERRAIN_HUMID)
#define TERRAIN_STREET       (TERRAIN_FREEOUTART | TERRAIN_CROWDED)
#define TERRAIN_OUTSTAIRS    (TERRAIN_FREEOUTART | TERRAIN_STEEP)
#define TERRAIN_FIELD        (TERRAIN_FREEOUTART | TERRAIN_SOIL | \
                              TERRAIN_PLANT | TERRAIN_ROCK)
#define TERRAIN_GARDEN       (TERRAIN_FREEOUTART | TERRAIN_SOIL | \
                              TERRAIN_PLANT)
#define TERRAIN_GRAVEYARD    (TERRAIN_FREEOUTART | TERRAIN_HASDEAD | \
                              TERRAIN_CLUTTER | TERRAIN_SOIL | \
                              TERRAIN_PLANT)
#define TERRAIN_SHIPDECK     (TERRAIN_FREEOUTART | TERRAIN_ONBOAT | \
                              TERRAIN_HUMID)
#define TERRAIN_PATH         (TERRAIN_CONFOUTART | TERRAIN_ROUGH | \
                              TERRAIN_PLANT)
#define TERRAIN_RUINS        (TERRAIN_CONFOUTART | TERRAIN_ROUGH | \
                              TERRAIN_ROCK | TERRAIN_CLUTTER | \
                              TERRAIN_SHADY)
#define TERRAIN_ALLEY        (TERRAIN_CONFOUTART | TERRAIN_SHADY)
#define TERRAIN_INSTAIRS     (TERRAIN_CONFOUTART | TERRAIN_STEEP)
#define TERRAIN_ROWBOAT      (TERRAIN_CONFOUTART | TERRAIN_ONBOAT | \
                              TERRAIN_HUMID)
#define TERRAIN_PIER         (TERRAIN_FREEOUTART | TERRAIN_HUMID)
#define TERRAIN_INRUINS      (TERRAIN_CONFINART | TERRAIN_ROUGH | \
                              TERRAIN_CLUTTER | TERRAIN_SHADY)
#define TERRAIN_TOMB         (TERRAIN_CONFINART | TERRAIN_HASDEAD | \
                              TERRAIN_SHADY)
#define TERRAIN_HOUSE        (TERRAIN_CONFINART | TERRAIN_CLUTTER | \
                              TERRAIN_RESIDENCE)
#define TERRAIN_INSHIP       (TERRAIN_CONFINART | TERRAIN_ONBOAT | \
                              TERRAIN_CLUTTER | TERRAIN_SHADY | \
                              TERRAIN_HUMID)
#define TERRAIN_SEWER        (TERRAIN_CONFINART | TERRAIN_SHADY | \
                              TERRAIN_WET | TERRAIN_HUMID | \
                              TERRAIN_CLUTTER | TERRAIN_ROUGH)

#endif

