#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
   set_short("Alley");
   set_long("This is an alley that takes you between the "+
      "harbour just east from here, and the town to the west. "+
      "Some fishing nets have been hung up to dry in the sun. "+
      "You skillfully cruise between them as you pass by. "+
      "The air is cold and damp. \n");
   
   add_item(({"net","nets","fishing nets"}),"A closer inspection of "+
      "the nets reveals that they are indeed well used. The big "+
      "angry holes in the nets leave you ironically wondering "+
      "if they shouldn't switch from catching fish to whales instead. \n");
   
   add_exit(THWIL + "a2" , "west" , 0);
   add_exit(THWIL + "h9" , "east" , 0);
   STREET;
}







