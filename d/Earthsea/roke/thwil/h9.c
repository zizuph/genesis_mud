#include "defs.h"
inherit THWIL_BASE_ROOM;
inherit "/lib/unique";

void create_thwil_room()
{
   set_short("pier");
   set_long("You are at the northwest corner of a strange pier. "+
      "It is unnaturally quiet here and you feel that "+
      "although there are not many people around, it would be "+
      "very unwise to disturb the calm of this place. "+
      "The pier continues east and south. An alley to the "+
      "west takes you further into the city. The beach " +
      "adjacent to harbour is to the north.\n");
   add_item("pier","It is a smooth well tended pier, funny not "+
      "any rubbish at all in sight... \n");
   
   add_exit(THWIL + "a3" , "west" , 0);
   add_exit(THWIL + "h6" , "east" , 0);
   add_exit(THWIL + "h8" , "south" , 0);
   add_exit(ROKE_BEACH + "/rooms/beach01", "north");
   BEACH;
}

