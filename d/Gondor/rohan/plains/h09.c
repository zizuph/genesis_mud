inherit "/d/Gondor/rohan/plains/plain.c";

#include "/d/Gondor/defs.h"

void
create_plain()
{
    set_geo("flat");
    set_wet("soggy");
    set_grass("thick dark green");
    set_land("the Westfold");
    set_where("southeast");
    set_special(5);
    set_river_name("Snowbourn");;
    set_rhard(10);
    set_rwhere("south");
    add_exit("i09","north",0,5);
    add_exit("h10","east",0,5);
    add_exit(ROH_DIR + "road/er1","south",crossing);
    add_exit("h08","west",0,5);


    set_drink_from( ({"stream","river","snowbourn"}) );
}
