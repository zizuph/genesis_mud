inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("path");
   set_long("You are standing on a small shelf on the cliffside wall. "+
      "Its not big, but there is enough space here for a bush "+
      "to grow to a fairly large size.\n");
   add_item(({"vegetation","scrubs","bush"}),"The shrubs cling "+
      "for their lives on the wall, while that larger "+
      "bush seems to have better conditions for life.\n");
   add_item(({"cliffside"}),"An enormous wall, completely "+
      "prevents passage westward. The cliffside stretches far to the north and "+
      "south, into the horizon. Straining your eyes you believe you can make "+
      "out the western bottomside, which seems to be covered in forests.\n");
   add_item(({"forests","forest"}),"It appears as a green ocean.\n");
   add_item(({"great hespyre mountains","hespyre mountains","mountains","mountain"}),
      "They tower far above the surrounding landscape, dwarfing "+
      "everything in the land with their size and splendor. So great is "+
      "their height that they seem to block out the sky itself.\n");
   add_exit("/d/Kalad/common/wild/pass/dwarf/chasm1","up",0,3,1);
}
init()
{
   ::init();
   add_action("search","search");
   add_action("enter","enter");
}
search(string str)
{
   notify_fail("Search what?\n");
   if(str!="bush") return 0;
   write("You start to search the bush.\n");
   say(QCTNAME(TP)+" starts to search the bush.\n");
   set_alarm(4.0,0.0,"result",TP);
   return 1;
}
result(object player)
{
   player->catch_msg("You see a small cave behind it.\n");
}
enter(string str)
{
   notify_fail("Enter what?\n");
   if(str != "cave") return 0;
   write("You crawl inside the cave.\n");
   TP->move_living("crawling into the bush",CPASS(dwarf/chasm3),1);
   return 1;
}
