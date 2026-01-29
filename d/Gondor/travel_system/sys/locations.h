/*
 * Every interesting room in Middle Earth should be 
 * identified by an integer.
 *
 * Definitions:
 * Division : Middle Earth has been divided into a number
 *            of "major areas", roughly shown in
 *            /d/Cherek/GAME/cherek_div.gif. These
 *            divisions are north, west, east, south,
 *            n_island and s_island.
 * Area :     An area is a number of rooms with a
 *            a common theme. They're often located in
 *            the same directory on disk, and comprise
 *            something like a city, a forest, a road
 *            between two cities, etc.
 * Subarea :  A subarea is a part of an areaa. It
 *            could be a building, the city park, the
 *            western part of the road or something
 *            similar.
 * Room :     A room is an actual room within the
 *            location that would be interesting to
 *            an npc.
 *
 * Bits allocated to Divisions and Areas should be
 * defined in /d/Cherek/GAME/sys/loc_areas.h, which
 * is automatically included from this file.
 *
 * Bits allocated to Subareas and Rooms in an area
 * should be defined in <area-path>/locations.h, for
 * use by other areas.
 *
 * BLAH!! This should be changed.
 *
 * Every room that an npc could be assumed to travel
 * through should define the function:
 *
 * public mixed
 * query_direction(int location)
 *
 * This should return a string with the command to
 * be used to move closer to the requested location.
 * If the room is the location requested it should
 * return the special value LOCATION_REACHED, and
 * if the location is unreachable it should return
 * 0.
 */

#ifndef ARDA_LOCATIONS_DEFS

// First 8 bits devoted to divisions of the domain. (1 << 31) .. (1 << 24)
#define DIVISION_MASK             (0xFF << 24)
// Bits 9-16 bits devoted to areas within the division. (1 << 23) .. (1 << 16)
#define AREA_MASK                 (0xFF << 16)
// Bits 17-24 bits devoted to locations within the area. (1 << 15) .. (1 << 8)
#define SUBAREA_MASK              (0xFF << 8)
// Last 8 bits devoted to rooms within the location. (1 << 7) .. 1
#define ROOM_MASK                 (0xFF)

#define LOCATION_REACHED          ("_okay_we're_friggin'_there_already_")

/*
 * DIV_PART(), AREA_PART(), SUBAREA_PART(), ROOM_PART()
 *
 * These all take an int as their argument.
 */ 
#define DIVISION_PART(xxx)        (xxx & DIVISION_MASK)
#define AREA_PART(xxx)            (xxx & AREA_MASK)
#define SUBAREA_PART(xxx)         (xxx & SUBAREA_MASK)
#define ROOM_PART(xxx)            (xxx & ROOM_MASK)

#define DIRECTION_DEFAULT         0xFFFFFFFF
#define DIRECTION_OTHER_DIVISIONS DIVISION_MASK
#define DIRECTION_OTHER_AREAS     AREA_MASK
#define DIRECTION_OTHER_SUBAREAS  SUBAREA_MASK
#define DIRECTION_OTHER_ROOMS     ROOM_MASK

#define LOCATION_NOWHERE          0

#include "loc_areas.h"

#define ARDA_LOCATIONS_DEFS
#endif

