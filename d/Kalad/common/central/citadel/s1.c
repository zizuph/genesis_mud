/* Citadel Road */
/* Made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
   ::create_room();
   
   set_short("Citadel Road");
   set_long(
      "You stand in front of a mighty Citadel. In awe you bow your head "+
      "but soon rise it again to stare at the tower. You see a huge bronze "+
      "bell in it, and you gather from the sound of it that its the "+
      "one you have heard all over the city.\n");
   
   hear_bell = 3; /* loud: outdoors in the central district */
   
   add_exit(CENTRAL(promenade/s3),"southeast",0,1);
   add_exit(CENTRAL(citadel/entrance),"northwest",0,1);
   
}
