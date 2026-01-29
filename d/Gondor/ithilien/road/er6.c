#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("central eastern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The long straight road climbs the slightly sloping hills "+
    "towards the east, while it makes its way down into the west. Green "+
    "and fair forests stretch out as far as you can see to the north and "+
    "beyond the foul-reeking stream to the south. "+
    "The eastern horizon is dominated by the grey and ominous mountains "+
    "that mark the border to Mordor.\n");
  add_item(({"mountains","mountain-range","mountain","ephel duath"}),
    "The mountains named Ephel Duath appear to be dark grey from here.\n"+
    "You judge the mountains to be between 5000 to 7000 feet tall,\n"+
    "and you guess they are only about 6 kilometers away now.\n");
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
  add_item(({"river","morgulduin","stream"}),
    "The Morgulduin runs from the accursed Morgul valley, and is\n"+
    "dark and foul to look upon, and there is a wrenching smell from it.\n");

    add_exit(ITH_DIR + "forest/haradpath1","south",0, 3);
    add_exit(ITH_DIR + "road/er7","east", 0, 3);
    add_exit(ITH_DIR + "road/er5","west", 0, 3);

}

