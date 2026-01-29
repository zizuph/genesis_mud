inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{

  set_rock_type("dark granite");
  set_cave_name("the Lonely Mountain");
  set_region("western");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("This is the main junction on this level. "
        + "On a wooden pole is a hangs a sign .\n");
 
  add_exit(CAVE_DIR + "lm2c14","north",0,1);
  add_exit(CAVE_DIR + "lm2c41","south",0,1);
  add_exit(CAVE_DIR + "lm2c28","east",0,1);
  add_exit(CAVE_DIR + "lm2c26","west",0,1);
  add_exit(CAVE_DIR + "lm2c42","southeast",0,1);
 
  add_item("sign","\n\n\n"
        + "|      Schoolhouse     |\n"
        + "|           |          |\n"
        + "|           |          |\n"
        + "| Mines  <-- -->Castle |\n"
        + "|           |          |\n"
        + "|           |          |\n"
        + "|         Shops        |\n"
        + "\n");
}
