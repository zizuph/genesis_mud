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
   set_short("Inside a magic lamp");
   set_long("@@long_descr");

   add_item(({"walls","wall","shining walls"}),
      "The walls are made of some kind of shining metal. They are " +
      "smooth and slippery.\n");
   add_item(({"entrance","enter","exit","neck","bottleneck","way","way out"}),
      "You see a narrow tunnel leading up and outside. Unfortunately " +
      "you have no chance to reach it.\n");

   INSIDE;

   set_event_time(20.0, 50.0);
   add_event("You feel the world turns upside down as the lamp " +
             "is beeing moved.\n");
   add_event("You feel a slight trembling. The lamp must be moved " +
             "somewhere.\n");
   add_event("The pressure inside this lamp is awful. How could anyone " +
             "stand it more than ten minutes ?\n");
   set_events_on(1);

   reset_flotsam_room();

}

string
long_descr()
{
   return "You are squeezed in a small, round place. You can't believe it, " +
          "but it realy looks like inside of the magic lamp. " +
          "You can hardly move your limbs and " +
          "have a terrible feeling that there is no way out." +
          "\n";
}
