inherit "/d/Gondor/rohan/plains/plain";

#include "/d/Gondor/defs.h"

void
create_plain() 
{
    set_land("Eastfold");
    set_where("north");
    set_geo("slicky");
    set_wet("wet");
    set_grass("thick, spicy green");
    set_rhard(30);
    set_river_name("Entwash");;
    set_rwhere("northeast");
    set_special(2);

    add_exit("h10","northwest",drown);
    add_exit("NotOpen/h11","northeast",drown);
/*
    add_exit("h10","northwest",crossing);
    add_exit("NotOpen/h11","northeast",crossing);
*/
    add_exit("g10","southwest",0,5);
    add_exit("g11","southeast",0,5);

    set_extraline("To the northwest, you can see the Snowbourn. To "
      + "the north, it joins the Entwash, that comes from the north, and "
      + "turns to the east here, continuing towards the marshes fed by "
      + "it, and finally to the mighty Anduin. You are inside a "
      + "thicket of willows that are thriving on the wet ground here. ");

    add_item(({"snowbourn"}), BSN("Here the river Snowbourn floats "
      + "away really fast and it might be quite hard to cross it here."));
 
    add_item(({"thicket","willow","willows","willow thickets"}), BSN(
        "Willows are known to prefer wet ground, so this marshy land is perfect for them."));
    set_drink_from( ({"snowbourn","stream","river"}) );

    add_herb_file(KRYNN_HERB_DIR + "grey_willow");
}
