inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

create_room(){
   
   set_short("Ice Wall");
   set_long(
      "Snow and ice stand packed against the stony mountain side," +
      " part revealed, showing a silver-veined rock. Upon the rock is" +
      " carved a circular pattern with writing in its midst." +
      " The wind howls howls here, wild from the north, shaking bits of snow" +
      "and ice down from above.\n"
   );
   
   add_item(({"circle", "circular pattern", "pattern"}),
      "A pattern of circles etched upon the cliff facing, one within the"
      + " other. In the midst thereof are letters.\n");
add_item(({"writing", "letters"}), "They are very strange and unknown.\n");
add_cmd_item("writing", "read", "DOL ASYU KOSS UDAS\n");

add_item("rock", "It shows through from the snow and ice.\n");

add_exit("/d/Terel/mecien/mountains/ice8", "east", 0);

}

