inherit "/d/Avenir/common/dark/l4/cr.c";

#include "/d/Avenir/common/dark/dark.h"

object ogre;

void
reset_room()
{
  if (objectp(ogre))
    return;
  if (random(2))
    {
      ogre = clone_object (MON + "insane_ogre");
      ogre->equip_me();
      ogre->move_living("leaves", this_object());
    }
}

void
create_room ()
{
  ::create_room();
  add_exit (L4 + "s3", "north" );
  reset_room();
}
