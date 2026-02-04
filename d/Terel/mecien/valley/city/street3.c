inherit "/std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/city/"

object *elf_arr;

reset_room()
{
   while(sizeof(elf_arr) < 4)
   elves();
}

elves()
{
   object ob;
  ob = clone_object("/d/Terel/mecien/valley/city/tp");
   /*
   ob->move(this_object());
   */
   ob->move_living("xx", this_object());
   
   if (!elf_arr)
      elf_arr = ({ ob });
   else
      elf_arr += ({ ob });
}

create_room()
{
   set_short("Street");
   set_long(
"The fog creaps along the cobblestone street, haunting the city edge\n"
+"with its dismal apparitions. A shadowy building rises to the west,\n"
+"its black roof hanging well over the street. A large sign hangs\n"
+"from the edge of the roof. The street runs south and to the north\n"
+"the city square opens out.\n"
);

add_item("sign", "It is a large wooden sign, a large raven is carved upon\n"
+"it and some lettering.\n");
add_cmd_item("sign", "read", "The Ravens Roost\n");
add_item(({"cobblestone", "street"}), "Small black and red stones fit neatly together.\n");
  add_exit(PATH + "tavern", "west", 0);
   add_exit(PATH + "street2", "south", 0);
  add_exit(PATH + "square", "north", 0);
   reset_room();
}
