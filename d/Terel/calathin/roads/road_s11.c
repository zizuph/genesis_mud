/*
    This is a standard south road. Mortricia 920723
    Updated by Shinto 10-21-98
  */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>

public void
create_room()
{
    set_short("The southern road, close to great forest");

    set_long(
        "You are now standing in the southern parts of Calathin. " +
        "There are trees scattered around the road, except to the west " +
        "where you see some sort of a camp. " +
        "The road continues north and south. To the south you " +
        "see a great forest.\n");

    add_item(({"tree", "trees", "conifers", "conifer"}), "Some of the " +
     "conifers look very old, " +
        "but there are a few saplings as well. The trees grow thicker " +
     "here.\n");
    add_item(({"snow"}), "The snow never disappears in this part of " +
        "the world. Here it's damn cold unless you have warm clothes.\n");
    add_item(({"forest"}), "The forest looks dark, "+
     "perhaps even a bit enchanted. " +
     "The forest consists mostly of conifers.\n");
    add_item(({"camp"}), "You see some carriages and people, but " +
     "you have to go closer in order to find out more about it.\n");


    add_exit(CALATHIN_DIR + "roads/road_s10", "north", 0);
    add_exit("/d/Terel/mortricia/camp/entrance",       "west", 0);
    add_exit("/d/Terel/enchanted/n_edge6",         "south", 0);
}
