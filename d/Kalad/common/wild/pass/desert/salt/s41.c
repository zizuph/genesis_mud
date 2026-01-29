inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("On the salt flat");
   set_long("Stretching before you is the desolate expanse known as the "+
      "Great Salt Flat. As its name implies, the ground is totally covered "+
      "with salt crystals. Nothing grows here, and not an animal can be "+
      "seen for hundreds of yards. The unrelenting Kaladian sun beats down "+
      "from above, blindingly reflecting off of the crystals.\n");
   add_item(({"desolate expanse","expanse","great salt flat","great flat","salt flat","flat"}),
      "A burning hot wasteland within the greater wasteland of the Great Kalad "+
      "Waste.\n");
   add_item(({"ground"}),"Littering the ground are hundreds upon "+
      "hundreds of salt crystals, glinting in the harsh light.\n");
   add_item(({"salt crystals","salt crystal","crystals","crystal"}),
      "The formations of salt cover the ground in every direction you "+
      "look. Perhaps centuries ago, this was the site of a lake or other body "+
      "of water. Now however, it is nothing but a wasteland.\n");
   add_item(({"unrelenting kaladian sun","unrelenting sun","kaladian sun","sun"}),
      "As you gaze up at it, you are nearly blinded by its brilliance!\n");
   add_exit(CPASS(desert/salt/s40),"west",0,4);
   add_exit(CPASS(desert/salt/s47),"north",0,4);
   add_exit(CPASS(desert/salt/s42),"east",0,4);
   add_exit(CPASS(desert/salt/s36),"south",0,4);
   set_alarm(3.0,0.0,"mirage");
}
void
init()
{
   ::init();
   clone_object("/d/Kalad/common/wild/pass/obj/mirage5")->move(TP,1);
}
leave_inv(ob, to)
{
   object mirage;
   ::leave_inv(ob);
   mirage = present("mirage5", ob);
   if (mirage) mirage -> remove_object();
}
mirage()
{
   tell_room(TO,"A pool of crystal clear water appears before you.\n");
   tell_room(TO,"As you take a step towards it, it vanishes.\n");
   return 1;
}
