inherit "/std/room";
inherit "/lib/store_support";
#include <wa_types.h>
#include "campdef.h"
 
void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");
 
   add_exit(CAMPDIR + "tcamp1", "east",0);
 
   set_max_values(13, 5);
}
 
 
