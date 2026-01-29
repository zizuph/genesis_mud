/*
 * Base outdoor room for black flame
 * -- Nerull, 2022
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "/d/Faerun/sys/mudtime.h";
#include "/d/Faerun/sys/sunlight.h"
#include <stdproperties.h>
#include <terrain.h>
#include <macros.h>

inherit FAERUN_OUTDOOR_BASE;
inherit "/d/Faerun/std/room_tell";
inherit HERB_SEARCH;


void
create_bf_outdoor()
{
}


void
create_faerun_room()
{
    ::create_faerun_room();

    extraline = "Additional room descriptions goes here.";

    set_short("Somewhere in Faerun");    
   
    create_bf_outdoor();
}

