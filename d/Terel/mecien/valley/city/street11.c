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
 "A foggy cobblestone street. Dark and shadowy, it winds through the town. " +
"A plain stone building with barred windows stands to the north, a bright " +
"white sign hanging over it. There is a small building on the south side "
+ "of the street, a large blackstone building to the east.\n"
);

add_item(({"white sign", "sign"}), "It is painted with letters.\n");
add_cmd_item("sign", "read", "Great Smith!\n");
add_item("plain building", "It is stone and barred.\n");
add_item("bars", "They cover the windows.\n");
add_item("windows", "They are barred.\n");
add_item("small building", "It is small and dark.\n");
   reset_room();
add_item(({"large building", "east building", "blackstone building"}), "It is a very large, secure looking building on the east side of the street.\n");
add_exit(PATH + "smithy", "north", 0);
add_exit(PATH + "square", "west", 0);
add_exit(PATH + "qshop", "south", 0);
add_exit(PATH + "g_house", "east", 0);
add_exit(PATH + "street12", "northeast", 0);
}
