
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("short description");
  set_long("Long description\n");
  add_exit("/d/Shire/khazad/west/wd11","west",-5,1);
  add_exit("/d/Shire/khazad/west/wd15","east",0,1);
}
