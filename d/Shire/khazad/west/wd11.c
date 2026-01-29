
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("short desciption");
  set_long("Long description\n");
  add_exit("/d/Shire/khazad/west/wd9","west",0,1);
  add_exit("/d/Shire/khazad/west/wd13","east",-5,1);
}
