/*
 * Ship navigation utilities
 */

#ifndef _SHIP_NAVIGATION
#define _SHIP_NAVIGATION

#define BASE_DIRECTIONS_AND_OPPOSITES ([ \
    "west"      : "east",      \
    "southwest" : "northeast", \
    "south"     : "north",     \
    "southeast" : "northwest", \
    "east"      : "west",      \
    "northeast" : "southwest", \
    "north"     : "south",     \
    "northwest" : "southeast"  \
])

#define MAX_PEER_DISTANCE (8)

#define DIR_ESE ({"e", "se", "ne", "s", "n", "sw", "nw", "w"})
#define DIR_SSE ({"s", "se", "sw", "e", "w", "ne", "nw", "n"})
#define DIR_SE  ({"se", "s", "e", "ne", "sw", "w", "n", "nw"})
#define DIR_ENE ({"e", "ne", "se", "n", "s", "nw", "sw", "w"})
#define DIR_NNE ({"n", "ne", "nw", "e", "w", "se", "sw", "s"})
#define DIR_NE  ({"ne", "n", "e", "se", "nw", "s", "w", "sw"})
#define DIR_WSW ({"w", "sw", "nw", "s", "n", "se", "ne", "e"})
#define DIR_SSW ({"sw", "s", "w", "nw", "se", "e", "n", "ne"})
#define DIR_SW  ({"sw", "s", "w", "nw", "se", "e", "n", "ne"})
#define DIR_WNW ({"w", "nw", "sw", "n", "s", "ne", "se", "e"})
#define DIR_NNW ({"n", "nw", "ne", "w", "e", "sw", "se", "s"})
#define DIR_NW  ({"nw", "n", "w", "sw", "ne", "e", "s", "se"})
//                                      Wx,  Ex,  Nx,  Sx
#define CONTINENTS ([ \
  "Ansalon"          : ({ "Ansalon",   200, 430, 320, 495 }), \
  "Avenir"           : ({ "Avenir",    110, 140, 400, 495 }), \
  "Cadu"             : ({ "Khalakhor",  25,  80, 410, 470 }), \
  "Calia"            : ({ "Calia",     390, 490,  50, 120 }), \
  "Carisca"          : ({ "Khalakhor",  30,  40, 480, 490 }), \
  "Cirath"           : ({ "Cirath",    106, 180, 230, 290 }), \
  "Eil Galaith"      : ({ "Khalakhor",  90, 120,  90, 120 }), \
  "Eldoral"          : ({ "Calia",     430, 460,  20,  45 }), \
  "Emerald"          : ({ "Emerald",   210, 280,  70, 150 }), \
  "Faerun"           : ({ "Faerun",    455, 495, 360, 480 }), \
  "Golden Island"    : ({ "Sparkle",   240, 260, 180, 200 }), \
  "Gont"             : ({ "Gont",       60, 120, 300, 390 }), \
  "Isle of the Dead" : ({ "Avenir",    150, 160, 400, 415 }), \
  "Kalad"            : ({ "Kalad",      30, 105, 230, 290 }), \
  "Khalakhor"        : ({ "Khalakhor",  20, 110,  20,  80 }), \
  "Middle Earth"     : ({ "Gondor",    300, 480, 150, 310 }), \
  "Mithas"           : ({ "Ansalon",   430, 440, 400, 460 }), \
  "Raumdor"          : ({ "Raumdor",    10, 120, 140, 200 }), \
  "Roke"             : ({ "Gont",       40,  55, 330, 370 }), \
  "Sparkle"          : ({ "Sparkle",   215, 285, 225, 275 }), \
  "Sybarus"          : ({ "Avenir",    150, 180, 430, 495 }), \
  "Baile Ashlagh"    : ({ "Khalakhor",  25,  45, 100, 115 }), \
  "Terel"            : ({ "Terel",     135, 190,   5, 150 })  \
])

#endif
