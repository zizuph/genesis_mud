inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("On the salt flat");
   set_long("The flat, empty landscape of the Great Salt Flat spreads "+
      "out before you, stretching to the distant horizon. The ground below "+
      "is smothered by a thick layer of salt crystals, which blindingly "+
      "reflect the harsh light of the Kaladian sun. Nothing grows here, for "+
      "this place is truly a wasteland.\n");
   add_item(({"flat landscape","empty landscape","landscape","great salt flat","great flat","salt flat","flat"}),
      "A burning hot wasteland within the greater wasteland of the Great Kalad "+
      "Waste.\n");
   add_item(({"distant horizon","horizon"}),"A thin line far in the distance.\n");
   add_item(({"ground"}),"Littering the ground are hundreds upon "+
      "hundreds of salt crystals, glinting in the harsh light.\n");
   add_item(({"thick layer","layer","salt crystals","salt crystal","crystals","crystal"}),
      "The formations of salt cover the ground in every direction you "+
      "look. Perhaps centuries ago, this was the site of a lake or other body "+
      "of water. Now however, it is nothing but a wasteland.\n");
   add_item(({"kaladian sun","sun"}),
      "As you gaze up at it, you are nearly blinded by its brilliance!\n");
   add_exit(CPASS(desert/salt/s25),"north",0,4);
   add_exit(CPASS(desert/salt/s23),"east",0,4);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/salt_mar));
      ob1 -> move_living("M",TO);
      tell_room(TO,"The salt crystals before you shift slightly.\n");
   }
}
