/*
 * Base file for mines of Moria
 * Finwe, February 2003
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/cmd/std/command_driver";
inherit BASE_COMMON;
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_mine_room() {}
 

public void
create_area_room()
{

    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_I_ALLOW_STEED, 0);

    set_area("deep in");
    set_areaname("the mines");
    set_land("Khazad-dum");
    set_areatype(0);
    set_areadesc("passage");

    set_add_all_rooms();
    create_mine_room();
 
 
}

 
void
init()
{   
    ::init();
//    add_action("drink_it",      "drink");
}

public string
long_desc()
{
// no time functions here, as it's impossible to tell what time it 
// is inside the mt.
    string desc;
    
    desc = CAP(query_short()) + ". ";

    if (strlen(extraline))
	desc += (" " + extraline);
    if (functionp(vbfc_extra))
	desc += " " + vbfc_extra();
    return (desc);
}
