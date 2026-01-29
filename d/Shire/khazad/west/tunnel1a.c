
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Mining tunnel");
  set_long("Small rocks chipped off from the walls litter the "+
     "ground here. This long abandoned mining tunnel continues "+
     "down the steep slope northwards. You can now make out the "+
     "distinct sounds of water dripping from somewhere deeper "+
     "in. A large boulder leans against the eastern wall.\n");

  add_item(({ "rocks", "chips" }),
     "Most are rough with sharp edges.\n");
  add_item(({ "walls", "wall" }),
     "Unfortunately these jagged, uneven walls show no signs "+
     "of anything worth mining.\n");
  add_item(({ "ground", "floor" }),
     "Littered with rocks and very steep the footing on the "+
     "ground is extremely treacherous.\n");
  add_item(({ "tunnel", "cavern" }),
     "Apparently made for minig purposes this tunnel has rough "+
     "walls and a low ceiling.\n");
  add_item(({ "slope", "steep slope"}),
     "Its steep angle makes for treacherous footing.\n");
  add_item(({ "boulder", "rock" }),
     "This large boulder appears to be smooth and well worn. "+
     "It somehow looks out of place here.\n");
  add_exit("/d/Shire/khazad/west/wp4","southwest",0,1);
  add_exit("/d/Shire/khazad/west/tunnel1b","north",0,1);
}

nomask void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/wp4")
    write("You carefully make your way down the steep slope.\n");
  else if (file_name(from) == "/d/Shire/khazad/west/tunnel1b")
    write("You carefully make your way up the steep slope.\n");
}
