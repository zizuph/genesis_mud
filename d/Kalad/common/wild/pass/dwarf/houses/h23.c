inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat - some houses */

void
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("within a hallway, in Underhome");
   set_long("You walk along a hallway, cut into the rock. The walls "+
      "is plain, but wellcrafted some hundred years ago. Some torches "+
      "has been placed here, lighting up the cavern. "+
      "You see the entrances of several smaller caves that "+
      "you believe must be occupied with families.\n");

   add_item(({"house","houses","caves"}),"They are small caves "+
      "that propably is occupied "+
      "by a family or a single deep dwarf. Weak red light streams "+
      "out from the entrances.\n");
   add_item("walls","The walls are smooth to the touch, but fairly "+
      "uninterresting.\n");
   add_item("torches","They emit a weak light.\n");

   add_exit(CPASS(dwarf/houses/h24),"northwest","@@walk");
   add_exit(CPASS(dwarf/houses/h25),"northeast","@@walk");
   add_exit(CPASS(dwarf/houses/h26),"southeast","@@walk");
   add_exit(CPASS(dwarf/houses/h21),"southwest");
}

walk()
{
   write("You enter one of the caves.\n");
   return 0;
}
