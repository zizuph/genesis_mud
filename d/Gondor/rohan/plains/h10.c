inherit "/d/Gondor/rohan/plains/plain.c";

#include "/d/Gondor/defs.h"


void
create_plain()
{
    set_geo("flat");
    set_wet("damp");
    set_grass("dark green and spicy");
    set_land("the Westfold");
    set_where("southeast");
    set_special(2);
    set_river_name("Entwash");;
    set_rhard(10);
    set_rwhere("east");

    add_exit("i10","north",0,5);
    add_exit("NotOpen/h11","east",drown);
    add_exit("willows","southeast",drown);
/*
    add_exit("NotOpen/h11","east",crossing);
*/
    add_exit("g10","south",crossing);
    add_exit("h09","west",0,5);

    set_extraline("You can see the Snowbourn south of here. To the southeast, "
     + "it joins the Entwash, that comes from the north, and turns to the "
     + "east here, continuing towards the marshes fed by it, and finally "
     + "to the mighty Anduin.");


    add_item(({"snowbourn"}), BSN(
        "The river Snowbourn seems to float quite gently right here. It "
      + "might be quite easy to cross it here."));

    set_drink_from( ({"snowbourn","entwash","river","stream"}) );
}

