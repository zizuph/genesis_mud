
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Bend in the Western passage");
  set_long("You stand in a bend in the Western passage. Empty torch "+
     "holders jut out of the cold, stone walls here. To the northwest "+
     "the corridor leads towards the ancient western entrance of "+
     "Khazad-dum. To the southeast the corridor winds its way deeper "+
     "into the univiting darkness. A strong wind can be felt "+
     "coming from the southern tunnel.\n");

  add_item(({ "tunnel", "southern tunnel" }),
     "A low, wide opening in the southern wall. A whistling sound "+
     "is made by the wind rushing out of it.\n");
   add_item(({ "bend", "corridor", "passageway", "passage" }),
     "The corridor runs northwest and southeast.\n");
  add_item(({ "holders", "torch holders" }),
     "A slender rod of iron a foot long protruding from the "+
     "wall. You see an opening in the end of the rod where "+
     "a torch would have been placed.\n");
  add_item(({ "walls", "stone walls" }),
     "Carved by dwarven craftsman of ages past these unadorned walls "+
     "are cold, and smooth to thec touch.\n");
  add_item(({ "floor", "ground" }),
     "Besides being covered by a fine dust the floor looks rather "+
     "barren as far as you can see.\n");
  add_item(({ "dust", "dirt" }),
     "It is very fine and has accumulated here for centuries.\n");
  add_exit("/d/Shire/khazad/west/wp14","northwest",0,1);
  add_exit("/d/Shire/khazad/west/cp1","southeast",0,1);
  add_exit("/d/Shire/khazad/west/tunnel3a","south",0,1);
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/cp1")
    write("You enter the tunnel.\n");
  else if (file_name(from) == "/d/Shire/khazad/west/tunnel3a")
  {
    write("You are forcefully hurried through the tunnel by the "+
    "powerful wind at your back.\n");
  }
}
