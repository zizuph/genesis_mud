inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Cave");
   set_long("You can barely see within the dark confines of this cave. "+
      "There is a faint light in the west, suggesting an exit, yet for some "+
      "strange reason the light does nothing to illuminate the interior of "+
      "this passage.\n");
   add_item(({"faint light","light"}),"The light is so faint it may have been "+
      "just a figment of your imagination.\n");
   add_item(({"passage","cave"}),"The stone walls of the cave are rough and "+
      "uneven, suggesting that this is a natural rock formation, as opposed to "+
      "it being artificially dug out.\n");
   add_exit(CPASS(underdark/u2),"west","@@check_drowwep",-1,0);
   add_exit("/d/Kalad/common/wild/pass/underdark/u4", "east",0);
}
check_drowwep()
{
   object *ob;
   int i;
   ob = deep_inventory(TP);
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->id("drowwep"))
      {
      write("Your drow weapon disintegrates!\n");
      ob[i]->remove_object();
      return 0;
   }
   write("You pass out into the open air.\n");
   return 0;
}
