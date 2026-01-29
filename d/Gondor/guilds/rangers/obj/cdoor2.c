/*
 *  /d/Gondor/guilds/rangers/obj/cdoor2.c
 *
 *  inner door to Central Headquarters council room.
 *
 *  Coded by Elessar
 *    Modified by Alto, 28 June 2001, to meet CH theme.
 *    Modified by Gwyneth, 6 May 2004
 *
 */
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_OBJ + "cdoor1.c";

public void
create_door()
{
    ::create_door();
    set_pass_command(({"e","east"}));
    set_other_room(RANGERS_HQ_DIR + "office");
}
