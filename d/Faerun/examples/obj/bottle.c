/*
 * Colored bottles
 * Knick knack a mantel
 * Finwe, March 2004
 */

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";

#define COLOR   ({"red", "blue", "green", "yellow", "clear","light-blue", "pale red", "purple", "pink", "frosted white"})
#define SIZE    ({"tall", "short", "medium-sized", "squat"})
#define SHAPE   ({"round", "tear-drop shaped", "square", "thin", "slender"})
create_object()
{
    string color, size, shape;

// add this for each object so it's assigned an id number
    seteuid(getuid());

// will randomly choose an element each of the defines above
    color  = ONE_OF_LIST(COLOR);
    size   = ONE_OF_LIST(SIZE);
    shape  = ONE_OF_LIST(SHAPE);
 

    set_name("bottle");
    add_name("_example_bottle_");
    add_name(color + " bottle");
    add_name(size + " " + color + " bottle");
    add_name(size + " " + " bottle");

    add_adj(size);
    add_adj(color);
 
    set_short(size + " " + color + " bottle");
    set_long("This is a " + short() + ". It is " + shape + " and made from blown glass. It appears fragile but still strikingly beautiful. \n");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 3);
    add_prop(OBJ_I_VALUE, 100);
}
