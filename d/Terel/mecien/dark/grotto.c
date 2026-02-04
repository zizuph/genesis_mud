inherit "/std/room";
#include <macros.h>

#define PATH "/d/Terel/mecien/dark/"

create_room(){
   
   set_short("Grotto");
   set_long("This small grotto formed of natural crystals stands\n" +
      "as a nemesis to the rest of the caverns. A light seems to shine\n"
      + "forth from the crystals. Streams of water trickle down the\n" +
      "walls of the cavern.\n"
   );
   
   add_cmd_item("crystal", "break", "They are too strong to break.\n");
   add_cmd_item("crystal", "chip", "@@chip");
   add_item("crystal", "It is beautiful rock crystal, it forms many\n"
      + "strange shapes and shines a variety of hues.\n");
   add_exit(PATH + "s3a", "north", 0);
   
}

chip(){
   object ob, crys;
    ob=present("chisel", this_player());
   if(!ob){
    write("You have no tool!\n");
      return 1;
   }
   write("You chip at the crystal formation, trying to gain a crystal.\n");
   say(QCTNAME(this_player()) + " tries to chip the crystal formations.\n");
   if(random(100) > 80){
     seteuid(getuid(this_object()));
      crys=clone_object("/d/Terel/mecien/valley/guild/quest/crystal");
      crys->move(this_object());
      write("A piece of crystal breaks loose and falls to the ground.\n");
   }
   return 1;
}
