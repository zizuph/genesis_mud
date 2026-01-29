#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("barren waste");
    set_area("south");
    set_areaname("the Isengard Valley");
    set_land("Misty Mountains");
    set_extraline("The road leads north through the barren valley of "
      + "Isengard and south along the west bank of the River Isen. "
      + "Further north you can see the tall, dark pinnacle of the "
      + "tower of Orthanc. A large stone is raised here, carved "
      + "in the fashion of a White Hand.");
    add_item(({"hand","white hand","stone"}), BSN(
	"The white stone slab is about 5 feet tall, and carved to "
      + "look like a giant white hand - the symbol of Saruman the "
      + "White, the Ruler of Orthanc."));
    add_item(({"pinnacle","tower", "orthanc", "tower of orthanc", }),
	     BSN("Dark clouds are gathered around the pinnacle of "
	+	 "the tower of Orthanc, concealing the peak from "
	+	 "view. Foul fumes seem to rise from the Circle of "
	+	 "Isengard surrounding the tower. The tower rises "
	+	 "more than 500 feet above the ground, and is "
	+	 "carved out of rock that is black as the night."));
    add_item(({"circle","isengard","Isengard"}),
	     BSN("The Circle of Isengard is the area surrounding the "
	+	 "tower of Orthanc, which is fenced in by a wall of "
	+	 "great height and a sheer outer wall."));
    add_item(({"valley", "river", "isen", "river isen", "road", }),
	     BSN("The road is running through the valley of the Isen "
	+	 "on the west bank of the river, following the river "
	+	 "southwards from the Circle of Isengard to the "
	+	 "Fords of Isen. The valley on both banks of the "
	+	 "Isen has been laid waste, cleansed of trees by "
	+	 "the orcs of Isengard a long time ago."));
	      
    add_exit(ISEN_DIR + "isenroad/isenroad4", "north", 0);
    add_exit(ISEN_DIR + "isenroad/isenroad2", "south", 0);
}

