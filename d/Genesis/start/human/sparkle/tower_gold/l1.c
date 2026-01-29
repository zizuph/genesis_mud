#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("The First floor");
    set_long("\n"+
             "This is the luxurious first floor.\n"+
             "A red velvet carpet is laid across the marble floor.\n"+
             "At one end are the stairs up and down, on the other end\n"+
             "is a large ebony door with a golden sign.\n"+
             "");

    add_item(({"carpet" }),"It is made out of the finest velvet and a pleasure to walk upon.\n"+
    "");
    add_item(({"floor" }),"You see your own reflection.\n"+
    "");
    add_item(({"stairs" }),"The stairs lead up to the second floor as well as down to the lobby.\n"+
    "");
    add_item(({"door","north door" }),"Wrought in ebony by expert hands and fitted with an exquisitely\n"+
    " crafted golden sign, this door is indeed very impressive.\n"+
    "");
    add_item(({"sign" }),"@@sign");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_exit(TOWN_DIR + "tower", "down");
    add_exit(TOWN_DIR + "l2", "up");
}

string
sign()
{
    string domain_arr, exit_name;
    exit_name = "Bath";

    return("  ####  Office of "+ exit_name +".  ####\n");
}
