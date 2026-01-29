inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Valley's End");
   set_long("A barren valley spreads out before you, nearly filling your "+
      "entire field of view. There is little in the way of vegetation here, "+
      "with only a few small scrubs here and there among dry grass. Further "+
      "west a huge chasm lies, that is where the valley ends in a sheer "+
      "drop to the very bottom of the chasm. Towering above it all are the "+
      "great Hespyre mountains, which cast a dark shadow across the land. The "+
      "vale continues to the east.\n");
   add_item(({"vegetation","scrubs","grass"}),"The floor of this valley is "+
      "covered in short dry grasses with the occasional bushy scrub here "+
      "and there.\n");
   add_item(({"chasm"}),"An enormous rift within the earth, it completely "+
      "prevents passage westward. The chasm stretches far to the north and "+
      "south, into the horizon. Straining your eyes you believe you can make "+
      "out the western side, which seems to be covered in forests.\n");
   add_item(({"forests","forest"}),"It appears as a thin green line across "+
      "the vast expanse of the chasm.\n");
   add_item(({"great hespyre mountains","hespyre mountains","mountains","mountain"}),
      "They tower far above the surrounding landscape, dwarfing "+
      "everything in the land with their size and splendor. So great is "+
      "their height that they seem to block out the sky itself.\n");
   add_exit("/d/Kalad/common/wild/pass/w20", "east",0,2);
}
init()
{
   add_action("search","search");
   add_action("climb","climb");
}

search(string str)
{
   notify_fail("Search what?\n");
   if (str != "chasm") return 0;
   write("You start to search the chasm.\n");
   set_alarm(4.0,0.0,"search_result");
   return 1;
}
search_result()
{
   write("You find a small path that might be climbable.\n");
}
climb(string str)
{
   notify_fail("Climb what?\n");
   if(!str || str!="path") return 0;
   if(TP->query_skill(SS_CLIMB)<20)
      {
      write("You start to climb, but soon realise "+
         "it is too hard for you.\n");
      return;
   }
   write("You start to climb along the small path.\n");
   TP->move_living("climbing down the chasm",CPASS(dwarf/chasm1),1);
   return 1;
}
