/*
 *  Road in Menzobarranzan
 *  -- Finwe, April 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
inherit BASE_COMMON;

void create_menzo_room()
{
	set_short("Along the north mantle");
	set_long(short() + ". The road runs east and west past stalactites that have been carved into ornate columns. They mark the northern end of the city. Houses and shops crowd the wide road, with more noble houses set away in the distance.\n");

    add_all_rooms();
    add_mantle();
    add_houses();

    add_exit("road03", "east");
    add_exit("road01","west");
        
}

void
init()
{
    ::init();
}