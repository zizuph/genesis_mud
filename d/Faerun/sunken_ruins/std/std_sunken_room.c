/*
 * Base room for Fire Knives guild rooms
 * Finwe, May 2017
 * Adjusted, Nerull 2018
 */

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_OUTDOOR_BASE;
inherit "/d/Faerun/std/room_tell";
inherit "/d/Faerun/std/search";
inherit "/d/Faerun/std/cmd_parse";

string extra_longdesc;

void set_extra_longdesc(string str);


/*
 * Function name: set_extra_longdesc()
 * Description  : Sets an additional static string to
 * the long description.
 */
void set_extra_longdesc(string str)
{
    extra_longdesc = str;
    return;
}


/*
 * Function name: query_extra_longdesc()
 * Description  : Returns the additional static long desc string.
 */
string query_extra_longdesc()
{
    return extra_longdesc;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_sunken_room(void)
{
    // Redefine this
}


void
create_faerun_room()
{
    seteuid(getuid());

    add_prop(ROOM_I_LIGHT, 1); 
    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
    
    set_short("short room description");
    set_long("Long room description.\n");

    set_room_tell_time(200 + random(100));
    
    reset_faerun_room();

    create_sunken_room();
}


void
reset_faerun_room()
{
}


void
init()
{
    ::init();
}

