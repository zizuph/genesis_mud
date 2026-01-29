#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("Street");
   set_long("You are walking alongside an ordinary street. "+
      "A steep hill rises above you to the west and slopes downwards "+
      "to the north and southeast. " +
      "There seem to be a lot of people " +
      "north from here.\n");
   
   add_exit(THWIL + "t2" , "west" , 0, 1);
   add_exit(THWIL + "t7" , "north" , 0, 1);
   add_exit(THWIL + "a1" , "southeast" , 0, 1);
   
   STREET;   
}







