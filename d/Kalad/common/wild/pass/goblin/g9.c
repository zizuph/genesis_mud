/**
 * We want people to be able to do these things before they all
 * close... so let's make the loot reboot!
*/
inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define DMG 50
#define LOOT "/d/Kalad/common/wild/pass/obj/loot"

string long;
object loot;

/* by Antharanos */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Inside the cave");
   set_long("You are inside a musty-smelling cave whose floor is "+
      "littered with all manner of refuse. The smell is so bad here that "+
      "it nearly makes you wretch. Along the walls are many crudely painted "+
      "images. The cave seems to continue to the east, while in the "+
      "southeast lies a mass of thorny shrubs.\n");
   add_item(({"floor","refuse"}),"Discarded and chewed bones, fecal "+
      "waste, along with bits and scraps of cloth are strewn across the "+
      "cave floor.\n");
   add_item(({"walls","wall"}),"The otherwise unremarkable cave interior "+
      "is covered in crude paintings.\n");
   add_item(({"crude paintings","paintings","painting","painted images","images","image"}),
      "A myriad variety of images, all of the same thing cover the walls. "+
      "The image is that of a bloody hand clutching an eyeball.\n");
   add_item(({"thorny scrubs","scrubs","scrub"}),"A barrier of thorn-filled "+
      "plants that seems to block the way out of this cave.\n");
   add_exit(CPASS(goblin/g10),"east",0,1,2);
   add_exit(CPASS(goblin/g8),"southeast","@@check_gob");
   reset_room();
}
check_gob()
{
   if(TP->query_race_name() != "goblin")
      {
      write("You try to go southeast, but simply can't squeeze yourself through the thorny shrubs.\n");
      write("You get scratched badly!\n");
      TP->heal_hp(-DMG);
      say(QCTNAME(TP) + " tries to go southeast but gets nothing but scratches for " + TP->query_possessive() + " effort.\n");
      if(TP->query_hp() <= 0)
         TP->do_die(TO);
      return 1;
   }
   write("You manage to squeeze through the shrubs without harm!\n");
   return 0;
}

public void
reset_room()
{
    if(!loot || !present(loot, this_object()))
    {
        loot = clone_object(LOOT);
        loot->move(TO, 1);
    }
}
