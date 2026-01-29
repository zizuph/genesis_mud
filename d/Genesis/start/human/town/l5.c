#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("5th floor");
    set_long("\n"+
             "The attic.\n"+
             "Narrow corridors twist and turn away in every direction.\n"+
             "You see lots of little shabby shacks with numbers on the doors.\n"+
             "The old wooden floor creaks forebodingly as you move across it.\n"+
             "A draft around your feet makes you shiver and the dust filled air\n"+
             "makes you sneeze. There is a sign next to the stairs down.\n"+
             "");

    add_item(({"floor" }),"The wooden floor is old and ill kept.\n"+
    "");
    add_item(({"shack","shacks" }),"These are the small offices of some of the less fortunate realms.\n"+
    "These are the ones that need your support.\n"+
    "");
    add_item(({"stairs" }),"The wooden stairs lead down to the fourth floor.\n"+
    "");
    add_item(({"doors" }),"You see nothing special about them.\n"+
    "");
    add_item(({"sign" }),"@@sign");

    add_exit(TOWN_DIR + "l4", "down");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
