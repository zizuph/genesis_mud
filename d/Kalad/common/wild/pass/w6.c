/* 
 * /d/Kalad/common/wild/pass/w6.c
 * Purpose    : Mountain passage
 * Located    : North of Caravan Route
 * Created By : Antharanos Shrug
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#define HARD_TO_CLIMB 40
#define DAMAGE 150
string long;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Bend in the Caravan Route");
   set_long("You have reached a bend in the Caravan Route.\n"+
      "From here the roadway travels eastward, through the very heart of "+
      "the mountain range, while the city of Kabal lies in the southwest. "+
      "All about you are the monolithic Hespyre mountains. Now that you are "+
      "within the mountain range, instead of just viewing it from a "+
      "distance, the sheer enormity of their size astounds you beyond "+
      "belief. At this point on the road, sheer cliff faces close in upon "+
      "you from all sides. Besides the Caravan Route, the only other way "+
      "out of this box canyon would be the northwest, where another canyon "+
      "seems to lie. Almost lost among the gigantic mountains are the "+
      "towering redwoods that lie at their base. Their huge canopies nearly "+
      "block out the entire sky.\n");
   add_item(({"caravan route","roadway","road","route"}),"A cobbled "+
      "roadway that is worn down due to heavy usage and the harsh effects "+
      "of weather.\n");
   add_item(({"mountain range","hespyre mountains","range","mountains","mountain"}),
      "Enormous mountains surround you in every direction, the passages "+
      "leading out if this area seem like mere cracks in the rocky facade "+
      "of the range. Their height is so great, that their shadows fall "+
      "upon most of the land, blanketing it in darkness.\n");
   add_item(({"sheer cliff faces","sheer cliff face","cliff faces","cliff face"}),
      "The sides of this box canyon, which you are in are sheer rock faces.  "+
      "On one particular cliff face in the west is what looks like the "+
      "entrance of a cave.\n");
   add_item(({"entrance","cave"}),"A darkened opening in the side of "+
      "a mountain. The only unusual thing about it is that instead of "+
      "opening out to the side, to allow horizontal passage inside, the "+
      "entrance opens out at the bottom, thereby allowing only vertical "+
      "passage inside.\n");
   add_item(({"canyon"}),"The canyon walls are too near one another for you "+
      "to get a clear view of what lies within.\n");
   add_item(({"towering redwoods","canopies","canopy","redwoods"}),
      "All about you lie the massive redwood trees of the Hespyre mountains. "+
      "Their great canopies of leaves form a natural roof over you, "+
      "protecting you from the mountain rains and the relentless sun.\n");
   add_exit("/d/Kalad/common/wild/pass/w17", "northwest",0,3);
   add_exit("/d/Kalad/common/wild/pass/w7", "east",0,3);
   add_exit("/d/Kalad/common/wild/pass/w5", "southwest",0,3);
   add_exit("/d/Kalad/common/wild/pass/shaft", "up", "@@climb",3);
}
void
init()
{
   ::init();
   write("The air is surprisingly still here.\n");
}
climb()
{
   if(TP->query_skill(SS_CLIMB) < random(HARD_TO_CLIMB))
      {
      write("You slip while climbing the sheer cliff face and fall down.\n");
      write("You slam into a group of boulders!\n");
      TP->heal_hp(-DAMAGE);
      say(QCTNAME(TP) + " fell down while trying to climb the cliff face and slammed into some boulders.\n");
      if(TP->query_hp() <= 0)
         TP->do_die(TO);
      return 1;
   }
   write("You manage to scale the cliff face.\n");
   return 0;
}
