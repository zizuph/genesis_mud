
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("short desciption");
  set_long("Long description\n");
  add_exit("/d/Shire/khazad/west/wd9","up",0,5);
  add_exit("/d/Shire/khazad/west/wd12","down",0,5);
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;

  if (file_name(from) == "/d/Shire/khazad/west/wd9")
    write("You make your way down the southern staircase.\n");
 
  else if (file_name(from) == "/d/Shire/khazad/west/wd12")
    write("You ascend the northern staircase.\n");
}
