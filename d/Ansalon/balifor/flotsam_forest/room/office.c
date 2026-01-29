#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;
object knight;

void
reset_flotsam_room()
{
   if(!objectp(knight))
      {
      knight = clone_object(FNPC + "darryn");
      knight->arm_me();
      knight->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Office");
   set_long("@@long_descr");
   
   add_item(({"office","room"}),"@@long_descr");
   add_item(({"desk","mahogany desk","papers","reports"}),
      "An old mahogany desk sits in the middle of the room, covered " +
      "with reports and papers. It is used by the leader of this " +
      "Circle of Knights.\n");
   add_item(({"tapestry","back wall"}),"On the back wall is a " +
      "magnificent tapestry. It depicts two of the symbols of the " +
      "Knighthood, a rose curled around an elegant sword.\n");
   
   add_exit(FROOM + "hall","east",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in an office, used by the leader of the Knights " +
   "Circle based outside of Flotsam. A mahogany desk sits in the centre " +
   "of the room, with a tapestry of a sword surrounded by roses hangs " +
   "on the back wall.\n";
}
