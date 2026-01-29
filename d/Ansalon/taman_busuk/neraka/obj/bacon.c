inherit "/std/food";
#include <stdproperties.h>

create_food()
{
   set_name("bacon");
   add_name("strips");
   set_short("few strips of bacon");
   set_pshort("few strips of bacon");
   set_long("Fresh from the griddle! These are strips from the "+
   "animal that goes oink!\n");
   set_amount(200);
}
