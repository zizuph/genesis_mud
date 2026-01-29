inherit "/std/workroom";
/* HELP WHAT ARE STANDARD INCLUDES? */
#include <macros.h>
#include <stdproperties.h>

void
create_workroom()
{
   ::create_workroom();
   set_short("This is Milan's workroom");
   set_long("This is Milan's workroom.\n");

   remove_exit("startloc");

   add_prop(ROOM_I_INSIDE, 1);
}
 
