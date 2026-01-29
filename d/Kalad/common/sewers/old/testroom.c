inherit "/d/Kalad/nroom_std";

#include "/d/Kalad/defs.h"

string kabal_test();

create_room()
{
   ::create_room();
    set_short("Testing Room");
    set_long(BS(
       "This is the testroom for this directory where we " +
       "can test changes to the domain/district/area. " +
       "This room is @@kabal_test@@ the city of Kabal. " +
       "\n"));

   hear_bell = 2;
   add_prop(ROOM_I_INSIDE,1);
}


string
kabal_test()
{
   if (IN_CITY)
      return "in";
   else
      return "not in";
}
