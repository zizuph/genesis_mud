#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <macros.h>

inherit FLOTSAM_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Inside the powerful wind");
   set_long("@@long_descr");

   set_event_time(10.0, 20.0);
   add_event("Flying like an eagle, you are feeling just strange.\n");
   add_event("A few hundreds meter down below, you can see glimpses " +
             "of an ocean.\n");
   add_event("You are impressed by the power of the wind.\n");
   set_events_on(1);

   reset_flotsam_room();

}

string
long_descr()
{
   return "You are carried by the powerful element." +
          "\n";
}
