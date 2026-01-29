#pragma strict_types

inherit "/d/Gondor/minas/lib/ingate";

#include "/d/Gondor/defs.h"
#include "ngatedefs.h"

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

    set_long(BSN("Before you to the north is the Anorien Fort, "+
    "the gate through which the road from Anorien enters the Pelennor. "+
    "The road continues south towards the City, crossing green "+
    "fields and farmlands. The fort is a strong construction of stone, "+
    "with battlements on the top, and guard stations both west and east."));
    set_short("Inside the Anorien Fort gate");
    add_exit(ANO_DIR+"pelennor/nroad3","south",0,1);
    add_exit(OUTGATE, GDIR, 1, 1, 1);
    add_exit(IGROOM,"west",0,0);
    add_exit(OGROOM,"east",0,0);
    add_item("fort","The gatehouse looks so strong it could be called a fort.\n"+
        "It is protecting the important gate, through which the road\n"+
        "from Anorien and Rohan enters the Pelennor fields. A large stone wall\n"+
        "is built in a wide circle around these farmlands of the great\n"+
        "city of Minas Tirith, capital of Gondor.\n");
    add_item(({"wall","walls"}),BS("The walls of the gatehouse are made of "+
        "strong stoneblocks, and so is the Rammas Echor, the vast circular "+
        "stone wall through which this gate leads.\n"));
    enable_reset();
    reset_room();
}
