inherit "/d/Gondor/rohan/plains/plain";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_plain() 
{
    set_geo("open");
    set_wet("damp");
    set_grass("long, dark green and spicy");
    set_land("the Eastfold");
    set_where("eastern");
    set_special(2);
    set_river_name("Entwash");;
    set_rhard(30);
    set_rwhere("north");
    add_exit("c15","south",0,5);
    add_exit("d14","west",0,5);
    add_exit(ENTWASH_DIR + "str6","east",crossing);
    set_extraline("To the east you can see the mouths "
      + "of the Entwash, where the mighty river splits up into dozens of "
      + "smaller streams, all running towards the great Anduin in the east. "
      + "The fens lying between the many rivers that make up the mouths "
      + "of the Entwash seem to be hardly passable.");
    set_drink_from( ({"entwash","river","stream"}) );
}

