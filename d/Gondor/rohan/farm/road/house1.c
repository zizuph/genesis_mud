/* This file is /d/Gondor/olorin/farm/road/house1.c        */
/* It belongs to a small farm in the Ered Nimrais          */	
/* Olorin, Nov 1992                                        */

inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

void
create_room() 
{
    set_short("a small cottage");
    set_long(BS("This is the only room of the small cottage. A whole family seems "
        +   "to have lived here. Now the cottage is deserted. It is "
        +   "completely empty. You wonder what made the farmer and his family leave this farm.\n"));
    add_exit(FARM_DIR + "road/yard1", "north", 0);
    add_item("furniture",BS("There is no furniture here. Everything has been taken away.\n"));
    add_prop(ROOM_I_INSIDE, 1);
    clone_object(FARM_DIR + "road/housedoor")->move(this_object());

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
}

string
do_search(object tp, string arg)
{
    if (strlen(arg) && (arg == "cottage" ||
        arg == "room" || arg == "house"))
        return "There is nothing to be found here.\n";

    return 0;
}

