/* 
 * /d/Kalad/common/wild/pass/w5.c
 * Purpose    : Road
 * Located    : Caravan Route
 * Created By : Antharanos Bet he couldnt tell you
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
      "The roadway rises dramatically towards the northeast, with the "+
      "terrain changing from the relatively low foothills to the towering heights "+
      "of the Hespyre mountains. Your immediate surroundings are a series "+
      "of large foothills which eventually form the base of the Hespyre "+
      "mountain range. Patches of forestland cover the hills around you. "+
      "The route southwest would eventually lead you to the city of Kabal.\n");
   add_item(({"caravan route","route","roadway"}),"A cobblestoned road "+
      "that has been worn down due to heavy usage and the elements.\n");
   add_item(({"terrain","large foothills","foothills","foothill","hills"}),"The "+
      "area aside the road is hilly and rocky with hardy-looking grass "+
      "and many trees covering its surface.\n");
   add_item(({"forestland","trees","tree"}),"Dark, and extremely huge "+
      "redwood trees mark the beginning of the lower slopes of the "+
      "Hespyre mountains. Their shadowy depths undoubtedly hold unexpected "+
      "surprises for anyone foolish enough to venture within.\n");
   add_item(({"grass"}),"Hardy long-grained grass typical of such hilly "+
      "terrain.\n");
   add_item(({"hespyre mountains","mountains","mountain"}),"The vista to "+
      "the northeast is absolutely breathtaking. Like a wall of solid rock, "+
      "the huge mountain range known as the Hespyre mountains rise like "+
      "giants over the entire area, casting deep shadows upon the land.\n");
   add_exit("/d/Kalad/common/wild/pass/w4", "southwest",0,2);
   add_exit("/d/Kalad/common/wild/pass/w6", "northeast",0,3);
}
void
init()
{
   ::init();
   write("A gust of wind nearly knocks you down.\n");
}
