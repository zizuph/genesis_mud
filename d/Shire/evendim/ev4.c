inherit "/d/Shire/eastroad/std/er_base.c";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

#define EXIT1 EVENDIM_DIR + "ev3","southwest",0,1
#define EXIT2 EVENDIM_DIR + "ev5","northwest",0,1
#define EXIT3 "/d/Shire/eastroad/girdley/girpath3","east",0,1

void add_stuff();

void
create_er_room()
{
    area = "in";
    areaname = "the hills of Evendim";
    land = "the Shire";
    areatype = 1;
    areadesc = "rolling hill";
    grass = "blue-green";
    extraline = "The rolling hills become steeper the farther "+
      "north you go. A small clump of bushes is the main landmark "+
	"here.  The track leads northwest and southwest, while "+
	  "a small path goes east.";
    add_item(({"hill","hills","rolling hills"}),
	     "They are covered with a blue-green grass, lending "+
	     "to their height by a small amount.\n");
    add_item(({"clump","small clump","bushes","bush"}),
	     "The small clump of bushes stands out against the "+
	     "stark rolling hills covered only with grass.\n");
    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
    set_noshow_obvious(1);

    add_stuff();
}

void
add_stuff()
{
    object animal;

    if(!present("wasp"))
    {
       animal = clone_object(EVENDIM_DIR + "npc/wasp");
       animal->move(TO);
    }
}
 
void
reset_shire_room()
{
   add_stuff();
}


