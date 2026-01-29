#include "defs.h"
inherit THWIL_BASE_ROOM;
inherit "/lib/unique";

void create_thwil_room()
{
   set_short("Alley");
   set_long("The alley leads east into the harbour "+
      "and northwest into the small, and only, town at Roke, "+
      "Thwil. Apart from other cities' dark " +
      "harbour alleys this one feels not threatening at all"+
      ", the cold, damp air makes you feel relaxed and peaceful. " +
      "There is a feeling of "+ 
      "magic surrounding you. \n");
   
   add_exit(THWIL + "t1" , "northwest" , 0);
   add_exit(THWIL + "h4" , "east" , 0);
   STREET;
}

