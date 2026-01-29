inherit "/d/Gondor/rohan/plains/plain.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_plain() 
{
    set_geo("open");
    set_wet("damp");
    set_grass("long, dark green and spicy");
    set_land("the Eastfold");
    set_where("north");
    set_special(2);
    set_river_name("Entwash");;
    set_rhard(30);
    set_rwhere("northeast");
    add_exit("g11","north",0,5);
    add_exit("f12","east",0,5);
    add_exit("e11","south",0,5);
    add_exit(ROH_DIR + "road/er2","west",0,2);
    set_drink_from( ({"entwash","river","stream"}) );
}

