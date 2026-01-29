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
    set_extraline("The long straight road runs up the sloping hills eastwards, "+
    "and slopes down west into the Vale of Anduin. Green and fair forests "+
    "stretch out as far as you can see to the north.  "+
"To the south you notice a small opening.  There is " +
    "an ever-present sweet smell of flowers, herbs and pollen in the air, "+
    "only mixed with the stench from the river which is flowing to the south, "+
    "alongside the road. Further east you see the dark and looming mountain-"+
    "range of the Ephel Duath, the border to Mordor.");
add_item("opening","There is an opening which is large " +
"enough to allow someone to travel south.\n");
  add_item(({"mountains","mountain-range","mountain","ephel duath"}),
    "The mountains named Ephel Duath appear to be dark grey from here.\n"+
    "You judge the mountains to be between 5000 to 7000 feet of height.\n"+
    "Being the border to Mordor, they were given the name Ephel Duath, which\n"+
    "means 'Fence of the Shadow' in the elven tongue.\n");
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
  add_exit(ITH_DIR + "road/er5","east", 0, 2);
  add_exit(ITH_DIR + "road/er3","west", 0, 2);
add_exit(ITH_DIR + "camp/rms/trail1","south",0,1,1);
}

