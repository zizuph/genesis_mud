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
   set_short("Cobbled street outside a store in the town of Flotsam");
   set_long("@@long_descr");
   
   add_item(({"street","cobblestone street"}),"A filthy, " +
      "well used, cobblestone street. \n");
   add_item(({"store","general store"}),"One of the few " +
      "stores open in Flotsam. \n");
   add_item(({"clouds","cloud"}),"Gloomy grey clouds hover " +
      "permanantly over the town of Flotsam it seems. \n");
   
   add_exit(FROOM + "street31","east",0);
   add_exit(FROOM + "store","south","@@ent_store",0);
   add_exit(FROOM + "street42","west",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + tod_descr2() + "You stand on a " +
   "cobblestone street in the south-eastern part of Flotsam. " +
   "To your south, an enterprising merchant has set up a general " +
   "store, where items can be bought and sold. The street continues " +
   "east and west. " + season_descr() + "\n";
}

int
ent_store()
{
   write("You enter the store... \n");
   return 0;
}
