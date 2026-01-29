#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/common/warfare/warfare.h"

#include <macros.h>
#include <stdproperties.h>

inherit "/d/Krynn/trelgorn/fields/field_base.c";

void
create_krynn_room()
{

    ::create_krynn_room();
    set_short("On a large field.");
    set_long("You are standing on a large field.\n");
    
    add_exit("field1","west");
    add_exit("field3","east");
}

void
reset_krynn_room()
{
    ::reset_krynn_room();
}
