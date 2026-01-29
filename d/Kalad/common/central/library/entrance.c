inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   /* No bell here, the library must remain quiet */
   INSIDE;
   set_short("Entrance to the library");
   set_long("A quiet little entrance room to the Central District Library "+
      "of Kabal. A grand red carpet covers the marble floors while the "+
      "walls themselves seem especially thick, probably to insure that no "+
      "sounds from outside can disturb people within the library. An arched "+
      "doorway leads to the south.\n");
   add_item(({"grand red carpet","grand carpet","red carpet","carpet"}),
      "A thick carpet that muffles the sounds of footfalls.\n");
   add_item(({"walls","wall","ceiling"}),"They look quite thick and "+
      "sturdy, to insure a stable location for the library as well as to "+
      "minimize the amount of sound that enters.\n");
   add_item(({"arched doorway","doorway"}),"A doorway leading south "+
      "into the library proper.\n");
   add_exit(CENTRAL(plaza/sq_east),"northwest",0,-1,-1);
   add_exit(CENTRAL(library/libr),"south",0,-1,-1);
}
