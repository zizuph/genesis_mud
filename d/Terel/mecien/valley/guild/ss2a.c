/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){
   
   object door;
   
   set_short("Secret Stair");
   set_long(
      "All about a mist coils upwards, rising from some abyssmal darkness toward " +
      "a dim light above, dancing upon the eerie steps of this forgotten staircase. The stone is a faint shade " +
      "of aquamarine. The stairs spiral around the outer walls of this cylindrical pit, standing open to the nothingness that is below.\n"
   );
   
   
   add_item("stairs", "They spiral up and down, made from a stone of\n"
      +"deep aquamarine.\n");
   add_item("mist", "It is like some mysterious viel that shrouds this place.\n");
   
   add_exit(PATH + "ss3", "down", 0);
   add_exit(PATH + "ss2", "up", -10);
   
}

init(){
   add_action("say", "say");
   ::init();
}

say(string str){
   object angel, key;
   if(!str) return 0;
   if(str == "let Truth be known"){
        seteuid(getuid());
      key=clone_object(PATH + "lkey");
      key->move(this_player());
      write("A mysterious key appears in your hand.\n");
      return 1;
   }
}

