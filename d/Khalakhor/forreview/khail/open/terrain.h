
// What defines.
#define TERRAIN_OUTSIDE    536870912 // Opposite is inside.

// Origin defines.
#define TERRAIN_NATURAL    268435456 // Opposite is artificial.

// Medium defines.
#define TERRAIN_UNDERWATER 134217728 // If not water medium, air medium.

// Freedom of movement defines.
#define TERRAIN_OPENSPACE   67108864 // If not open, confined.

// Where defines.
#define TERRAIN_INAIR       33554432 // In case someone can fly...
#define TERRAIN_ONWATER     16777216 // On the water, not on ground.
#define TERRAIN_UNDERGROUND  8388608 // If not underground, aboveground.

// Water defines.
#define TERRAIN_WATERFLOW    4194304 // If not flowing, stationary.

// Terrain has defines.
#define TERRAIN_SALTYWTR     2097152 // If no saltwater, no water.
#define TERRAIN_FRESHWTR     1048576 // If no freshwater, no water.
#define TERRAIN_TREE          524288 // Or else no trees.
#define TERRAIN_WET           262144 // If not wet, dry.
#define TERRAIN_ROCK          131072 // Either that, or no rocks.
#define TERRAIN_SAND           65536 // If not sandy, no sand.
#define TERRAIN_SOIL           32768 // Or no soil at all.
#define TERRAIN_HUMID          16384 // If not humid, dry air.
#define TERRAIN_LAVA            8192 // Why not?
#define TERRAIN_ICE             4096 // If not, no ice.
#define TERRAIN_CLUTTER         2048 // If not cluttered, clean.
#define TERRAIN_PLANT           1024 // Herbs and shrubs, or none.
#define TERRAIN_MUD         (TERRAIN_WET | TERRAIN_SOIL)

// Terrain size defines.
#define TERRAIN_LARGE            512 // If not large, small.

//Terrain topography defines.
#define TERRAIN_ROUGH            256 // If not rough, gentle.
#define TERRAIN_STEEP            128 // If not steep, flat.

// Consistency defines.
#define TERRAIN_SPLOTCHY          64 // If not splotchy or random, uniform.

// Population defines.
#define TERRAIN_CROWDED           32 // Either that, or no one there.

// Light level defines.
#define TERRAIN_SHADY             16 // Or else not shady.

// Domicile defines.
#define TERRAIN_RESIDENCE          8 // Or else not a habitation.

// Dead defines.
#define TERRAIN_HASDEAD            4 // Or else no deads.

// Boat defines.
#define TERRAIN_ONBOAT 2

// Simple combination of two defines, out and inside, natural and artificial.
#define TERRAIN_OUTNAT       (TERRAIN_OUTSIDE | TERRAIN_NATURAL)
#define TERRAIN_INNAT        (TERRAIN_NATURAL)
#define TERRAIN_OUTART       (TERRAIN_OUTSIDE)
#define TERRAIN_INART        (0)

// The useful underwater defines.
#define TERRAIN_WATEROUTNUND (TERRAIN_OUTNAT | TERRAIN_UNDERWATER | \
                              TERRAIN_WET | TERRAIN_HUMID)
#define TERRAIN_WATERINAUND  (TERRAIN_INART | TERRAIN_UNDERWATER | \
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
#define TERRAIN_FREEWON      (TERRAIN_WATEROUTNUND | TERRAIN_OPENSPACE)  
#define TERRAIN_CONFWIA      (TERRAIN_WATERINAUND)

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
#define TERRAIN_UNDERPOND    (TERRAIN_FREEWON | TERRAIN_FRESHWTR | \
                              TERRAIN_SHADY)
#define TERRAIN_RIVER        (TERRAIN_FRESHWATER | TERRAIN_LARGE | \
                              TERRAIN_WATERFLOW | TERRAIN_ROUGH)
#define TERRAIN_UNDERRIVER   (TERRAIN_FREEWON | TERRAIN_LARGE | \
                              TERRAIN_WATERFLOW | TERRAIN_ROUGH | \
                              TERRAIN_FRESHWTR | TERRAIN_SHADY)
#define TERRAIN_STREAM       (TERRAIN_FRESHWATER | TERRAIN_WATERFLOW)
#define TERRAIN_WATERFALL    (TERRAIN_FRESHWATER | TERRAIN_WATERFLOW | \
                              TERRAIN_ROUGH)
#define TERRAIN_UNDWATFALL   (TERRAIN_FREEWON | TERRAIN_WATERFLOW | \
                              TERRAIN_ROUGH | TERRAIN_FRESHWTR | \
                              TERRAIN_SHADY)
#define TERRAIN_INWELL       (TERRAIN_CONFINART | TERRAIN_ONWATER | \
                              TERRAIN_FRESHWTR | TERRAIN_SHADY)
#define TERRAIN_UNDERWELL    (TERRAIN_CONFWIA | TERRAIN_FRESHWTR | \
                              TERRAIN_SHADY)

// Land defines.
#define TERRAIN_WILDERNESS   (TERRAIN_OUTNAT)

#define TERRAIN_FLATLAND     (TERRAIN_WILDERNESS | TERRAIN_LARGE | \
                              TERRAIN_OPENSPACE)
#define TERRAIN_PLAIN        (TERRAIN_FLATLAND | TERRAIN_SOIL | \
                              TERRAIN_PLANT)
#define TERRAIN_MOOR         (TERRAIN_FLATLAND | TERRAIN_SOIL | \
                              TERRAIN_PLANT | TERRAIN_HUMID | \
                              TERRAIN_ROCK)
#define TERRAIN_GLACIER      (TERRAIN_FLATLAND | TERRAIN_ICE | \
                              TERRAIN_ROUGH)
#define TERRAIN_DESERT       (TERRAIN_FLATLAND | TERRAIN_SAND | \
                              TERRAIN_ROUGH)
#define TERRAIN_BADLAND      (TERRAIN_FLATLAND | TERRAIN_SAND | \
                              TERRAIN_PLANT | TERRAIN_ROUGH | \
                              TERRAIN_SPLOTCHY | TERRAIN_ROCK | \
                              TERRAIN_SHADY)
#define TERRAIN_TUNDRA       (TERRAIN_FLATLAND | TERRAIN_ICE | \
                              TERRAIN_PLANT)

#define TERRAIN_ROCKLAND     (TERRAIN_WILDERNESS | TERRAIN_ROUGH | \
                              TERRAIN_LARGE | TERRAIN_ROCK | TERRAIN_SHADY)
#define TERRAIN_MOUNTAIN     (TERRAIN_ROCKLAND | TERRAIN_STEEP)
#define TERRAIN_HILL         (TERRAIN_ROCKLAND | TERRAIN_SOIL | \
                              TERRAIN_PLANT | TERRAIN_OPENSPACE)
#define TERRAIN_CLIFF        (TERRAIN_ROCKLAND | TERRAIN_STEEP | \
                              TERRAIN_SPLOTCHY)
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
                              TERRAIN_ROUGH | TERRAIN_SPLOTCHY | \
                              TERRAIN_PLANT)
#define TERRAIN_SWAMP        (TERRAIN_WETLAND | TERRAIN_TREE | \
                              TERRAIN_SOIL | TERRAIN_SHADY | \
                              TERRAIN_FRESHWTR)
#define TERRAIN_MARSH        (TERRAIN_WETLAND | TERRAIN_OPENSPACE | \
                              TERRAIN_SOIL | TERRAIN_FRESHWTR)
#define TERRAIN_BOG          (TERRAIN_WETLAND | TERRAIN_OPENSPACE | \
                              TERRAIN_FRESHWTR)

#define TERRAIN_FOREST       (TERRAIN_WILDERNESS | TERRAIN_TREE | \
                              TERRAIN_SOIL | TERRAIN_PLANT | \
                              TERRAIN_SHADY)
#define TERRAIN_THICKET      (TERRAIN_FOREST | TERRAIN_SPLOTCHY | \
                              TERRAIN_ROUGH)
#define TERRAIN_BUSH         (TERRAIN_FOREST | TERRAIN_OPENSPACE)
#define TERRAIN_TRUEFOREST   (TERRAIN_FOREST | TERRAIN_ROUGH | \
                              TERRAIN_LARGE)
#define TERRAIN_JUNGLE       (TERRAIN_FOREST | TERRAIN_ROUGH | \
                              TERRAIN_LARGE | TERRAIN_HUMID)

//Underground defines.
#define TERRAIN_UGNATURAL    (TERRAIN_UNDERGROUND | TERRAIN_INNAT \
                              TERRAIN_ROCK | TERRAIN_SHADY)
#define TERRAIN_UGARTIFICIAL (TERRAIN_UNDERGROUND | TERRAIN_INART | \
                              TERRAIN_SHADY)

#define TERRAIN_NATCVTUNNEL  (TERRAIN_UGNATURAL | TERRAIN_ROUGH)
#define TERRAIN_NATCV        (TERRAIN_UGNATURAL | TERRAIN_ROUGH | \
                              TERRAIN_OPENSPACE)
#define TERRAIN_NATCVLAKESH  (TERRAIN_NATCAVE | TERRAIN_FRESHWTR | \
                              TERRAIN_WET | TERRAIN_HUMID)
#define TERRAIN_NATCVMAGMA   (TERRAIN_NATCAVE | TERRAIN_LAVA)

#define TERRAIN_ARTCVTUNNEL  (TERRAIN_UGARTIFICIAL)
#define TERRAIN_ARTOPENING   (TERRAIN_UGARTIFICIAL | TERRAIN_OPENSPACE)
#define TERRAIN_MINE         (TERRAIN_UGARTIFICIAL | TERRAIN_ROCK | \
                              TERRAIN_ROUGH)
#define TERRAIN_ARTOPENLAVA  (TERRAIN_ARTOPENING | TERRAIN_LAVA)

// Some artificial defines.
#define TERRAIN_OPENDOMESTIC (TERRAIN_FREEOUTART)
#define TERRAIN_CONFDOMESTIC (TERRAIN_CONFOUTART)

#define TERRAIN_ROAD         (TERRAIN_OPENDOMESTIC | TERRAIN_PLANT)
#define TERRAIN_BRIDGE       (TERRAIN_OPENDOMESTIC)
#define TERRAIN_PATH         (TERRAIN_CONFDOMESTIC | TERRAIN_ROUGH | \
                              TERRAIN_PLANT)
#define TERRAIN_RUINS        (TERRAIN_CONFDOMESTIC | TERRAIN_ROUGH | \
                              TERRAIN_ROCK | TERRAIN_CLUTTER | \
                              TERRAIN_SHADY)
#define TERRAIN_STREET       (TERRAIN_OPENDOMESTIC | TERRAIN_CROWDED)
#define TERRAIN_ALLEY        (TERRAIN_CONFDOMESTIC | TERRAIN_SHADY)
#define TERRAIN_OUTSTAIRS    (TERRAIN_OPENDOMESTIC | TERRAIN_STEEP)
#define TERRAIN_INSTAIRS     (TERRAIN_CONFDOMESTIC | TERRAIN_STEEP)
#define TERRAIN_INRUINS      (TERRAIN_CONFINART | TERRAIN_ROUGH | \
                              TERRAIN_CLUTTER | TERRAIN_SHADY)
#define TERRAIN_FIELD        (TERRAIN_OPENDOMESTIC | TERRAIN_SOIL | \
                              TERRAIN_PLANT | TERRAIN_ROCK)
#define TERRAIN_GARDEN       (TERRAIN_OPENDOMESTIC | TERRAIN_SOIL | \
                              TERRAIN_PLANT)
#define TERRAIN_GRAVEYARD    (TERRAIN_OPENDOMESTIC | TERRAIN_HASDEAD | \
                              TERRAIN_CLUTTER | TERRAIN_SOIL)
#define TERRAIN_TOMB         (TERRAIN_CONFINART | TERRAIN_HASDEAD | \
                              TERRAIN_SHADY)
#define TERRAIN_HOUSE        (TERRAIN_CONFINART | TERRAIN_CLUTTER | \
                              TERRAIN_RESIDENCE)
#define TERRAIN_SHIPDECK     (TERRAIN_OPENDOMESTIC | TERRAIN_ONBOAT | \
                              TERRAIN_HUMID)
#define TERRAIN_ROWBOAT      (TERRAIN_CONFDOMESTIC | TERRAIN_ONBOAT | \
                              TERRAIN_HUMID)
#define TERRAIN_INSHIP       (TERRAIN_CONFINART | TERRAIN_ONBOAT | \
                              TERRAIN_CLUTTER | TERRAIN_SHADY | \
                              TERRAIN_HUMID)
#define TERRAIN_PIER         (TERRAIN_OPENDOMESTIC | TERRAIN_HUMID)
#define TERRAIN_HALL         (0)
#define TERRAIN_SEWER        (TERRAIN_CONFINART | TERRAIN_SEWER | \
                              TERRAIN_WET | TERRAIN_HUMID | \
                              TERRAIN_CLUTTER | TERRAIN_ROUGH)


