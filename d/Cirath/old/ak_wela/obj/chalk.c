inherit "/std/object";
#include "/d/Cirath/common/defs.h"

void
create_object()
{
    string *colors = ({"red", "yellow", "orange", "green", "blue", 
                       "purple", "pink", "white", "charcoal"});

    set_name("chalk");
    add_name("_graffitti_chalk_");

    set_adj(colors[random(sizeof(colors))]);
    add_adj("small");
    add_adj("dusty");

    set_short("small " + query_adj() + " piece of chalk");
    set_pshort("small " + query_adj() + " pieces of chalk");

    set_long("A piece of " + query_adj() + "-colored chalk, small " +
             "and dusty.  You can probably use it to write, scribble, " +
             "and draw on some surfaces.\n");
}
