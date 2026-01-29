inherit "/d/Gondor/rohan/plains/plain.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_plain()
{
    set_geo("rocky");
    set_wet("high");
    set_grass("long, dark green");
    set_land("the Westfold");
    set_where("northern");
    set_special(2);
    set_river_name("Deeping Stream");;
    set_rwhere("northwest");
    add_exit("l05","north",0,5);
    add_exit("k06","east",0,5);
    add_exit("j05","south",0,5);
    add_exit("k04","west",0,5);
 
    set_drink_from( ({"stream","river","deeping stream"}) );
}
