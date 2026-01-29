
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("On a ledge");
  set_long("The narrow ledge slopes steeply down into the chasm here. "+
     "The towering western wall runs further north with the "+
     "chasm by its sides. A tunnel entrance can be seen to "+
     "the west. The ledge continues on to the south.\n");

  add_item(({ "chasm", "darkness" }),
     "It fills the eastern half of this cavern. You can see "+
     "a single spire of stone rising from its depths.\n");
  add_item(({ "face", "wall", "western wall" }),
     "Its grey surface looks relatively smooth and even.\n");
  add_item(({ "depths", "darkness" }),
     "Looking down into the chasm gives you a momentary sense "+
     "of vertigo.\n");
  add_item(({ "spire", "rocky spire", "stone spire" }),
     "A slender column of stone standing silently in the "+
     "darkness.\n");
  add_item(({ "ledge", "path", "slope" }),
     "It's only broad enough for one person to pass at a time.\n");
  add_exit("/d/Shire/khazad/west/tunnel2c","south",0,1);
  add_exit("/d/Shire/khazad/west/random_tunnel3","west",0,1);
}
