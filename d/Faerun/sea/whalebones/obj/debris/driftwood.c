/*
 * Debris on Finback Island
 * by Nucifera, 2021
 * based on 'Colored bottles' by Finwe, March 2004
 */
// sets domain defs file. include in all files.
#include "/d/Faerun/defs.h"
// loads the area def file
#include "/d/Faerun/sea/whalebones/defs.h"

// loads basic routines for this file
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
inherit "/std/object";
#define COLOR   ({"redish brown", "blue tinged", "dull green", "splattered yellow", "faded blue", "pale red-brown", "purple tinged", "dull buff", "boring brown"})
#define SIZE    ({"small", "average-sized", "medium-sized", "man-sized"})
#define SHAPE   ({"splintered", "square", "thin", "slender"})
create_object()
{
    string color, size, shape;
// add this for each object so it's assigned an id number
    seteuid(getuid());
// will randomly choose an element each of the defines above
    color  = ONE_OF_LIST(COLOR);
    size   = ONE_OF_LIST(SIZE);
    shape  = ONE_OF_LIST(SHAPE);

    set_name("driftwood");
    add_name(color + " driftwood");
    add_name(size + " " + color + " driftwood");
    add_name(size + " " + " driftwood");
    add_adj(size);
    add_adj(color);

    set_short(size + " " + color + " driftwood");
    set_long("This is a " + short() + ". It is " + shape + " and weathered down by wind and sea. It appears to be debris from a shipwreck.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 3);
    add_prop(OBJ_I_VALUE, 100);
}
