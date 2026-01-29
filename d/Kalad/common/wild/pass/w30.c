/* 
 * /d/Kalad/common/wild/pass/w30.c
 * Purpose    : Valley setting
 * Located    : Hespyre Mountains
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Clearing");
   set_long("You have reached a clearing within the valley.\n"+
      "This area is almost totally devoid of trees, and plants in general. "+
      "A huge area of the forest has been stripped bare, for nothing grows "+
      "in a circular area with a radius of at least five hundred feet. "+
      "Nothing but bare stone and dirt lies within this clearing. The "+
      "remnants of the forest grow at the edges of the clearing while the "+
      "Hespyre mountains tower above everything, affected by nothing.\n");
   add_item(({"forest","plants"}),"The once proud redwoods of the forest "+
      "look like they've taken a lot of abuse, showing many scars upon "+
      "their barks, and many branches having been broken off.\n");
   add_item(({"bare stone","stone"}),"A few rocks lie around the clearing.\n");
   add_item(({"dirt"}),"The ground is slightly moist, and is covered with "+
      "huge foot prints!\n");
   add_item(({"huge foot prints","foot prints","prints","print"}),"The "+
      "prints are just over three feet long! No ordinary creature could "+
      "have made such marks.\n");
   add_item(({"hespyre mountains","mountains","mountain"}),"The mountains "+
      "around here, although massive compared with the surrounding landscape, "+
      "seem lower in altitude then the rest of the range. They cast dark "+
      "shadows across the land.\n");
   add_exit("/d/Kalad/common/wild/pass/w31", "north",0,2);
   add_exit("/d/Kalad/common/wild/pass/w29", "east",0,2);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if (!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/obj/rock");
      ob1 -> move(TO);
   }
}
