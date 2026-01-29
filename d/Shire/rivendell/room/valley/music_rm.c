/*
 * Music room
 * By Finwe, February 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()
{
    set_short("The music room");
    set_long("This is the music room of Imladris. A vast array " +
        "of music scores are kept here as are the many " +
        "instruments which the elves play. Many times during the " +
        "day, elven musicians come here to either pen a song or " +
        "practice an instrument. Their music seems to resonate " +
        "here. The accoustics of the room are perfect as the " +
        "room echoes with your every movement.\n");
 
 
    add_item(({"pillars", "square pillars", "square wooden pillars"}),
        "The pillars are carved of thick trees. They are squared " +
        "and are set into the walls. The pillars are expertly " +
        "decorated with carved leaves.\n");
    add_item(({"music scores", "scores"}),
        "The music scores are written on parchment in a flowing " +
        "handwriting. Unfortunately, you can't read the music " +
        "and can only guess at what it says.\n");
    add_item("parchments",
        "They are of fine paper andlook durable.\n");
    add_item(({"instruments", "many instruments"}),
        "Many instruments line the walls. Some are recognizable " +
        "while others are foreign to you. Nonetheless, they all " +
        "look to be in perfect shape and undoubtably are used " +
        "regulary.\n");
 
    add_exit(VALLEY_DIR + "d_cor01",  "south");
}
