inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include <macros.h>

#define EXIT1 EVENDIM_DIR + "ev1","south",0,1
#define EXIT2 EVENDIM_DIR + "ev3","northeast",0,1

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
    extraline = "The hills of Evendim rise somewhat and begin "+
      "to spread out in all directions.  South is the East "+
	"Road.  Northeast will lead you farther into the North "+
	  "Farthing of the Shire.";
    add_item(({"hill","hills"}),
	     "The hills are blue-green from the grass that grows "+
	     "on them.\n");
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
