inherit "/std/room";
#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"

#define PATH "/d/Terel/mecien/dark/"

object *dark_arr;

reset_room()
{
   object mon;
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
   ob = clone_object("/d/Terel/mecien/dark/mon/dark_elf");
   ob->move_living("xx", this_object());
   
   dark_arr[which_dark] = ob;
}

create_room()
{
   set_short("Center");
   set_long(
      "A hall of stone, carved magnificently from the living rock\n"
      +"of this place. Four collumns support the hall, made into the\n"
      +"images of serpents. The ceiling forms a vault, which has been\n"
      +"engraved with a demonic face. In the center of the hall is a\n"
      +"fire pit that heats and lights the area, but with only a faint\n"
      +"flickering glow.\n"
   );
   add_item(({"fire pit", "fire", "pit"}), 
      "It is lit with coal. It is very hot, but provides little light.\n");
   add_item(({"face", "demonic face", "ceiling"}), 
      "Engraved upon the ceiling is a horrible visage, a nightmare\n"
      +"made in stone. It must be an entity worshipped by the beings\n"
      +"that carved this hall. The face looks like that of an animal,\n"
      +"perhaps a goat. Its mouth gapes open, displaying hook like\n"
      +"teeth. Its eyes only slits. Its head crowned by many strange\n"
      +"and differing horns, some twisted, others spiral or straight.\n"
      +"From the face are six small talon-like claws, that circle it.\n"
      +"Out from the talons reach four bat-like wings. Light from\n"
      +"the fire below it seems almost to bring it to life.\n");
   add_exit(PATH + "s5", "south", 0);
   add_exit(PATH + "n1", "north", 0);
   add_exit(PATH + "e1", "east", 0);
   add_exit(PATH + "w1", "west", 0);
   add_exit(PATH + "cave1", "northeast", 0);
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);
   reset_room();
}
