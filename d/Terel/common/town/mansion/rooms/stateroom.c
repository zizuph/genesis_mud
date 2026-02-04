inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

create_room(){
set_short("Stateroom");
set_long(
"This hall of fiery gold, is the magnificent stateroom of the great\n"
+ "mansion, used for entertaining dignified guests. Though the\n"
+ "hall has fallen into a state of disrepair, it still retains\n"
+ "a good measure of its grandeur. Its plush gold carpeting is\n"
+ "coated in dust and dirt, the gold painted ceiling is chipped\n"
+ "and pieces of plaster missing. Once proud tapestries are now\n"
+ "dingy tattered rags, even somewhat burned. A long row of windows\n"
+ "look out into the mansion yard, though coated with dust. Most\n"
+ "of the furniture is rotted, though the long banquet table and\n"
+ "sofa remain in good shape.\n"
);

add_item("tapestries", "They are but rags now, they look as though there\n"
   + "could have been a fire in here.\n");
add_item("carpeting", "It is gold and plush, though coated with dust and dirt.\n");
  add_item("windows", "They look out into the mansion yard, it may be\n"
   + "the courtyard.\n");
add_item("furniture", "It is rotted and decayed.\n");
add_item("sofa", "It is a golden sofa and still in decent condition.\n");
add_item("table", "It is a banquet table, made of a slightly golden wood\n"
  + "and well carved with scroll-work.\n");

add_exit(MANSION + "wing_w5", "west", 0);


}
