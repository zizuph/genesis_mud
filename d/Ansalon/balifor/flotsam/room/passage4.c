#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("A dark passageway under a deserted manor in Flotsam");
   set_long("@@long_descr");
   
   add_item(({"wall","walls","stone walls","cold stone walls"}),
      "The walls " +
      "are made of big blocks of grey stone. Or are they? You " +
      "notice something strange about the eastern wall.\n");
   add_item("passageway","The passages lead north and south " +
      "into shadows. You notice the eastern wall shimmers " +
      "slightly as your gaze passes over it.\n");
   add_item(({"east wall","eastern wall"}),"After careful " +
      "inspection, you notice this wall is nothing but an " +
      "illusion! You could probably walk right through it.\n");
   
   add_exit(FROOM + "passage8","north",0);
   add_exit(FROOM + "passage2","south",0);
   add_invis_exit(FROOM + "temple/t1","east","@@enter_wall");
   
   DARK;
   
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in a dark passageway in the cellar of a " +
   "deserted house in the town of Flotsam. It is uncomfortably " +
   "silent down here. Not even vermin make their home in this " +
   "evil place. " +
   "The cold stone walls of the passageway continue to the " +
   "north and south. " +
   "\n";
}

int
enter_wall()
{
   write("You pass through an illusionary wall!\n");
   return 0;
}
