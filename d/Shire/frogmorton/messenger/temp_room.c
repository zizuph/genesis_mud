/*
 * This is a temporary room where the hobbits are placed 
 * while messages are being 'delivered'. Ever wonder where 
 * all those messengers go when delivering their notes to 
 * other players? The code puts them in rooms like this.
 * By Finwe, February 2002
 */

#include "../defs.h"
 
inherit "/d/Shire/std/room";
 
object sign;
 
void
create_shire_room()
{
   set_short("Temporary room for couriers.\n");
   set_long("Temporary room for couriers.\n"); 
}
