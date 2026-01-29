#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

inherit "/std/room";

void
create_room()
{
    set_short("The eastern corridor");
    set_long("This is the eastern corridor of the second " +
        "floor of the house. A small door into a cubby-hole " +
        "is all you see except from the window in the " +
        "east wall.\n");
    add_item("stairs", "You look at the cubby-hole and then up at " +
        "the ceiling. All signs tells you that here is the place " +
        "where the stairs went up to the tower room once before. " +
        "Now this way up is sealed and shut closed.\n");
    add_item("window","You try to open the window but its " +
        "impossible. Looking through the dirty " +
        "glass you see only the grass lawn surrounding the " +
        "house and some trees blocking any view you else " +
        "might have had.\n");
    add_item(({"lawn","grass lawn"}),"Outside, below the window, the " +
        "grass lawn stretches out to the hedge.\n");
    add_item("hedge","You look over the grass lawn at the hedge. Its " +
        "high and well grown and its impossible to see anything through " +
        "or behind it from this distance.\n");
    add_item(({"door", "cubby-hole"}),"You pull up the door " +
        "and take a quick look inside. It seems to be a very " +
        "small cubby-hole, about 3 feet deep and once used " +
        "for storing cleaning equipment. Now its completely " +
        "empty and the shelves are staring empty at you.\n");
    add_item(({"corridor", "broad corridor"}),
        "It is a wide corridor. Your imagination gives it gleaming "+
        "hardwood floors, a runner of reddish carpet, and wall sconces, "+
        "but you cannot hold the image and it reverts to what it is: "+
        "a dusty, neglected corridor running east and west along the "+
        "length of the house. You measure the corridor to be approximately 18 feet wide.\n");
    add_item(({"shelf","shelves"}),"Inside the cubby-hole are " +
        "some empty shelves staring at you. There is absolutely " +
        "nothing on them at this moment.\n");
    add_item(({"ceiling","opening","planks","wooden planks"}), "You look up at the ceiling. There are clear " +
        "signs of an opening. But someone sealed the opening with " +
        "wooden planks. Most likely the cubby-hole was made where " +
        "the stairs went up to the tower room before.\n");
    add_item(({"trees","tree"}),"Through the window you watch the " +
        "treetops of the trees outside, but you cant see anything of " +
        "interest. Nothing in the tree or nothing through the " +
        "branches.\n");
    add_exit("platform","west");
    reset_room();
}

void
reset_room()
{

}

void
init()
{
    ::init();
        add_action("open_window","open");
}


int
open_window(string str)
{

    if ((str) && (str == "window"))
    {
        write("You walk up to the window and try to open it. " +
            "Its doesn't give after one tiny bit though. " +
            "Probably someone hit a nail or two in it from the " +
            "outside, but you cannot tell for sure.\n");
        say(({METNAME + " tries to open the window but it seems " +
            "to be stuck and it wont open.\n",
            TART_NONMETNAME + " tries to open the window but it seems " +
            "to be stuck and it wont open.\n",
            "You hear a noice from the window.\n"}), TP);
        return 1;
    }
    return 0;

}

