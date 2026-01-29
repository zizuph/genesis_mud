inherit "/d/Kalad/common/wild/pass/mind/mind_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A dead end");
   set_long("A dead end.\n");
     add_exit(CPASS(mind/m12),"north",0,2)
}
