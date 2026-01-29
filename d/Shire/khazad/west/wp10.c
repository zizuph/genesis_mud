
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Bend in the western passage");
  set_long("You stand in a bend in the Western passage. Empty torch "+
     "holders jut out of the cold, stone walls here. To the southwest "+
     "the corridor leads towards the ancient western entrance of "+
     "Khazad-dum. To the east the corridor winds its way deeper "+
     "into the univiting darkness. A rough cut tunnel breaks off "+
     "up a slope north of the main corridor.\n");

  add_item(({ "bend", "corridor", "passageway", "passage" }),
     "The corridor runs southwest and east.\n");
  add_item(({ "holders", "torch holders" }),
     "A slender rod of iron a foot long protruding from the "+
     "wall. You see an opening in the end of the rod where "+
     "a torch would have been placed.\n");
  add_item(({ "walls", "stone walls" }),
     "Carved by dwarven craftsman of ages past these unadorned walls "+
     "are cold, and smooth to the touch.\n");
  add_item("slope",
     "A shallow, rocky incline to the north.\n");
  add_item(({ "floor", "ground" }),
     "Besides being covered by a fine dust the floor looks rather "+
     "barren as far as you can see.\n");
  add_item(({ "dust", "dirt" }),
     "It is very fine and has accumulated here for centuries.\n");
  add_exit("/d/Shire/khazad/west/tunnel2a","north",0,1);
  add_exit("/d/Shire/khazad/west/wp9","southwest",0,1);
  add_exit("/d/Shire/khazad/west/wp11","east",0,1);
}
