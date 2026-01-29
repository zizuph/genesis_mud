inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the endless sand dunes");
   set_long("All around you, in great sloping mounds are "+
      "the huge glittering ridges of the sand dunes. "+
      "The loose sand that fills your parched throat makes travel through "+
      "this harsh clime extremely difficult, for "+
      "it seems as if you sink lower and lower with each step, and even "+
      "the smallest of sand dunes is a hindrance to travel. "+
      "A particularly massive sand dune lies directly to the east. Along "+
      "with the smaller dune to the west, it forms a narrow depression "+
      "upon which you are located, leaving but two ways out, to the "+
      "northwest and southwest. "+
      "The scorching rays of the Kaladian sun hammer down on the dunes "+
      "all about you, so intense is the heat that ripples of air are "+
      "clearly visible.\n");
   add_item(({"great sloping mounds","great mounds","sloping mounds","mounds","mound","huge glittering ridges","huge ridges","glittering ridges","ridges","sand dunes","sand dune","dunes","dune"}),
      "Formed from the continual action of the harsh desert winds, the great "+
      "collections of sands are ever-shifting in the landscape, threatening "+
      "anything of permanence with ignoble burial.\n");
   add_item(({"loose sand","sand"}),"The tiny, fine granules slip through "+
      "your grasp.\n");
   add_item(({"kaladian sun","sun"}),"The harshly brilliant orb hangs "+
      "in the sky, scorching the land beneath it with its rays of light.\n");
   add_item(({"way","ways"}),"Nothing but depressions among the sand dunes.\n");
   add_item(({"massive sand dune"}),"The great mass of sand reaches "+
      "skyward dozens of feet, appearing as a looming, and faintly "+
      "threatening mass in the east.\n");
   add_item(({"smaller dune"}),"It appears as nothing more than a pile "+
      "of sand when compared with the dune in the east.\n");
   add_item(({"narrow depression","depression"}),"Where you presently "+
      "are, of course.\n");
   add_exit(CPASS(desert/sand/d5),"northwest",0,3);
   add_exit(CPASS(desert/sand/d12),"southwest",0,3);
set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
if(!ob1)
{
ob1 = clone_object(CPASS(npc/d_snake));
ob1 -> move_living("M",TO);
tell_room(TO,"A rattling sound alerts you to a rattler snake's presence.\n");
}
}
