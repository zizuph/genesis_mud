inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/hforest/"

#define TO this_object()

object mon;

reset_room(){

  if(mon) return 0;
  mon = clone_object("/d/Terel/mecien/mountains/goblin");
  mon->move(TO);

}

create_room(){

set_long("Dark Forest");
set_long(
  "A darkened forest, filled with trees that seem altogether shadowy "
+"and somehow unpleasant, as if they had some spirit of evil dwelling within them. " +
"It is cold here, a wind blowing with bits of ice." +
"\n");

  add_item("trees", "These dark forboding trees haunt this place, like sentinals of some great evil.\n");


   add_exit(PATH + "firep", "south", 0);
   add_exit(PATH + "df4", "northwest", 0);

 add_prop(CONT_I_LIGHT, 0);
reset_room();

}

