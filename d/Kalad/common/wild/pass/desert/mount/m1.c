inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("In the mountains");
   set_long("An abundance of slate-grey rocks surrounds you on all sides, "+
      "making the world seem composed solely of mountainous terrain. "+
      "You are travelling on a rocky path that winds its way uphill to the "+
      "northeast and downhill to the southwest, where it intersects with the "+
      "Caravan Route. The harsh rays of the Kaladian sun beat down on you "+
      "from above, hindering your movement.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"rocky path","path"}),"A rugged trail that winds its "+
      "way through this rocky terrain.\n");
   add_item(({"caravan route","route"}),"A hazy, indistinct line in the "+
      "distance.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly blind you!\n");
   add_exit(CPASS(desert/d24),"southwest","@@msg",4);
   add_exit(CPASS(desert/mount/m2),"northeast",0,4);
}
msg()
{
   write("You step back onto the Caravan Route, a swirl of dust heralding "+
      "your arrival.\n");
   return 0;
}
