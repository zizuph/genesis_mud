inherit "/d/Gondor/rohan/plains/plain.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_plain()
{
    set_geo("flat");
    set_wet("high");
    set_grass("thick and long");
    set_land("the Westfold");
    set_where("east");
    set_special(2);
    set_river_name("Entwash");;
    set_rhard(20);
    set_rwhere("east");
    set_extraline("Far to the south, you can see the Snowbourn join it. ");

    add_exit("j10","north",0,5);
    add_exit("NotOpen/i11","east",drown);
/*
    add_exit("NotOpen/i11","east",crossing);
*/
    add_exit("h10","south",0,5);
    add_exit("i09","west",0,5);


    set_drink_from( ({"entwash","river","stream"}) );
}
