inherit "/std/room";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
object mon;


#define PATH "/d/Terel/mecien/valley/city/"
#define TO this_object()

reset_room(){
   if(mon) return;
   mon = clone_object(PATH + "guard");
  mon->move(TO);
   clone_object(PATH + "captain")->move_living("from the barred door", TO);
   
}

create_room(){
   set_short("Guard House");
   set_long(
      "This large stone building is an outpost for the city guard. A barred " +
      "door leads into the barracks. A bench and table sit here, upon the wall is " +
      "a large rack for holding halberds. A stone fireplace keeps the place " +
      "warm.\n");
   add_item("fireplace", "It is stone, used to heat this hall. There is some " +
      "ash in it from the remains of the fires. Above it is a statue of an eagle.\n");
   add_item(({"statue of eagle", "eagle", "statue"}), "It is a small statue of an eagle, it looks noble.\n");
   add_item("rack", "It is used for holding halberds and other polearms.\n");
add_item("bench", "It is wood, used to sit at the table.\n");
add_item("table", "It is a large wooden table.\n");
add_item("ash", "Remains from the fires.\n");
add_item("door", "It is locked and barred, very secure.\n");
add_cmd_item("door", "open", "It is locked.\n");

add_exit(PATH + "street11", "west", 0);
   reset_room();
}

