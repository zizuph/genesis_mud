

inherit "/std/room";
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include <macros.h>

int NUM;

reset_room(arg){
   NUM = 5;
}

create_room(){
   set_short("Shrine");
    set_long(
"Ancient and in virtual ruin, this small stone structure seems\n"
+"to be some small shrine. The stone is partially fallen in, snow\n"
+"and ice coat everything. The shrine itself hangs over the edge of\n"
+"the mountain, as if to drop off into nothingness. The clouds hang\n"
+"down into this place, creating a mysterious and solemn awe. A huge\n"
+"block of ice rests in the center of the shrine, it is broken and\n"
+"crumbling into pieces.\n"
);

add_item("clouds", "They enter this place almost as guardians.\n");
add_item("snow", "It coats almost everything.\n");
add_item("stone", "It seems very old and ruinous.\n");
add_item("ice", "It coats everything here like a sheet.\n");
add_item(({"block", "ice block", "huge block"}),
 "It is a large block of cloudy ice, it seems as though it has\n"
+"been struck by lightening a few times. A strange feeling emanates\n"
+"from it. Pieces of it are loose and it might be possible to take\n"
+"a piece of the ice.\n");
add_item("down", "All you can see is clouds below the shrine.\n");
add_cmd_item("ice", "take", "@@take");
add_exit("/d/Terel/mountains/mtop", "south", 0);
   reset_room();
}

take(){
/*
   object ob;
   NUM --;
   if(NUM < 1){
*/
  write("There are no more loose pieces.\n");
  return 1;

/*
   seteuid(getuid(this_object()));
   ob=clone_object("/d/Terel/mecien/valley/guild/quest/ice");
   ob->move(this_player());
   write("You remove a loose piece of ice from the giant block.\n");
   say(QCTNAME(this_player()) + " takes a piece of ice from the block.\n");
   return 1;
*/
}
