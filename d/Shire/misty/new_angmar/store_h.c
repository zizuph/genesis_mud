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
   set_long("This is the store room for the shop. Travelling supplies " +
        "for the Army were stored here. now the room is bare from looters.\n");

   add_exit(NEW_ANGMAR + "store_r", "west");

}

