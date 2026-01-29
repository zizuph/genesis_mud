inherit "/d/Rhovanion/lib/caves.c";

#include "def.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h";

create_cave()
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(2);
  set_long(" It looks like the King make parties in these halls, they "
	   + "are continuing to the west. "
	   + " \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave23","west",0,1);
  
  reset_room();
}

void
reset_room()
{
    if (!present("restscroll", TO))
    clone_object("/d/Gondor/common/guild/spells/obj/rest_scroll")->move(this_object());
    
}