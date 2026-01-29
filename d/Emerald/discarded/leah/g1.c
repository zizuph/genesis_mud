inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
    set_short("In a garden");
    set_long("   You step through low-hanging wisteria into an incredibly "+
      "sweet smelling area. A profusion of poppies assails your "+
      "eyes as well as your nose. You pause, take a deep breath "+
      "and smile languidly as the penetrating fragrance of the "+
      "flower wafts through your mind. Bemusedly you notice that the path "+
      "seems to shift even as you tread on it. Suddenly, in the back of"+
      " your mind, you recall a screechy voice cackling, 'Poppies, poppies!"+
      " Poppies will make them sleep...'"+
      " You realize you must get out of this field fast!\n\n");

    add_item(({"path"}),"A small stone walkway.\n");
    add_item(({"flowers", "poppies"}), ("@@they_alive"));

    add_exit(VILLAGE_DIR + "g2", "north", 0);
    add_exit(VILLAGE_DIR + "garden4", "out", 0);
    set_alarm(1.0,0.0,"reset_room");
}

void
reset_room()
{
    object pop;
    if(present("poppies")) return;
    seteuid(getuid(this_object()));
    pop=clone_object(VILLAGE_DIR+"npc/poppies");
    pop->move(this_object());
}

string
they_alive()
{
    if(present("poppies"))
	return "";
    return "The poppies are still and uninteresting.\n";
}
