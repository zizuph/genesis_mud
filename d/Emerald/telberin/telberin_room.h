/*
 * /d/Emerald/telberin/telberin_room.h
 *
 * Copyright (C) February 2000, by Cooper Sherry (Gorboth)
 *
 * base defs for telberin
 */

#ifndef _TELBERIN_DEFS
#define _TELBERIN_DEFS

/* room types */
#define TYPE_STREET     1
#define TYPE_DOCKS      2
#define TYPE_POOR       3
#define TYPE_SQUARE     4


/* street names
 * using #define's removes the little inconsistencies:
 * "was it admiral street or admiral way"?  "shipwright street"
 * or "shipwright's street"? etc etc. of course, you can
 * still wonder about STREET_SHIPWRIGHT vs STREET_SHIPWRIGHTS,
 * but the driver will let you know if you get it wrong :-)
 */
#define STREET_BEACON           "Beacon Street"
#define STREET_BELFALAS         "Belfalas Way"
#define STREET_MARKET           "Market Street"
#define STREET_ADMIRAL          "Admiral Street"
#define STREET_SHIPWRIGHT       "Shipwright Street"
#define STREET_SWAN           "Swan Street"
#define STREET_PEDDLERS         "Peddlers Lane"


/* similarly, using defines avoids mixtures of "north" 
 * and "northern", etc
 */
#define PART_NORTH              "northern"
#define PART_EAST               "eastern"
#define PART_WEST               "western"
#define PART_SOUTH              "southern"

/* various npc files */
#define CITIZEN_FILE    (PELAR_DIR + "npc/citizen")
#define THIEF_FILE      (PELAR_DIR + "npc/yngthief")
#define SAILOR_FILE     (PELAR_DIR + "npc/swashb")
#define RUFFIAN_FILE    (PELAR_DIR + "npc/ruffian")

#endif /* _TELBERIN_DEFS */
