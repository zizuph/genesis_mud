
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("On a ledge");
  set_long("A gaping chasm lies to the east of the narrow, rocky "+
     "ledge you now stand upon. The sheer face of the western wall "+
     "rises out of sight above you. The only thing visible in the "+
     "darkness to the east is a rocky spire emerging from the "+
     "depths below. The ledge continues to the north while the "+
     "tunnel entrance lies immediately southeast.\n");

  add_item(({ "tunnel", "mine" }),
     "A narrow entrance to the mining tunnel can be seen "+
     "to the south.\n");
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
  add_exit("/d/Shire/khazad/west/tunnel2b","southeast",0,1);
  add_exit("/d/Shire/khazad/west/tunnel2d","north",0,1);
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/tunnel2b")
    write("You emerge from the cramped tunnel.\n");
  switch(random(8))
  {
  case 0:
      ob->catch_msg("A warm updraft rolls over your body.\n");
      break;
  case 1:
      ob->catch_msg("A chilly wind gusts from the chasm.\n");
      break;
  case 2:
      ob->catch_msg("A fierce wind from the chasm assaults you. You "+
          "lean against the western wall for support.\n");
      break;
  case 3:
      ob->catch_msg("The wind whistles around in the dark "+
          "chasm below.\n");
      break;
  case 4:
      ob->catch_msg("A sudden downdraft tugs you towards the yawning "+
          "chasm.\n");
      break;
  }
}
