inherit "/d/Gondor/rohan/plains/plain";

#include <macros.h>

#include "/d/Gondor/defs.h"


void
create_plain()
{
    set_geo("open");
    set_wet("damp");
    set_grass("long, thick green");
    set_land("the Eastfold");
    set_where("southeast");
    set_special(2);
    set_rwhere("east");
    set_rhard(10);
    set_extraline("The Mering Stream is to the east, where it comes"
      + " flowing out of the Firienwood Forest to the South, marking"
      + " the border between Gondor and Rohan. ");

    add_item( ({"stream", "river", "mering stream"}), BSN(
        "The Mering Stream flows by quickly to the east, where a"
      + " deep gulley has been delved by the flowing current."));
    add_item( ({"gully", "deep gulley"}), BSN(
        "The gulley which has been delved by the flowing current"
      + " of the Mering Stream is deep, with banks which make it"
      + " look as if crossing at this point will be impossible."));
    add_item( ({"bank", "banks", "banks of the mering stream"}), BSN(
        "The banks of the Mering Stream are deep and severely"
      + " undercut here, making them impossible to cross."));

    add_exit("d15","north",0,5);
    add_exit("b14","southwest",0,5);
    add_exit("c14","west",0,5);

    set_no_exit_msg("east", 
        BSN("The banks of the Mering Stream are deep and severely"
          + " undercut here, making them impossible to cross."));

    set_drink_from( ({"stream","river","mering stream"}) );
}
