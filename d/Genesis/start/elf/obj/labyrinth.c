#include <stdproperties.h>
#include "../stddefs.h"

#pragma save_binary

inherit OBJECT;
inherit STRINGLIB;

#define LONG \
  "It is a large wooden table. Its surface is sunken, as on a pool table, "+\
  "but instead there is a simple labyrinth built on the surface. In each " +\
  "edge there are two holes, one black, one red, reachable from the " +\
  "labyrinth.\n"

#define HOLE_ITEM ({"hole", "holes", "black hole", "red hole"})
#define HOLE_DESC \
  "The holes are semi-circular and about 4 inches in diameter. " +\
  "They seem to lead to some kind of tunnels inside the table.\n"

#define GET_FAIL_MSG \
  "It is attached to the floor.\n"

create_object() {
  set_name("labyrinth");
  set_adj(({"wooden"}));

  set_long(WRAP(LONG));

  add_item(HOLE_ITEM, WRAP(HOLE_DESC));

  add_prop(OBJ_M_NO_GET, GET_FAIL_MSG);
}

