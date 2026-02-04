/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){
   
   set_short("Hallway");
   set_long("A solemn peace lingers in the air of this arched\n"
      +"stone hall, a feeling of strength. The old stone of this\n"
      +"place being worn and smooth, traversed by many. High above,\n"
      +"stain-glass skylights cascade prisms of colored light down\n"
      +"into the beleaguered hall.\n"
   );
   
   add_exit(PATH + "s_hall1", "north", 0);
   add_exit(PATH + "refectory", "south", 0);
   add_exit(PATH + "dormitory", "east", 0);
   add_exit(PATH + "emporium", "west", 0);
   
   add_item(({"stain-glass", "skylights"}),
      "They are four large stain-glass skylights, the depict four\n"
      +"strange creatures. One is a goat-fish, the second a fiery\n"
      +"eagle, the third a one-eyed giant and the fourth is a silvery\n"
      +"winged serpent.\n");
   
   
}
