
/*
 * startroom.c
 *
 * Starting room for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 * Added entrance to the library and portal to the new Elemental
 * Temple for the Spirit Circle guild closure (so that old members
 * who haven't been converted yet have a place to enter the realms
 * and a way to get over to the new temple/start room).
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

void
create_room()
{
    set_short("Ruined sleeping chamber");
    set_long("A few rows of ruined small wooden bunks line the walls "+
        "of this chamber. This simple room was once the sleeping "+
        "chamber of the temple. The walls are plain, grey stone as "+
        "are the ceiling and the floor. It looks like there was a "+
        "large battle that took place at this temple as the chamber "+
        "now lies in ruins with many broken boards scattered on the "+
        "floor where bunks used to stand previously. There is a hole "+
        "in the northwest wall that you could walk through if you "+
        "wished and a portal on the south wall.\n");
    
    add_item("floor","The floor is made from the same plain grey "+
        "stone as the walls and ceiling are made from.\n");
    add_item(({"roof","ceiling"}),"The ceiling is made of the "+
        "same plain grey stone as the walls and floor are made from.\n");
    add_item(({"wall","walls"}),"The walls are very plain and "+
        "made out of grey stones placed together.\n");
    add_item(({"bunk","bunks","wooden bunk","wooden bunks",
        "small wooden bunk","small wooden bunks","row","rows",
        "boards","broken boards"}),
        "There are several rows of wooden bunks lining the walls "+
        "of this chamber. They look fairly plain, yet comfortable "+
        "to sleep on. There are also several broken boards on the "+
        "floor where bunks used to stand previously.\n");
    add_item("portal","When you look through the portal, you see the "+
        "new Elemental Temple equipment room.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"library","northwest",0,1);
    add_exit("/d/Calia/guilds/elementalists/temple/ec_rack","south",0,1);
}
