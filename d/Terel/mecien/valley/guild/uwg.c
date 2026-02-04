/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define PATH  "/d/Terel/mecien/valley/guild/"
#define TP  this_player()

reset_room(arg){
   object ob;
   if(!present("capricorn")){
      ob=clone_object(PATH + "quest/keeper");
      ob->move(this_object());
   }
}

create_room(){
   set_short("Grotto");
   set_long(
      "Arcane and mysterious, this sunken grotto glimmers like the\n"
      + "moon and sparkles like the stars. A pocket of air fills the\n"
      + "upper half of the cavern, which is coated with small shellfish\n"
      + "and small stalactites. The water here is warm and peaceful.\n"
   );
   add_item("air", "It fills the upper half of the grotto, allowing\n"
      + "stalactites to form.\n");
   add_item("stalactites", "Small conical deposits that have formed on\n"
      + "the ceiling of the grotto.\n");
   add_item("shellfish", "They are very small, perhaps clams. They are\n"
      + "secured to the ceiling.\n");
   add_exit("/d/Terel/mecien/valley/guild/water3", "out", "@@out");
   reset_room();
}

out(){
write("You leave the grotto and swim back up to the surface.\n");
}
