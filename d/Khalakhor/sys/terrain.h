#ifndef _TERRAIN_KHAL_H_
#define _TERRAIN_KHAL_H_

#include "/sys/terrain.h"

// This file contains composites of the terrain types defined by
// the above file (in other words, these are shortcuts).

// Simple combination of two defines, out and inside, natural and artificial.
// Temperature is assumed to be TERRAIN_TEMPERATE.
#define TERRAIN_OUTNAT       (TERRAIN_OUTSIDE | TERRAIN_NATURAL)
// Inside is assumed.
#define TERRAIN_INNAT        (TERRAIN_NATURAL)
// Natural is assumed.
#define TERRAIN_OUTART       (TERRAIN_OUTSIDE)
// Bit-wise, the default is an inside, artificial room - and oddly enough, 
// with no shade!
#define TERRAIN_INART        0

// The useful underwater defines.
// Underwater lakes and pools, natural setting. Should be used in conjunction
// with temperature.
#define TERRAIN_WATERONUND   (TERRAIN_OUTNAT | TERRAIN_UNDERWATER | \
                              TERRAIN_WET)
// Inside and artificial under water - wells. Should use temperature, too.
#define TERRAIN_WATERIAUND   (TERRAIN_INART | TERRAIN_UNDERWATER | \
                              TERRAIN_WET)

// The combination of four basic defines.
// Add in freedom of movement, as this probably has most effect on specials.
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
                              TERRAIN_WET)

#define TERRAIN_SALTWATER    (TERRAIN_OPENWATER | TERRAIN_IMPURE)
#define TERRAIN_OCEAN        (TERRAIN_SALTWATER | TERRAIN_ROUGH | \
                              TERRAIN_LARGE)
#define TERRAIN_UNDERSEA     (TERRAIN_FREEWON | TERRAIN_LARGE | \
                              TERRAIN_IMPURE | TERRAIN_SHADOWS)
#define TERRAIN_SALINELAKE   (TERRAIN_SALTWATER | TERRAIN_LARGE)
#define TERRAIN_BAY          (TERRAIN_SALTWATER | TERRAIN_LARGE)

#define TERRAIN_FRESHWATER   (TERRAIN_OPENWATER)

#define TERRAIN_LAKE         (TERRAIN_FRESHWATER | TERRAIN_ROUGH | \
                              TERRAIN_LARGE)
#define TERRAIN_UNDERLAKE    (TERRAIN_FREEWON | TERRAIN_LARGE | \
                              TERRAIN_SHADOWS)
#define TERRAIN_POND         (TERRAIN_FRESHWATER)
#define TERRAIN_RIVER        (TERRAIN_FRESHWATER | TERRAIN_LARGE | \
                              TERRAIN_CURRENT | TERRAIN_ROUGH)
#define TERRAIN_STREAM       (TERRAIN_FRESHWATER | TERRAIN_CURRENT)
#define TERRAIN_WATERFALL    (TERRAIN_FRESHWATER | TERRAIN_CURRENT | \
                              TERRAIN_ROUGH)
#define TERRAIN_INWELL       (TERRAIN_CONFINART | TERRAIN_ONWATER | \
                              TERRAIN_SHADOWS)

// Land defines.
#define TERRAIN_WILDERNESS   (TERRAIN_OUTNAT)

#define TERRAIN_FLATLAND     (TERRAIN_WILDERNESS | TERRAIN_LARGE | \
                              TERRAIN_OPENSPACE)

#define TERRAIN_PLAIN        (TERRAIN_FLATLAND | TERRAIN_SOIL | \
                              TERRAIN_SMALL_PLANT)
#define TERRAIN_MOOR         (TERRAIN_PLAIN | TERRAIN_ROCK | \
                              TERRAIN_COOL)
#define TERRAIN_GLACIER      (TERRAIN_FLATLAND | TERRAIN_ROUGH | \
                              TERRAIN_FREEZING)
#define TERRAIN_TUNDRA       (TERRAIN_FLATLAND | TERRAIN_COLD | \
                              TERRAIN_SMALL_PLANT)
#define TERRAIN_DESERT       (TERRAIN_FLATLAND | TERRAIN_SAND | \
                              TERRAIN_ROUGH | TERRAIN_HOT)
#define TERRAIN_SCRUB        (TERRAIN_DESERT | TERRAIN_SMALL_PLANT)
#define TERRAIN_BADLAND      (TERRAIN_DESERT | TERRAIN_SMALL_PLANT | \
                              TERRAIN_ROCK | TERRAIN_SHADOWS)
#define TERRAIN_WASTELAND    (TERRAIN_DESERT | TERRAIN_ROCK)

#define TERRAIN_ROCKLAND     (TERRAIN_WILDERNESS | TERRAIN_ROUGH | \
                              TERRAIN_LARGE | TERRAIN_ROCK | TERRAIN_SHADOWS)
#define TERRAIN_MOUNTAIN     (TERRAIN_ROCKLAND | TERRAIN_STEEP | \
                              TERRAIN_COOL) 
#define TERRAIN_HILL         (TERRAIN_ROCKLAND | TERRAIN_SOIL | \
                              TERRAIN_SMALL_PLANT | TERRAIN_OPENSPACE)
#define TERRAIN_CLIFF        (TERRAIN_ROCKLAND | TERRAIN_STEEP)
#define TERRAIN_VOLCANO      (TERRAIN_ROCKLAND | TERRAIN_HOT | \
                              TERRAIN_STEEP)

#define TERRAIN_COASTLAND    (TERRAIN_WILDERNESS | TERRAIN_SMALL_PLANT | \
                              TERRAIN_OPENSPACE | TERRAIN_WET)
#define TERRAIN_LAKESHORE    (TERRAIN_COASTLAND | TERRAIN_ROCK)
#define TERRAIN_COAST        (TERRAIN_COASTLAND | TERRAIN_ROUGH | \
                              TERRAIN_ROCK | TERRAIN_IMPURE)
#define TERRAIN_RIVERBANK    (TERRAIN_COASTLAND | TERRAIN_SOIL | \
                              TERRAIN_SAND)
#define TERRAIN_SALTBEACH    (TERRAIN_COASTLAND | TERRAIN_IMPURE | \
                              TERRAIN_SAND)
#define TERRAIN_FRESHBEACH   (TERRAIN_COASTLAND | TERRAIN_SAND)

#define TERRAIN_WETLAND      (TERRAIN_WILDERNESS | TERRAIN_LARGE | \
                              TERRAIN_WET | TERRAIN_ROUGH | \
                              TERRAIN_SMALL_PLANT)
#define TERRAIN_SWAMP        (TERRAIN_WETLAND | TERRAIN_TALL_PLANT | \
                              TERRAIN_SOIL | TERRAIN_SHADOWS)
#define TERRAIN_MARSH        (TERRAIN_WETLAND | TERRAIN_OPENSPACE | \
                              TERRAIN_SOIL)
#define TERRAIN_BOG          (TERRAIN_WETLAND | TERRAIN_OPENSPACE)

#define TERRAIN_WOODS        (TERRAIN_WILDERNESS | TERRAIN_TALL_PLANT | \
                              TERRAIN_SOIL | TERRAIN_SMALL_PLANT)
#define TERRAIN_THICKET      (TERRAIN_WOODS | TERRAIN_ROUGH)
#define TERRAIN_BUSH         (TERRAIN_WOODS | TERRAIN_OPENSPACE)
#define TERRAIN_FOREST       (TERRAIN_WOODS | TERRAIN_ROUGH | \
                              TERRAIN_LARGE)
#define TERRAIN_JUNGLE       (TERRAIN_FOREST | TERRAIN_HOT)
#define TERRAIN_MIXEDWOOD    (TERRAIN_FOREST | TERRAIN_SHADOWS)
#define TERRAIN_CONIFEROUS   (TERRAIN_FOREST | TERRAIN_SHADOWS | \
                              TERRAIN_COOL)
#define TERRAIN_DECIDUOUS    (TERRAIN_FOREST | TERRAIN_SHADOWS)

//Underground defines.
#define TERRAIN_UGNAT        (TERRAIN_UNDERGROUND | TERRAIN_INNAT | \
                              TERRAIN_ROCK | TERRAIN_SHADOWS)
#define TERRAIN_NCAVETUNNEL  (TERRAIN_UGNAT | TERRAIN_ROUGH)
#define TERRAIN_NCAVE        (TERRAIN_UGNAT | TERRAIN_ROUGH | \
                              TERRAIN_OPENSPACE)
#define TERRAIN_NCAVELAKESH  (TERRAIN_NCAVE | TERRAIN_WET)
#define TERRAIN_NCAVEMAGMA   (TERRAIN_NCAVE | TERRAIN_HOT)
#define TERRAIN_UGART        (TERRAIN_UNDERGROUND | TERRAIN_INART | \
                              TERRAIN_SHADOWS)
#define TERRAIN_MINE         (TERRAIN_UGART | TERRAIN_ROCK | \
                              TERRAIN_ROUGH)
#define TERRAIN_ARTOPENING   (TERRAIN_UGART | TERRAIN_OPENSPACE)
#define TERRAIN_ARTOPENLAVA  (TERRAIN_ARTOPENING | TERRAIN_HOT)

// Some artificial defines.
#define TERRAIN_HALL         (TERRAIN_INART)
#define TERRAIN_ROAD         (TERRAIN_FREEOUTART | TERRAIN_SMALL_PLANT)
#define TERRAIN_BRIDGE       (TERRAIN_FREEOUTART)
#define TERRAIN_STREET       (TERRAIN_FREEOUTART | TERRAIN_CROWDED)
#define TERRAIN_OUTSTAIRS    (TERRAIN_FREEOUTART | TERRAIN_STEEP)
#define TERRAIN_FIELD        (TERRAIN_FREEOUTART | TERRAIN_SOIL | \
                              TERRAIN_SMALL_PLANT | TERRAIN_ROCK)
#define TERRAIN_GARDEN       (TERRAIN_FREEOUTART | TERRAIN_SOIL | \
                              TERRAIN_SMALL_PLANT)
#define TERRAIN_GRAVEYARD    (TERRAIN_FREEOUTART | TERRAIN_HASDEAD | \
                              TERRAIN_CLUTTER | TERRAIN_SOIL | \
                              TERRAIN_SMALL_PLANT)
#define TERRAIN_SHIPDECK     (TERRAIN_FREEOUTART | TERRAIN_ONVEHICLE)
#define TERRAIN_PATH         (TERRAIN_CONFOUTART | TERRAIN_ROUGH | \
                              TERRAIN_SMALL_PLANT)
#define TERRAIN_RUINS        (TERRAIN_CONFOUTART | TERRAIN_ROUGH | \
                              TERRAIN_ROCK | TERRAIN_CLUTTER | \
                              TERRAIN_SHADOWS)
#define TERRAIN_ALLEY        (TERRAIN_CONFOUTART | TERRAIN_SHADOWS)
#define TERRAIN_INSTAIRS     (TERRAIN_CONFOUTART | TERRAIN_STEEP)
#define TERRAIN_ROWBOAT      (TERRAIN_CONFOUTART | TERRAIN_ONVEHICLE)
#define TERRAIN_PIER         (TERRAIN_FREEOUTART)
#define TERRAIN_INRUINS      (TERRAIN_CONFINART | TERRAIN_ROUGH | \
                              TERRAIN_CLUTTER | TERRAIN_SHADOWS)
#define TERRAIN_TOMB         (TERRAIN_CONFINART | TERRAIN_HASDEAD | \
                              TERRAIN_SHADOWS)
#define TERRAIN_HOUSE        (TERRAIN_CONFINART | TERRAIN_CLUTTER | \
                              TERRAIN_RESIDENCE)
#define TERRAIN_INSHIP       (TERRAIN_CONFINART | TERRAIN_ONVEHICLE | \
                              TERRAIN_CLUTTER | TERRAIN_SHADOWS)
#define TERRAIN_SEWER        (TERRAIN_CONFINART | TERRAIN_SHADOWS | \
                              TERRAIN_WET | TERRAIN_ROUGH | \
                              TERRAIN_CLUTTER)

#endif

