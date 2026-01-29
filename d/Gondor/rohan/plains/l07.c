inherit "/d/Gondor/rohan/plains/plain.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

create_plain()
{
    set_geo("hilly");
    set_wet("damp");
    set_grass("high green");
    set_land("the West Emnet");
    set_where("central");
    set_special(1);
    set_river_name("Deeping Stream");;
    set_rhard(20);
    set_rwhere("north");

    add_exit("NotOpen/m07","north",drown);
/*
    add_exit("NotOpen/m07","north",crossing);
*/
    add_exit("l08","east",0,5);
    add_exit("k07","south",0,5);
    add_exit("l06","west",0,5);

    set_drink_from( ({"stream","river","deeping stream"}) );
}

