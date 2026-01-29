/*
 * File Name        : center_room.c
 * By               : Elmore and Boron
 * Inspiration from : -
 * Date             : March 2001.
 * Description      : Just another guild room :)
 *
 */

#include "../local.h"
#include <stdproperties.h>

inherit "/d/Krynn/std/room";

void
create_krynn_room()
{
   set_short("Grand circular room");
   set_long("A huge white circular room, people are moving in "
        + "all direction minding thier own business, you notice "
        + "what seems like training to the north, and it might "
        + "be trading going on to the east.\n");

   clone_object(GUILD_OBJ + "normal_board")->move(this_object());

   add_exit("hall","south",0,0);
   add_exit("train","north",0,0);
   add_exit("shop","east",0,0);
   add_exit("start","northeast",0,0);
}

