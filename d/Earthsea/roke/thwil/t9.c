#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("Street");
   set_long("This is the northern part of Thwil. " +
      "Although it is a small city, the usual shouts "+
      "of merchants competing for customers can be heard mixed "+
      "up with the sound of sheep. You see a shop full of glassware "+
      "containing different kinds of strangely coloured bubbling " +
      "liquids on the north side of the street. The street continues " +
      "downhill to the east, and uphill to the west.\n");
   
   add_exit(THWIL + "alchemist" , "north" , 0, 0);
   add_exit(THWIL + "ta" , "east" , 0, 0);
   add_exit(THWIL + "t8" , "west" , 0, 2);
   
   STREET;
}



