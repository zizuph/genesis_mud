inherit "/d/Gondor/common/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_room() {
  set_short("A winding road near Rath Dinen");
  set_long("The winding road descends in many curves down to the west,\n"+
    "leading towards domed stone buildings on a narrow plateau under\n"+
    "Mount Mindolluin. Up to the east the road reaches a stone door in\n"+
    "the wall of the Sixth Circle. Stone walls with ancient carvings line\n"+
    "the winding road, obscuring the Fifth Circle from view.\n");
  add_item(({"walls","carvings"}),BS("The ancient walls line the narrow "+
    "road so nobody will fall down into the streets of the Fifth Circle. "+
    "The walls bear carvings that depict several events of Gondorian "+
    "history, deeds of Kings and their Stewards that shaped the land.\n"));
  add_item("road",BS("The paved road seems little used. "+
    "It descends down many curves towards some stone buildings.\n"));
  add_item("buildings",BS("The buildings are built of pale stone, with many "+
    "pillars, and domed ceilings. They remind you of magnificent mausoleums.\n"));
  add_item(({"chimneys","roofs"}),
    "The roofs are of the tallest houses in the Fifth Circle.\n");
  add_item("precipice","You are awed by the steep walls of Mount Mindolluin.\n");
  add_exit(MINAS_DIR+"houses/dinen1","east",0,3);
  add_exit(MINAS_DIR+"houses/dinen3","west",0,1);
}



