inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route");
   set_long("You are journeying along the Caravan Route.\n"+
      "West the road reaches the beginning of a narrow valley, which eventually "+
      "leads towards the exalted city of Kabal. All about you are the "+
      "mountains of the Hespyre range, however the ones in your immediate "+
      "surrounding are not as high as those further west, indicating the "+
      "eastern side of the mountain range. Virtually lost amid the towering "+
      "heights of the mountains are the no less impressive redwoods, that "+
      "blanket the lower slopes of the range. The Caravan Route continues "+
      "to the east, eventually leading into the the great Kalad waste.\n");
   add_item(({"caravan route","route","road"}),"A cobblestoned roadway "+
      "that is worn and cracked due to heavy usage and the effects of time "+
      "and the weather.\n");
   add_item(({"valley"}),"A narrow indentation between the mountain "+
      "range with sheer walls.\n");
   add_item(({"mountains","mountain","hespyre range","range","mountain range"}),
      "Craning your neck to take in the full sight of the mountains, their "+
      "sheer size and cold beauty make you feel as insignificant as a bug "+
      "compared with a human being. The mountains of the range cast a dark "+
      "shadow over the land.\n");
   add_item(({"impressive redwoods","lower slopes","impressive redwood","lower slope","slopes","slope","redwoods","redwood"}),
      "Giant redwood trees, as large as twenty feet across at the base "+
      "cover the lower slopes of the mountains. On the higher slopes, thin "+
      "blankets of snow are visible.\n");
   add_item(({"sheer walls","sheer wall","walls","wall"}),"The "+
      "unclimbable sides of the mountains.\n");
   add_exit(CPASS(w16),"west",0,2,1);
   add_exit(CPASS(goblin/g2),"east",0,2,1);
}
