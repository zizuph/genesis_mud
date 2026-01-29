
inherit "/d/Shire/khazad/moria_room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Western passage");
  set_long("A long corridor slowly climbing to the east.\n");
  add_exit("/d/Shire/khazad/west/wp1","west",0,1);
  add_exit("/d/Shire/khazad/west/wp3","east",0,1);
}
