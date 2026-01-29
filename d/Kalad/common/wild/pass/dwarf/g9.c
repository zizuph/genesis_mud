inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
object ob1;

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("All around you there are cracked pillars and tombstones "+
      "with just a few of them managing to stay up the way they were "+
      "rised with skilled hands some centuries ago. When you look around "+
      "you notice a path snaking itself north and southeast "+
      "through all the rubble of this ruined graveyard. North you will "+
      "enter other parts of this yard while southeastwards you see the "+
      "ruined gate leading out of this place.\n");
   add_item(({"tombstone","tombstones","stones","pillars","pillar","rubble"}),
      "Just a few whole stones can be seen but the letters on them are "+
      "unreadable. Most of them are cracked and ruined "+
      "after decades of decay.\n");
   add_item(({"yard","graveyard"}),"This place must be an old graveyard, "+
      "dating back to the terrible wars of ancient times when the dwarves "+
      "lost so many of their men in violent combat.\n");
   add_item(({"path","street","streets"}),"Among all the rubble you can "+
      "walk along a small trodden path that the dwarven boots has "+
      "managed to clear.\n");
   add_item("gate","Its is an old ruined iron-gate that once had some "+
      "decorations to it, but time has made sure to destroy them along "+
      "with the rest of this graveyard.\n");
   add_exit(CPASS(dwarf/g8),"north");
   add_exit(CPASS(dwarf/s3),"southeast");
   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(ob1))
   {
      ob1 = clone_object(CPASS(dwarf/npc/ghoul));
      ob1 -> arm_me();
      ob1->move_living("M",TO);
      tell_room(TO,"A wift of decay seems to envelope you from behind.\n");
   }
}
