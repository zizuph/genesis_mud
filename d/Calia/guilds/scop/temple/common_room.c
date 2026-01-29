
/*
 * common_room.c
 *
 * Common Board room for the Spirit Circle of Psuchae Temple
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

void    load_board();

void
create_room()
{
    set_short("A strange golden chamber");
    set_long("This chamber of the temple is mysteriously illuminated "+
        "by a luminous golden light that leave the details of the walls "+
        "and floor shimmering and indistinct. The only thing you can "+
        "clearly focus upon is a massive golden bulletin board that dominates "+
        "the entire room, upon which are written the decrees of wizards and "+
        "sages. To the north, a sharp break in the light yields an entrance "+
        "back into the temple's chapel.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"chapel","north",0,1);
    
    load_board();
}

void
load_board()
{
    seteuid(getuid(TO));

    clone_object("/d/Genesis/obj/board")->move(TO);
}

/*
 * Function: enter_inv
 * Description: block non-interactives from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob) && !interactive(ob))
        ob->move(from);
}