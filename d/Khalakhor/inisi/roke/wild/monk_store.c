/*
 * monk_store.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*Kaheda guild store added by Mona July ‘96
*for the sale of herbpouches*/

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>

static int pouch;

void
reset_room()
{
    pouch = 1;
}

void
create_room()
{
    set_short("smelling room");

    set_long("There is a rich and complex scent in the air. It reminds " +
             "you of spices and leather. The back wall is covered with " +
             "shelves.\n");

    add_item(({"shelf", "shelves"}), "The empty shelves cover the wall " +
             "almost to the ceiling, the top shelf being just out of sight.\n");
    add_item("top shelf", "The top shelf is a bit too high up to see.\n");

    add_prop(OBJ_S_SEARCH_FUN, "search_shelf");

    add_exit("monk_discuss", "north");
    reset_room();
}

string
search_shelf(object who, string s)
{
    if (s == "shelf" || s == "top shelf" || s == "shelves")
    {
        if (pouch)
        {
            //clone_object(ROKEDIR + "obj/herbpouch")->move(who);
            clone_object("/d/Gondor/common/guild/obj/herbpouch")->move(who);
            say(QCTNAME(who) + " found something on in the desk.\n");
            pouch = 0;
            return "You found a pouch on the top shelf.\n";

        }
        return "You find nothing on the shelves.\n";
    }
    return "";
}
