inherit "/d/Shire/eastroad/std/er_base";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
 
#include "local.h"
#define EXIT1 ER_BASE_DIR + "girdley/isle1","east","@@give_message"
#define EXIT2 ER_BASE_DIR + "girdley/girpath2","south",0,1
#define EXIT3 EVENDIM_DIR + "ev4","west",0,1
 
 
int
give_message()
{
   write("You splash out into the slow-moving water and make your way "+
   "across the river to the island.\n");
   return 0;
}
 
 
void
create_er_room()
{
   area = "just west of";
   areaname = "Girdley Island";
   land = "the Shire";
   areatype = 7;
   areadesc = "overgrown river path";
   grass = "green";
 
   extraline = "The trees widen somewhat here and it seems an old track "+
   "once led to the west, over some slight hills.  East, as the river winds "+
   "its way past, you can see Girdley Island and a ford leading to it is here."+
   " Dense vines block the path northward, far to the south is the Brandywine "+
   "bridge.";
 
   add_item(({"vines","vine","path"}),
   "The path which is overgrown largely here, is overgrown completely "+
   "to the north- it is impassable on this side of the river, thanks to the "+
   "long curly vines that are all around.\n");
   add_item(({"trees","tree"}),"The trees are mostly birches and willows, "+
   "tall enough to be several decades old at the least.\n");
   add_item(({"track","west","old track"}),"The old track that disappears "+
  "on the other side of this path seems to have been a wagon trail, but "+
  "has fallen into disuse.\n");
   add_item("water","The water is brown and muddy, flowing slowly by.\n");
   add_item(({"bank","river","brandywine river"}),
   "The bank on this side is narrow and slightly muddy along the river, which "+
   "flows southward towards Sarn Ford.  The ford to the east seems to be "+
   "large enough to get a wagon and horse-team across to the island on.\n");
   add_item(({"island","girdley island"}),
   "The island is roughly triangular in shape and nearer to this bank than the "+
   "far bank of the Baranduin.\n");
 
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);

     set_up_herbs( ({   GONDOR_HERB_DIR + "tuo",
                        GONDOR_HERB_DIR + "lothore",
                        SHIRE_HERB_DIR  + "columbine", 
                        SHIRE_HERB_DIR  + "chives",
                        GONDOR_HERB_DIR + "raspberry",
                        
                        }),
                  ({"river","ground","riverbank","flowers","path","track"}), 3);


    set_drink_from( ({ "river", "brandywine", "baranduin", }) );

}
