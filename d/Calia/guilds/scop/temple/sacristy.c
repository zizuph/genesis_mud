
/*
 * sacristy.c
 *
 * Sacristy for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

object cabinet;

void 
reset_room() 
{
    if (!(cabinet)) 
    {
        cabinet=clone_object(SPIRIT_OBJECTS+"cabinet");
        cabinet->move(TO);
    }

}

void
create_room()
{
    set_short("Sacristy");
    set_long("You are in a small chamber known as the sacristy. This "+
        "chamber holds all of the ceremonial and holy items for use "+
        "in ceremonies. A small cabinet sits against the southern "+
        "wall. There is a small golden door leading back out to the "+
        "chapel to the north.\n");

    add_item(({"wall","walls"}),"The walls of this room are painted "+
        "bright gold in colour. Against the south wall there is a "+
        "cabinet. In the northern wall is a small golden door.\n");
    add_item(({"golden door", "small golden door"}), "There is a small "+
        "golden door in the nortth wall. It leads back out to the chapel.\n");
    add_item("floor", "The floor and ceiling are both constructed with "+
      "a grey stone and then smoothed and polished afterwards. The floor "+
      "is quite comfortable to walk on.\n");
    add_item("ceiling", "The floor and ceiling are both constructed with "+
      "a grey stone and then smoothed and polished afterwards.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"chapel","north",0,1);
    reset_room();
}
