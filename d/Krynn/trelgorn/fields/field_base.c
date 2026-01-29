#pragma strict_types
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/common/warfare/warfare.h"

#include <macros.h>
#include <stdproperties.h>

inherit "/d/Krynn/common/warfare/conquer_base.c";
inherit "/d/Krynn/std/room.c";

void
create_krynn_room()
{

   set_short("You are standing on a large field.");
   set_long("This is a large field with flowers and grass as far as the eye can see of a blind man.\n");

   set_area_name(WAR_AREA_TRELGORN);
   reset_krynn_room();
}

void
reset_krynn_room()
{
    reset_conquer_room();
}

void
init()
{
    ::init();
    init_conquer();
}


