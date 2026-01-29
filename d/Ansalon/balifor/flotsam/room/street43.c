#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Street in the upper parts of the town of Flotsam");
   set_long("@@long_descr");
   
   add_item("street","This street runs east and west. To the " +
      "south you can see a Post Office. \n");
   add_item("rise","To the west the street starts to rise up a " +
      "gentle slope.\n");
   add_item(({"eastern town","town","lower slums","slums"}),
      "To your east you look over the wretched town of Flotsam. There is " +
      "nothing spectacular about it, in fact you find it quite pathetic. " +
      "Populated by the dregs of the continent, the town is " +
      "pretty much nothing more than an expansive slum sprawling " +
      "away from the sea. \n");
   add_item(({"office","post office"}),"To your south is " +
      "the entrance to the local post office of Flotsam.\n");
   
   add_exit(FROOM + "street41","east",0);
   add_exit(FROOM + "p_office","south",0);
   add_exit(FROOM + "street44","west","@@rise",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "The street you " +
   "stand on is much cleaner than the streets of lower " +
   "Flotsam, but not friendlier. Being on a rise, the " +
   "street overlooks much of the eastern town. To the west the " +
   "street continues up the rise, while to the east the street " +
   "returns to the lower slums of Flotsam. To the south there " +
   "is a post office. " + season_descr() + "\n";
}

int
rise()
{
   write("You head up the sloping street...\n");
   return 0;
}
