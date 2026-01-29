inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by .... */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0); /* change 0 to 1 for light or -? for even darker */
   set_short("the short room descriprion");
   set_long("The long description.\n");

   add_item(({"littered","refuse","rubble"}),
      "It is all over this once proud road.\n"); /* items the player sees in the long desc. */

   add_exit(CPASS(dwarf/s29),"east"); /* exits from the room */

   set_noshow_obvious(1); /* add this if you don't want the player to see the exits. */
/* if you use this, be sure to describe the exits in the set_long() */
}

