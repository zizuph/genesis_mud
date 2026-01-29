
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("short description");
  set_long("Long description\n");
  add_exit("/d/Shire/khazad/west/wd10","up",0,5);
  add_exit("/d/Shire/khazad/west/wd14","southwest",0,1);
}
 
void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;

  if (file_name(from) == "/d/Shire/khazad/west/wd10")
    write("Heading south you continue your descent.\n");
}
