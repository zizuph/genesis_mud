inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere3/"

void
create_cave()
{

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("central");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("There is not much to see here but some "
         + "paintings hanging on each side of the corridor. Ofcourse "
         + "there is also a big sign here.\n");
 
  add_item("sign","The sign read:\n\n            "
         + "   DO NOT TOUCH!\n\n"
         + "and this obviously means the paintings.\n");
 
  add_item(({"painting","paintings"}),"The paintings "
         + "are old dwarven paintings. They are probably from the "
         + "times when dwarves and elves lived "
         + "in greater friendship than today, as you can spot some "
         + "elves on the paintings too. Its not clear "
         + "where they are painted, or by who.\n");
 
  add_exit(CAVE_DIR + "lm3c11","south",0,1);
  add_exit(CAVE_DIR + "lm3c1","north",0,1);
}
