inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "camp.h"

create_room()
{
  create_camproom();
  set_short("Within the camp");
   set_long("The main of the camp is to your south and west, while "+
   "the tents seem to thin out to the north and east. Still "+
   "the number of tents here is quite high, but only one has its "+
   "flap open. This is evidently a section of warrior tents, as "+
   "it is kept reasonably clean, but you don't expect the warriors "+
   "to do that themselves.\n");

  add_exit(GREEN_DIR + "camp/camp13","west",0);
  add_exit(GREEN_DIR + "camp/camp10","southwest",0);
  add_exit(GREEN_DIR + "camp/camp11","southeast",0);
  set_tent_name("tent14");
}
