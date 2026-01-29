/*
 * Base Phlan indoor room
 *
 * Nerull 2021
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit FAERUN_OUTDOOR_BASE;
inherit "/d/Faerun/std/room_tell";
inherit "/d/Faerun/std/search";
inherit "/d/Faerun/std/cmd_parse";


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_phlan_room(void)
{
    // Redefine this
}


void
create_faerun_room()
{
    seteuid(getuid());

    add_prop(ROOM_I_LIGHT, 1); 
    add_prop(ROOM_I_INSIDE, 1); 
    
    set_short("short room description");
    set_long("Long room description.\n");
    
    //add_room_tell("Mists drift past you, swirling around and floating away.");
    
    create_phlan_room();
    
    reset_faerun_room();  
}


void
reset_faerun_room()
{
}

