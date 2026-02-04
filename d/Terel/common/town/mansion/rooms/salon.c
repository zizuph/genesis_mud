inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <macros.h>
#include <stdproperties.h>

create_room(){
set_short("Salon");
set_long("Dazzling in its opulence, this grand room is a salon for\n"
  + "formal visits and relaxing. The floor is covered with a fine\n"
  + "thick and plush purple carpet, the walls hung with fine\n"
  + "tapestries of gold and purple. The room is filled with a vast\n"
  + "assortment of chairs and sofas, illuminated by a large golden\n"
  + "chandelier. It all seems untouched.\n"
  + "Large picture windows, framed in gold, look out into the\n"
  + "mansion yard, the view being mostly of trees. A small fireplace\n"
  + "of amber colored stone is built into the east wall. Over it\n"
  + "hangs a beautiful silver mirror.\n"
);

   add_item("mirror", "It is a strange looking mirror, of silver and\n"
    + "framed in wood gilded with silver. The frame is designed to look\n"
   + "like writhing serpents and a woman standing over them.\n");
   add_item("carpet", "It is a fine and elegant plush purple carpet,\n"
     + "it is in excellent condition.\n");
   add_item("tapestries", "They are of fine gold and purple, but rather\n"
    + "plain, being undecorated.\n");
   add_item("chairs", "There are about a dozen of them, most are large\n"
    + "and plush, fitting for relaxation.\n");
   add_item("sofas", "They are fine comfortable sofas, very plush and seem\n"
  + "to be in excellent condition.\n");
  add_item("fireplace", "It is a large opulent fireplace of a strange\n"
   + "amber colored stone.\n");
  add_item("windows", "They look out into the yard of the mansion.\n");
add_exit(MANSION + "wing_w1", "northeast", 0);

}

