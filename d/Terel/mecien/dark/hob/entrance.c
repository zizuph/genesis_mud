inherit "/std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/dark/"

object *dark_arr, door;

reset_room()
{
   object mon;
   door->reset_object();
   if (!dark_arr)
      dark_arr = ({ 0, 0, 0, 0, 0, 0 });
   call_out("delay_reset_room", 1, 0);
   if(present("lizard")) return;
   mon=clone_object(PATH + "mon/lizard");
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
   ob = clone_object("/d/Terel/mecien/dark/mon/hobgoblin");
   ob->move_living("xx", this_object());
   
   dark_arr[which_dark] = ob;
}

create_room()
{
   set_short("Lair Entrance");
   set_long(
      "This blackened cavern echoes sounds of grief coming from\n"
      +"the deeper parts of the world. The cavern area has been\n"
      +"crudely carved from the stone. A corridor leads up.\n"
   );
   door=clone_object(PATH + "hob/door1");
   door->move(this_object());
   door->set_key(6056);
   add_exit(PATH + "s3c", "up", 0);
   reset_room();
}
