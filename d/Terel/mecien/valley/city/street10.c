inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/city/"
#define TO this_object()


object mon;

reset_room(){
   if(mon) return;
   mon = clone_object(PATH + "crone");
   mon->move(TO);
}

create_room(){
   
   set_short("Street");
   set_long(
      "This part of the town is full of houses that ring the street. They are "
      + "gloomy and cast shadows over this place.\n"
      +"A large stone stronghold stands to the northwest.\n"
   );
   
   add_item("gate", "It is lowered and there is no other way in. Made from " +
      "iron it is impervious to damage.\n");
   add_item("street", "It is cobblestone, but rather worn here.\n");
   add_item("stronghold", "It is a great stone building, usable in defense. It has an iron gate.\n");
   add_exit(PATH + "street9", "southwest", 0);
   add_exit(PATH + "stronghold", "northwest", "@@closed");
   add_item(({"house", "houses"}), "They are old residences of the inhabitants "
      + "of the city, they look off-limits.\n");
   
   reset_room();
}

closed(){
   write("It is closed.\n");
   return 1;
}

