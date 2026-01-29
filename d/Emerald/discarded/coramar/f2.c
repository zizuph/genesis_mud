#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");


  
    set_long("   The narrow path through the forest seems like little more than an "+
              "ancient outline beneath the heavy mist. The moist, gray "+
              "blanket covers the entire area. The enormous, towering trees "+
              "appear like giant shadows of columns soaring into the gray nothingness above. "+
              "The narrow path winding through the enormous trees and the "+
              "heavy, gray fog making it nearly impossible to see anything "+
              "act to create a feeling of confinement here. A cool breeze "+
              "blows across the path through the wood, whistling gently in "+
              "an eerie, high pitch. As you notice that the fog does not "+
              "move with the breeze, you begin to wonder about the nature "+
              "of the blue-gray cloud.\n\n");

    add_fexit(CORAMAR+"f3", "north", 0);
    add_fexit(CORAMAR+"f1", "south", 0);
}
