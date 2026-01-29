inherit "/d/Shire/eastroad/std/er_base.c";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "fairroad3","southwest"



void
create_er_room()
{
   area = "in";
   areaname = "Michel Delving";
   land = "the Shire";
   areatype = 1;
   areadesc = "field";
   grass = "green";

   extraline = "This Fair Field is fair indeed, not just because the "+
   "Midsummer's Fair is held here, but also because it is a peaceful, "+
   "quiet place.  A few small bushes dot the field.  An obstinate stump "+
   "stands between two willow trees.  A large iron fence runs around the " +
   "field behind the stump.  Set in the fence is a large gate.";

   add_item(({"small bushes","bushes","bushes"}),
   "The bushes appear to be of the huckleberry family.\n");

   add_item(({"stump","obstinate stump","oak stump"}),
   "This old stump is solid and about five feet in diameter.  Counting the rings "+
   "you see the tree the stump was made from was quite old.\n");

   add_item(({"tree","trees","two willow trees","willow tree","willow trees"}),
   "The two willow trees stand as guardians to the old oak stump, but they "+
   "tower more than forty feet above the ground.\n");

   add_item(({"field","fair field","fair"}),
   "This is the Fair Field, where every seven years a new Mayor of "+
   "the Shire is chosen.\n");

   add_item(({"path","grey path","grey gravel path"}),
   "The gravel path starts here, leading west, covering beautiful green grass.\n");

    add_item(({"fence", "large iron fence", "iron fence"}),
        "It is forged of iron and encloses a large part of the field. The fence is waist high, but seems impolite to climb over it unless you're invited. \n");
    add_item(({"large gate", "gate", "large iron gate", "iron gate""}),
        "It is an opening in the iron fence. The gate can be opened to allow visitors through it to attend parties.\n");
    

   add_exit(EXIT1);

//   set_noshow_obvious(1);
}
