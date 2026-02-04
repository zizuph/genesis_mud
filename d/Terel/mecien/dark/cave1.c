inherit "/std/room";
#include <stdproperties.h>

object *troll_arr;

reset_room()
{
   if (!troll_arr)
      troll_arr = ({ 0, 0, 0, 0 });
   call_out("delay_reset_room", 1, 0);
}

delay_reset_room(which_troll) {
   if (!troll_arr[which_troll])
      trolls(which_troll);
   if (which_troll < 3) 
      call_out("delay_reset_room", 1, which_troll + 1);
}

trolls(which_troll)
{
   object ob;
   ob = clone_object("/d/Terel/common/moor/troll");
   ob->move_living("xx", this_object());
   
   troll_arr[which_troll] = ob;
}

create_room()
{
   set_short("Dark Cave");
   set_long(
      "This black and dismal cavern smells of rotting flesh and\n"
      +"fecal matter. The cavern walls are coated with a layer of\n"
      +"slime and mold. The floor is covered with loose rocks,\n"
      +"bones and water.\n"
   );
   add_item("bones", "They are many and of various types, "
      +"gnawed clean and broken.\n");
   add_item("slime", "It is deep and foul, an almost luminous green.\n");
   add_item("mold", "A natural consequence of the rot.\n");
   add_exit("/d/Terel/mecien/dark/center", "southwest", 0);
   reset_room();
}
