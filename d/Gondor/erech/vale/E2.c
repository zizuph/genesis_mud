/*
 * E2.c
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
      "to the south the vale of Erech widens out. Across the vale a " +
      "small edge with a strange hill at its end can be seen. A road " +
      "leads northwest and south east.");
  
  vale_items();
  path_items();

  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

  add_exit(E_VALE + "D1.c", "northwest", 0, 2, 0);
  add_exit(E_VALE + "F3.c", "southeast", 0, 2, 0);
  add_exit(E_FIELD + "D2.c", "west", &to_field(), 2, 1);
}
