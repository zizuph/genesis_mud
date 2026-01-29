#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("Street");
   set_long("You stroll along a tidy and clean street in " +
      "the center of Thwil. " +
      "The smell of fresh herbs linger in the air. "+
      "To the north a winding street takes you up to a hill. "+ 
      "There is a herb shop to the east.\n");
   
   add_exit(THWIL + "t8" , "north" , 0);
   add_exit(THWIL + "herb" , "east" , 0);
   
   STREET;   
}







