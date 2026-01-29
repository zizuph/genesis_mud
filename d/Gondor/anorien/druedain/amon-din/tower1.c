/*
 *  This is tower1.c
 *
 *  July 1995 by Gorboth
 *
 *  Comments:  This room is incomplete. If you want to let folks into the
 *             tower, you may feel free to finish it yourself.
 */

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"

create_room()
{
    set_short("at the base of a tower atop Amon Din");
    set_long("Gorboth never finished this room! If you want to do so"
      + " yourself, please feel free!\n");

    clone_object(AMON_DIR + "doors/towerdoorin")->move(TO);
}
