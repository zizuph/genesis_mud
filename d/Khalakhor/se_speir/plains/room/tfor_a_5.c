// temp forest room - Zima
#include "plains.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/defs.h"
inherit "/d/Khalakhor/se_speir/plains/room/tforbase";
inherit SR_DIR+"lib/branchcmd";
inherit HERBSEARCH;

void reset_room() { set_searched(0);  set_numbranches(2); }

void create_khalakhor_room()
{
   create_tforest();
   set_branchnum(4); // hazelnut branch avail here
   set_numbranches(2);
   add_item("trees",
      "They are tall and straight, mostly pine, their branches blocking "+
      "most of the sunlight. There is a small tree with nuts mixed in "+
      "with the pines.\n");
   add_item(({"tree","small tree","shrub"}),
      "It is a small tree, really just a large shrub, growing amongst "+
      "the pines. It has small embracted nuts on it.\n");
   add_item("nuts","There are some on the small tree, though they "+
                   "look too green to pick.\n");
   add_cmd_item(({"nuts","nut","nut from tree"}),"pick",
      "The nuts on the tree look too green to pick. Perhaps some "+
      "have fallen onto the forest floor though.\n");
   add_exit(PLAINS+"tfor_a_4","east");
   set_up_herbs(({KRHERB+"hazelnut"}), ({"here","forest","floor"}), 2);
}

void init()
{
   ::init();
   add_action(&break_branch(),"break");
}
