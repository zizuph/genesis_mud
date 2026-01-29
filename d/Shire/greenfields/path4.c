inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 GREEN_DIR + "path5","west","@@west@@"
#define EXIT2 GREEN_DIR + "path3","south",0,1

int
west()
{
    int ran;
    ran = random(50);
    if(ran > 40)  /* 20% failure */
    {
	write("You trip on some rocks and fall down.\n");
	TP->add_fatigue(-10);
	return 1;
    }
    return 0;

}

void
create_er_room()
{

    area = "a good bit from";
    areaname = "Greenfields";
    land = "the Shire";
    areatype = 5;
    areadesc = "valley";
    grass = "green";


    extraline = "Here the twisty path comes to an end and only large stones "+
    "and small boulders cover the dusty ground.  The air is much drier here than "+
    "one might expect nestled in amongst the tight hills.  West is a bend around "+
    "a large hill that stops northward progress, and south is the twisty path.";

    add_item(({"stones","stone","large stone"}),
      "These stones appear to be granite, broken up from a large slab by a great "+
      "heaving of the earth.\n");

    add_item(({"boulder","boulders","small boulders"}),
      "The boulders are chunks of the rocky hillsides that gravity defeated.\n");

    add_item(({"hills","tight hills"}),
      "These tight hills restrict movement- it is a perfect place for an ambush.\n");

    add_item(({"hill","large hill"}),  "The large hill prevents any climbing or "+
      "walking upon.  You must go around it.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);

}


