
inherit "/d/Shire/khazad/moria_room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Western passage");
  set_long("A long corridor slowly climbing to the east.\n");
  add_exit("/d/Shire/khazad/west/wp2","west",0,1);
  add_exit("/d/Shire/khazad/west/wp4","east",0,1);
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  switch (random(8))
  {
  case 0:
      tell_room(TO, "Your legs begin to ache from the "+
          "laborious trek thru the darkness.\n");
      break;
  case 1:
      tell_room(TO, "The echo of your footsteps breaks "+
          "the lingering silence that has descended on Khazad-dum.\n");
      break;
  case 2:
      tell_room(TO, "The corridor bends slightly to the left.\n");
      break;
  case 3:
      tell_room(TO, "The corridor bends slightly to the right.\n");
      break;
  }
}
