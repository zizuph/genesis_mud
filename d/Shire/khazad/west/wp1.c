
inherit "/d/Shire/khazad/moria_room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Western passage");
  set_long("A long corridor slowly climbing to the east.\n");
  
  add_exit("/d/Shire/khazad/west/stairs_top","west",0,1);
  add_exit("/d/Shire/khazad/west/wp2","east",-5,0);
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  switch (random(6))
  {
  case 0:
      tell_room(TO, "A slight breeze stirs the stale air.\n");
      break;
  case 1:
      tell_room(TO, "You see a multitude of dark openings "+
     "and passageways off to either side of the main corridor. You "+
     "wisely decide not to explore them.\n");
      break;
  case 2:
      tell_room(TO, "The corridor widens slightly.\n");
      break;
  }
}
