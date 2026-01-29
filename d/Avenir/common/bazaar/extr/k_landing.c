// file name:  k_landing
// creator:    Cirion, May 1996
// last update:
// purpose:    This is where the ship to Kalad docks.
// note:
// bug(s):
// to_do:

inherit "/std/room";
#include "../bazaar.h"

object    ship;

create_room()
{
   set_short("western landing");
   set_long("A long sturdy landing extends "
           +"out over the black water here. There "
           +"is a large post where a boat can tie "
           +"up, and to the east the landing continues.\n");
   AI(({"dock","landing","pier","ground","floor"}),
            "The pier is "
           +"made of sturdy wood, and seems to "
           +"be quite old.\n");
   AI(({"water","sea","dark sea","ocean"}),"The vast "
           +"dark sea stretches out to the north into "
           +"blackness. It is calm and still, its "
           +"murky black surface undisturbed.\n");
   AI(({"street","road"}),"The quiet street runs to the "
           +"north.\n");
   AI(({"source","ceiling","cavern","cave"}),"The "
           +"great ceiling of Sybarus cavern "
           +"is high above. From it, you can make "
           +"out the dim gloaming of the Source.\n");

   HAS_WATER;
   
   add_prop(NO_BAZAAR_TELLS, 1);

   AE(BAZAAR + "intr/d_landing", "east");

#if 0
   ship = clone_object(SHIP + "kalad/ship");

     ship->move(this_object(), 1);
     ship->start_ship();
#endif
}
