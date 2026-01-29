/* Void coded by Lord Rastlin */
/* Copied over for Ansalon by Lord Macker */

inherit "/std/room";
#include "/sys/stdproperties.h"

create_room() {
   set_short("VOID");
   set_long("The void. And remember, magic is useless in the void.\n");
   add_prop(ROOM_I_NO_CLEANUP, 1);
}

