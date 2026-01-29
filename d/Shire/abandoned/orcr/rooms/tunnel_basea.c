/*
 * This is the base room for the Orc racial guild tunnels
 * /Finwe, Oct 2000
 *  
 */
/* 
inherit "/d/Shire/std/room.c";
inherit "/d/Shire/std/room/room_tell";
//inherit AREA_ROOM;
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
*/

#include "/d/Shire/sys/defs.h"
#include "local.h"
inherit "/d/Shire/std/room/room_tell";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_tunnel_room()
{
}
 
public void
//create_shire_room()

create_room()
{

    set_short("A dark tunnel deep inside the Misty Mountains");
    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room
//    add_prop(ROOM_M_NO_TELEPORT_TO, 
//        "A great elven-power prevents teleporting there.\n");
    add_prop(ROOM_I_ALLOW_STEED, 0); // no horsies in the house. They're messy. 
    create_tunnel_room();
    add_item(({"wall", "walls"}),
        "The walls are rough and have odd shaped grooves, " +
        "almost like the tunnel was carved by crude tools. They " +
        "curve upwards, somewhat, and meet together, forming an " +
        "uneven ceiling.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling is uneven with many deep groves, like it " +
        "was carved out of the mountain with crude tools.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor is uneven. Grooves mark where crude tools " +
        "were used to dig the tunnel. Oddly enough, the floor " +
        "is unusually clean.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A dripping sound echoes in the distance.");
    add_room_tell("A large rat scampers past you.");
    add_room_tell("Some odd sounds echo in the distance.");
    add_room_tell("Something rancid smelling drifts past you.");
}

/*
 * Tunnel descriptions
 */
 
string tunnel_desc1()
{
    return "You stand in a tunnel beneath the Misty mountains. " +
    "It has been roughly carved from the mountain, leaving the " +
    "walls rough looking and grooved. The darkness is " +
    "suffocating and absorbs any light. A feeling of uneasiness " +
    "seems to pervade the area. ";
}

string tunnel_desc2()
{
    return "This is a tunnel deep in the mountains. The rough " +
    "walls are evidence that the tunnel was carved by orcs or " +
    "trolls or even their slaves. There are deep grooves in the " +
    "wall, probably from the crude tools used to carve out the " +
    "tunnel. The darkness is thick, almost clammy as it absorbs " +
    "all light and sound. ";
}

string tunnel_desc3()
{
    return "Deep gashes in " +
    "the walls, ceiling, and floor show that the tunnel was " +
    "carved ages ago by terrible creatures. ";
}

string tunnel_desc4()
{
    return "A dark and forboding tunnel inside the Misty " +
    "Mountains. Darkness seems to blanket everything here, " +
    "smothering out all light. Gashes in the wall are evidence " +
    "that terrible creatures may have once inhabited these " +
    "tunnels. ";
}

/*
public string
long_desc()
{
    string  time  = CLOCK->query_time_of_day(),
    desc = CAP(query_short()) + ". ";
/*
    if (strlen(extraline))
	desc += (" " + extraline);
    if (functionp(vbfc_extra))
	desc += " " + vbfc_extra();
*/

/*
    desc += vbfc_extra() + extraline;
    return (desc);
}
*/