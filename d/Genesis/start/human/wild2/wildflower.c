/*
 * Wildlower - Varian, March 2016
 */


#include <stdproperties.h>
#include "/d/Genesis/start/human/wild2/wild.h"
inherit "/std/object";

string colour();

string
colour()
{
    string *colour;
    colour = ({"blue", "purple", "yellow", "red", "orange", "pink", "white"});
    return colour[random(sizeof(colour))];
}

void
create_object()
{
    set_name("wildflower");
    add_name("flower");
    set_adj(colour());
    set_short(colour() + " wildflower");
    set_long("This wildflower is a vivid " + colour() + " colour and judging " +
        "by the wonderful smell, it appears to have been freshly picked.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);
}


