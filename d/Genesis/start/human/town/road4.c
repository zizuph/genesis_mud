/*
 *  /d/Genesis/start/human/town/road4.c
 *
 *  This is the crossroads at the middle of Sparkle Town just south of
 *  the Church.
 *
 *  Created in ancient times by ??
 *
 *  Modification Log:
 *    - October 2006 (Gorboth) - added box with maps for newbies to take
 */
#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
reset_room()
{
    if (!present("midsommarst ng") && time() > 835307984 && time() < 835394384)
        room_add_object("/d/Relic/lugdush/obj/pole");
}

void
create_room()
{
    set_short("Sparkle Road");
    set_long("\n"+
             "The road is quite crowded here. People are running in all\n"+
             "directions trying to mind their daily business. North is\n"+
             "the Church of Sparkle. It is a hall of life and a holy\n"+
             "place for the human race. South is the Tower of Realms.\n"+
             "");

    add_item(({"church" }),"It is a white building and quite simple on"
      + "the outside. However, you can clearly see that is made by"
      + " skilled hands.\n");
    add_item(({"people" }),"Oh they're just commoners. Nothing special"
      + " about them.\n");
    add_item(({"tower","road" }),"");

    add_exit(TOWN_DIR + "church","north");
    add_exit(TOWN_DIR + "road3","west");
    add_exit(TOWN_DIR + "tower","south");
    add_exit(TOWN_DIR + "square","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    room_add_object(OBJ_DIR + "mapbox");

    reset_room();
}
