inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(5);
  set_long("This must be the house of the schoolteacher. "
        + "You can easily detect that from all kinds of books, "
        + "rulers and all kind of stuff he uses for his classes.\n");
  add_item("books","The books are thrown into a huge heap " +
          "without any order. It seems to be mainly historybooks " +
          "from the First Age.\n");
  add_item("rulers","Standard dwarven rulers, made of wood.\n");

  add_exit(CAVE_DIR + "lm2c9","east",0,1);
}
