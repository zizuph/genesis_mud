// street through the village
#include "defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/guilds/sean-rhian/defs.h"
inherit STREET;
inherit HERBSEARCH;
inherit SR_LIB+"branchcmd";
 
public int* query_local_coords() { return ({6,6}); }
 
public void reset_room()
{
   set_searched(0);
   numbranches=2;
}
 
create_khalakhor_room()
{
   create_common();
   set_short("On the common greens of a quaint village");
   set_long("You are standing on the greens of the common, a small squared "+
            "grassy area bordered with flowerbeds and encircled by the "+
            "street on all four sides. It is sort of a park in the "+
            "middle of town, used for town gatherings and as just a "+
            "nice place to be. A rather large tree grows in the middle "+
            "of the greens, the only one you've seen in town.\n");
   add_item("tree",
       "It is a tree with fleshy spiny green leaves and red berries, "+
       "probably planted here for decorative purposes, as it is a rather "+
       "nice tree to behold. You recognize it as a holly tree, though a "+
       "rather tall one.\n");
   add_item(({"berry","berries"}),
       "There are several small red berries on the tree, though they "+
       "don't look completely ripened.\n");
   add_cmd_item(({"berry","berry from tree"}),"pick",
       "The berries on the tree are not ripe enough to pick. The birds "+
       "must have taken all the good ones, though they may have "+
       "dropped some.\n");
   add_cmd_item(({"tree","holly"}),"climb",
      "You could get arrested for doing that here!\n");
 
   add_exit("street6n", "northwest");
   add_exit("street4n", "northeast");
   add_exit("street6s", "southwest");
   add_exit("street4s", "southeast");
 
   set_branchnum(2); // for holly
   set_up_herbs(({GOHERB+"holly"}),({"here","tree"}), 2);
   reset_room();
}
 
public void init()
{
   ::init();
   add_action(&break_branch(),"break");
}
