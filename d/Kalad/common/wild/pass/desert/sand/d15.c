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
      "A large sand dune lies to the west and south while a smaller dune "+
      "lies just to the north. A way past the dunes can be discerned to "+
      "the northwest, northeast and southeast. "+
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
   add_item(({"large sand dune"}),"A great, hill-sized mound of shifting "+
      "sand.\n");
   add_item(({"smaller dune"}),"The size of a small hill, the great "+
      "mound of sand appears to shift before your eyes from the constant "+
      "presence of the wind.\n");
   add_item(({"way"}),"A passage through the sand dunes.\n");
   add_exit(CPASS(desert/sand/d10),"northwest",0,3);
   add_exit(CPASS(desert/sand/d11),"northeast",0,3);
   add_exit(CPASS(desert/sand/d16),"east",0,3);
   add_exit(CPASS(desert/sand/d21),"southeast",0,3);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/sand_mar));
      ob1 -> move_living("M",TO);
      tell_room(TO,"The sand before you shifts slightly.\n");
   }
}
