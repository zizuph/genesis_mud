inherit "/d/Gondor/rohan/plains/plain.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_plain()
{
    set_geo("rocky");
    set_wet("damp");
    set_grass("short dark green");
    set_land("the Westfold");
    set_where("northwestern");
    set_special(2);
    set_river_name("Deeping Stream");;
    set_rhard(20);
    set_rwhere("north");
    add_exit("NotOpen/l03","north",drown);
/*
    add_exit("NotOpen/l03","north",crossing);
*/
    add_exit("k04","east",0,5);
    add_exit(ROH_DIR + "road/wr5","south",0,2);
    add_exit(ROH_DIR + "road/wr6","west",0,2);

    set_drink_from( ({"stream","river","deeping stream"}) );
}
