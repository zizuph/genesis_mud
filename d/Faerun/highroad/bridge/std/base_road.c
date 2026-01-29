/*
 * Base Room for High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/d/Faerun/highroad/bridge/std/base_common.c";
inherit FAERUN_OUTDOOR_BASE;

void
create_road()
{
}


void
create_faerun_room()
{
    ::create_faerun_room();

    extraline = "Room description goes here.";

    set_short("Along the High Road");
//    set_long(short() + ". " + extra_line + "\n");
    create_road();
}

/*
 * Function name : add_highway
 * Description   : adds descr of highway
 */
void add_highway()
{
}

