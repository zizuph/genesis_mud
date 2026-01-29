/*
   /d/Kalad/sys/areas.h
   
   Defines for ids of areas and districts in Kalad.
   Each area has a unique id, each district in an area
   must have a unique id too. Areas and districts for
   each area start at 1.
   
   Fysix@Genesis, Nov 1997
 */
#ifndef _KALAD_AREAS_DEF
#define _KALAD_AREAS_DEF

// The Kabal area with its districts
#define AREA_KABAL         1
#define DISTRICT_CARAVAN   1
#define DISTRICT_CENTRAL   2
#define DISTRICT_MARKET    3
#define DISTRICT_NOBLE     4
#define DISTRICT_PORT      5
#define DISTRICT_SEWERS    6
#define DISTRICT_TRADE     7

// query_in_kabal call kept for backwards compatibility
#define IN_CITY(x)         ((x)->query_in_kabal() || \
   (x)->query_area() == AREA_KABAL)

// The waste area
#define AREA_WASTE         2

// Array entries must be exactly according
// to the defines above! Areas without district
// must have a ({ 0 }) entry in the district_names array.
#define AREA_NAMES         ({0, "Kabal", "Waste"})
#define DISTRICT_NAMES     ({\
   ({0}),\
   ({0, "Caravan", "Central", "Market", "Noble", "Port",\
      "Sewers", "Central"}),\
   ({0}),\
   })

#endif
