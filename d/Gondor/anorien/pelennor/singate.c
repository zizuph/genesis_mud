#pragma strict_types

inherit "/d/Gondor/minas/lib/ingate";

#include "/d/Gondor/defs.h"
#include "sgatedefs.h"

public void
create_gondor()
{
    set_igroom(IGROOM);
    set_gfile2(GFILE2);
    set_groomdir(GROOMDIR);
    set_ofile(OFILE);
    set_grtoig(GRTOIG);
    set_gdir(GDIR);
    set_wroom(WROOM);

    ::create_gondor();

    set_long(BSN("Before you to the south is the Harlond Fort, "+
    "the gate through which the road from Lebennin enters the Pelennor. "+
    "The road continues north towards the City, crossing green "+
    "fields and farmlands. The fort is a strong construction of stone, "+
    "with battlements on the top, and guard stations both west and east."));
    set_short("Inside the Harlond Fort gate");
    add_exit(ANO_DIR+"pelennor/sroad1","north",0,1);
    add_exit(IGROOM,"east",0,0);
    add_exit(OGROOM,"west",0,0);
    add_item("fort","The gatehouse looks so strong it could be called a fort.\n"+
    "It is protecting the important gate, through which the road\n"+
    "from Lebennin enters the Pelennor fields. A large stone wall\n"+
    "is built in a wide circle around these farmlands of the great\n"+
    "city of Minas Tirith, capital of Gondor.\n");
  add_item(({"wall","walls"}),BS("The walls of the gatehouse are made of "+
    "strong stoneblocks, and so is the Rammas Echor, the vast circular "+
    "stone wall through which this gate leads.\n"));
    enable_reset();
  reset_room();
}
