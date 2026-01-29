/*
 * Broken bottle for well trash
 * Finwe, May 2020
 */

#include "/d/Shire/sys/defs.h" 
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";

create_object()
{
//    int x,y,z;
//    string *color, *size, *shape;
//
//    seteuid(getuid());
//
//    color  = ({"red", "blue", "green", "yellow", "clear","light-blue",
//        "pale red", "purple", "pink", "frosted white"});
//    size   = ({"tall", "short", "medium-sized", "squat"});
//    shape  = ({"round", "tear-drop shaped", "square", "thin", "slender"});
// 
//    x = random(sizeof(color));
//    y = random(sizeof(size));
//    z = random(sizeof(shape));

    set_name("bottle");
    add_name("_well_bottle_");
    add_name("bottle");
    add_name("jagged");
    add_name("clear");

    set_short("jagged clear bottle");
    set_long("This is a " + short() + ". The bottom has broken off " +
        "from being dropped. The only part remaining is the neck and " +
        "a jagged edge. It looks like it once held a drink in it, but " +
        "now it's worthless.\n");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 3);
    add_prop(OBJ_I_VALUE, 100);
}
