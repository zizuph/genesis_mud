/*
 * Forest in an example area.
 *
 * Written by Toby.
 */
#pragma strict_types

#include "defs.h"
#include DEFS_LOCATIONS

inherit STD_ROOM;

public void
create_subpart_east_room()
{  
  make_me_road("The road continues east and northwest.");
  
  add_exit(FOREST_PATH + "road03x02", "east");
  add_exit(FOREST_PATH + "road01x03", "northwest");
  add_exit(FOREST_PATH + "forest02x03", "north");
  add_exit(FOREST_PATH + "forest02x01", "south");
  add_exit(FOREST_PATH + "forest01x02", "west");


  add_known_location(SUBAREA_WEST_EXIT, "northwest");
  add_known_location(SUBAREA_EAST_EXIT, "east");
  add_known_location(SUBAREA_PATH_ENTR, "north");
  add_known_location(DIRECTION_DEFAULT, "east");
}
