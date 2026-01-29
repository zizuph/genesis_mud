/* 
 * /d/Kalad/common/wild/pass/w4.c
 * Purpose    : Road
 * Located    : Caravan Route out of Kalad
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
string long;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route");
   set_long("You are travelling along the Caravan Route.\n"+
      "The roadway slowly rises the further you travel northeast, with the "+
      "terrain becoming increasingly mountainous. Your immediate "+
      "surroundings are medium foothills which slowly rise to the towering "+
      "heights of the Hespyre mountains, towards the northeast. Heading "+
      "southwest would take you to the great city of Kabal.\n");
   add_item(({"caravan route","route","roadway"}),"A cobblestoned road "+
      "that has been worn down due to heavy usage and the elements.\n");
   add_item(({"terrain","medium foothills","foothills","foothill"}),"The "+
      "area aside the road is hilly and rocky with hardy-looking grass "+
      "and some trees covering its surface.\n");
   add_item(({"trees","tree"}),"A few pine trees can be seen interspersed among "+
      "the long-grained grass.\n");
   add_item(({"grass"}),"Hardy long-grained grass typical of such hilly "+
      "terrain.\n");
   add_item(({"hespyre mountains","mountains","mountain"}),"The vista to "+
      "the northeast is absolutely breathtaking. Like a wall of solid rock, "+
      "the huge mountain range known as the Hespyre mountains rise like "+
      "giants over the entire area, casting deep shadows upon the land.\n");
   add_exit("/d/Kalad/common/wild/pass/w3", "southwest",0,2);
   add_exit("/d/Kalad/common/wild/pass/w5", "northeast",0,2);
}
void
init()
{
   ::init();
   write("A strong breeze blows past you.\n");
}
