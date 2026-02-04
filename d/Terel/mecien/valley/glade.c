inherit "/std/room";
#include <stdproperties.h>
#include "defs.h";


object *dark_arr;

reset_room()
{
   object mon;
   if (!dark_arr)
      dark_arr = ({ 0, 0, 0, 0, 0, 0 });
   call_out("delay_reset_room", 1, 0);
   if(present("sylph")) return;
    mon=clone_object(PATH + "sylph");
   mon->move(this_object());
}

delay_reset_room(which_dark) {
   if (!dark_arr[which_dark])
      darks(which_dark);
   if (which_dark < 5) 
      call_out("delay_reset_room", 1, which_dark + 1);
}

darks(which_dark)
{
   object ob;
    ob = clone_object("/d/Terel/enchanted/monster/sprite");
   ob->move_living("xx", this_object());
   
   dark_arr[which_dark] = ob;
}

create_room()
{
   set_short("Glade");
   set_long(
   "Wondrous and exalted this small glade radiates like a place\n"
 + "of miraculous joy, unearthly and untouched. The trees shimmer\n"
  + "in their vibrant glow, almost animated.\n"
   );
   add_exit(PATH + "forest10", "north", 0);
   reset_room();
}
