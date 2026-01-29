#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

public void
create_roads()
{
    set_street("big, dirty road");
    set_where("south");
    set_county("Fenmark");
    set_land("Rohan");
    set_mountain("Mountains of Nimrais");
    set_vegetation("long, dark green, spicy grass");
    set_forest("Firien Forest");
    set_extraline("You are in a clearing, in the middle of the " +Forest+ ". "
           + "The road comes out of the forest from northwest and enters it again "
           + "to the east.");

    add_exit(ROH_DIR + "road/er6", "northwest", 0);
    add_exit(ROH_DIR + "road/mering", "east", 0);
    add_exit(ROH_DIR + "plains/b14", "north", 0,2);
 
}

