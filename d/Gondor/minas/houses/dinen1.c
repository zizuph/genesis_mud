inherit "/d/Gondor/common/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

object door;

create_room() {
  set_short("Beyond the Fen Hollen");
  set_long("You are standing just inside the Fen Hollen, the Closed Door\n"+
    "of the Sixth Circle. A winding road descends westwards down many\n"+
    "curves towards a narrow land under the shadow of Mount Mindolluin's\n"+
    "precipice. Ancient walls line the road, and beyond them you can see\n"+
    "the roofs and chimneys of the tallest houses of the Fifth Circle.\n"+
    "The stone door leads east into the Sixth Circle.\n");
  add_item(({"walls","ancient walls"}),BS("The ancient walls line the narrow "+
    "so that noone will fall down into the streets of the Fifth Circle.\n"));
  add_item("road",BS("The road is expertly paved, and seems little used. "+
    "It descends down many curves towards a complex of pillared buildings.\n"));
  add_item("buildings",BS("The buildings are built of pale stone, with many "+
    "pillars, and domed ceilings. They remind you of magnificent mausoleums.\n"));
  add_item(({"chimneys","roofs"}),
    "The roofs are of the tallest houses in the Fifth Circle.\n");
  add_item("precipice","You are awed by the steep walls of Mount Mindolluin.\n");
  door = clone_object(MINAS_DIR+"obj/fenhollenin");
  door->move(TO);
  add_exit(MINAS_DIR+"houses/dinen2","west",0,2);
}



