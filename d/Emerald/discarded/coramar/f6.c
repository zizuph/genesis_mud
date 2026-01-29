#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");


    add_fexit(CORAMAR+"f9", "west", 0);
    set_long("   The mist-shrouded forest is tall and overwhelming. Looking "+
             "up into the canopy of the forest you can see nothing but "+
             "the dark outlines of the treetops. The path here widens as "+
             "it continues through the dark, gray depths of the forest "+
             "to the west. As the path narrows to the southeast, the "+
             "dark outline of an arch-like shape formed by two trees can "+
             "be seen. The cool breeze gently whistles through the forest "+
             "floor. The wind is blowing gently from east to west, though the mist "+
             "is swirling from west to east.\n\n");

    add_fexit(CORAMAR+"f4", "southeast", 0);
}
