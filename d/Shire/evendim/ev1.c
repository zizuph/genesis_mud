inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#define EXIT1 ER_DIR + "er16n2","south",0,1
#define EXIT2 EVENDIM_DIR + "ev2","north",0,1


void add_stuff();

void
create_er_room()
{
    int i;
    area = "in";
    areaname = "the hills of Evendim";
    land = "the Shire";
    areatype = 1;
    areadesc = "rolling hill";
    grass = "blue-green";
    extraline = "A good ways north of the East Road, the hills "+
      "start to roll more and more.  The flora is rare "+
	"other than grass, but wildlife is not.  A small track "+
	  "goes north, and south will lead back towards Frogmorton.";

    add_item(({"hill","hills"}),
	     "The rolling hills are a blue-green thanks to the grass "+
	     "which grows upon them.  They seem steeper to the north.\n");
    add_item(({"flora","grass","wildlife"}),
	     "The flora that is here, the blue-green grass is typical in "+
	     "the Hills of Evendim which start to rise above the flat "+
	     "grasslands near the East Road.\n");
    add_item(({"track","small track"}),
	     "The small track meanders quite a bit, probably made from "+
	     "habitual travel than any concerted effort to make a trail.\n");
    add_exit(EXIT1);
    add_exit(EXIT2);
    set_noshow_obvious(1);
    add_stuff();
}

void
add_stuff()
{
    object animal;
    if(!present("ant"))
    {
      animal = clone_object(EVENDIM_DIR + "npc/ant");
      animal->move(TO);
    }
}
 
void
reset_shire_room()
{
   add_stuff();
}
