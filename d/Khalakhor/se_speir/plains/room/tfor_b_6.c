// temp forest room - Zima
#include "plains.h"
inherit "/d/Khalakhor/se_speir/plains/room/tforbase";
inherit SR_DIR+"lib/branchcmd";

void reset_room() { set_numbranches(2); }

void create_khalakhor_room()
{
   create_tforest();
   add_item("trees",
      "They are tall and straight, mostly pine, their branches blocking "+
      "most of the sunlight. There is a small thorny tree or shrub "+
      "growing amongst the pines.\n");
   add_item(({"plum","shrub","wild plum","small tree","thorny tree"}),
      "It is a small thorny tree, really a shrub, with white flowers "+
      "and burgundy colored fruits. It looks like a wild plum.\n");
   add_item(({"plum","plums","fruit","fruits"}),
      "They are burgundy colored plums hanging on the thorny shrub. "+
      "They don't look ripe.\n");
   add_cmd_item(({"plum","fruit","plum from shrub","fruit from shrub"}),
      ({"take","get","pick","pluck"}),
      "They are not ripe enough to pick.\n");
   set_branchnum(8); // plum
   set_numbranches(2);
   add_exit(PLAINS+"tfor_b_3","southeast");
   add_exit(PLAINS+"tfor_b_8","northeast");
}

void init()
{
   ::init();
   add_action(&break_branch(),"break");
}
