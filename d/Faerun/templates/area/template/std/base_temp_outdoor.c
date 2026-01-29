/*
 * Base outdoor room for <template>
 *
 * -- Nerull, 2020
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include "/d/Faerun/sys/mudtime.h";
#include "/d/Faerun/sys/sunlight.h"
#include <stdproperties.h>
#include <terrain.h>
#include <macros.h>

inherit FAERUN_OUTDOOR_BASE;
inherit "/d/Faerun/std/room_tell";
inherit HERB_SEARCH;


void
create_temp_outdoor()
{
}


void
create_faerun_room()
{
    ::create_faerun_room();

    extraline = "Additional room descriptions goes here.";

    set_short("Somewhere outdoorst");    
   
    create_temp_outdoor();

    add_room_tell("Mists drift past you, swirling around and floating away.");
}

