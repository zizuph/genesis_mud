/* This is example room with warfare implemented
 * YOU MUST NOT LOAD IT UP else you can make some area unconquerable!
 * if you happen to load it up - destruct it and room will auto-unregister
 * itself from warfare (probably) Do not leave it loaded up - if there will be
 * any warfare npc in it - you are going to be hanged :)
 */

#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/std/room";
inherit CONQUER_BASE


void
reset_krynn_room()
{
    if (gAreaName)
      reset_conquer_room();
    else
      ::reset_krynn_room();
}


create_krynn_room()
{
    set_short("a test room");
    set_long("This is a test room.\n");
    set_area_name("Solace Area");

    set_alarm(1.0,0.0,reset);
}

void
init()
{
    init_conquer();
    ::init();
}
