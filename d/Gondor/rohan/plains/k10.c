inherit "/d/Gondor/rohan/plains/plain.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_plain()
{
     set_geo("flat");
     set_wet("high");
     set_grass("long, dark green");
     set_land("the West Emnet");
     set_where("southeast");
     set_special(1);
     set_river_name("Entwash");;
     set_rhard(5);
     set_rwhere("east");
    add_exit("l10","north",0,5);
    add_exit("NotOpen/k11","east",drown);
/*
    add_exit(ENTWASH_DIR + "str1", "east", crossing, rhard);
*/
    add_exit("j10","south",0,5);
    add_exit("k09","west",0,5);

    set_drink_from( ({"entwash","river","stream"}) );
}
