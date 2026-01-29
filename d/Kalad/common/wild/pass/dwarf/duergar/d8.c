inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("You are within an old ruin. Large blocks of granite that once "+
      "held up the stone-roof lies scattered around in a random order, "+
      "making it hard to walk in here. Still, you notice signs of life in "+
      "here. The odd gnawed bone, scraps of refuse and dry crumbles lies "+
      "next to broken weapons and torn-up clothes. "+
      "There seems to be possible to walk north, northeast, east and "+
      "southwest, but the "+
      "other ways are closed off by the ruins.\n");
   add_item(({"crumbles","refuse","bone","bones","rubble"}),
      "They lie scattered around in here along with the rubble of stone "+
      "that once was part of an impressive building.\n");
   add_item(({"block","blocks","stone blocks","roof","walls"}),
      "Most of the building has decayed into a rubble of broken stones, "+
      "but some of the walls still stand tall and seems to even hold up "+
      "a roof further east.\n");
   add_item(({"weapons","clothes","torn-up","broken weapons"}),
      "The weapons and clothes seems to have been fairly newly dropped, "+
      "but all look very useless.\n");
   add_item(({"building","buildings"}),
      "You are not really sure what this building once housed, but you "+
      "guess it once was some kind of temple.\n");

   add_exit(CPASS(dwarf/duergar/d9),"southwest");
   add_exit(CPASS(dwarf/duergar/d7),"north");
   add_exit(CPASS(dwarf/duergar/d12),"northeast");
   add_exit(CPASS(dwarf/duergar/d11),"east");

   set_noshow_obvious(1);
}
