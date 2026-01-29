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
    set_rwhere("north and east");
    add_exit("NotOpen/g12","north",drown);
    add_exit("NotOpen/f13","east",drown);
/*
    add_exit("NotOpen/g12","north",crossing);
    add_exit("NotOpen/f13","east",crossing);
*/
    add_exit("e12","south",0,5);
    add_exit("f11","west",0,5);

    set_drink_from( ({"entwash","river","stream"}) );
}

