
/*  Grand Palace in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

void
create_water_room()
{
    set_short("Royal Baths");
    set_long("You have entered the Royal Baths. Here is "+
        "where the residents of this palace come to relax "+
        "in the warm water baths that you see in front of "+
        "you. They are unlike any baths you have seen before "+
        "though.  Each bath is encased in some type of clear "+
        "glass-like material and filled with amazingly warm "+
        "water (unlike the water around you). You see a hallway "+
        "running to both the west and east from here.\n");

    add_item(({"bath", "baths"}), "Each bath is encased in "+
        "some type of clear glass-like material and filled "+
        "with amazingly warm water. Upon closer inspection "+
        "of the baths, you notice there are pipes leading "+
        "up to the inside of the baths from the bottom, "+
        "most likely supplying them with the warm water. "+
        "Above each of the baths seems to be an air pocket.\n");
    add_item(({"air pocket","air pockets","pocket", "pockets"}), 
        "There appears to be an air pocket above each of the "+
        "baths. If you were to enter the bath, there would "+
        "probably be enough air to breathe.\n");

    IN;

    add_swim_exit(THALC+"palace_2_7","west",0,1);
    add_swim_exit(THALC+"palace_2_9","east",0,1);
}

int
do_enter(string str)
{
    if (!str || str != "bath")
    {
        NF("Enter what? The bath? <enter bath>\n");
        return 0;
    }

        write("You swim up into one of the bath chambers. You "+
            "breath a sigh of relief as the pure air enters your "+
            "lungs once more.\n");
        tell_room(environment(TP), QCTNAME(TP) +
            " swims up into one of the bath chambers.\n", TP);
        this_player()->move_living("M",THALC+"bath",0);
        tell_room(environment(TP), QCTNAME(TP) +
            " arrives and takes in a deep breath of air.\n", TP);
        return 1;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
}
