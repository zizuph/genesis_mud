/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"

object ob;

void
reset_room()
{
    if (!ob) {
        ob = clone_object(PATH + "sacristan");
        ob -> move(this_object());
    } else {
        ob -> reset_trader();
    }
}

create_room(){
   set_short("Sacristy");
   set_long(
      "This elegant wooden chamber is the sacristy of the sanctuary, the place\n"
      + "where mystics prepare for ceremonies. The ceiling is wooden arches\n"
      + "and elaborate panels of carved mahognay. The floor is also fine wood,\n"
   + "covered with a thick black carpet. A silver basin of water and a\n"
  + "marble pedestal rest against the north wall.\n");
   
   add_item("pedestal", "It is a plain white marble pedestal.\n");
  add_item("panels", "They are carved of mahogany, covering the walls and ceiling. They are\n"
  +"engraved with images of the ancient days.\n");
  add_item("basin", "It is sparkling silver, used to wash before\n"
  +" taking part in ceremony.\n");
   add_item("ceiling", "It is made of carved wooden arches, slender\n"
  +"and elegant.\n");
  add_item("carpet", "It is a thick black carpet.\n");
   add_exit(PATH + "sanctuary", "west", 0);
   add_exit(PATH + "storage", "east", 0);
   reset_room();
   
}


