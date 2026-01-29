#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("central");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The long straight road climbs the hillslopes eastwards, and "+
    "slopes down towards the west and the Vale of Anduin. North of the road "+
    "you see the forests of Ithilien, fair and green to look upon. There is "+
    "an ever-present sweet odour of flowers, herbs and pollen in the air, "+
    "only mixed with the foul fumes from the river Morgulduin which runs "+
    "along westward on the south side of the road.");
  add_item("road","This is the long straight road that in the high days of Gondor\n"+
    "had been made to run from the fair Tower of the Sun, Minas Anor, which\n"+
    "now is Minas Tirith, the Tower of Guard, to the tall Tower of the \n"+
    "Moon, Minas Ithil, which now is Minas Morgul in its accursed vale.\n"+
    "The road is well crafted, cobbled with stones and lined with high banks,\n"+
    "going in a straight line east and west.\n");
  add_item(({"forest","forests","woods","flowers","trees","bushes"}),
    "The forests of Ithilien are lovely to look upon, consisting of small\n"+
    "woods of resinous trees, fir and cedar and cypress, oaks and ash-trees,\n"+
    "and among them grows bushes of olive and of bay, junipers and myrtles,\n"+
    "and beautiful sage flowers and marjorams and parsleys, asphodels and lilies.\n");
  add_item(({"river","morgulduin"}),
    "The Morgulduin runs from the accursed vale of Imlad Morgul, and is\n"+
    "dark and foul to look upon, and there is a wrenching reek from it.\n");
  add_exit(ITH_DIR + "road/er4","east",0, 2);
  add_exit(ITH_DIR + "road/er2","west",0, 2);
}

