/*
 * F3.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit "/d/Gondor/common/lib/area_room";

inherit E_STD + "vale.c";

#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_area_room();

/*
 * Function name:    create_area_room()
 * Definition   :    Creates the room.
 */
public void
create_area_room()
{
  set_short("In the vale of Erech.");
  set_areatype(AREATYPE_ROAD);
  set_area("northern");
  set_areadesc("valley side");
  set_areaname("Erech");
  set_extraline("To the north the White Mountains towers up, while " +
      "to the south the vale of Erech widens out. Across the vale to " +
      "the west a small ridge with a strange hill at its end can be " +
      "seen. A bit to the east the sound of running water can be heard. " +
      "A road leads northwest and east.");
  
  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

  path_items();
  vale_items();

  add_exit(E_VALE + "E2.c", "northwest", 0, 2, 0);
  add_exit(E_VALE + "G3.c", "east", 0, 2, 0);
}
