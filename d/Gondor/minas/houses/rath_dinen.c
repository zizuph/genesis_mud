inherit "/d/Gondor/common/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_room() {
  set_short("Rath Dinen");
  set_long("North and south of the Silent Street, Rath Dinen, are the\n"+
    "Hallows - the House of the Kings to the south, and the House of the\n"+
    "Stewards to the north. Stone stairs lined by many-pillared balusters\n"+
    "lead up to the heavy stone doors under the pale domes of the buildings.\n"+
    "A narrow road leads east up towards the Sixth Circle.\n"); 
  add_item("street",BS("The short street is lined with the mansions of the "+
    "dead Kings and of the Stewards. It is indeed silent here.\n"));
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
    "pillars, and domed ceilings. Stone stairs lead up to heavy doors on "+
    "each building.\n"));
  add_item("precipice","You are awed by the steep walls of Mount Mindolluin.\n");
  add_exit(MINAS_DIR+"houses/dinen3","east",0,3);
  add_exit(MINAS_DIR+"houses/stewards_porch","north",0,0);
  add_exit(MINAS_DIR+"houses/kings_porch","south",0,0);
}
