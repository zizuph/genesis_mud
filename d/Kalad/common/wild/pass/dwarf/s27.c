inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("From here you can see a large ruin "+
      "westwards, while the littered road continues "+
      "north, southwest and southeast to what looks like a small "+
      "plaza. Northeast another ruin "+
      "lingers on the edge of your lightsource, but looks "+
      "so destroyed that you doubt you can enter it.\n");

   add_item(({"littered","refuse","rubble"}),
      "It is all over this once proud road.\n");
   add_item(({"building","temple","block","blocks","stone blocks","roof","walls"}),
      "Most of the western ruin has decayed into a rubble of broken stones, "+
      "but some of the walls still stand tall and seems to even hold up "+
      "a roof.\n");
   add_item("road","The road was once skillfully constructed by "+
      "using large, flat stones that was put edge to edge in "+
      "marvellous patterns. But now its all cracked and ruined. "+
      "Several stones lacks and the ones still here have suffered "+
      "from long time of decay.\n");

   add_exit(CPASS(dwarf/temple/t1),"southeast");
   add_exit(CPASS(dwarf/s28),"southwest");
   add_exit(CPASS(dwarf/s26),"north");

   set_noshow_obvious(1);
}

