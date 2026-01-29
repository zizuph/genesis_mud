inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("All around you there are cracked pillars and tombstones "+
      "with just a few of them managing to stay up the way they were "+
      "rised with skilled hands some centuries ago. Grey moss lies "+
      "like a carpet over them. When you look around "+
      "you notice a path snaking itself west, east and southwest "+
      "through all the rubble of this ruined graveyard.\n");
   add_item(({"tombstone","tombstones","stones","pillars","pillar","rubble"}),
      "Just a few whole stones can be seen but the letters on them are "+
      "unreadable. Most of them are cracked and ruined "+
      "after decades of decay.\n");
   add_item(({"moss","grey moss"}),"Covering the stones like a carpet, "+
      "the moss tells a tale of years without much disturbance.\n");
   add_item(({"yard","graveyard"}),"This place must be an old graveyard, "+
      "dating back to the terrible wars of ancient times when the dwarves "+
      "lost so many of their men in violent combat.\n");
   add_item(({"path","street","streets"}),"Among all the rubble you can "+
      "walk along a small trodden path that the dwarven boots has "+
      "managed to clear.\n");
   add_exit(CPASS(dwarf/g1),"east");
   add_exit(CPASS(dwarf/g3),"west");
   add_exit(CPASS(dwarf/g4),"southwest");
   set_noshow_obvious(1);
}
