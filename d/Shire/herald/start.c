#pragma save_binary

inherit "/d/Shire/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/herald/herald.h"
#include "/d/Shire/bits.h"



void
create_room()
{
  set_short("Top of the tree");
  set_long("This is the top of the giant maple tree, at least "+
                "as high as it is safe to climb.  The branches here "+
                "are still quite thick however.  Several branches have "+
                "padding laid on them, making quite nice little beds, "+
                "complete with the canopy of the thick branches and "+
                "maple leaves overhead.  A sign has been placed on "+
                "the trunk.  You may also follow the trunk back down.\n");

   add_item(({"tree","giant maple tree","maple tree","trunk"}),
   "This giant maple tree is taller than you imagined.  It seems "+
   "about eighty feet from the ground at this point, and still the "+
   "branches tower above.\n");

   add_item(({"branches","thick branches","leaves","maple leaves"}),
    "The combination of thick branches and many maple leaves "+
    "leaves little to be seen above.  It is dim here, even in the day "+
    "and the moon has little more success at night.\n");

   add_item(({"canopy","beds","bed","padding"}),
   "The canopy of the thick conglomeration of leaves and branch will "+
   "keep out all but the most fierce rain and wind.  The comfortable "+
   "soft padding will keep you from being sore when you next awake.\n");

    room_add_object("/d/Shire/herald/rack_h.c");
    room_add_object("/d/Shire/herald/rack_ar.c");
    room_add_object("/d/Shire/herald/rack_c.c");
    room_add_object("/d/Shire/herald/rack_a.c");
    room_add_object("/d/Shire/herald/rack_w.c");

  add_cmd_item("sign","read",
               "You may start here when entering the game:\n"
             + "to do so, you must 'start here'.\n");

  add_exit(HERALD_DIR + "post","down");


}


init()
{
  ::init();

    add_action("start","start");
}


int
start(string str)
{
   if(str == "here" && (IS_MEMBER(this_player())))
     {
       TP->set_default_start_location("/d/Shire/herald/start");
       write("You will awaken here when next you sleep.\n");
       return 1;

     }

  write("You are not a Herald of the Valar, how did you get in here?\n");
  return 1;
}
