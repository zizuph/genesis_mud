/*
 *
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/d/Faerun/highroad/std/base_common.c";

inherit FAERUN_INDOORS_BASE;

object item_found;

int count = 0;


void
create_dragonslair_inside()
{
	
}


void
create_indoor_room()
{
    ::create_indoor_room();
	
    NO_STEEDS;

    //extraline = "Room description goes here.";

    set_short("In a ruined citadel");
	
	create_dragonslair_inside();
}