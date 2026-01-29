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
//    add_exit("NotOpen/h11","north",drown);
//    add_exit("NotOpen/g12","east",drown);
/*
    add_exit("NotOpen/h11","north",crossing);
    add_exit("NotOpen/g12","east",crossing);
*/
    add_exit("f11","south",0,5);
    add_exit("g10","west",0,5);
    add_exit("willows","northwest",0,5);
    set_extraline("To the northwest you can see the willow thickets "
      + "where the Snowbourn joins the Entwash.");
    add_item(({"thicket","willow","willows","willow thickets"}), BSN(
        "These willows are growing at the joining of the Snowbourn with the Entwash."));
    set_drink_from( ({"entwash","river","stream"}) );
}

