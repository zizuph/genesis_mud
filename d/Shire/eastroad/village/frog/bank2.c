inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/elessar/lib/time.c"
#include "/d/Shire/common/defs.h"

object deposit;

create_room()
{
   set_short("The branch of the money-deposit service in Frogmorton");
   set_long("You are in a side-room of the Frogmorton Bank. This is the\n"+
      "branch of the Gnomes of Genesis money-deposit in Frogmorton,\n"+
      "opened quite recently as a service to the travellers of Genesis\n"+
      "who have found their way to the Shire in Middle-Earth. The service is\n"+
      "quite special, as gnomes are not that common in Middle-Earth, but\n"+
      "this might be the first step towards a better relationship.\n"+
      "The main bank is back west.\n");
   add_exit ("/d/Shire/eastroad/village/frog/bank.c","east",0,1);
   add_prop(ROOM_I_INSIDE,1);
   add_dep_box();
}

add_dep_box()
{
   if (deposit) return;
   deposit = clone_object("/d/Genesis/obj/deposit");
   deposit->move(this_object());
}

reset_room()
{
   if (!deposit) add_dep_box();
}
