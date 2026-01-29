inherit "/d/Gondor/common/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_room() {
  set_short("A plateau under the precipices of Mount Mindolluin");
  set_long("You are at the Rath Dinen, the Silent Street, where the ancient\n"+
    "tombs of the Kings and Stewards of Gondor have been since the\n"+
    "building of the City. Great stone buildings stand at both sides of\n"+
    "the street west of here, tall columns and carven figures lined\n"+
    "up on both sides. East the road winds up many steep curves towards\n"+
    "Fen Hollen of the Sixth Circle.\n"); 
  add_item("street",BS("The short street is lined with the mansions of the "+
    "dead Kings and of the Stewards.\n"));
  add_item("columns",BS("Tall, grey, stone columns line the road, bearing "+
    "names of the old Stewards of Gondor. Stewards have ruled Gondor since "+
    "the last King died nearly a millenium ago - ruling while awaiting the "+
    "return of the King.....\n"));
  add_item(({"figures","figure","carven figures"}),
    BS("The carven stone statues bear the images of the old kings, tall men "+
    "long dead - Gondor has been without a king for nearly a millenium.\n"));
  add_item("road",BS("The paved road seems little used. "+
    "It climbs up many curves towards Fen Hollen, the door to the Sixth Circle.\n"));
  add_item("buildings",BS("The buildings are built of pale stone, with many "+
    "pillars, and domed ceilings. They remind you of magnificent mausoleums.\n"));
  add_item(({"chimneys","roofs"}),
    "The roofs are of the tallest houses in the Fifth Circle.\n");
  add_item("precipice","You are awed by the steep walls of Mount Mindolluin.\n");
  add_exit(MINAS_DIR+"houses/dinen2","east",0,3);
  add_exit(MINAS_DIR+"houses/rath_dinen","west",0,0);
}
