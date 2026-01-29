/* ctower/obj/starsaph.c is cloned by ctower/bsaph.c */

inherit "/d/Emerald/ctower/obj/gem_base";
 
#include <stdproperties.h>
 
void
create_gem()
{
  add_name("sapphire");
  set_name("star sapphire");
  set_long("This is a crystal clear star sapphire gem that tingles " +
      "when held.\n");

  add_prop(OBJ_I_VALUE, 1728);
}

void invoke_msgs()
{
  write("The sapphire glows briefly and then dims.\n");
}
