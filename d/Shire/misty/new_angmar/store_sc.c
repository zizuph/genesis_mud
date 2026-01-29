/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */


inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"

void
create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop. It was the main " +
        "room for holding weapon and armours the Army used in their battles. \n");

   add_exit(NEW_ANGMAR + "shop", "west");
   add_exit(NEW_ANGMAR + "store_r", "east");


}
