/* /d/Faerun/guilds/fire_knives/rooms/top-of-rope.c
 *
 * At the foot of the mountain, west past the hidden exit for full members.
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1); 

    set_short("Within a small cell near the exit to a yard.");
    
    set_long("Inside the small cell dividing the first floor from the yard "
    +"is nothing decorative at all. The room is compact and devoid of any "
    +"completed work. To the western side is a thick wooden door sealed shut "
    +"with a heavy log lodged between it and the rest of the area to keep it "
    +"from being opened by the blowing winds. At its left side is an iron "
    +"bollard placed firmly into the ground around which the end of the rope "
    +"is tied. A single torch is found within a sconce hanging from the "
    +"northern "
    +"wall. To your east begins a long hallway.\n");


    add_item(({"rope"}),
    "The rope is tied to the bollard on the west, extending across the room "
    +"and down through a hole on the ground. You could use it to climb down "
    +"from here. \n");
    
    /* Climb down rope */

    add_item(({"ground","floor"}),
    "The ground is of a cold, rough stone, and devoid of any "
    +"decorative functions. "
    +"at its center is a hole wide enough for you to crawl "
    +"through, into which a "
    +"rope is lost.\n");

    add_item(({"walls"}),
    "The walls are bare, without any decorations. Only a single sconce "
    +"with a torch "
    +"in it serves to beautify it somewhat, its light dispersing the "
    +"darkness that "
    +"would otherwise consume the area.\n");

    add_item(({"cell","room","area"}),
    "The cell is small and compact, separating the long hallway to your east "
    +"from the door to your west.\n");

    add_item(({"yard"}),
    "You cannot see the yard from here, but it lies beyond the door to "
    +"the west, "
    +"which has now been sealed shut.\n");

    add_item(({"sconce","torch"}),
    "There is a single sconce hanging from the wall with a lit torch "
    +"resting in it. "
    +"The light is enough to brighten the otherwise dark room.\n");

    add_item(({"door","wooden door"}),
    "The wooden door lies to your west, thick, firm and sealed shut "
    +"by a big heavy "
    +"log lodged between it and the rest of the room. It would lead "
    +"outside to the "
    +"yard of the keep. \n");

    add_item(({"wind","winds"}),
    "The winds cannot be felt here, but their presence is still "
    +"obvious due to the "
    +"strong sounds coming from outside.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "o9", "east");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
