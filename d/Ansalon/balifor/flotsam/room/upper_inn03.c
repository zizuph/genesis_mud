#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_IN;

object officer;


void
reset_flotsam_room()
{
   if (!objectp(officer))
      {
      officer = clone_object(FNPC + "d_officer");
      officer->arm_me();
      officer->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Highlords room");
   set_long("@@long_descr");
   
   add_item("bed","A large bed that has been " +
      "recently used. \n");
   
   add_exit(FROOM + "upper_inn02","east","@@out",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in the bedroom of the Blue Dragon " +
   "Highlord, the leader of the armies that have occupied " +
   "Flotsam. At present rumours say she is in the west fighting " +
   "the Solamnians, so she obviously would not be here. Still, " +
   "the room looks like it is being used, probably by an officer " +
   "of hers that she favours. There is a large bed at the side of " +
   "room, and the doorway is to the east. \n";
}

int
out()
{
   write("You step out of the Highlords room...\n");
}
