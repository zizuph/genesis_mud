#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;

void
create_outpost_inside_room()
{
    set_short("In the main barracks.");
    set_em_long("From the simple accommodations that you see before you, you realize " +
        "that this must be the general barracks that regular soldiers use while " +
        "on duty in the outpost. Long rows of cots line the room, each of them " +
        "neatly made. Dim light from the iron lamps attached to the walls dances " +
        "open a table in the middle of the room and the chairs surrounding it. " +
        "There is an archway built into the northern wall, a door in the southern " +
        "wall, and an exit to your west which leads back outside.\n");


    add_item( ({"cots", "cot", "rows", "rows of cots"}),
        "Row upon row of cots line the floor of this room. With their wooden frames " +
        "and thin mattresses, these beds do not look very comfortable. A footlocker " +
        "sits at the foot of each cot.\n");

    add_item( ({"footlocker", "footlockers"}),
        "At the foot of each cot, a small wooden footlocker holds the personal items " +
        "for each guard.\n");

    add_item( ({"table"}),
        "In the middle of a room, a table stand surrounded by wooden chairs. You imagine " +
        "that the guards stationed here spend some of their off time playing cards and " +
        "other assorted games in this room. Scratches mar both the surface and the legs " +
        "of the table.\n");

    add_item( ({"chairs", "simple chair", "wooden chair", "wooden chairs", "chair"}),
        "These simple wooden chairs ring the table in the middle of the room. Even " +
        "with the thin cusions on the seats, they do not look very comfortable.\n");

    add_item( ({"walls", "wooden walls", "rough walls", "rough wooden walls"}),
        "The walls of the room are made from the same wood as the rest of " +
        "the building. Large logs have been placed horrizontally, one on top " +
        "of the other to form a good barrier from the weather.\n"); 
   
    add_item( ({"lamp", "lamps", "iron lamps", "iron lamp", "wall lamp", 
                "wall lamps", "iron wall lamp", "iron wall lamps"}),
        "Iron wall lamps are attached to the walls. Fueled by oil, they cast " +
        "dim light throughout the large room.\n");


    add_exit("yard_09.c","west");
    add_exit("ubrcks.c","north");
    add_door_exit(OUTPOST_DOOR_OBJ, OUTPOST_DIR + "cptnq", "south");
}
